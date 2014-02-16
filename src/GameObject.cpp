

#include "GameObject.h"

#include <sstream>


GameObject::GameObject(Game &attachedGame) : game(attachedGame) {
	this->enabled = true;
	Start();
}



void GameObject::Start() {
	transform = new Transform(this, game.getSceneRoot()); 
	
	entity = game.getSceneManager()->createEntity("Ninja", "ninja.mesh");
	game.getSceneRoot()->createChildSceneNode()->attachObject(entity);
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

