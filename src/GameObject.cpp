
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
	Start();
}



void GameObject::Start() {
	transform = new Transform(this, game->getSceneRoot()); 
	
	entity = game->getSceneManager()->createEntity("Ninja", "ninja.mesh");
	transform->sceneNode->attachObject(entity);
}



void GameObject::Update() {

	cout << "Updating GameObject '" << this->name << "'!" << endl;

	for (auto componentsIter = components.begin(); componentsIter != components.end(); ++componentsIter) {
        (*componentsIter)->Update();
    }


}



void GameObject::FixedUpdate() {
	// TODO
}



void GameObject::Kill() {
	// TODO
}

