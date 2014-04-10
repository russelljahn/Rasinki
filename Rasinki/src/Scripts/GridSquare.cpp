#include "GridSquare.h"
#include <ctime>

GridSquare::GridSquare(GameObject *attachedGameObject) : Script(attachedGameObject) {

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



void GridSquare::Start() {
	Script::Start();
}



void GridSquare::Update() {
	Script::Update();
	if (!this->gameObject->renderer->isEnabled()) {
		this->gameObject->physics->setEnabled(false);
	}
}



void GridSquare::OnCollision(Ogre::Vector3 point, GameObject* collidedWith) {
	this->gameObject->renderer->setEnabled(false);
	if (gameObject->game->getNetwork()->isServer) {
		gameObject->game->getNetwork()->SendMessageToClient(ServerMessage(DISABLEOBJECT,gameObject->objIndex));
	}
	//hit = true;
	//gameObject->physics->setGravity(Ogre::Vector3(0, -98, 0));
	gameObject->game->getPlayer()->scored(pointsOnDeath);
	gameObject->game->getSoundManager()->playSound2();
}