#ifndef __HOMEBASE_H__
#define __HOMEBASE_H__


#include "GameObject.h"

class HomeBase : public GameObject {
	public:
		HomeBase(Game *attachedGame);
		~HomeBase();

		void Start();
		void Update();
		void FixedUpdate();

		void OnCollision(Ogre::Vector3 point, GameObject* collidedWith);

};




#endif