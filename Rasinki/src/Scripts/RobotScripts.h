
#ifndef __Robot_SCRIPT_H__
#define __Robot_SCRIPT_H__

#include "../Components/Script.h"

/* 
	Code to control Robot behavior.
*/
class RobotScript : public Script {

	public:
		RobotScript(GameObject *attachedGameObject);

		void Start(void);
		void Update(void);
		void OnCollision(Ogre::Vector3 point, GameObject* collidedWith);
	private:
		bool up;
		bool down;
		bool left;
		bool right;
};


#endif