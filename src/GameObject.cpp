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

	if (objectType == "ninja")
	{
		entity = game->getSceneManager()->createEntity("Ninja", "ninja.mesh");
		transform->sceneNode->attachObject(entity);
	}
	else if (objectType == "sphere")
	{
		entity = game->getSceneManager()->createEntity("Sphere", "sphere.mesh");
		transform->sceneNode->attachObject(entity);
	}
	else if (objectType == "cube")
	{
		entity = game->getSceneManager()->createEntity("Cube", "cube.mesh");
		transform->sceneNode->attachObject(entity);
		transform->sceneNode->scale(2,.25,2);
	}
	else
	{
		cout << "Specify object type" << endl;
	} 
	
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

