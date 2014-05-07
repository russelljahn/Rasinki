#include "HomeBase.h"
#include "GameObject.h"
#include "Cube.h"
#include "../Scripts/EnemyScript.h"
#include <btBulletDynamicsCommon.h>

HomeBase::HomeBase(Game *attachedGame) : GameObject(attachedGame){
	Start();
}
HomeBase::~HomeBase() {

}
void HomeBase::Start() {

	ostringstream nameCoverter;
	nameCoverter << "HomeBase ";
	nameCoverter << id;

	float scale = 35;
	transform = new Transform(this, game->getSceneRoot());
	renderer->entity = game->getSceneManager()->createEntity(nameCoverter.str(), "Tower.mesh");
	transform->sceneNode->attachObject(renderer->entity);
	// Ogre::Vector3 halfExtents = transform->getLocalScale()/2.0f;
	physics = new Physics(this, 0, new btBoxShape(btVector3(scale, scale, scale)), Ogre::Vector3::ZERO, false);
	// physics->setLinearFactor(Ogre::Vector3(1,0,1));

	renderer->setMaterial("Chrome_Red");

	transform->setWorldScale(Ogre::Vector3(2.5, 2.5, 2.5));
	transform->setLocalRotationEuler(Ogre::Vector3(0, 180, 0));

}


void HomeBase::Update() {
	GameObject::Update();
}

void HomeBase::FixedUpdate() {

}

