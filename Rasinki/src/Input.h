#ifndef __INPUT_CLASS_H__
#define __INPUT_CLASS_H__

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>


/* 
	Manager used to poll input from the game.
*/

class Input {
	public:
		static void Initialize(OIS::Keyboard *keyboard, OIS::Mouse *mouse);
		// static bool IsKeyUp(OIS::KeyCode keyCode);
		static bool IsKeyDown(OIS::KeyCode keyCode);

		static void Update();

		static bool mouseDown;
		static bool mouseReleased;

	private:
	    //OIS Input devices
	    static OIS::Mouse*    mouse;
	    static OIS::Keyboard* keyboard;
};

#endif