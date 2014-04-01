
#include "Input.h"

#include <iostream>

OIS::Keyboard *Input::keyboard = NULL;
OIS::Mouse *Input::mouse = NULL;
Ogre::Vector3 Input::mousePositionLastFrame = Ogre::Vector3::ZERO; // In screen coordinates, (0,0) is top left, (screenWidth, screenHeight) is bottom right.
Ogre::Vector3 Input::mousePositionThisFrame = Ogre::Vector3::ZERO; // In screen coordinates, (0,0) is top left, (screenWidth, screenHeight) is bottom right.

void Input::Initialize(OIS::Keyboard *keyboard, OIS::Mouse *mouse) {
    Input::keyboard = keyboard;
    Input::mouse = mouse;
}

// bool Input::IsKeyUp(OIS::KeyCode keyCode) {
// 	return Input::keyboard->isKeyUp(keyCode);
// }

bool Input::IsKeyDown(OIS::KeyCode keyCode) {
	return Input::keyboard->isKeyDown(keyCode);
}


void Input::Update() {
	Input::mousePositionLastFrame = Input::mousePositionThisFrame;
	CEGUI::Point mousePosition = CEGUI::MouseCursor::getSingleton().getPosition();
	Input::mousePositionThisFrame = Ogre::Vector3(mousePosition.d_x, mousePosition.d_y, 0);
}


// -x is left, +x is right, -y is down, +y is up
Ogre::Vector3 Input::GetMouseDelta() {
	Ogre::Vector3 mouseDelta = mousePositionThisFrame - mousePositionLastFrame;
	mouseDelta.y *= -1;
	return mouseDelta;
}