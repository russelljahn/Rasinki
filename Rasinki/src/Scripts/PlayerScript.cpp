
#include "PlayerScript.h"



PlayerScript::PlayerScript(GameObject *attachedGameObject) : Script(attachedGameObject) {
	controllingPlayer = (gameObject->game->playerList[gameObject->playerNum]);
	Start();
};



void PlayerScript::Start() {
	Script::Start();
	currentPlayerState = new PlayerState(this);
}



void PlayerScript::Update() {
	if (gameObject->game->getNetwork()->isServer) {
		Script::Update();

		previousPlayerState = currentPlayerState;
		currentPlayerState = currentPlayerState->NextState();
		currentPlayerState->Update();

		// Clean up memory allocation if necessary
		if (previousPlayerState != currentPlayerState) {
			delete previousPlayerState;
		}

		// if (controllingPlayer->IsKeyDown(OIS::KC_LEFT) || controllingPlayer->IsKeyDown(OIS::KC_A)) {
		// }
		// if (controllingPlayer->IsKeyDown(OIS::KC_RIGHT) || controllingPlayer->IsKeyDown(OIS::KC_D)) {
		// }
		// if (controllingPlayer->IsKeyDown(OIS::KC_UP) || controllingPlayer->IsKeyDown(OIS::KC_W)) {
		// }
		// if (controllingPlayer->IsKeyDown(OIS::KC_DOWN) || controllingPlayer->IsKeyDown(OIS::KC_S)) {
		// }
	}
}


void PlayerScript::OnCollision(Ogre::Vector3 point, GameObject* collidedWith) {

}