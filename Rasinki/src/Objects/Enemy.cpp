#include "Enemy.h"
#include "GameObject.h"
#include "Game.h"

Enemy::Enemy(Game *attachedGame, float mass) : GameObject(attachedGame) {
	this->mass = mass;	
	Start();
}

void Enemy::Start() {
	ostringstream nameCoverter;
	nameCoverter << "Enemy ";
	nameCoverter << id;

	float colliderScale = 50;

	transform = new Transform(this, game->getSceneRoot());

	renderer->entity = game->getSceneManager()->createEntity(nameCoverter.str(), "ninja.mesh");
	transform->sceneNode->attachObject(renderer->entity);

	physics = new Physics(this, mass , new btBoxShape(btVector3(colliderScale,colliderScale,colliderScale)), Ogre::Vector3::ZERO, false);
	renderer->setMaterial("Examples/Ninja");
	gameObject->renderer->mAnimationState = gameObject->renderer->entity->getAnimationState("Walk");
	gameObject->renderer->mAnimationState->setLoop(true);
    gameObject->renderer->mAnimationState->setEnabled(true);

    transform->setWorldScale(Ogre::Vector3(0.5f, 0.5f, 0.5f));
}

