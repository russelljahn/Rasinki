#include "SphereComponent.h"

SphereComponent::SphereComponent(GameObject *attachedGameObject) : Script(attachedGameObject){
	this->speed = attachedGameObject->physics->getLinearVelocity().length();
}

void SphereComponent::Update() {
	Ogre::Vector3 nvec = gameObject->physics->getLinearVelocity();
	nvec.normalise();
	gameObject->physics->setLinearVelocity(nvec*speed);

	if (gameObject->game->getKeyboard()->isKeyDown(OIS::KC_SPACE)) {
		Ogre::Vector3 vec = gameObject->physics->getLinearVelocity();
		gameObject->physics->setLinearVelocity(Ogre::Vector3(vec.x, vec.y-100, vec.z));
	}
}
void SphereComponent::OnCollision(Ogre::Vector3 point, GameObject* collidedWith) {
	gameObject->game->getSoundManager()->playSound();
}