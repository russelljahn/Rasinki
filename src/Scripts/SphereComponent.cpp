#include "SphereComponent.h"
#include <string>

int SphereComponent::numSpheres = 0;

SphereComponent::SphereComponent(GameObject *attachedGameObject) : Script(attachedGameObject) {
	++SphereComponent::numSpheres;
}

void SphereComponent::OnCollision(Ogre::Vector3 point, GameObject* collidedWith) {
	gameObject->game->getSoundManager()->playSound();

	// std::cout << this->gameObject->name << " is colliding with " << collidedWith->name << std::endl;
	if (collidedWith->name == "ground") {
		// this->gameObject->Kill(); //TODO: Use this instead once implemented.
		this->gameObject->renderer->setEnabled(false);
		this->gameObject->physics->setEnabled(false);

		--SphereComponent::numSpheres;
	}
}