#include "Player.h"

Player::Player(ControlType type) {
	mControlType = type;
	mScore = 0;
	deltaScore = 0;
}
void Player::scored(int points) {
	mScore += points;
	deltaScore += points;
	// std::cout << "Player score: " << mScore << std::endl;
}
bool Player::IsKeyDown(OIS::KeyCode key) {
	if (mControlType == LOCAL)
		return Input::IsKeyDown(key);
	// clientInput->print();
	switch (key) {
		case OIS::KC_W:
			return clientInput->isKeyDownW;
		case OIS::KC_A:
			return clientInput->isKeyDownA;
		case OIS::KC_S:
			return clientInput->isKeyDownS;
		case OIS::KC_D:
			return clientInput->isKeyDownD;
	}
	return false;
}