#ifndef __INPUT_CLASS_H__
#define __INPUT_CLASS_H__

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreRenderWindow.h>

#include <CEGUI/CEGUI.h>



/* 
	Manager used to poll input from the game.
*/

class Input {
	public:
		static void Initialize(OIS::Keyboard *keyboard, OIS::Mouse *mouse, Ogre::RenderWindow *window);
		// static bool IsKeyUp(OIS::KeyCode keyCode);
		static bool IsKeyDown(OIS::KeyCode keyCode);
		static void Update();
		static Ogre::Vector3 GetMouseDelta(); // -x is left, +x is right, -y is down, +y is up
		static Ogre::Vector3 GetMouseInViewportCoord(); // (-1,-1) is bottom left of viewport, (1,1) is top right of viewport, (0,0) is center of viewport

	private:
	    //OIS Input devices
	    static OIS::Mouse*    mouse;
	    static OIS::Keyboard* keyboard;
	    static Ogre::RenderWindow* window;

	    static Ogre::Vector3 mousePositionLastFrame; // In unmapped screen coordinates, (0,0) is top left, (screenWidth, screenHeight) is bottom right. Note y is flipped.
	    static Ogre::Vector3 mousePositionThisFrame; // In unmapped screen coordinates, (0,0) is top left, (screenWidth, screenHeight) is bottom right. Note y is flipped.

};

#endif