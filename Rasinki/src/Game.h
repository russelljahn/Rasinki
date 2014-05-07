#include <OgreRenderWindow.h>
#include <OgreRoot.h>
#include <OgreWindowEventUtilities.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#ifndef __Game_h_
#define __Game_h_

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkTrays.h>
#include <SdkCameraMan.h>

#include <vector>
#include <map>

#include "GameObject.h"
#include "PhysicsSimulator.h"
#include "Player.h"
#include "SoundManager.h"
#include "Network.h"
#include "Input.h"

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>

#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>

/*Foward Declarations*/
class GameObject;
class PhysicsSimulator;
class Player;
class SoundManager;
class Network;
class EnemySpawner;

using namespace std;

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
#    define OGRE_IS_IOS 1
#    include <OISMultiTouch.h>
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS || OGRE_PLATFORM == OGRE_PLATFORM_APPLE
#   include <macUtils.h>
#endif

#ifdef OGRE_IS_IOS
class Game : public Ogre::FrameListener, public Ogre::WindowEventListener, OIS::KeyListener, OIS::MultiTouchListener, OgreBites::SdkTrayListener
#else
class Game : public Ogre::FrameListener, public Ogre::WindowEventListener, public OIS::KeyListener, public OIS::MouseListener, OgreBites::SdkTrayListener
#endif
{
public:
    Game(void);
    void destroyGameObject(GameObject* object);
    virtual ~Game(void);

    virtual void run(void);

    // Ogre::FrameListener
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
    bool newGame();
    Ogre::SceneNode* getSceneRoot(void);
    Ogre::SceneManager* getSceneManager(void);
    void setAnimationState(Ogre::AnimationState* anState);
    PhysicsSimulator* getPhysicsSimulator(void);
    SoundManager* getSoundManager(void);
    Network* getNetwork(void) { return mNetwork; }
    Player* getPlayer(void);
    OIS::Keyboard* getKeyboard(void);
    OIS::Mouse* getMouse(void);
    Ogre::Camera* getCamera(void);
    Ogre::SceneNode* getCameraNode(void);
    int camQuadrant(void);
    int camSide(void);

    int level;
    bool viewMode;
    bool gameMode;
    bool inMultiplayerMenu;
    bool OnServerQuit();
    bool multiplayer;

    // Miscellaneous
    vector<Player *> playerList;
    map<int, GameObject *> gameObjects;
    EnemySpawner* enemySpawner;
    float getDeltaTime() { return deltaTime; }
protected:
    virtual bool setup();
    virtual bool configure(void);
    virtual void chooseSceneManager(void);
    virtual void createCamera(void);
    virtual void createFrameListener(void);
    virtual void createLights(void);
    virtual void createGUI(void); 
    virtual void createScene(void); 
    virtual void destroyScene(void);
    virtual void createViewports(void);
    virtual void setupResources(void);
    virtual void createResourceListener(void);
    virtual void loadResources(void);

    //GUI 
    virtual bool onStartServer(const CEGUI::EventArgs &e);
    virtual bool onConnectToServer(const CEGUI::EventArgs &e);
    virtual bool onClickPlayMultiplayer(const CEGUI::EventArgs &e);
    virtual bool onClickBackFromMultiplayerMenu(const CEGUI::EventArgs &e);
    virtual void disableMainMenu();
    virtual void enableMainMenu();
    virtual void disableGameWindow();
    virtual void enableGameWindow();
    virtual void disableMultiplayerMenu();
    virtual void enableMultiplayerMenu();
    virtual void disableTowerMenu();
    virtual void enableTowerMenu();
    virtual void sell();
    virtual void upgrade();


    // OIS::KeyListener
    virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );
    // OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

    bool quit(const CEGUI::EventArgs &e);
    bool newGame(const CEGUI::EventArgs &e);


    // Ogre::WindowEventListener
    //Adjust mouse clipping area
    virtual void windowResized(Ogre::RenderWindow* rw);
    //Unattach OIS before window shutdown (very important under Linux)
    virtual void windowClosed(Ogre::RenderWindow* rw);


    Ogre::Root *mRoot;
    Ogre::Viewport *vp;
    Ogre::Camera** mCamera;
    Ogre::SceneNode** mCameraNode;
    Ogre::SceneManager* mSceneManager;
    Ogre::RenderWindow* mWindow;
    Ogre::String mResourcesConfig;
    Ogre::String mPluginsConfig;
    Ogre::AnimationState *mAnimationState;

    // Player and World Camera/CameraNode
    Ogre::Camera* worldCamera;
    Ogre::SceneNode* worldCameraNode;
    Ogre::Camera* playerCamera;
    Ogre::SceneNode* playerCameraNode;

    // OgreBites
    OgreBites::SdkTrayManager* mTrayManager;
    OgreBites::SdkCameraMan* mCameraMan;       // basic camera controller
    OgreBites::ParamsPanel* mStatsPanel;       // Game stats panel
    OgreBites::Label* mGameOverLabel;
    OgreBites::ParamsPanel* mGameOverPanel;    // Game over stats panel
    bool mCursorWasVisible;                    // was cursor visible before dialog appeared
    bool mShutDown;

    //OIS Input devices
    OIS::InputManager* mInputManager;
    OIS::Mouse*    mMouse;
    OIS::Keyboard* mKeyboard;

    PhysicsSimulator* mPhysicsSimulator;
    SoundManager* mSoundManager;
    Player* mPlayer;
    Network* mNetwork;

    //CEGUI::Renderer
    CEGUI::OgreRenderer* mRenderer;
    CEGUI::Window* rootWindow;

    CEGUI::Window* mainMenu;
    CEGUI::Window* multiplayerMenu;
    CEGUI::Window* gameWindow;
    CEGUI::Window* towerMenu;


    RobotScript *robotScript;
    
    
    //Strings
    string* playerGold;
    string* playerScore;


private:
    //Ogre Terrain
    Ogre::TerrainGlobalOptions* mTerrainGlobals;
    Ogre::TerrainGroup* mTerrainGroup;
    bool mTerrainsImported;
 
    void defineTerrain(long x, long y);
    void initBlendMaps(Ogre::Terrain* terrain);
    void configureTerrainDefaults(Ogre::Light* light);

    float deltaTime;
};

#endif // #ifndef __Game_h_

