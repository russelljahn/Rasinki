#include <Game.h>
#include <iostream>

using namespace std;

#include "Game.h"

#include "Scripts/PaddleScript.h"
#include "Scripts/PointBlock.h"
#include "Scripts/Wall.h"

#include "Objects/Paddle.h"
#include "Objects/Sphere.h"
#include "Objects/Plane.h"
#include "Objects/Cube.h"

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
    mDetailsPanel(0),
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
    // if (mCameraMan) delete mCameraMan;

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
    mCamera->setPosition(Ogre::Vector3(2000,2000,2000));
    // Look back along -Z
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    mCamera->setNearClipDistance(5);

    // mCameraMan = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
    // mCameraMan->setTopSpeed(400.0f);
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
    mTrayManager->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    mTrayManager->showLogo(OgreBites::TL_BOTTOMRIGHT);
    mTrayManager->hideCursor();

    // create a params panel for displaying sample details
    Ogre::StringVector items;
    items.push_back("cam.pX");
    items.push_back("cam.pY");
    items.push_back("cam.pZ");
    items.push_back("");
    items.push_back("cam.oW");
    items.push_back("cam.oX");
    items.push_back("cam.oY");
    items.push_back("cam.oZ");
    items.push_back("");
    items.push_back("Filtering");
    items.push_back("Poly Mode");

    mDetailsPanel = mTrayManager->createParamsPanel(OgreBites::TL_NONE, "DetailsPanel", 200, items);
    mDetailsPanel->setParamValue(9, "Bilinear");
    mDetailsPanel->setParamValue(10, "Solid");
    mDetailsPanel->hide();

    mRoot->addFrameListener(this);
}
//-------------------------------------------------------------------------------------
void Game::destroyScene(void)
{
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
    destroyScene();
}
//-------------------------------------------------------------------------------------
bool Game::setup(void)
{
    mRoot = new Ogre::Root(mPluginsConfig);
    mPhysicsSimulator = new PhysicsSimulator();

    setupResources();

    bool carryOn = configure();
    if (!carryOn) return false;

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
    createScene();

    createFrameListener();
    return true;
};
//-------------------------------------------------------------------------------------
bool Game::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if(mWindow->isClosed())
        return false;

    if(mShutDown)
        return false;

    //Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();

    mTrayManager->frameRenderingQueued(evt);
    mPhysicsSimulator->stepSimulation(evt.timeSinceLastFrame);

    if (mKeyboard->isKeyDown(OIS::KC_Z))
    {
        Ogre::Vector3 pos = mCamera->getPosition();
        Ogre::Vector3 rotPos = Ogre::Vector3::ZERO;
        rotPos.x = Ogre::Math::Cos(.01)*pos.x + Ogre::Math::Sin(.01)*pos.z;
        rotPos.z = Ogre::Math::Sin(.01)*-pos.x + Ogre::Math::Cos(.01)*pos.z;
        mCamera->setPosition(Ogre::Vector3(rotPos.x, pos.y, rotPos.z));
        mCamera->lookAt(Ogre::Vector3(0,0,0));
        mCamera->setNearClipDistance(5);
        
    }
    else if (mKeyboard->isKeyDown(OIS::KC_X))
    {
        Ogre::Vector3 pos = mCamera->getPosition();
        Ogre::Vector3 rotPos = Ogre::Vector3::ZERO;
        rotPos.x = Ogre::Math::Cos(-.01)*pos.x + Ogre::Math::Sin(-.01)*pos.z;
        rotPos.z = Ogre::Math::Sin(-.01)*-pos.x + Ogre::Math::Cos(-.01)*pos.z;
        mCamera->setPosition(Ogre::Vector3(rotPos.x, pos.y, rotPos.z));
        mCamera->lookAt(Ogre::Vector3(0,0,0));
        mCamera->setNearClipDistance(5);
    }

    if (!mTrayManager->isDialogVisible())
    {
        // mCameraMan->frameRenderingQueued(evt);   // if dialog isn't up, then update the camera
        if (mDetailsPanel->isVisible())   // if details panel is visible, then update its contents
        {
            mDetailsPanel->setParamValue(0, Ogre::StringConverter::toString(mCamera->getDerivedPosition().x));
            mDetailsPanel->setParamValue(1, Ogre::StringConverter::toString(mCamera->getDerivedPosition().y));
            mDetailsPanel->setParamValue(2, Ogre::StringConverter::toString(mCamera->getDerivedPosition().z));
            mDetailsPanel->setParamValue(4, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().w));
            mDetailsPanel->setParamValue(5, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().x));
            mDetailsPanel->setParamValue(6, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().y));
            mDetailsPanel->setParamValue(7, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().z));
        }
    }

    for (auto gameObjectIter = gameObjects.begin(); gameObjectIter != gameObjects.end(); ++gameObjectIter) {
        (*gameObjectIter)->Update();
    }

    return true;
}
//-------------------------------------------------------------------------------------
bool Game::keyPressed( const OIS::KeyEvent &arg )
{
    if (mTrayManager->isDialogVisible()) return true;   // don't process any more keys if dialog is up

    if (arg.key == OIS::KC_F)   // toggle visibility of advanced frame stats
    {
        mTrayManager->toggleAdvancedFrameStats();
    }
    else if (arg.key == OIS::KC_G)   // toggle visibility of even rarer debugging details
    {
        if (mDetailsPanel->getTrayLocation() == OgreBites::TL_NONE)
        {
            mTrayManager->moveWidgetToTray(mDetailsPanel, OgreBites::TL_TOPRIGHT, 0);
            mDetailsPanel->show();
        }
        else
        {
            mTrayManager->removeWidgetFromTray(mDetailsPanel);
            mDetailsPanel->hide();
        }
    }
    else if (arg.key == OIS::KC_T)   // cycle polygon rendering mode
    {
        Ogre::String newVal;
        Ogre::TextureFilterOptions tfo;
        unsigned int aniso;

        switch (mDetailsPanel->getParamValue(9).asUTF8()[0])
        {
        case 'B':
            newVal = "Trilinear";
            tfo = Ogre::TFO_TRILINEAR;
            aniso = 1;
            break;
        case 'T':
            newVal = "Anisotropic";
            tfo = Ogre::TFO_ANISOTROPIC;
            aniso = 8;
            break;
        case 'A':
            newVal = "None";
            tfo = Ogre::TFO_NONE;
            aniso = 1;
            break;
        default:
            newVal = "Bilinear";
            tfo = Ogre::TFO_BILINEAR;
            aniso = 1;
        }

        Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(tfo);
        Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(aniso);
        mDetailsPanel->setParamValue(9, newVal);
    }
    else if (arg.key == OIS::KC_R)   // cycle polygon rendering mode
    {
        Ogre::String newVal;
        Ogre::PolygonMode pm;

        switch (mCamera->getPolygonMode())
        {
        case Ogre::PM_SOLID:
            newVal = "Wireframe";
            pm = Ogre::PM_WIREFRAME;
            break;
        case Ogre::PM_WIREFRAME:
            newVal = "Points";
            pm = Ogre::PM_POINTS;
            break;
        default:
            newVal = "Solid";
            pm = Ogre::PM_SOLID;
        }

        mCamera->setPolygonMode(pm);
        mDetailsPanel->setParamValue(10, newVal);
    }
    else if(arg.key == OIS::KC_F5)   // refresh all textures
    {
        Ogre::TextureManager::getSingleton().reloadAll();
    }
    else if (arg.key == OIS::KC_SYSRQ)   // take a screenshot
    {
        mWindow->writeContentsToTimestampedFile("screenshot", ".jpg");
    }
    else if (arg.key == OIS::KC_ESCAPE)
    {
        mShutDown = true;
    }

    // mCameraMan->injectKeyDown(arg);
    return true;
}

bool Game::keyReleased( const OIS::KeyEvent &arg )
{
    // mCameraMan->injectKeyUp(arg);
    return true;
}

bool Game::mouseMoved( const OIS::MouseEvent &arg )
{
    // if (mTrayManager->injectMouseMove(arg)) return true;
    // mCameraMan->injectMouseMove(arg);
    return true;
}

bool Game::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    if (mTrayManager->injectMouseDown(arg, id)) return true;
    // mCameraMan->injectMouseDown(arg, id);
    return true;
}

bool Game::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    if (mTrayManager->injectMouseUp(arg, id)) return true;
    // mCameraMan->injectMouseUp(arg, id);
    return true;
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
    // mSceneManager->setShadowTechnique(Ogre::SHADOWTYPE_NONE);
    cout << "Done creating lights!" << endl;
}



void Game::createScene(void) {
    cout << "Creating scene..." << endl;

    // Environment
    Cube *ground = new Cube(this);
    ground->transform->setWorldPosition(Ogre::Vector3(0,-1000,0));
    ground->transform->setWorldScale(Ogre::Vector3(20, 1, 20));
    ground->name = "cube";
    ground->renderer->setMaterial("Examples/GrassFloor");
    gameObjects.push_back(ground);

    Cube *ceiling = new Cube(this);
    ceiling->transform->setWorldPosition(Ogre::Vector3(0,1250,0));
    ceiling->transform->setWorldScale(Ogre::Vector3(20, 1, 20));
    ceiling->name = "ceiling";
    ceiling->renderer->setEnabled(false);
    gameObjects.push_back(ceiling);

    Cube *west = new Cube(this);
    west->AddComponentOfType<Wall>();
    west->transform->setWorldPosition(Ogre::Vector3(-1000,0,0));
    west->transform->setWorldScale(Ogre::Vector3(1, 25, 20));
    west->name = "west";
    west->renderer->setMaterial("Examples/BumpyMetal");
    gameObjects.push_back(west);

    Cube *east = new Cube(this);
    east->AddComponentOfType<Wall>();
    east->transform->setWorldPosition(Ogre::Vector3(1000,0,0));
    east->transform->setWorldScale(Ogre::Vector3(1, 25, 20));
    east->name = "east";
    east->renderer->setMaterial("Examples/BumpyMetal");
    east->renderer->setEnabled(false);
    gameObjects.push_back(east);

    Cube *south = new Cube(this);
    south->AddComponentOfType<Wall>();
    south->transform->setWorldPosition(Ogre::Vector3(0, 0, 1000));
    south->transform->setWorldScale(Ogre::Vector3(20, 25, 1));
    south->name = "south";
    south->renderer->setMaterial("Examples/BumpyMetal");
    south->renderer->setEnabled(false);
    gameObjects.push_back(south);

    Cube *north = new Cube(this);
    north->AddComponentOfType<Wall>();
    north->transform->setWorldPosition(Ogre::Vector3(0, 0, -1000));
    north->transform->setWorldScale(Ogre::Vector3(20, 25, 1));
    north->name = "north";
    north->renderer->setMaterial("Examples/BumpyMetal");
    gameObjects.push_back(north);

    
    // Balls
    Sphere *ball01 = new Sphere(this, 75);
    ball01->transform->setWorldPosition(Ogre::Vector3(-100,800,0));
    ball01->name = "ball01";
    ball01->renderer->setMaterial("Examples/SphereMappedRustySteel");
    ball01->physics->setLinearVelocity(Ogre::Vector3(-200, -400, -200));
    ball01->physics->setGravity(Ogre::Vector3(0, -200, 0));
    gameObjects.push_back(ball01);

    Sphere *ball02 = new Sphere(this, 75);
    ball02->transform->setWorldPosition(Ogre::Vector3(100,800,0));
    ball02->name = "ball02";
    ball02->renderer->setMaterial("Examples/SphereMappedRustySteel");
    ball02->physics->setLinearVelocity(Ogre::Vector3(200, -400, 200));
    ball02->physics->setGravity(Ogre::Vector3(0, -200, 0));
    gameObjects.push_back(ball02);

    Sphere *ball03 = new Sphere(this, 75);
    ball03->transform->setWorldPosition(Ogre::Vector3(000,800,000));
    ball03->name = "ball03";
    ball03->renderer->setMaterial("Examples/SphereMappedRustySteel");
    ball03->physics->setLinearVelocity(Ogre::Vector3(0, -400, -0));
    ball03->physics->setGravity(Ogre::Vector3(0, -200, 0));
    gameObjects.push_back(ball03);


    // Paddle
    Paddle *newPaddle = new Paddle(this);
    newPaddle->AddComponentOfType<PaddleScript>();
    newPaddle->transform->setWorldPosition(Ogre::Vector3(0,-400,0));
    newPaddle->transform->setLocalScale(Ogre::Vector3(3, .25, 3));
    newPaddle->name = "paddle";
    newPaddle->renderer->setMaterial("Examples/Rockwall");
    gameObjects.push_back(newPaddle);


    // PointBlocks
    Cube *block01 = new Cube(this);
    block01->AddComponentOfType<PointBlock>();
    block01->transform->setWorldPosition(Ogre::Vector3(0,0,0));
    block01->transform->setLocalScale(Ogre::Vector3(1, 1, 1));
    block01->name = "cube";
    gameObjects.push_back(block01);


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