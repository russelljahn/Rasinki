
#ifndef __PADDLE_SCRIPT_H__
#define __PADDLE_SCRIPT_H__

#include "../Components/Script.h"

/* 
	Code to control paddle behavior.
*/
class PaddleScript : public Script {

	public:
		PaddleScript(GameObject *attachedGameObject);

		void Start(void);
		void Update(void);
	private:
		bool up;
		bool down;
		bool left;
		bool right;
};


#endif