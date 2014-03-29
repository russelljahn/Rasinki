#include <sstream>
#include "GameObject.h"



int GameObject::nextAvailableId = 0;



GameObject::GameObject(Game *attachedGame) {
	this->game = attachedGame;
	this->enabled = true;
	this->id = GameObject::nextAvailableId++;

	ostringstream nameCoverter;
	nameCoverter << id;
	this->name = nameCoverter.str();
	this->gameObject = this;

	renderer = new Renderer(this);

	std::cout << "Creating GameObject with id: " << id << std::endl;
	Start();
}
GameObject::GameObject(Game *attachedGame, int playerNum) {
	this->game = attachedGame;
	this->enabled = true;
	this->id = GameObject::nextAvailableId++;
	this->playerNum = playerNum;

	ostringstream nameCoverter;
	nameCoverter << id;
	this->name = nameCoverter.str();
	this->gameObject = this;

	renderer = new Renderer(this);

	std::cout << "Creating GameObject with id: " << id << std::endl;
	Start();
}
GameObject::~GameObject() {
	if (physics != NULL)
		delete physics;
	delete transform;
	delete renderer;
	for (auto componentsIter = components.begin(); componentsIter != components.end(); ++componentsIter) {
       delete (*componentsIter);
    }
	// components.clear();
}
void GameObject::Start() {
	
}



void GameObject::Update() {
	for (auto componentsIter = components.begin(); componentsIter != components.end(); ++componentsIter) {
        (*componentsIter)->Update();
    }
}


void GameObject::FixedUpdate() {
	physics->FixedUpdate();
	/*for (int i = 0; i < components.size(); i++) {
		components[i].FixedUpdate();
	}*/
}


// void GameObject::Kill() {
	// TODO
// }


void GameObject::OnCollision(Ogre::Vector3 point, GameObject* collidedWith) {
	for (auto componentsIter = components.begin(); componentsIter != components.end(); ++componentsIter) {
        (*componentsIter)->OnCollision(point, collidedWith);
    }
}