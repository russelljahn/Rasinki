#include "Barrier.h"
#include "GameObject.h"
#include "Cube.h"
#include "../Scripts/EnemyScript.h"
#include <btBulletDynamicsCommon.h>

Barrier::Barrier(Game *attachedGame) : GameObject(attachedGame){
	Start();
}
Barrier::~Barrier() {

}
void Barrier::Start() {

	ostringstream nameCoverter;
	nameCoverter << "Barrier ";
	nameCoverter << id;
	grid = NULL;

	float scale = 35;
	transform = new Transform(this, game->getSceneRoot());
	renderer->entity = game->getSceneManager()->createEntity(nameCoverter.str(), "cube.mesh");
	transform->sceneNode->attachObject(renderer->entity);
	Ogre::Vector3 halfExtents = transform->getLocalScale()/2.0f;
	physics = new Physics(this, 0, new btBoxShape(btVector3(scale, scale, scale)));
	physics->setLinearFactor(Ogre::Vector3(1,0,1));

	renderer->setMaterial("Brick1");

	transform->setWorldScale(Ogre::Vector3(2.5, 1, 2.5));

}


void Barrier::Update() {
	GameObject::Update();
}

void Barrier::FixedUpdate() {

}

