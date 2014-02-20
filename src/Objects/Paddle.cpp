#include "Paddle.h"
#include "GameObject.h"
#include <btBulletDynamicsCommon.h>

Paddle::Paddle(Game *attachedGame) : GameObject(attachedGame){
	Start();
}

void Paddle::Start() {
	transform = new Transform(this, game->getSceneRoot());
	entity = game->getSceneManager()->createEntity("Paddle", "cube.mesh");
	//transform->sceneNode->scale(2,0.25,2);
	transform->sceneNode->attachObject(entity);
	Ogre::Vector3 halfSize = entity->getBoundingBox().getHalfSize();
	//physics = new Physics(*this, 0, new btBoxShape(btVector3(halfSize.x, halfSize.y, halfSize.z )));
	physics = new Physics(*this);
}

void Paddle::Update() {

}

void Paddle::FixedUpdate() {

}

void Paddle::Kill() {
	
}

