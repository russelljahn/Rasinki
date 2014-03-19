#include <Game.h>
#include <iostream>

using namespace std;

#include "Game.h"
#include "Time.h"

#include "Scripts/PaddleScript.h"
#include "Scripts/PointBlock.h"
#include "Scripts/Wall.h"
#include "Scripts/SphereComponent.h"
#include "Scripts/GameplayScript.h"

#include "Objects/Paddle.h"
#include "Objects/Sphere.h"
#include "Objects/Plane.h"
#include "Objects/Cube.h"

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
void Game::createCamera(void)
{
    // Create the camera
    mCamera = mSceneManager->createCamera("PlayerCam");

    // Position it at 500 in Z direction
    mCamera->setPosition(Ogre::Vector3(875,3500,3500));
    // Look back along -Z
    mCamera->lookAt(Ogre::Vector3(0,-200,0));
    mCamera->setNearClipDistance(5);

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

void Game::disableGUI(void)
{
    mRenderer->setRenderingEnabled(false);
    sheet->disable();
}

void Game::enableGUI(void)
{
    mRenderer->setRenderingEnabled(true);
    sheet->enable();
}

void Game::destroyScene(void)
{
    for (auto gameObjectIter = gameObjects.begin(); gameObjectIter != gameObjects.end(); ++gameObjectIter) {
       delete (*gameObjectIter);
    }
    gameObjects.clear();
    mPlayer->reset();
    mSceneManager->clearScene();
    Time::Reset();

    mStatsPanel->show();
    mGameOverPanel->hide();
    SphereComponent::numSpheres = 0;
}
//-------------------------------------------------------------------------------------
void Game::createViewports(void)
{
    // Create one viewport, entire window
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(
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
    mPlayer = new Player();
    setupResources();

    bool carryOn = configure();
    if (!carryOn) return false;

    level = 1;
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
    createScene();

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

    //Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();

    mTrayManager->frameRenderingQueued(evt);
    CEGUI::System::getSingleton().injectTimePulse(evt.timeSinceLastFrame);

    if (gameMode == true)
    {
        mPhysicsSimulator->stepSimulation(evt.timeSinceLastFrame);
        if (GameplayScript::IsGameOver()) {
            mStatsPanel->hide();
            mGameOverPanel->show();
            mGameOverPanel->setParamValue(0, " "); // Score
            mGameOverPanel->setParamValue(1, Ogre::StringConverter::toString(mPlayer->getScore())); // Score
            mGameOverPanel->setParamValue(2, Ogre::StringConverter::toString(GameplayScript::GetGameOverTime())); // Time elapsed
        }
        else {
            mStatsPanel->show();
            mGameOverPanel->hide();
            mStatsPanel->setParamValue(0, Ogre::StringConverter::toString(mPlayer->getScore())); // Score
            mStatsPanel->setParamValue(1, Ogre::StringConverter::toString(SphereComponent::numSpheres)); // Balls remaining
        }

        for (auto gameObjectIter = gameObjects.begin(); gameObjectIter != gameObjects.end(); ++gameObjectIter) {
            (*gameObjectIter)->Update();
        }
    }
    
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
        if( gameMode == true )
            disableGUI();
        else
            enableGUI();
    }
    else if (arg.key == OIS::KC_X)
    {
        for (int i = 1; i <= 10; ++i)
        {
            float rot = Ogre::Math::HALF_PI/10;
            Ogre::Vector3 pos = mCamera->getPosition();
            Ogre::Vector3 rotPos = Ogre::Vector3::ZERO;
            rotPos.x = Ogre::Math::Cos(rot)*pos.x + Ogre::Math::Sin(rot)*pos.z;
            rotPos.z = Ogre::Math::Sin(rot)*-pos.x + Ogre::Math::Cos(rot)*pos.z;
            mCamera->setPosition(Ogre::Vector3(rotPos.x, pos.y, rotPos.z));
            mCamera->lookAt(Ogre::Vector3(0,-200,0));
            mCamera->setNearClipDistance(5);
            mRoot->renderOneFrame();
        }
    }
    else if (arg.key == OIS::KC_Z)
    {
        for (int i = 0; i < 10; ++i)
        {
            float rot = Ogre::Math::HALF_PI/10;
            Ogre::Vector3 pos = mCamera->getPosition();
            Ogre::Vector3 rotPos = Ogre::Vector3::ZERO;
            rotPos.x = Ogre::Math::Cos(-rot)*pos.x + Ogre::Math::Sin(-rot)*pos.z;
            rotPos.z = Ogre::Math::Sin(-rot)*-pos.x + Ogre::Math::Cos(-rot)*pos.z;
            mCamera->setPosition(Ogre::Vector3(rotPos.x, pos.y, rotPos.z));
            mCamera->lookAt(Ogre::Vector3(0,-200,0));
            mCamera->setNearClipDistance(5);
            mRoot->renderOneFrame();
        }
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
    CEGUI::System::getSingleton().injectMouseButtonDown(convertButton(id));
    cout << "Mouse pressed" << endl;
    if (mTrayManager->injectMouseDown(arg, id)) return true;
    return true;
}

bool Game::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
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
    directionalLight->setDirection(Ogre::Vector3(0,-1,0));
    directionalLight->setDiffuseColour(Ogre::ColourValue(.5, .5, .5));
    directionalLight->setSpecularColour(Ogre::ColourValue(.25, .25, 0));

    Ogre::Light *pointLight = mSceneManager->createLight("pointLight");
    pointLight->setType(Ogre::Light::LT_POINT);
    pointLight->setPosition(Ogre::Vector3(0, 1000, 0));
    pointLight->setDiffuseColour(1.0, 0.8, 0.8);
    pointLight->setSpecularColour(1.0, 0.8, 0.8);

    Ogre::Light* spotLight1 = mSceneManager->createLight("spotLight1");
    spotLight1->setType(Ogre::Light::LT_SPOTLIGHT);
    spotLight1->setDiffuseColour(0.8, 0.8, 1.0);
    spotLight1->setSpecularColour(0.8, 0.8, 1.0);
    spotLight1->setDirection(-1, -1, 0);
    spotLight1->setPosition(Ogre::Vector3(0, 300, 0));
    spotLight1->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));

    Ogre::Light* spotLight2 = mSceneManager->createLight("spotLight2");
    spotLight2->setType(Ogre::Light::LT_SPOTLIGHT);
    spotLight2->setDiffuseColour(1.0, 0.8, 0.8);
    spotLight2->setSpecularColour(1.0, 0.8, 0.8);
    spotLight2->setDirection(-1, 1, 0);
    spotLight2->setPosition(Ogre::Vector3(0, -300, 0));
    spotLight2->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));

    Ogre::Light* spotLight3 = mSceneManager->createLight("spotLight3");
    spotLight3->setType(Ogre::Light::LT_SPOTLIGHT);
    spotLight3->setDiffuseColour(1.0, 0.8, 0.8);
    spotLight3->setSpecularColour(1.0, 0.8, 0.8);
    spotLight3->setDirection(1, -1, 0);
    spotLight3->setPosition(Ogre::Vector3(0, 300, 0));
    spotLight3->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));

    Ogre::Light* spotLight4 = mSceneManager->createLight("spotLight4");
    spotLight4->setType(Ogre::Light::LT_SPOTLIGHT);
    spotLight4->setDiffuseColour(0.8, 0.8, 1.0);
    spotLight4->setSpecularColour(0.8, 0.8, 1.0);
    spotLight4->setDirection(1, 1, 0);
    spotLight4->setPosition(Ogre::Vector3(0, -300, 0));
    spotLight4->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));

    mSceneManager->setAmbientLight(Ogre::ColourValue(.25, .25, .25));
    mSceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
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
    sheet = wmgr.createWindow((CEGUI::utf8*)"DefaultWindow", (CEGUI::utf8*)"RootWindow");  

    CEGUI::Window *quit = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/QuitButton");
    quit->setText("Quit");
    quit->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
    quit->setPosition(CEGUI::UVector2(CEGUI::UDim(0.3f, 0),CEGUI::UDim(0.5f, 0)));
    quit->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Game::quit, this));

    CEGUI::Window *newGame = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/NewGameButton");
    newGame->setText("NewGame");
    newGame->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
    newGame->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5f, 0),CEGUI::UDim(0.5f, 0)));
    newGame->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Game::newGame, this));

    CEGUI::Window *level1 = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/Level1Button");
    level1->setText("1");
    level1->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
    level1->setPosition(CEGUI::UVector2(CEGUI::UDim(0.3f, 0),CEGUI::UDim(0.6f, 0)));
    level1->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Game::level1, this));

    CEGUI::Window *level2 = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/Level2Button");
    level2->setText("2");
    level2->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
    level2->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5f, 0),CEGUI::UDim(0.6f, 0)));
    level2->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Game::level2, this));

    sheet->addChildWindow(quit);
    sheet->addChildWindow(newGame);
    sheet->addChildWindow(level1);
    sheet->addChildWindow(level2);
    CEGUI::System::getSingleton().setGUISheet(sheet);
    cout << "Done creating GUI..." << endl;
}

void Game::createScene(void) {
    cout << "Creating scene..." << endl;

    // Environment
    Cube *ground = new Cube(this);
    ground->transform->setWorldPosition(Ogre::Vector3(0,-1005,0));
    ground->transform->setWorldScale(Ogre::Vector3(25, .1, 25));
    ground->name = "ground";
    ground->renderer->setMaterial("Examples/AcidFloor");
    gameObjects.push_back(ground);

    Cube *ceiling = new Cube(this);
    ceiling->transform->setWorldPosition(Ogre::Vector3(0,1005,0));
    ceiling->transform->setWorldScale(Ogre::Vector3(25, .1, 25));
    ceiling->name = "ceiling";
    ceiling->renderer->setEnabled(false);
    gameObjects.push_back(ceiling);

    Cube *west = new Cube(this);
    west->AddComponentOfType<Wall>();
    west->transform->setWorldPosition(Ogre::Vector3(-1260,0,0));
    west->transform->setWorldScale(Ogre::Vector3(.1, 20, 25));
    west->name = "west";
    west->renderer->setMaterial("Examples/BumpyMetal");
    gameObjects.push_back(west);

    Cube *east = new Cube(this);
    east->AddComponentOfType<Wall>();
    east->transform->setWorldPosition(Ogre::Vector3(1260,0,0));
    east->transform->setWorldScale(Ogre::Vector3(.1, 20, 25));
    east->name = "east";
    east->renderer->setMaterial("Examples/BumpyMetalT");
    east->renderer->setEnabled(false);
    gameObjects.push_back(east);

    Cube *south = new Cube(this);
    south->AddComponentOfType<Wall>();
    south->transform->setWorldPosition(Ogre::Vector3(0, 0, 1260));
    south->transform->setWorldScale(Ogre::Vector3(25, 20, .1));
    south->name = "south";
    south->renderer->setMaterial("Examples/BumpyMetalP");
    south->renderer->setEnabled(false);
    gameObjects.push_back(south);

    Cube *north = new Cube(this);
    north->AddComponentOfType<Wall>();
    north->transform->setWorldPosition(Ogre::Vector3(0, 0, -1260));
    north->transform->setWorldScale(Ogre::Vector3(25, 20, .1));
    north->name = "north";
    north->renderer->setMaterial("Examples/BumpyMetalG");
    gameObjects.push_back(north);

    // Paddle
    Paddle *newPaddle = new Paddle(this);
    newPaddle->AddComponentOfType<PaddleScript>();
    newPaddle->AddComponentOfType<GameplayScript>();
    newPaddle->transform->setWorldPosition(Ogre::Vector3(0,-800,0));
    newPaddle->transform->setLocalScale(Ogre::Vector3(3, .25, 3));
    newPaddle->name = "paddle";
    newPaddle->renderer->setMaterial("Examples/Rockwall");
    gameObjects.push_back(newPaddle);

    int cubeid = 0;
    switch(level)
    {
        default:
        case 1:

        cubeid = 0;
        for (int i = -220; i <= 220; i+=110)
        {
            for (int j = -220; j <= 220; j+=110)
            {
                for (int k = -220; k <= 220; k+=110)
                {
                    Cube *block = new Cube(this);
                    block->AddComponentOfType<PointBlock>();
                    block->transform->setWorldPosition(Ogre::Vector3(i,j,k));
                    block->transform->setLocalScale(Ogre::Vector3(1, 1, 1));
                    block->name = "block"+cubeid;
                    gameObjects.push_back(block);
                }
            }
            cubeid++;
        }
        break;

        case 2:

        cubeid = 0;

        srand ( time(NULL) );
        Ogre::Real posx;
        Ogre::Real posy;
        Ogre::Real posz;
        for (int i = 0; i < 100; ++i)
        {
            posx = Ogre::Math::RangeRandom(-900,900);
            posy = Ogre::Math::RangeRandom(0,900);
            posz = Ogre::Math::RangeRandom(-900,900);
            Cube *block = new Cube(this);
            block->AddComponentOfType<PointBlock>();
            block->transform->setWorldPosition(Ogre::Vector3(posx,posy,posz));
            block->transform->setLocalScale(Ogre::Vector3(1, 1, 1));
            block->name = "block"+cubeid;
            gameObjects.push_back(block);
        }
        break;
    }

    float ballSpeed = 1000.0f;

    // Balls
    Sphere *ball01 = new Sphere(this, 75);
    ball01->transform->setWorldPosition(Ogre::Vector3(0,-700,0));
    ball01->name = "ball01";
    ball01->renderer->setMaterial("Examples/SphereMappedRustySteel");
    ball01->physics->setLinearVelocity(Ogre::Vector3(.5*ballSpeed, 1*ballSpeed, .5*ballSpeed));
    ball01->AddComponentOfType<SphereComponent>();
    gameObjects.push_back(ball01);

    cout << "Done creating scene!" << endl;
}



Ogre::SceneNode* Game::getSceneRoot(void) {
    return mSceneManager->getRootSceneNode();
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
    return mCamera;
}

int Game::camQuadrant () {
    Ogre::Vector3 pos = mCamera->getPosition();
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
    Ogre::Vector3 pos = mCamera->getPosition();
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
    return mPlayer;
}
SoundManager* Game::getSoundManager(void) {
    return mSoundManager;
}

bool Game::quit(const CEGUI::EventArgs &e){
    mShutDown = true;
    return true;
}

bool Game::newGame(const CEGUI::EventArgs &e){
    gameMode = !gameMode;
    disableGUI();
    destroyScene();
    createLights();
    createScene();
}

bool Game::level1(const CEGUI::EventArgs &e){
    level = 1;
    gameMode = !gameMode;
    disableGUI();
    destroyScene();
    createLights();
    createScene();

}

bool Game::level2(const CEGUI::EventArgs &e){
    level = 2;
    gameMode = !gameMode;
    disableGUI();
    destroyScene();
    createLights();
    createScene();
}