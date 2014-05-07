#include "Enemy.h"
#include "GameObject.h"
#include "Game.h"

Enemy::Enemy(Game *attachedGame, float mass) : GameObject(attachedGame) {
	this->mass = mass;	
	Start();
}

void Enemy::Start() {
	ostringstream nameCoverter;
	nameCoverter << "cube ";
	nameCoverter << id;

	float colliderScale = 50;

	transform = new Transform(this, game->getSceneRoot());

	renderer->entity = game->getSceneManager()->createEntity(nameCoverter.str(), "cube.mesh");
	transform->sceneNode->attachObject(renderer->entity);
	physics = new Physics(this, mass , new btBoxShape(btVector3(colliderScale,colliderScale,colliderScale)), Ogre::Vector3::ZERO, false);
	renderer->setMaterial("Examples/Rockwall");
}

