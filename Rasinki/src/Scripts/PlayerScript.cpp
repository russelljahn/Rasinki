
#include "PlayerScript.h"



PlayerScript::PlayerScript(GameObject *attachedGameObject) : Script(attachedGameObject) {
	controllingPlayer = (gameObject->game->playerList[gameObject->playerNum]);
	Start();
};



void PlayerScript::Start() {
	Script::Start();
	currentPlayerState = new Standing(this);
	forward = new Ogre::Vector3(0, 0, 0);
	movementSpeed = 30.0f;
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
	}
}


void PlayerScript::OnCollision(Ogre::Vector3 point, GameObject* collidedWith) {

}