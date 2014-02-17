

#include "GameObject.h"

#include <sstream>


GameObject::GameObject(Game *attachedGame) {
	this->game = attachedGame;
	this->enabled = true;
	Start();
}



void GameObject::Start() {
	transform = new Transform(this, game->getSceneRoot()); 
	
	entity = game->getSceneManager()->createEntity("Ninja", "ninja.mesh");
	transform->sceneNode->attachObject(entity);
}



void GameObject::Update() {
	// std::cout << "Before: " << transform->getLocalPosition() << std::endl;
	Ogre::Vector3 currentPosition = transform->getLocalPosition();
	float movementSpeed = 1.0f;

	// pos.x += 9;
	// std::cout << "After: " << transform->getLocalPosition() << std::endl;
	if (game->getKeyboard()->isKeyDown(OIS::KC_LEFT) || game->getKeyboard()->isKeyDown(OIS::KC_A)) {
		cout << "Left is down!" << endl;
		currentPosition.x -= movementSpeed;
	}
	if (game->getKeyboard()->isKeyDown(OIS::KC_RIGHT) || game->getKeyboard()->isKeyDown(OIS::KC_D)) {
		cout << "Right is down!" << endl;
		currentPosition.x += movementSpeed;
	}
	if (game->getKeyboard()->isKeyDown(OIS::KC_UP) ||game->getKeyboard()->isKeyDown(OIS::KC_W)) {
		cout << "Up is down!" << endl;
		currentPosition.y += movementSpeed;
	}
	if (game->getKeyboard()->isKeyDown(OIS::KC_DOWN) || game->getKeyboard()->isKeyDown(OIS::KC_S)) {
		cout << "Down is down!" << endl;
		currentPosition.y -= movementSpeed;
	}

	transform->setLocalPosition(currentPosition);

}



void GameObject::FixedUpdate() {
	// TODO
}



void GameObject::Kill() {
	// TODO
}

