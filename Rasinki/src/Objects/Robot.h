
#ifndef __ROBOT_H__
#include "GameObject.h"

class Robot : public GameObject {
	public:
		Robot(Game *attachedGame);
		Robot(Game *attachedGame, int pNum);
		void Start();
		void Update();
		void FixedUpdate();

		void Kill();
		void OnCollision(Ogre::Vector3 point, GameObject* collidedWith);
};

#endif