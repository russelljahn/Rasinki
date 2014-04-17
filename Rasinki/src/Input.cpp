
#include "Input.h"

#include <iostream>

OIS::Keyboard *Input::keyboard = NULL;
OIS::Mouse *Input::mouse = NULL;
bool Input::mouseDown = false;
bool Input::mouseReleased = false;


void Input::Initialize(OIS::Keyboard *keyboard, OIS::Mouse *mouse) {
    Input::keyboard = keyboard;
    Input::mouse = mouse;
}

// bool Input::IsKeyUp(OIS::KeyCode keyCode) {
// 	return Input::keyboard->isKeyUp(keyCode);
// }

void Input::Update() {
	Input::mouseReleased = false;
}

bool Input::IsKeyDown(OIS::KeyCode keyCode) {
	return Input::keyboard->isKeyDown(keyCode);
}
