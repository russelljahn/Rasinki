

#include "GameObject.h"

#include <sstream>


GameObject::GameObject(Game &attachedGame) : game(attachedGame) {
	this->enabled = true;
	Start();
}



void GameObject::Start() {
	transform = new Transform(this, game.getSceneRoot()); 
	
	entity = game.getSceneManager()->createEntity("Ninja", "ninja.mesh");
	transform->sceneNode->attachObject(entity);
}



void GameObject::Update() {
	// std::cout << "Before: " << transform->getLocalPosition() << std::endl;
	// Ogre::Vector3 pos = transform->getLocalPosition();
	// pos.x += 9;
	// transform->setLocalPosition(pos);
	// std::cout << "After: " << transform->getLocalPosition() << std::endl;
}



void GameObject::FixedUpdate() {
	// TODO
}



void GameObject::Kill() {
	// TODO
}

