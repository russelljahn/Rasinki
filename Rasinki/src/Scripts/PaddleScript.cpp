
#include "PaddleScript.h"



PaddleScript::PaddleScript(GameObject *attachedGameObject) : Script(attachedGameObject) {
	controllingPlayer = (gameObject->game->playerList[gameObject->playerNum]);
	Start();
};



void PaddleScript::Start() {
	Script::Start();
}



void PaddleScript::Update() {
	if (gameObject->game->getNetwork()->isServer) {
		Script::Update();
		gameObject->physics->setLinearVelocity(Ogre::Vector3(0, 0, 0));
		float movementSpeed = 1500.0f;
		int side = gameObject->game->camSide();

		if (controllingPlayer->IsKeyDown(OIS::KC_LEFT) || controllingPlayer->IsKeyDown(OIS::KC_A)) {
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
		if (controllingPlayer->IsKeyDown(OIS::KC_RIGHT) || controllingPlayer->IsKeyDown(OIS::KC_D)) {
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
		if (controllingPlayer->IsKeyDown(OIS::KC_UP) || controllingPlayer->IsKeyDown(OIS::KC_W)) {
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
		if (controllingPlayer->IsKeyDown(OIS::KC_DOWN) || controllingPlayer->IsKeyDown(OIS::KC_S)) {
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
}



void PaddleScript::OnCollision(Ogre::Vector3 point, GameObject* collidedWith) {

}