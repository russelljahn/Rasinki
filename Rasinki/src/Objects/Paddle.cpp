#include "Paddle.h"
#include "GameObject.h"
#include <btBulletDynamicsCommon.h>

Paddle::Paddle(Game *attachedGame) : GameObject(attachedGame){
	Start();
}

void Paddle::Start() {

	ostringstream nameCoverter;
	nameCoverter << "paddle ";
	nameCoverter << id;

	float scale = 50;
	transform = new Transform(this, game->getSceneRoot());
	renderer->entity = game->getSceneManager()->createEntity(nameCoverter.str(), "cube.mesh");
	transform->sceneNode->attachObject(renderer->entity);
	Ogre::Vector3 halfExtents = transform->getLocalScale()/2.0f;
	physics = new Physics(this, 1, new btBoxShape(btVector3(scale, scale, scale)));
	physics->setLinearFactor(Ogre::Vector3(1,0,1));

	renderer->setMaterial("Examples/Rockwall");
}

void Paddle::Update() {

}

void Paddle::FixedUpdate() {

}

void Paddle::Kill() {
	
}