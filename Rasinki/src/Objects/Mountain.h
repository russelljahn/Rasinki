

#ifndef __MOUNTAIN_H__
#define __MOUNTAIN_H__

#include "GameObject.h"


class Mountain : public GameObject {
	public:

		Mountain(Game *attachedGame);
		void Start();
		float mass;

};


#endif