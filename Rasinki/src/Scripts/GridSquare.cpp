#include "GridSquare.h"
#include <ctime>

GridSquare::GridSquare(GameObject *attachedGameObject) : Script(attachedGameObject) {
    
   	scale = Ogre::Vector3(5, .25, 5);
    this->gameObject->transform->setLocalScale(scale);

	int random = rand()%100;
	if (random < 33) {
		this->gameObject->renderer->setMaterial("Examples/Chrome_Blue");
	}
	else if (random < 66) {
		this->gameObject->renderer->setMaterial("Examples/Chrome_Red");
	}
	else {
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