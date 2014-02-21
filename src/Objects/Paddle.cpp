#include "Paddle.h"
#include "GameObject.h"
#include <btBulletDynamicsCommon.h>

Paddle::Paddle(Game *attachedGame) : GameObject(attachedGame){
	Start();
}

void Paddle::Start() {
	scale = 25;
	transform = new Transform(this, game->getSceneRoot());
	entity = game->getSceneManager()->createEntity("Paddle", "cube.mesh");
	//transform->sceneNode->scale(2,0.25,2);
	transform->sceneNode->attachObject(entity);
	Ogre::Vector3 halfExtents = transform->getLocalScale()/2.0f;
	physics = new Physics(*this, 100, new btBoxShape(btVector3(scale, scale, scale)), Ogre::Vector3::ZERO);
}

void Paddle::Update() {

}

void Paddle::FixedUpdate() {

}

void Paddle::Kill() {
	
}

