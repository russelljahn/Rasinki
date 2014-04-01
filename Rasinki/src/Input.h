#ifndef __INPUT_CLASS_H__
#define __INPUT_CLASS_H__

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OgreRoot.h>

#include <CEGUI/CEGUI.h>



/* 
	Manager used to poll input from the game.
*/

class Input {
	public:
		static void Initialize(OIS::Keyboard *keyboard, OIS::Mouse *mouse);
		// static bool IsKeyUp(OIS::KeyCode keyCode);
		static bool IsKeyDown(OIS::KeyCode keyCode);
		static void Update();
		static Ogre::Vector3 GetMouseDelta(); // -x is left, +x is right, -y is down, +y is up

	private:
	    //OIS Input devices
	    static OIS::Mouse*    mouse;
	    static OIS::Keyboard* keyboard;
	    static Ogre::Vector3 mousePositionLastFrame; // In screen coordinates, (0,0) is top left, (screenWidth, screenHeight) is bottom right.
	    static Ogre::Vector3 mousePositionThisFrame; // In screen coordinates, (0,0) is top left, (screenWidth, screenHeight) is bottom right.

};

#endif