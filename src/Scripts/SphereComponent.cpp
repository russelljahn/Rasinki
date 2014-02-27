#include "SphereComponent.h"

SphereComponent::SphereComponent(GameObject *attachedGameObject) : Script(attachedGameObject){

}

void SphereComponent::OnCollision(Ogre::Vector3 point, GameObject* collidedWith) {
	gameObject->game->getSoundManager()->playSound();
}