#ifndef __GAMEOBJECT_COMPONENT_Pathfinder_H__
#define __GAMEOBJECT_COMPONENT_Pathfinder_H__

#include "../Components/Script.h"
#include "GameObject.h"
#include "Scripts/GridSquare.h"
#include "Scripts/Grid.h"

using namespace std;

/* Forward declarations. */
class GameObject;
class Grid;
class GridSquare;

struct PathSquare {
public:
	int x, y, f, g, h;
    bool open;
    bool closed;
    GridSquare* gridSquare;
	PathSquare* parent;
	PathSquare(int xIndex, int yIndex, GridSquare* gridSquare) {
		std::cout << xIndex << " " << yIndex << std::endl;
		x = xIndex; y = yIndex;
		this->gridSquare = gridSquare;
		parent = NULL;
		open = false;
		closed = false;
	}
	void calculateScores(PathSquare* goal) {
		h = std::abs(x - goal->x) + std::abs(y - goal->y);
		calculateG(this);
		f = g + h;
	}
	bool isWalkable() { return !gridSquare->IsOccupied(); }
	int calculateG(PathSquare* p) { 
		if (x == parent->x || y == parent->y)
			g = 10 + parent->g;
		else 
			g = 14+parent->g;
		return g; 
	}
	Ogre::Vector3 getPosition() {
		Ogre::Vector3 ans = gridSquare->getBounds();
		ans.x *= x;
		ans.y = 0;
		ans.z *= y;
		return ans;
	}
};

class Pathfinder : public Script {
public:
	static PathSquare** _grid;
	static int gridWidth;
	static int gridDepth;

	Pathfinder(GameObject *attachedGameObject) : Script(attachedGameObject) {}
	void Initialize(Grid* grid);
	list<PathSquare*> FindPath(int goalX, int goalY);
	void setCurrentGridSquare(Ogre::Vector3 worldPos) {
   		Ogre::Vector3 bounds = _grid[0]->gridSquare->getBounds();
   		PathSquare* square;
		/* Will need to offeset if the grid gets moved off the origin */
		if (worldPos.x > 0 && worldPos.z > 0 && worldPos.x<bounds.x*gridWidth && worldPos.z<bounds.z*gridDepth) {
	    square = _grid[(int)( (worldPos.x + bounds.x*.5)/bounds.x) * gridWidth + (int) ( ( worldPos.z + bounds.z*.5 ) /bounds.z)];
		}
		else 
			square = _grid[0];
		currentX = square->x;
		currentY = square->y;
		cout << "SET CURRENT POS: (" << worldPos.x << ", " << worldPos.y<< ", " << worldPos.z << ") "<<currentX << " " << currentY << std::endl;
	}
private:
	int currentX, currentY; 
};

#endif