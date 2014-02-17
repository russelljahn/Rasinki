#include <sstream>
#include "GameObject.h"



int GameObject::nextAvailableId = 0;



GameObject::GameObject(Game *attachedGame, std::string objectType) {
	this->game = attachedGame;
	this->enabled = true;
	this->id = GameObject::nextAvailableId++;
	this->objectType = objectType;

	ostringstream nameCoverter;
	nameCoverter << id;
	this->name = nameCoverter.str();
	Start();
}


void GameObject::Start() {
	transform = new Transform(this, game->getSceneRoot());
	physics = new Physics(*this, 0.2);	
}



void GameObject::Update() {
	cout << "Updating GameObject '" << this->name << "'!" << endl;

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


void GameObject::Kill() {
	// TODO
}

