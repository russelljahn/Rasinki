
#ifndef __PLAYER_SCRIPT_H__
#define __PLAYER_SCRIPT_H__

#include "../Components/Script.h"
#include "../PlayerState.h"

class PlayerState;

/* 
	Code for a player's runtime behaviour, including a character controller.
*/
class PlayerScript : public Script {

	public:
		PlayerScript(GameObject *attachedGameObject);

		void Start(void);
		void Update(void);
		void OnCollision(Ogre::Vector3 point, GameObject* collidedWith);

		PlayerState *previousPlayerState;
		PlayerState *currentPlayerState;
	private:
		bool up;
		bool down;
		bool left;
		bool right;
		Player *controllingPlayer;
};


#endif