#include "Cube.h"
#include "GameObject.h"
#include "Game.h"

Cube::Cube(Game *attachedGame, float mass) : GameObject(attachedGame) {
	this->mass = mass;	
	Start();
}

void Cube::Start() {
	ostringstream nameCoverter;
	nameCoverter << "cube ";
	nameCoverter << id;

	float colliderScale = 50;

	transform = new Transform(this, game->getSceneRoot());

	renderer->entity = game->getSceneManager()->createEntity(nameCoverter.str(), "cube.mesh");
	transform->sceneNode->attachObject(renderer->entity);

	physics = new Physics(this, mass , new btBoxShape(btVector3(colliderScale,colliderScale,colliderScale)), Ogre::Vector3::ZERO);
	renderer->setMaterial("Examples/Rockwall");
}

