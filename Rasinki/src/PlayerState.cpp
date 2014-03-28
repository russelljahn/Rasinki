
#include "PlayerState.h"
#include <iostream>

using namespace std;


/* 
================================================
	Base PlayerState classs
================================================
*/
PlayerState::PlayerState(PlayerScript *playerScript) {
	this->playerScript = playerScript;
}


void PlayerState::Update() {
	using namespace std;
	cout << "PlayerState::Update()!" << endl;
}


PlayerState* PlayerState::NextState() {
	return this;
}


/* 
================================================
	Standing
================================================
*/
Standing::Standing(PlayerScript *playerScript) : PlayerState(playerScript) {
	cout << "Standing!" << endl;
	// Need to play idle animation.
}


void Standing::Update() {
	;
}


PlayerState* Standing::NextState() {
	Player *controllingPlayer = playerScript->controllingPlayer;

	if (controllingPlayer->IsKeyDown(OIS::KC_SPACE)) {
		return new Jumping(playerScript);
	}
	else if (controllingPlayer->IsKeyDown(OIS::KC_W) || controllingPlayer->IsKeyDown(OIS::KC_A) || 
			 controllingPlayer->IsKeyDown(OIS::KC_S) || controllingPlayer->IsKeyDown(OIS::KC_D)) {
		return new Walking(playerScript);
	}
	return this;
}


/* 
================================================
	Walking
================================================
*/
Walking::Walking(PlayerScript *playerScript) : PlayerState(playerScript) {
	cout << "Walking!" << endl;
	// Need to play walking animation.
}


void Walking::Update() {
	// Need to update movement based on input. Probably WASD FPS style.
}


PlayerState* Walking::NextState() {
	Player *controllingPlayer = playerScript->controllingPlayer;

	if (controllingPlayer->IsKeyDown(OIS::KC_SPACE)) {
		return new Jumping(playerScript);
	}
	else if (controllingPlayer->IsKeyDown(OIS::KC_W) || controllingPlayer->IsKeyDown(OIS::KC_A) || 
		controllingPlayer->IsKeyDown(OIS::KC_S) || controllingPlayer->IsKeyDown(OIS::KC_D)) {
		return this;
	}
	else {
		return new Standing(playerScript);
	}
}


/* 
================================================
	Jumping
================================================
*/
Jumping::Jumping(PlayerScript *playerScript) : PlayerState(playerScript) {
	cout << "Jumping!" << endl;
	// Need to play jumping animation.
	// Apply force once to propel character up.
}


void Jumping::Update() {
	// Move player based on input.
}


PlayerState* Jumping::NextState() {
	Player *controllingPlayer = playerScript->controllingPlayer;

	if (true) { // Need to check if character's velocity <= 0.
		return new Falling(playerScript);
	}
	else {
		return this;
	}
}


/* 
================================================
	Falling
================================================
*/
Falling::Falling(PlayerScript *playerScript) : PlayerState(playerScript) {
	cout << "Falling!" << endl;
	// Need to play falling animation.
}


void Falling::Update() {
	// Move player based on input.
}


PlayerState* Falling::NextState() {
	Player *controllingPlayer = playerScript->controllingPlayer;

	if (true) { // Need to check if character landed on the ground.
		return new Standing(playerScript);
	}
	else {
		return this;
	}
}



