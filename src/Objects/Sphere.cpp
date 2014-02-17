#include "Sphere.h"
#include "GameObject.h"

Sphere::Sphere(Game *attachedGame, std::string objectType) : GameObject(attachedGame, objectType){
	
}

void Sphere::Start() {
	entity = game->getSceneManager()->createEntity("Sphere", "sphere.mesh");
	transform->sceneNode->attachObject(entity);
	physics = new Physics(*this, 0.2);
}