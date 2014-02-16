

#include "GameObject.h"



GameObject::GameObject(Game &attachedGame) : game(attachedGame) {
	this->enabled = true;
}



void GameObject::Start() {
	transform = new Transform(this, game.getSceneRoot()); 
	// components.push_back(newTransform);
	// this->transform = static_cast<Transform *>(&components.back());
}



void GameObject::Update() {
	// TODO
}



void GameObject::FixedUpdate() {
	// TODO
}



void GameObject::Kill() {
	// TODO
}

