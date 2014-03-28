
#include "GameState.h"
#include <iostream>



void GameState::Update() {
	using namespace std;
	cout << "GameState::Update()!" << endl;
}

GameState* GameState::NextState() {
	return this;
}
