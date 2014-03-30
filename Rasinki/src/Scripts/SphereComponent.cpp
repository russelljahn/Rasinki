#include "SphereComponent.h"
#include <string>


int SphereComponent::numSpheres = 0;

SphereComponent::SphereComponent(GameObject *attachedGameObject) : Script(attachedGameObject) {
	++numSpheres;
	this->speed = attachedGameObject->physics->getLinearVelocity().length();
}

SphereComponent::~SphereComponent() {

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
	gameObject->game->getSoundManager()->playSound1();

	// std::cout << this->gameObject->name << " is colliding with " << collidedWith->name << std::endl;
	if (collidedWith->name == "ground") {
		if (gameObject->game->getNetwork()->isServer) {
		gameObject->game->getNetwork()->SendMessageToClient(ServerMessage(DISABLESPHERE,gameObject->objIndex));
	}
		// this->gameObject->Kill(); //TODO: Use this instead once implemented.
		this->gameObject->renderer->setEnabled(false);
		this->gameObject->physics->setEnabled(false);
		--numSpheres;

		this->~SphereComponent();
	}
}