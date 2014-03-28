
#include "PlayerState.h"
#include <iostream>


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

