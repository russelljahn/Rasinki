
#include "GameplayScript.h"
#include "SphereComponent.h"


GameplayScript::GameplayScript(GameObject *attachedGameObject) : Script(attachedGameObject) {
	Start();

};



void GameplayScript::Start() {
	Script::Start();
}



void GameplayScript::Update() {
	Script::Update();
	
	std::cout << "Spheres left in the game: " << SphereComponent::numSpheres << std::endl;
}

