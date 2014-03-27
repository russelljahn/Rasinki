#ifndef __Player_H__
#define __Player_H__
#include <btBulletDynamicsCommon.h>
#include <OgreRoot.h>
#include "GameObject.h"
#include <OISEvents.h>
#include <OISKeyboard.h>
#include "Network.h"


/* Forward Declarations */
class GameObject;
struct ClientInput;

enum ControlType { LOCAL, NETWORK };

class Player {
	public:
		Player(ControlType type);
		void scored(int points = 1);
		int getScore() { return mScore; }
		void reset() {mScore = 0;}
		bool IsKeyDown(OIS::KeyCode);

		ClientInput* clientInput;
	private:
		int mScore;
		ControlType mControlType;
};
#endif