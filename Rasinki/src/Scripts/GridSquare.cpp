#include "GridSquare.h"
#include <ctime>

GridSquare::GridSquare(GameObject *attachedGameObject) : Script(attachedGameObject) {
    
   	scale = Ogre::Vector3(2.5, .125, 2.5);
    this->gameObject->transform->setLocalScale(scale);
    this->gameObject->physics->setColliderScale(scale);

	int random = rand()%100;
	if (random < 33) {
		this->gameObject->renderer->setMaterial("Grass1");
	}
	else if (random < 66) {
		this->gameObject->renderer->setMaterial("Sand1");
	}
	else {
		this->gameObject->renderer->setMaterial("Rock1");
	}

	occupant = NULL;
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
	// this->gameObject->renderer->setEnabled(false);
	// if (gameObject->game->getNetwork()->isServer) {
	// 	gameObject->game->getNetwork()->SendMessageToClient(ServerMessage(DISABLEOBJECT,gameObject->objIndex));
	// }
	// //hit = true;
	// //gameObject->physics->setGravity(Ogre::Vector3(0, -98, 0));
	// gameObject->game->getSoundManager()->playSound2();
}

Ogre::Vector3 GridSquare::getBounds() {
	return scale * 100;
}

bool GridSquare::IsOccupied() {
    return occupant != NULL;
}