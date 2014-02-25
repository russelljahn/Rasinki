
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
}



void PointBlock::OnCollision(Ogre::Vector3 point, GameObject* collidedWith) {
	this->gameObject->renderer->setEnabled(false);
	this->gameObject->physics->setEnabled(false);
	gameObject->game->getPlayer()->scored(pointsOnDeath);
}