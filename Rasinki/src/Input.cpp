#include "Input.h"

#include <iostream>

OIS::Keyboard* Input::keyboard = NULL;
OIS::Mouse* Input::mouse = NULL;
Ogre::RenderWindow* Input::window = NULL;
bool Input::mouseDown = false;
bool Input::mouseReleased = false;

Ogre::Vector3 Input::mousePositionLastFrame = Ogre::Vector3::ZERO; // In screen coordinates, (0,0) is top left, (screenWidth, screenHeight) is bottom right.
Ogre::Vector3 Input::mousePositionThisFrame = Ogre::Vector3::ZERO; // In screen coordinates, (0,0) is top left, (screenWidth, screenHeight) is bottom right.

void Input::Initialize(OIS::Keyboard *keyboard, OIS::Mouse *mouse, Ogre::RenderWindow *window) {
    Input::keyboard = keyboard;
    Input::mouse = mouse;
    Input::window = window;
}

// bool Input::IsKeyUp(OIS::KeyCode keyCode) {
// 	return Input::keyboard->isKeyUp(keyCode);
// }

bool Input::IsKeyDown(OIS::KeyCode keyCode) {
	return Input::keyboard->isKeyDown(keyCode);
}


void Input::Update() {
	Input::mouseReleased = false;
	Input::mousePositionLastFrame = Input::mousePositionThisFrame;
	CEGUI::Point mousePosition = CEGUI::MouseCursor::getSingleton().getPosition();
	Input::mousePositionThisFrame = Ogre::Vector3(mousePosition.d_x, mousePosition.d_y, 0);
}


// -x is left, +x is right, -y is down, +y is up
Ogre::Vector3 Input::GetMouseDelta() {
	Ogre::Vector3 mouseDelta = mousePositionThisFrame - mousePositionLastFrame;
	mouseDelta.y = -mouseDelta.y;
	return mouseDelta;
}


// (-1,-1) is bottom left of viewport, (1,1) is top right of viewport, (0,0) is center of viewport
Ogre::Vector3 Input::GetMouseInViewportCoord() {
	int height = Input::window->getHeight();
	int width = Input::window->getWidth();
	return Ogre::Vector3(-1.0+2.0f*mousePositionThisFrame.x/width, 1.0-2.0*mousePositionThisFrame.y/height, mousePositionThisFrame.z);
}