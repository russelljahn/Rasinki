#ifndef __Player_H__
#define __Player_H__
#include <btBulletDynamicsCommon.h>
#include <OgreRoot.h>
#include "GameObject.h"

/* Forward Declarations */
class GameObject;

class Player {
	public:
		Player();
		void scored(int points = 1);
		int getScore() { return mScore; }
		void reset() {mScore = 0;}
	private:
		int mScore;
};
#endif