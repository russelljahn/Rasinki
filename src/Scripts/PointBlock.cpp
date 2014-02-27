
#include "PointBlock.h"



PointBlock::PointBlock(GameObject *attachedGameObject) : Script(attachedGameObject) {


	pointsOnDeath = 1;
	this->gameObject->renderer->setMaterial("Examples/Chrome");
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