
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
	if (gameObject->game->getKeyboard()->isKeyDown(OIS::KC_LEFT)) {
		cout << "Left is down!" << endl;
		currentPosition.x -= movementSpeed;
	}
	if (gameObject->game->getKeyboard()->isKeyDown(OIS::KC_RIGHT)) {
		cout << "Right is down!" << endl;
		currentPosition.x += movementSpeed;
	}
	if (gameObject->game->getKeyboard()->isKeyDown(OIS::KC_UP)) {
		cout << "Up is down!" << endl;
		currentPosition.z -= movementSpeed;
	}
	if (gameObject->game->getKeyboard()->isKeyDown(OIS::KC_DOWN)) {
		cout << "Down is down!" << endl;
	}
	if (gameObject->game->getKeyboard()->isKeyDown(OIS::KC_SPACE)) {
		currentPosition.y += movementSpeed;
	}

	gameObject->transform->setLocalPosition(currentPosition);
}