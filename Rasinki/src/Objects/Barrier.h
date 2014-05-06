#ifndef __BARRIER_H__
#define __BARRIER_H__

#include "../Scripts/GridSquare.h"
#include "../Scripts/Grid.h"



#include "GameObject.h"

class Barrier : public GameObject {
	public:
		Barrier(Game *attachedGame);
		~Barrier();

		void Start();
		void Update();
		void FixedUpdate();

		void OnCollision(Ogre::Vector3 point, GameObject* collidedWith);

		Grid *grid;
};




#endif