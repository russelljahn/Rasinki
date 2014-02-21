#include "Sphere.h"
#include "GameObject.h"

Sphere::Sphere(Game *attachedGame, float radius) : GameObject(attachedGame){
	this->radius = radius;
	Start();
}

void Sphere::Start() {
	scale = 50;
	transform = new Transform(this, game->getSceneRoot());
	entity = game->getSceneManager()->createEntity("Sphere", "sphere.mesh");
	transform->sceneNode->scale(Ogre::Vector3( radius/100, radius/100, radius/100));
	transform->sceneNode->attachObject(entity);
	physics = new Physics(*this, 1 , new btBoxShape(btVector3(1, 1, 1)));
}

void Sphere::Update() {

}

void Sphere::FixedUpdate() {

}

void Sphere::Kill() {
	
}

