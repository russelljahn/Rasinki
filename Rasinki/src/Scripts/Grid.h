
#ifndef __GRID_SCRIPT_H__
#define __GRID_SCRIPT_H__

#include "../Components/Script.h"
#include "GridSquare.h"

/* 
	Grid containing squares w/ towers.
*/
class Grid : public Script {

	public:
		Grid(GameObject *attachedGameObject);

		void Start(void);
		void Update(void);
		void OnCollision(Ogre::Vector3 point, GameObject* collidedWith);
		GridSquare* gridSquareAtPos(Ogre::Vector3 worldPos);
	private:
		int width;
		int depth;
		GridSquare** squares; // Pointer to matrix of GridSquare pointers. Matrix is really a long array mapping values in form of a matrix.
};


#endif