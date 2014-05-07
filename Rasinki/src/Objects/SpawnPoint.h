

#ifndef __SPAWNPOINT_H__
#define __SPAWNPOINT_H__

#include "GameObject.h"


class SpawnPoint : public GameObject {
	public:

		SpawnPoint(Game *attachedGame);
		void Start();
		float mass;

};


#endif