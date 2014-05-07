

#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "GameObject.h"


class Enemy : public GameObject {
	public:

		Enemy(Game *attachedGame, float mass);
		void Start();
		float mass;

};


#endif