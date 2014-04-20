#include "EnemyScript.h"

EnemyScript::EnemyScript(GameObject *attachedGameObject) : Script(attachedGameObject) {
	Start();
	moveSpeed = 150.0f;
	destination = gameObject->transform->getWorldPosition();
	gameObject->renderer->setMaterial("Examples/Chrome_Red");
}

void EnemyScript::Start() {
	
}
void EnemyScript::Update() {
	Ogre::Vector3 veloc = (destination - gameObject->physics->getWorldPosition());
	veloc.normalise();
	veloc *= moveSpeed;
	gameObject->physics->setLinearVelocity(veloc);
}
