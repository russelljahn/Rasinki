#include "Mountain.h"
#include "GameObject.h"
#include "Game.h"

Mountain::Mountain(Game *attachedGame) : GameObject(attachedGame) {
	this->mass = mass;	
	Start();
}

void Mountain::Start() {
	ostringstream nameCoverter;
	nameCoverter << "Mountain ";
	nameCoverter << id;

	float colliderScale = 50;

	transform = new Transform(this, game->getSceneRoot());

	renderer->entity = game->getSceneManager()->createEntity(nameCoverter.str(), "Mountain.mesh");
	transform->sceneNode->attachObject(renderer->entity);

	physics = new Physics(this, 0 , new btBoxShape(btVector3(colliderScale,colliderScale,colliderScale)), Ogre::Vector3::ZERO, false);
	renderer->setMaterial("Examples/Rockwall");
	transform->setWorldScale(Ogre::Vector3(100, 100, 100));
}

