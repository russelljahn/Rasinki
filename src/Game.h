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

#include "GameObject.h"
#include "PhysicsSimulator.h"
#include "Player.h"
#include "SoundManager.h"


/*Foward Declarations*/
class GameObject;
class PhysicsSimulator;
class Player;
class SoundManager;

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
    virtual ~Game(void);

    virtual void run(void);

    // Ogre::FrameListener
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    Ogre::SceneNode* getSceneRoot(void);
    Ogre::SceneManager* getSceneManager(void);
    PhysicsSimulator* getPhysicsSimulator(void);
    OIS::Keyboard* getKeyboard(void);
    OIS::Mouse* getMouse(void);
    Ogre::Camera* getCamera(void);
    int camQuadrant(void);
    int camSide(void);
    Player* getPlayer(void);


protected:
    virtual bool setup();
    virtual bool configure(void);
    virtual void chooseSceneManager(void);
    virtual void createCamera(void);
    virtual void createFrameListener(void);
    virtual void createLights(void); 
    virtual void createScene(void); 
    virtual void destroyScene(void);
    virtual void createViewports(void);
    virtual void setupResources(void);
    virtual void createResourceListener(void);
    virtual void loadResources(void);

    // OIS::KeyListener
    virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );
    // OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

    // Ogre::WindowEventListener
    //Adjust mouse clipping area
    virtual void windowResized(Ogre::RenderWindow* rw);
    //Unattach OIS before window shutdown (very important under Linux)
    virtual void windowClosed(Ogre::RenderWindow* rw);


    Ogre::Root *mRoot;
    Ogre::Camera* mCamera;
    Ogre::SceneManager* mSceneManager;
    Ogre::RenderWindow* mWindow;
    Ogre::String mResourcesConfig;
    Ogre::String mPluginsConfig;

    // OgreBites
    OgreBites::SdkTrayManager* mTrayManager;
    OgreBites::SdkCameraMan* mCameraMan;       // basic camera controller
    OgreBites::ParamsPanel* mDetailsPanel;     // sample details panel
    bool mCursorWasVisible;                    // was cursor visible before dialog appeared
    bool mShutDown;

    //OIS Input devices
    OIS::InputManager* mInputManager;
    OIS::Mouse*    mMouse;
    OIS::Keyboard* mKeyboard;

    PhysicsSimulator* mPhysicsSimulator;
    SoundManager* mSoundManager;
    Player* mPlayer;
    // Miscellaneous
    vector<GameObject *> gameObjects;
};

#endif // #ifndef __Game_h_

