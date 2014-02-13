#include <Game.h>
#include <iostream>

using namespace std;

Game::Game()
{
    
}

void Game::run()
{
    // all of this is just copied from various methods in the tutorial code
    
    mRoot = new Ogre::Root("cfg/plugins.cfg");
    
    // Show the configuration dialog and initialise the system
    // You can skip this and use root.restoreConfig() to load configuration
    // settings if you were sure there are valid ones saved in ogre.cfg
    if(mRoot->showConfigDialog())
    {
        // If returned true, user clicked OK so initialise
        // Here we choose to let the system create a default rendering window by passing 'true'
        mWindow = mRoot->initialise(true, "TutorialApplication Render Window");
    }
    else
    {
        return;
    }
    
    // initialize input
    
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    // I'm actually not sure what this bit is doing.
    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

    mInputManager = OIS::InputManager::createInputSystem( pl );

    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));

    mMouse->setEventCallback(this);
    mKeyboard->setEventCallback(this);
    
    // Set initial mouse clipping size
    windowResized(mWindow);
    
    // Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
    // Register as frame listener
    mRoot->addFrameListener(this);
    
    // begin render loop
    mRoot->startRendering();
}

bool Game::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    return true;
}

bool Game::keyPressed( const OIS::KeyEvent &arg )
{
    cout << "key press\n";
    return true;
}

bool Game::keyReleased( const OIS::KeyEvent &arg )
{
    cout << "key release\n";
    return true;
}

bool Game::mouseMoved( const OIS::MouseEvent &arg )
{
    cout << "mouse move\n";
    return true;
}

bool Game::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    cout << "mouse press\n";
    return true;
}

bool Game::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    cout << "mouse release\n";
    return true;
}

// Adjust mouse clipping area
void Game::windowResized(Ogre::RenderWindow* rw)
{
    // unsigned int width, height, depth;
    // int left, top;
    // rw->getMetrics(width, height, depth, left, top);

    // const OIS::MouseState &ms = mMouse->getMouseState();
    // ms.width = width;
    // ms.height = height;
}

// Unattach OIS before window shutdown (very important under Linux)
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
