
#ifndef __GAMEPLAY_SCRIPT_H__
#define __GAMEPLAY_SCRIPT_H__

#include "../Components/Script.h"

/* 
	Code to control Gameplay behavior.
*/
class GameplayScript : public Script {

	public:
		GameplayScript(GameObject *attachedGameObject);

		void Start(void);
		void Update(void);
};


#endif