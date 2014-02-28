
#include "PointBlock.h"
#include <ctime>


PointBlock::PointBlock(GameObject *attachedGameObject) : Script(attachedGameObject) {

	int random = rand()%100;

	if (random < 20) {
		pointsOnDeath = 25;
		this->gameObject->renderer->setMaterial("Examples/Chrome_Blue");
	}
	else if (random < 40) {
		pointsOnDeath = 10;
		this->gameObject->renderer->setMaterial("Examples/Chrome_Red");
	}
	else {
		pointsOnDeath = 1;
		this->gameObject->renderer->setMaterial("Examples/Chrome");
	}
};



void PointBlock::Start() {
	Script::Start();
}



void PointBlock::Update() {
	Script::Update();
	if (!this->gameObject->renderer->isEnabled()){
		this->gameObject->physics->setEnabled(false);
	}
}



void PointBlock::OnCollision(Ogre::Vector3 point, GameObject* collidedWith) {
	this->gameObject->renderer->setEnabled(false);
	gameObject->game->getPlayer()->scored(pointsOnDeath);
}