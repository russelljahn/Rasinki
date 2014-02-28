
#include "PaddleScript.h"



PaddleScript::PaddleScript(GameObject *attachedGameObject) : Script(attachedGameObject) {
	Start();
};



void PaddleScript::Start() {
	Script::Start();
}



void PaddleScript::Update() {
	Script::Update();
	gameObject->physics->setLinearVelocity(Ogre::Vector3(0, 0, 0));
	float movementSpeed = 1500.0f;
	int side = gameObject->game->camSide();

	if (gameObject->game->getKeyboard()->isKeyDown(OIS::KC_LEFT) || gameObject->game->getKeyboard()->isKeyDown(OIS::KC_A)) {
		Ogre::Vector3 veloc = gameObject->physics->getLinearVelocity();

		switch(side)
		{
			case 1:
				veloc.x = -movementSpeed;
				break;
			case 2:
				veloc.z = movementSpeed;
				break;
			case 3:
				veloc.x = movementSpeed;
				break;
			case 4:
				veloc.z = -movementSpeed;
				break;
			default:
				break;
		}

		gameObject->physics->setLinearVelocity(veloc);
	}
	if (gameObject->game->getKeyboard()->isKeyDown(OIS::KC_RIGHT) || gameObject->game->getKeyboard()->isKeyDown(OIS::KC_D)) {
		Ogre::Vector3 veloc = gameObject->physics->getLinearVelocity();

		switch(side)
		{
			case 1:
				veloc.x = movementSpeed;
				break;
			case 2:
				veloc.z = -movementSpeed;
				break;
			case 3:
				veloc.x = -movementSpeed;
				break;
			case 4:
				veloc.z = movementSpeed;
				break;
			default:
				break;
		}

		gameObject->physics->setLinearVelocity(veloc);
	}
	if (gameObject->game->getKeyboard()->isKeyDown(OIS::KC_UP) || gameObject->game->getKeyboard()->isKeyDown(OIS::KC_W)) {
		Ogre::Vector3 veloc = gameObject->physics->getLinearVelocity();

		switch(side)
		{
			case 1:
				veloc.z = -movementSpeed;
				break;
			case 2:
				veloc.x = -movementSpeed;
				break;
			case 3:
				veloc.z = movementSpeed;
				break;
			case 4:
				veloc.x = movementSpeed;
				break;
			default:
				break;
		}

		gameObject->physics->setLinearVelocity(veloc);
	}
	if (gameObject->game->getKeyboard()->isKeyDown(OIS::KC_DOWN) || gameObject->game->getKeyboard()->isKeyDown(OIS::KC_S)) {
		Ogre::Vector3 veloc = gameObject->physics->getLinearVelocity();
		
		switch(side)
		{
			case 1:
				veloc.z = movementSpeed;
				break;
			case 2:
				veloc.x = movementSpeed;
				break;
			case 3:
				veloc.z = -movementSpeed;
				break;
			case 4:
				veloc.x = -movementSpeed;
				break;
			default:
				break;
		}

		gameObject->physics->setLinearVelocity(veloc);
	}
}



void PaddleScript::OnCollision(Ogre::Vector3 point, GameObject* collidedWith) {

}