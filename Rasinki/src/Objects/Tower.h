#ifndef __TOWER_H__
#define __TOWER_H__




#include "GameObject.h"

class Tower : public GameObject {
	public:
		Tower(Game *attachedGame);
		Tower(Game *attachedGame, int pNum);
		void Start();
		void Update();
		void FixedUpdate();

		void Kill();
		void OnCollision(Ogre::Vector3 point, GameObject* collidedWith);
};




#endif