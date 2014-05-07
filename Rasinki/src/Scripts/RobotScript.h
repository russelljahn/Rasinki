
#ifndef __Robot_SCRIPT_H__
#define __Robot_SCRIPT_H__

#include "../Components/Script.h"
#include "Grid.h"
#include "GridSquare.h"
#include "../Objects/Cube.h"
#include "../Objects/Tower.h"
#include "../Objects/Barrier.h"


/* 
	Code to control Robot behavior.
*/
class RobotScript : public Script {

	public:
		RobotScript(GameObject *attachedGameObject);

		//RobotState *previousRobotState; // Only needed for memory deallocation right now
    	//RobotState *currentRobotState;

		void Start(void);
		void Update(void);
		void OnCollision(Ogre::Vector3 point, GameObject* collidedWith);
		void HandleTower();

		Grid *grid;
		Cube *glowTile;
	private:
		bool up;
		bool down;
		bool left;
		bool right;
		bool jumping;
		bool falling;
};


#endif