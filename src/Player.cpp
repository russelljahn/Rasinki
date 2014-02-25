#include "Player.h"

Player::Player() {
	mScore = 0;
}
void Player::scored(int points) {
	mScore += points;
	std::cout << "Player score: " << mScore << std::endl;
}