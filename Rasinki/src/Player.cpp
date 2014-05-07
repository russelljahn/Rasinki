#include "Player.h"

Player::Player(ControlType type) {
	mControlType = type;
	mScore = 99; //Debug purposes
  mGold = 100; //Debug purposes
	currentHealth = 10;
	deltaScore = 0;
	clientInput = NULL;
}
void Player::scored(int points) {
	mScore += points;
	deltaScore += points;
	std::cout << "Player score: " << mScore << std::endl;
}
bool Player::IsKeyDown(OIS::KeyCode key) {
	if (mControlType == LOCAL)
		return Input::IsKeyDown(key);
	return false;
}
void Player::loseHealth(){
	currentHealth--;
	std::cout<< "Player lost health, current health: " << currentHealth <<std::endl;
}
