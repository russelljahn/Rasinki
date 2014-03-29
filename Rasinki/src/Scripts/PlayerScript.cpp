
#include "PlayerScript.h"
#include <cassert>


PlayerScript::PlayerScript(GameObject *attachedGameObject) : Script(attachedGameObject) {
	controllingPlayer = (gameObject->game->playerList[gameObject->playerNum]);
	this->camera = NULL;
	Start();
};


void PlayerScript::setCamera(Ogre::Camera *camera) {
	this->camera = camera;

    camera->setPosition(gameObject->physics->getWorldPosition());
    // Look back along -Z
    camera->lookAt(Ogre::Vector3(0,-200,0));
    camera->setNearClipDistance(5);

}



void PlayerScript::Start() {
	Script::Start();
	currentPlayerState = new Standing(this);
	forward = new Ogre::Vector3(0, 0, 0);
	movementSpeed = 30.0f;
}



void PlayerScript::Update() {
	if (gameObject->game->getNetwork()->isServer) {

		assert(camera != NULL);
		updateCamera();

		Script::Update();

		previousPlayerState = currentPlayerState;
		currentPlayerState = currentPlayerState->NextState();
		currentPlayerState->Update();

		// Clean up memory allocation if necessary
		if (previousPlayerState != currentPlayerState) {
			delete previousPlayerState;
		}
	}
}


void PlayerScript::updateCamera() {
	cout << "gameObject->transform->getWorldPosition(): " << gameObject->physics->getWorldPosition() << endl;
    camera->setPosition(gameObject->physics->getWorldPosition());

    // Ogre::Vector3 forward = gameObject->transform->sceneNode->getOrientation() * Ogre::Vector3(1, 0, 0); // Would be Vector3(0, 0, -1), but compensating for initial robot rotation.
    // camera->setOrientation(gameObject->transform->sceneNode->getOrientation());
}


void PlayerScript::OnCollision(Ogre::Vector3 point, GameObject* collidedWith) {

}