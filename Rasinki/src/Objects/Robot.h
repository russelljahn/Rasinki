#ifndef __ROBOT_H__
#define __ROBOT_H__

#include "GameObject.h"

class Robot : public GameObject {
	public:
		Robot(Game *attachedGame);
		void Start();
		void Update();
		void FixedUpdate();

		void Kill();
		void OnCollision(Ogre::Vector3 point, GameObject* collidedWith);
};

#endif