#include <Game.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

#include "Game.h"
#include "Time.h"

#include "Scripts/RobotScript.h"
#include "Scripts/GameplayScript.h"
#include "Scripts/Grid.h"
#include "Scripts/GridSquare.h"
#include "Scripts/Pathfinder.h"
#include "Scripts/EnemySpawner.h"
#include "Scripts/EnemyScript.h"
#include "Scripts/RobotScript.h"

#include "Objects/SpawnPoint.h"
#include "Objects/HomeBase.h"
#include "Objects/Cube.h"
#include "Objects/Robot.h"
#include "Objects/Mountain.h"




CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);

//-------------------------------------------------------------------------------------
Game::Game(void)
    : mRoot(0),
    mCamera(0),
    mSceneManager(0),
    mWindow(0),
    mResourcesConfig(Ogre::StringUtil::BLANK),
    mPluginsConfig(Ogre::StringUtil::BLANK),
    mTrayManager(0),
    mCameraMan(0),
    mStatsPanel(0),
    mGameOverPanel(0),
    mCursorWasVisible(false),
    mShutDown(false),
    mInputManager(0),
    mMouse(0),
    mKeyboard(0)
{
}

//-------------------------------------------------------------------------------------
Game::~Game(void)
{
    if (mTrayManager) delete mTrayManager;

    //Remove ourself as a Window listener
    Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
    windowClosed(mWindow);
    delete mRoot;
}

//-------------------------------------------------------------------------------------
bool Game::configure(void)
{
    // Show the configuration dialog and initialise the system
    // You can skip this and use root.restoreConfig() to load configuration
    // settings if you were sure there are valid ones saved in ogre.cfg
    if(mRoot->showConfigDialog())
    {
        // If returned true, user clicked OK so initialise
        // Here we choose to let the system create a default rendering window by passing 'true'
        mWindow = mRoot->initialise(true, "TutorialApplication Render Window");

        return true;
    }
    else
    {
        return false;
    }
}
//-------------------------------------------------------------------------------------
void Game::chooseSceneManager(void)
{
    // Get the SceneManager, in this case a generic one
    mSceneManager = mRoot->createSceneManager(Ogre::ST_GENERIC);
}
//-------------------------------------------------------------------------------------
void Game::createCamera()
{
    // Create the camera
    worldCamera = mSceneManager->createCamera("WorldCam");
    playerCamera = mSceneManager->createCamera("PlayerCam");

    mCamera = &playerCamera;

    // Position it at 500 in Z direction
    worldCamera->setPosition(Ogre::Vector3(-1500,6000,-1500));
    // Look back along -Z
    worldCamera->lookAt(Ogre::Vector3(250*25/2 - 1000,0,250*25/2 - 1000));
    worldCamera->setNearClipDistance(5);
    worldCamera->setFarClipDistance(50000);
 
    if (mRoot->getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_INFINITE_FAR_PLANE))
    {
        worldCamera->setFarClipDistance(0);   // enable infinite far clip distance if we can
    }

}
//-------------------------------------------------------------------------------------
void Game::createFrameListener(void)
{

    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

    mInputManager = OIS::InputManager::createInputSystem( pl );

    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));

    mMouse->setEventCallback(this);
    mKeyboard->setEventCallback(this);
    
    Input::Initialize(mKeyboard, mMouse, mWindow);

    //Set initial mouse clipping size
    windowResized(mWindow);

    //Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

    mTrayManager = new OgreBites::SdkTrayManager("InterfaceName", mWindow, mMouse, this);
    mTrayManager->hideCursor();

    // create a params panel for displaying stats details
    Ogre::StringVector statsPanelItems;
    statsPanelItems.push_back("Score");
    statsPanelItems.push_back("Balls Left");
    mStatsPanel = mTrayManager->createParamsPanel(OgreBites::TL_NONE, "StatsPanel", 200, statsPanelItems);
    mStatsPanel->hide();

    // create a params panel for displaying game over details
    Ogre::StringVector gameOverPanelItems;
    gameOverPanelItems.push_back("GAME OVER");
    gameOverPanelItems.push_back("Final Score");
    gameOverPanelItems.push_back("Time");
    mGameOverPanel = mTrayManager->createParamsPanel(OgreBites::TL_NONE, "GameOverPanel", 200, gameOverPanelItems);
    mGameOverPanel->hide();

    mRoot->addFrameListener(this);


}
//-------------------------------------------------------------------------------------
void Game::destroyScene(void)
{
    for (auto gameObjectIter = gameObjects.begin(); gameObjectIter != gameObjects.end(); ++gameObjectIter) {
       delete (*gameObjectIter).second;; 
    }
    mSceneManager->clearScene();
    gameObjects.clear();
    playerList[0]->reset();
    Time::Reset();

    mStatsPanel->hide();
    mGameOverPanel->hide();
}
//-------------------------------------------------------------------------------------
void Game::createViewports(void)
{
    // Create one viewport, entire window
    vp = mWindow->addViewport(getCamera());
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

    // Alter the camera aspect ratio to match the viewport
    getCamera()->setAspectRatio(
        Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}
//-------------------------------------------------------------------------------------
void Game::setupResources(void)
{
    // Load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load(mResourcesConfig);

    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
            // OS X does not set the working directory relative to the app,
            // In order to make things portable on OS X we need to provide
            // the loading with it's own bundle path location
            if (!Ogre::StringUtil::startsWith(archName, "/", false)) // only adjust relative dirs
                archName = Ogre::String(Ogre::macBundlePath() + "/Contents/Resources/" + archName);
#endif
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }
}
//-------------------------------------------------------------------------------------
void Game::createResourceListener(void)
{

}
//-------------------------------------------------------------------------------------
void Game::loadResources(void)
{
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}
//-------------------------------------------------------------------------------------
void Game::run(void)
{
#ifdef _DEBUG
    mResourcesConfig = "resources_d.cfg";
    mPluginsConfig = "plugins_d.cfg";
#else
    mResourcesConfig = "resources.cfg";
    mPluginsConfig = "plugins.cfg";
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS || OGRE_PLATFORM == OGRE_PLATFORM_APPLE
    Ogre::String workingDir = Ogre::macBundlePath()+"/Contents/Resources/";
    mResourcesConfig = workingDir + mResourcesConfig;
    mPluginsConfig = workingDir + mPluginsConfig;
#endif

    if (!setup())
        return;

    mRoot->startRendering();

    // clean up
    //destroyScene();
}
//-------------------------------------------------------------------------------------
bool Game::setup(void)
{
    Time::Start();

    mRoot = new Ogre::Root(mPluginsConfig);
    mPhysicsSimulator = new PhysicsSimulator();
    mSoundManager = new SoundManager();
    playerList.push_back(new Player(LOCAL));
    setupResources();

    bool carryOn = configure();
    if (!carryOn) return false;

    level = 1;
    viewMode = false;
    gameMode = false;

    chooseSceneManager();
    createCamera();
    createViewports();

    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    // Create any resource listeners (for loading screens)
    createResourceListener();
    // Load resources
    loadResources();

    // Create the scene
    createLights();
    createGUI();

    createFrameListener();
    return true;
};
//-------------------------------------------------------------------------------------
bool Game::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    Time::Update();
    if (mWindow->isClosed())
        return false;

    if (mShutDown)
        return false;

    if (playerList[0]->mLives <= 0 && lost == false){
        lost = true;
        robotScript->can_move = false;
        disableGameWindow();
        enableGameOverMenu();
    }
    //Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();
   
    *playerGold = string("Gold: ");
    int num = playerList[0]->mGold;       // number to be converted to a string
    ostringstream convert;   // stream used for int to string conversion
    convert << num;      // insert the textual representation of 'Number' in the characters in the stream
    playerGold->append(convert.str()); // set 'Result' to the contents of the stream
    *playerScore = string("Score: ");
    num = playerList[0]->mScore;       // number to be converted to a string
    ostringstream convert1;   // stream used for int to string conversion
    convert1 << num;      // insert the textual representation of 'Number' in the characters in the stream
    playerScore->append(convert1.str()); // set 'Result' to the contents of the stream
    *playerLives = string("Lives: ");
    num = playerList[0]->mLives;       // number to be converted to a string
    ostringstream convert2;   // stream used for int to string conversion
    convert2 << num;      // insert the textual representation of 'Number' in the characters in the stream
    playerLives->append(convert2.str()); // set 'Result' to the contents of the stream
    gameWindow->getChild("gold")->setText(*playerGold);
    gameWindow->getChild("score")->setText(*playerScore);
    gameWindow->getChild("lives")->setText(*playerLives);
    towerMenu->getChild("gold1")->setText(*playerGold);
    towerMenu->getChild("score1")->setText(*playerScore);
    towerMenu->getChild("lives1")->setText(*playerLives);
    mTrayManager->frameRenderingQueued(evt);
    CEGUI::System::getSingleton().injectTimePulse(evt.timeSinceLastFrame);
    deltaTime = evt.timeSinceLastFrame;
    if (gameMode == true)
    {
        mAnimationState->addTime(evt.timeSinceLastFrame*2);
        mPhysicsSimulator->stepSimulation(evt.timeSinceLastFrame);

        for (auto gameObjectIter = gameObjects.begin(); gameObjectIter != gameObjects.end(); ++gameObjectIter) {
            (*gameObjectIter).second->Update();
        }
    }
    Input::Update();
    return true;
}
//-------------------------------------------------------------------------------------
bool Game::keyPressed( const OIS::KeyEvent &arg )
{
    CEGUI::System &sys = CEGUI::System::getSingleton();
    sys.injectKeyDown(arg.key);
    sys.injectChar(arg.text);

    if (arg.key == OIS::KC_ESCAPE) {
        gameMode = !gameMode;
        CEGUI::EventArgs args;
        if( gameMode == true ){
            enableGameWindow();
            disableMainMenu();
            robotScript->can_move = true;
        }
        else{
            disableGameWindow();
            enableMainMenu();
            robotScript->can_move = false;

        }
    }
    else if (arg.key == OIS::KC_LSHIFT)
    {
        viewMode = !viewMode;
        if(viewMode == true) 
        {
            cout << "world view" << endl;
            mCamera = &worldCamera;
            vp->setCamera(getCamera());  
        }
        else
        {
            cout << "player view" << endl;
            mCamera = &playerCamera;
            mCameraNode = &playerCameraNode;
            vp->setCamera(getCamera());
        }
    }
    
    else if (arg.key == OIS::KC_Z)
    {
        if (!enemySpawner->isSpawning()) {
	    	enemySpawner->numSpawned = 0;
            enemySpawner->waveNum++;
            enemySpawner->startSpawning();
        }
    }
    else if (arg.key == OIS::KC_N)
    {
        newGame();
    }
    else if (arg.key == OIS::KC_M)
    {
        mSoundManager->toggleSound();
    }

    return true;
}

bool Game::keyReleased( const OIS::KeyEvent &arg )
{
    CEGUI::System::getSingleton().injectKeyUp(arg.key);
    return true;
}

bool Game::mouseMoved( const OIS::MouseEvent &arg )
{
    CEGUI::System &sys = CEGUI::System::getSingleton();
    sys.injectMouseMove(arg.state.X.rel, arg.state.Y.rel);
    // Scroll wheel.
    if (arg.state.Z.rel)
        sys.injectMouseWheelChange(arg.state.Z.rel / 120.0f);

    if (mTrayManager->injectMouseMove(arg)) return true;
    return true;
}

bool Game::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    Input::mouseDown = true;
    CEGUI::System::getSingleton().injectMouseButtonDown(convertButton(id));
    cout << "Mouse pressed" << endl;
    if (mTrayManager->injectMouseDown(arg, id)) return true;
    return true;
}

bool Game::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    Input::mouseDown = false;
    Input::mouseReleased = true;


    CEGUI::System::getSingleton().injectMouseButtonUp(convertButton(id));
    if (mTrayManager->injectMouseUp(arg, id)) return true;
    return true;
}

CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID)
{
    switch (buttonID)
    {
    case OIS::MB_Left:
        return CEGUI::LeftButton;
 
    case OIS::MB_Right:
        return CEGUI::RightButton;
 
    case OIS::MB_Middle:
        return CEGUI::MiddleButton;
 
    default:
        return CEGUI::LeftButton;
    }
}

//Adjust mouse clipping area
void Game::windowResized(Ogre::RenderWindow* rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}

//Unattach OIS before window shutdown (very important under Linux)
void Game::windowClosed(Ogre::RenderWindow* rw)
{
    //Only close for window that created OIS (the main window in these demos)
    if( rw == mWindow )
    {
        if( mInputManager )
        {
            mInputManager->destroyInputObject( mMouse );
            mInputManager->destroyInputObject( mKeyboard );

            OIS::InputManager::destroyInputSystem(mInputManager);
            mInputManager = 0;
        }
    }
}



void Game::createLights(void) {
    cout << "Creating lights..." << endl;

    Ogre::Light* directionalLight = mSceneManager->createLight("directionalLight");
    directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
    directionalLight->setDirection(Ogre::Vector3(0.75,.25,0));
    directionalLight->setDiffuseColour(Ogre::ColourValue(.25, .25, .25));
    directionalLight->setSpecularColour(Ogre::ColourValue(.25, .25, 0));

    Ogre::Light *pointLight = mSceneManager->createLight("pointLight");
    pointLight->setType(Ogre::Light::LT_POINT);
    pointLight->setPosition(Ogre::Vector3(0, 1000, 0));
    pointLight->setDiffuseColour(1.0, 0.8, 0.8);
    pointLight->setSpecularColour(1.0, 0.8, 0.8);

    // Ogre::Light* spotLight3 = mSceneManager->createLight("spotLight3");
    // spotLight3->setType(Ogre::Light::LT_SPOTLIGHT);
    // spotLight3->setDiffuseColour(1.0, 0.8, 0.8);
    // spotLight3->setSpecularColour(1.0, 0.8, 0.8);
    // spotLight3->setDirection(1, -1, 0);
    // spotLight3->setPosition(Ogre::Vector3(0, 300, 0));
    // spotLight3->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));

    Ogre::Light* spotLight4 = mSceneManager->createLight("spotLight4");
    spotLight4->setType(Ogre::Light::LT_SPOTLIGHT);
    spotLight4->setDiffuseColour(0.8, 0.8, 1.0);
    spotLight4->setSpecularColour(0.8, 0.8, 1.0);
    spotLight4->setDirection(.25, .4, 0);
    spotLight4->setPosition(Ogre::Vector3(0, -300, 0));
    spotLight4->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));

    mSceneManager->setAmbientLight(Ogre::ColourValue(.5, .5, .5));
    mSceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
    mSceneManager->setShadowColour(Ogre::ColourValue::Black);

    cout << "Done creating lights!" << endl;
}

void Game::createGUI(void) {
    cout << "Creating GUI..." << endl;
    mRenderer = &CEGUI::OgreRenderer::bootstrapSystem();

    CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
    CEGUI::Font::setDefaultResourceGroup("Fonts");
    CEGUI::Scheme::setDefaultResourceGroup("Schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
    CEGUI::WindowManager::setDefaultResourceGroup("Layouts");

    CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");
    CEGUI::System::getSingleton().setDefaultMouseCursor("TaharezLook", "MouseArrow");

    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
    rootWindow = wmgr.createWindow((CEGUI::utf8*)"DefaultWindow", (CEGUI::utf8*)"RootWindow");  


    // Main Menu
    mainMenu = wmgr.createWindow((CEGUI::utf8*)"DefaultWindow", (CEGUI::utf8*)"mainMenu");  


    //TEST CODE
    // Menu Background
    CEGUI::ImagesetManager &ismmgr = CEGUI::ImagesetManager::getSingleton();
    CEGUI::Imageset* background_set = &ismmgr.createFromImageFile("background_set", "test.jpg");


    CEGUI::Window *menuBackground = wmgr.createWindow("TaharezLook/StaticImage", "background");
    menuBackground->setProperty( "Image", "set:background_set image:full_image" );
    menuBackground->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.0f, 0.0f ), CEGUI::UDim( 0.0f, 0.0f) ) );
    menuBackground->setSize( CEGUI::UVector2( CEGUI::UDim( 1.0f, 0.0f ), CEGUI::UDim( 1.0f, 0.0f ) ) );  // full screen
    //END OF TEST CODE
    CEGUI::EventArgs args;

    CEGUI::Window *quit = wmgr.createWindow("TaharezLook/Button", "quit");
    quit->setText("Quit");
    quit->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
    quit->setPosition(CEGUI::UVector2(CEGUI::UDim(0.375f, 0),CEGUI::UDim(0.5f, 0)));
    quit->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Game::quit, this));

    CEGUI::Window *newGame = wmgr.createWindow("TaharezLook/Button", "newGame");
    newGame->setText("NewGame");
    newGame->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
    newGame->setPosition(CEGUI::UVector2(CEGUI::UDim(0.375f, 0),CEGUI::UDim(0.4f, 0)));
    newGame->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Game::newGame, this));

    rootWindow->addChildWindow(mainMenu);
    mainMenu->addChildWindow(menuBackground);
    menuBackground->addChildWindow(quit);
    menuBackground->addChildWindow(newGame);

    // Game Window
    gameWindow = wmgr.createWindow((CEGUI::utf8*)"DefaultWindow", (CEGUI::utf8*)"gameWindow");  
    
    playerGold = new string(); 
    playerScore = new string();
    playerLives = new string();

    *playerGold = string("Gold: ");
    *playerScore = string("Score: ");
    *playerLives = string("Lives: ");

    CEGUI::Window *gold = wmgr.createWindow("TaharezLook/Button", "gold");
    gold->setText(*playerGold); // + playerList[0]->mGold);
    gold->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
    gold->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0),CEGUI::UDim(0.0f, 0)));

    CEGUI::Window *score = wmgr.createWindow("TaharezLook/Button", "score");
    score->setText(*playerScore); // + playerList[0]->mScore);
    score->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
    score->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0),CEGUI::UDim(0.05f, 0)));
    
    CEGUI::Window *lives = wmgr.createWindow("TaharezLook/Button", "lives");
    lives->setText(*playerLives); // + playerList[0]->mGold);
    lives->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
    lives->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0),CEGUI::UDim(0.1f, 0)));

    CEGUI::Window *towerhelp = wmgr.createWindow("TaharezLook/Button", "towerhelp");
    towerhelp->setText("Tap 1: turret"); // + playerList[0]->mGold);
    towerhelp->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
    towerhelp->setPosition(CEGUI::UVector2(CEGUI::UDim(0.8f, 0),CEGUI::UDim(0.0f, 0)));
    
    CEGUI::Window *wallhelp = wmgr.createWindow("TaharezLook/Button", "wallhelp");
    wallhelp->setText("Tap 2: wall"); // + playerList[0]->mGold);
    wallhelp->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
    wallhelp->setPosition(CEGUI::UVector2(CEGUI::UDim(0.8f, 0),CEGUI::UDim(0.05f, 0)));

    CEGUI::Window *taphelp = wmgr.createWindow("TaharezLook/Button", "taphelp");
    taphelp->setText("Tap z: wave"); // + playerList[0]->mGold);
    taphelp->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
    taphelp->setPosition(CEGUI::UVector2(CEGUI::UDim(0.8f, 0),CEGUI::UDim(0.1f, 0)));


    rootWindow->addChildWindow(gameWindow);
    gameWindow->addChildWindow(gold);
    gameWindow->addChildWindow(score);
    gameWindow->addChildWindow(lives);
    gameWindow->addChildWindow(towerhelp);
    gameWindow->addChildWindow(wallhelp);
    gameWindow->addChildWindow(taphelp);

    disableGameWindow();
    enableMainMenu();

    // Tower Menu
    towerMenu = wmgr.createWindow((CEGUI::utf8*)"DefaultWindow", (CEGUI::utf8*)"towerMenu");  
//     CEGUI::Window *towerBackground = wmgr.createWindow("TaharezLook/StaticImage", "tbackground");
//     towerBackground->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.0f, 0.0f ), CEGUI::UDim( 0.0f, 0.0f) ) );
//     towerBackground->setSize( CEGUI::UVector2( CEGUI::UDim( 1.0f, 0.0f ), CEGUI::UDim( 1.0f, 0.0f ) ) );  // full screen

    
    playerGold = new string(); 
    playerScore = new string();
    playerLives = new string();

    *playerGold = string("Gold: ");
    *playerScore = string("Score: ");
    *playerLives = string("Lives: ");

    CEGUI::Window *sell = wmgr.createWindow("TaharezLook/Button", "sell");
    sell->setText("Sell for half"); 
    sell->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
    sell->setPosition(CEGUI::UVector2(CEGUI::UDim(0.375f, 0),CEGUI::UDim(0.5f, 0)));
    sell->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Game::sell, this));

    CEGUI::Window *upgrade = wmgr.createWindow("TaharezLook/Button", "upgrade");
    upgrade->setText("Upgrade: 100");
    upgrade->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
    upgrade->setPosition(CEGUI::UVector2(CEGUI::UDim(0.375f, 0),CEGUI::UDim(0.4f, 0)));
    upgrade->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Game::upgrade, this));
    
    CEGUI::Window *cancel = wmgr.createWindow("TaharezLook/Button", "cancel");
    cancel->setText("Cancel");
    cancel->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
    cancel->setPosition(CEGUI::UVector2(CEGUI::UDim(0.375f, 0),CEGUI::UDim(0.6f, 0)));
    cancel->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Game::cancel, this));

    CEGUI::Window *gold1 = wmgr.createWindow("TaharezLook/Button", "gold1");
    gold1->setText(*playerGold); // + playerList[0]->mgold1);
    gold1->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
    gold1->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0),CEGUI::UDim(0.0f, 0)));

    CEGUI::Window *score1 = wmgr.createWindow("TaharezLook/Button", "score1");
    score1->setText(*playerScore); // + playerList[0]->mScore);
    score1->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
    score1->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0),CEGUI::UDim(0.05f, 0)));

    CEGUI::Window *lives1 = wmgr.createWindow("TaharezLook/Button", "lives1");
    lives->setText(*playerLives); // + playerList[0]->mGold);
    lives->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
    lives->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0),CEGUI::UDim(0.1f, 0)));

    rootWindow->addChildWindow(towerMenu);
//     towerMenu->addChildWindow(towerBackground);
//     towerBackground->addChildWindow(sell);
//     towerBackground->addChildWindow(upgrade);
    towerMenu->addChildWindow(sell);
    towerMenu->addChildWindow(upgrade);
    towerMenu->addChildWindow(cancel);
    towerMenu->addChildWindow(gold1);
    towerMenu->addChildWindow(score1);
    towerMenu->addChildWindow(lives1);

    disableTowerMenu();
    enableMainMenu();


    winnerMenu = wmgr.createWindow((CEGUI::utf8*)"DefaultWindow", (CEGUI::utf8*)"winnerMenu");  

    CEGUI::Window *winner = wmgr.createWindow("TaharezLook/Button", "winner");
    winner->setText("You Won!"); // + playerList[0]->mGold);
    winner->setSize(CEGUI::UVector2(CEGUI::UDim(0.3, 0), CEGUI::UDim(0.15, 0)));
    winner->setPosition(CEGUI::UVector2(CEGUI::UDim(0.35f, 0),CEGUI::UDim(0.1f, 0)));

    CEGUI::Window *quit2 = wmgr.createWindow("TaharezLook/Button", "quit2");
    quit2->setText("Quit");
    quit2->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
    quit2->setPosition(CEGUI::UVector2(CEGUI::UDim(0.375f, 0),CEGUI::UDim(0.5f, 0)));
    quit2->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Game::quit, this));

    CEGUI::Window *newGame2 = wmgr.createWindow("TaharezLook/Button", "newGame2");
    newGame2->setText("NewGame");
    newGame2->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
    newGame2->setPosition(CEGUI::UVector2(CEGUI::UDim(0.375f, 0),CEGUI::UDim(0.4f, 0)));
    newGame2->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Game::newGame, this));

    rootWindow->addChildWindow(winnerMenu);
    winnerMenu->addChildWindow(winner);
    winnerMenu->addChildWindow(newGame2);
    winnerMenu->addChildWindow(quit2);

    disableWinnerMenu();
    enableMainMenu();

    gameOverMenu = wmgr.createWindow((CEGUI::utf8*)"DefaultWindow", (CEGUI::utf8*)"gameOverMenu");  
    
    CEGUI::Window *gameover = wmgr.createWindow("TaharezLook/Button", "gameover");
    gameover->setText("Game Over"); // + playerList[0]->mGold);
    gameover->setSize(CEGUI::UVector2(CEGUI::UDim(0.3, 0), CEGUI::UDim(0.15, 0)));
    gameover->setPosition(CEGUI::UVector2(CEGUI::UDim(0.35f, 0),CEGUI::UDim(0.1f, 0)));

    CEGUI::Window *quit1 = wmgr.createWindow("TaharezLook/Button", "quit1");
    quit1->setText("Quit");
    quit1->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
    quit1->setPosition(CEGUI::UVector2(CEGUI::UDim(0.375f, 0),CEGUI::UDim(0.5f, 0)));
    quit1->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Game::quit, this));

    CEGUI::Window *newGame1 = wmgr.createWindow("TaharezLook/Button", "newGame1");
    newGame1->setText("NewGame");
    newGame1->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
    newGame1->setPosition(CEGUI::UVector2(CEGUI::UDim(0.375f, 0),CEGUI::UDim(0.4f, 0)));
    newGame1->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Game::newGame, this));
    // mainMenu->addChildWindow(hostIP);
    CEGUI::System::getSingleton().setGUISheet(rootWindow);
    Ogre::Root::getSingleton().renderOneFrame();

    rootWindow->addChildWindow(gameOverMenu);
    gameOverMenu->addChildWindow(gameover);
    gameOverMenu->addChildWindow(newGame1);
    gameOverMenu->addChildWindow(quit1);

    disableGameOverMenu();
    enableMainMenu();

    cout << "Done creating GUI..." << endl;
}

//Gui functions

void Game::disableWinnerMenu(){
  winnerMenu->disable();
  winnerMenu->setVisible(false);
}

void Game::enableWinnerMenu(){
  winnerMenu->enable();
  winnerMenu->setVisible(true);
}

void Game::disableGameOverMenu(){
  gameOverMenu->disable();
  gameOverMenu->setVisible(false);
}

void Game::enableGameOverMenu(){
  gameOverMenu->enable();
  gameOverMenu->setVisible(true);
}

void Game::disableTowerMenu(){
  towerMenu->disable();
  towerMenu->setVisible(false);
}

void Game::enableTowerMenu(bool upgraded){
  if (upgraded){
    towerMenu->getChild("upgrade")->setVisible(false);
  }
  else
    towerMenu->getChild("upgrade")->setVisible(true);

  towerMenu->enable();
  towerMenu->setVisible(true);
}

bool Game::sell(const CEGUI::EventArgs &e){
  cout << "Welcome to sell()\n";
  //TODO: update player resources
  robotScript->sellTower();
  robotScript->can_move = true;
  disableTowerMenu();
  enableGameWindow();
}


bool Game::cancel(const CEGUI::EventArgs &e){
  cout << "Welcome to not sell()\n";
  //TODO: update player resources
  robotScript->sold = true;
  robotScript->can_move = true;
  disableTowerMenu();
  enableGameWindow();
}
bool Game::upgrade(const CEGUI::EventArgs &e){
  cout << "Welcome to upgrade()\n";
  //TODO: This function
  robotScript->upgradeTower();
  robotScript->can_move = true;
  disableTowerMenu();
  enableGameWindow();
}

//Main Menu gui functions
void Game::disableMainMenu() {
    mainMenu->disable();
    mainMenu->setVisible(false);
}
void Game::enableMainMenu() {
    mainMenu->enable();
    mainMenu->setVisible(true);
    mainMenu->getChild("background")->getChild("newGame")->setVisible(true);
}

void Game::disableGameWindow() {
    gameWindow->disable();
    gameWindow->setVisible(false);
}
void Game::enableGameWindow() {
    gameWindow->enable();
    gameWindow->setVisible(true);
}

void Game::createScene(void) {
    cout << "Creating scene..." << endl;

    // Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(Ogre::TFO_ANISOTROPIC);
    // Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(7);

    mSceneManager->setSkyDome(true, "Cloud1", 5, 8);

    GameObject *gridGameObject = new GameObject(this);
    Grid *grid = gridGameObject->AddComponentOfType<Grid>();
    
    Robot *bob = new Robot(this);
    robotScript = bob->AddComponentOfType<RobotScript>();
    bob->transform->setWorldPosition(Ogre::Vector3(0,10,0));
    bob->transform->setWorldScale(Ogre::Vector3(1,1,1));
    bob->physics->setGravity(Ogre::Vector3(0,-9.8f,0));
    bob->name = "bob";
    robotScript->grid = grid;

    Ogre::Vector3 subpos = bob->physics->getWorldPosition();

    // Position it at 500 in Z direction
    playerCamera->setPosition(Ogre::Vector3(subpos.x - 300, subpos.y + 300, subpos.z));
    // Look back along -Z
    playerCamera->lookAt(Ogre::Vector3(subpos.x,subpos.y + 80,subpos.z));
    playerCamera->setNearClipDistance(5);

    playerCameraNode = bob->transform->sceneNode->createChildSceneNode("CameraNode");
    playerCameraNode->attachObject(playerCamera);

    mCamera = &playerCamera;
    mCameraNode = &playerCameraNode;

    mAnimationState = bob->renderer->entity->getAnimationState("Idle");
    mAnimationState->setLoop(true);
    mAnimationState->setEnabled(true);

    // Mountain *mountain1 = new Mountain(this);
    // mountain1->transform->setWorldPosition(Ogre::Vector3(-1000, -100, -1000));

    HomeBase *homeBase = new HomeBase(this);

    cout << "Done creating scene!" << endl;
}



Ogre::SceneNode* Game::getSceneRoot(void) {
    return mSceneManager->getRootSceneNode();
}

void Game::setAnimationState(Ogre::AnimationState* anState) {
    mAnimationState = anState;
    mAnimationState->setLoop(true);
    mAnimationState->setEnabled(true);
}

Ogre::SceneManager* Game::getSceneManager(void) {
    return mSceneManager;
}

PhysicsSimulator* Game::getPhysicsSimulator(void) {
    return mPhysicsSimulator;
}

OIS::Keyboard* Game::getKeyboard(void) {
    return mKeyboard;
}

OIS::Mouse* Game::getMouse(void) {
    return mMouse;
}

Ogre::Camera* Game::getCamera(void) {
    return *mCamera;
}

Ogre::SceneNode* Game::getCameraNode(void) {
    return *mCameraNode;
}


int Game::camQuadrant () {
    Ogre::Vector3 pos = getCamera()->getPosition();
    if(pos.x > 0 & pos.z > 0)
    {
        return 1;
    }
    else if(pos.x > 0 & pos.z < 0)
    {
        return 2;
    }
    else if(pos.x < 0 & pos.z > 0)
    {
        return 3;
    }
    else if(pos.x < 0 & pos.z < 0)
    {
        return 4;
    }
}

int Game::camSide () {
    Ogre::Vector3 pos = getCamera()->getPosition();
    Ogre::Vector3 camToY = Ogre::Vector3(pos.x, 0, pos.z);
    
    if( camToY.dotProduct( Ogre::Vector3(-1,0,1) ) > 0 && camToY.dotProduct( Ogre::Vector3(1,0,1) ) > 0 )
        return 1;
    else if ( camToY.dotProduct( Ogre::Vector3(1,0,1) ) > 0 && camToY.dotProduct( Ogre::Vector3(1,0,-1) ) > 0 ) 
        return 2;
    else if ( camToY.dotProduct( Ogre::Vector3(1,0,-1) ) > 0 && camToY.dotProduct( Ogre::Vector3(-1,0,-1) ) > 0 )
        return 3;
    else if ( camToY.dotProduct( Ogre::Vector3(-1,0,-1) ) > 0 && camToY.dotProduct( Ogre::Vector3(-1,0,1) ) > 0 ) 
        return 4;
}

Player* Game::getPlayer(void) {
    return playerList[0];
}
SoundManager* Game::getSoundManager(void) {
    return mSoundManager;
}

bool Game::quit(const CEGUI::EventArgs &e){
    mShutDown = true;
    return true;
}

bool Game::newGame(const CEGUI::EventArgs &e){
    gameMode = true;
    disableGameOverMenu();
    disableMainMenu();
    disableWinnerMenu();
    enableGameWindow();
    destroyScene();
    createLights();
    createScene();
    playerList[0]->mGold = 150;
    playerList[0]->mScore = 0;
    playerList[0]->mLives = 25;
    enemySpawner->waveNum = -1;
    lost = false;
}
bool Game::newGame() {
    gameMode = true;
    disableGameOverMenu();
    disableMainMenu();
    disableWinnerMenu();
    enableGameWindow();
    destroyScene();
    createLights();
    createScene();
    playerList[0]->mGold = 150;
    playerList[0]->mScore = 0;
    playerList[0]->mLives = 10;
    enemySpawner->waveNum = 0;
    lost = false;
}
