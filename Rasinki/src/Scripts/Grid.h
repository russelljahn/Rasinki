
#ifndef __GRID_SCRIPT_H__
#define __GRID_SCRIPT_H__

#include "../Components/Script.h"
#include "GridSquare.h"
#include "../Objects/Cube.h"

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
		int getWidth() { return width; }
		int getDepth() { return depth; }
		GridSquare* getSquareAtIndex(int i, int j) {
			return squares[i*width + j];
		}

		void disableWallsRender();
		void enableWallsRender();

		GridSquare** squares; // Pointer to matrix of GridSquare pointers. Matrix is really a long array mapping values in form of a matrix.
	private:
		Cube* west;
		Cube* south;
		Cube* east;
		Cube* north;
		int width;
		int depth;
};


#endif