#include "Sphere.h"
#include "GameObject.h"

Sphere::Sphere(Game *attachedGame) : GameObject(attachedGame){
	Start();
}

void Sphere::Start() {
	transform = new Transform(this, game->getSceneRoot());
	entity = game->getSceneManager()->createEntity("Sphere", "sphere.mesh");
	transform->sceneNode->attachObject(entity);
	physics = new Physics(*this);
}

void Sphere::Update() {

}

void Sphere::FixedUpdate() {

}

void Sphere::Kill() {
	
}

