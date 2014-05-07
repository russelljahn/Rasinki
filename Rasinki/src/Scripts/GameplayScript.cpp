
#include "GameplayScript.h"
#include "../Time.h"

bool GameplayScript::gameOver = false;
float GameplayScript::gameOverTime = 0;

GameplayScript::GameplayScript(GameObject *attachedGameObject) : Script(attachedGameObject) {
	Script::Start();
};


GameplayScript::~GameplayScript() {
	GameplayScript::gameOver = false;
	GameplayScript::gameOverTime = 0;
};



void GameplayScript::Start() {
	Script::Start();
}



void GameplayScript::Update() {
	std::cout << "GameplayScript update begin" << std::endl;
	Script::Update();

	// std::cout << "SphereComponent::numSpheres: " << SphereComponent::numSpheres << std::endl;
	
	if (!GameplayScript::IsGameOver()) {
		GameplayScript::gameOver = true;
		GameplayScript::gameOverTime = Time::time;
		gameObject->game->getSoundManager()->playSound3();
	}
	std::cout << "GameplayScript update begin" << std::endl;
}


float GameplayScript::GetGameOverTime() {
	return GameplayScript::gameOverTime;
}



bool GameplayScript::IsGameOver() {
	return gameOver;
}