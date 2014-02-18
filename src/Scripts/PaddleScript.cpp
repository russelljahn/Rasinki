
#include "PaddleScript.h"



PaddleScript::PaddleScript(GameObject *attachedGameObject) : Script(attachedGameObject) {
};



void PaddleScript::Start() {
	Script::Start();

}



void PaddleScript::Update() {
	Script::Update();
	
	Ogre::Vector3 currentPosition = gameObject->transform->getLocalPosition();
	float movementSpeed = 1.0f;

	if (gameObject->game->getKeyboard()->isKeyDown(OIS::KC_LEFT) || gameObject->game->getKeyboard()->isKeyDown(OIS::KC_A)) {
		currentPosition.x -= movementSpeed;
	}
	if (gameObject->game->getKeyboard()->isKeyDown(OIS::KC_RIGHT) || gameObject->game->getKeyboard()->isKeyDown(OIS::KC_D)) {
		currentPosition.x += movementSpeed;
	}
	if (gameObject->game->getKeyboard()->isKeyDown(OIS::KC_UP) || gameObject->game->getKeyboard()->isKeyDown(OIS::KC_W)) {
		currentPosition.z -= movementSpeed;
	}
	if (gameObject->game->getKeyboard()->isKeyDown(OIS::KC_DOWN) || gameObject->game->getKeyboard()->isKeyDown(OIS::KC_S)) {
		currentPosition.z += movementSpeed;
	}
	if (gameObject->game->getKeyboard()->isKeyDown(OIS::KC_SPACE)) {
		currentPosition.y += movementSpeed;
	}

	gameObject->transform->setLocalPosition(currentPosition);
}