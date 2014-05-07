#ifndef __Player_H__
#define __Player_H__
#include <btBulletDynamicsCommon.h>
#include <OgreRoot.h>
#include "GameObject.h"
#include <OISEvents.h>
#include <OISKeyboard.h>


/* Forward Declarations */
class GameObject;
struct ClientInput;

enum ControlType { LOCAL, NETWORK };

class Player {
	public:
		int deltaScore;

		Player(ControlType type);
		void scored(int points = 1);
		void loseHealth();
		int getScore() { return mScore; }
		int getGold() { return mGold; }
		void reset() {mScore = 0;}
		void changeGold(int ammount) {
			mGold += ammount;
		}
		bool IsKeyDown(OIS::KeyCode);

		
		int currentHealth;

		ClientInput* clientInput;
	private:
		int mScore;
    	int mGold;
		ControlType mControlType;
};
#endif
