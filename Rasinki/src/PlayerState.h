#ifndef __PLAYERSTATE_CLASS_H__
#define __PLAYERSTATE_CLASS_H__

#include "GameState.h"
#include "Scripts/PlayerScript.h"

class PlayerScript;

/* 
	GameState specialized for holding player state, such as am I standing, jumping, walking, etc.
*/
class PlayerState : public GameState {

	public:
		PlayerScript * playerScript;

		PlayerState(PlayerScript *playerScript);
		virtual void Update();
		virtual PlayerState* NextState();
};

#endif