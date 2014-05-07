#include "SpawnPoint.h"
#include "GameObject.h"
#include "Game.h"

SpawnPoint::SpawnPoint(Game *attachedGame) : GameObject(attachedGame) {
	this->mass = mass;	
	Start();
}

void SpawnPoint::Start() {
	ostringstream nameCoverter;
	nameCoverter << "SpawnPoint ";
	nameCoverter << id;

	float colliderScale = 50;

	transform = new Transform(this, game->getSceneRoot());

	renderer->entity = game->getSceneManager()->createEntity(nameCoverter.str(), "SpawnPoint.mesh");
	transform->sceneNode->attachObject(renderer->entity);

	physics = new Physics(this, 0 , new btBoxShape(btVector3(colliderScale,colliderScale,colliderScale)), Ogre::Vector3::ZERO, false);
	renderer->setMaterial("Chrome_Red");
	transform->setWorldScale(Ogre::Vector3(5, 5, 5));
}

