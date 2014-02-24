
#include "PaddleScript.h"



PaddleScript::PaddleScript(GameObject *attachedGameObject) : Script(attachedGameObject) {
};



void PaddleScript::Start() {
	Script::Start();
}



void PaddleScript::Update() {
	Script::Update();
	gameObject->physics->setLinearVelocity(Ogre::Vector3(0, 0, 0));
	float movementSpeed = 1500.0f;

	if (gameObject->game->getKeyboard()->isKeyDown(OIS::KC_LEFT) || gameObject->game->getKeyboard()->isKeyDown(OIS::KC_A)) {
		Ogre::Vector3 veloc = gameObject->physics->getLinearVelocity();
		veloc.x = -movementSpeed;
		gameObject->physics->setLinearVelocity(veloc);
		std::cout << "Left" << std::endl;
	}
	if (gameObject->game->getKeyboard()->isKeyDown(OIS::KC_RIGHT) || gameObject->game->getKeyboard()->isKeyDown(OIS::KC_D)) {
		Ogre::Vector3 veloc = gameObject->physics->getLinearVelocity();
		veloc.x = movementSpeed;
		gameObject->physics->setLinearVelocity(veloc);
		std::cout << "Right" << std::endl;
	}
	if (gameObject->game->getKeyboard()->isKeyDown(OIS::KC_UP) || gameObject->game->getKeyboard()->isKeyDown(OIS::KC_W)) {
		Ogre::Vector3 veloc = gameObject->physics->getLinearVelocity();
		veloc.z = -movementSpeed;
		gameObject->physics->setLinearVelocity(veloc);
		std::cout << "Up" << std::endl;
	}
	if (gameObject->game->getKeyboard()->isKeyDown(OIS::KC_DOWN) || gameObject->game->getKeyboard()->isKeyDown(OIS::KC_S)) {
		Ogre::Vector3 veloc = gameObject->physics->getLinearVelocity();
		veloc.z = movementSpeed;
		gameObject->physics->setLinearVelocity(veloc);
		std::cout << "Right" << std::endl;
	}
}
void PaddleScript::OnCollision(Ogre::Vector3 point, GameObject* collidedWith) {

}