#ifndef __GAMEOBJECT_COMPONENT_Pathfinder_H__
#define __GAMEOBJECT_COMPONENT_Pathfinder_H__

#include "Component.h"
#include "GameObject.h"
#include "Scripts/GridSquare.h"

/* Forward declarations. */
class GameObject;

struct PathSquare {
public:
	int x, y, f, g, h;
    bool open;
    bool closed;
    GridSquare* gridSquare;
	PathSquare* parent;
	PathSquare(int xIndex, int yIndex, GridSquare*** grid) {
		x = xIndex; y = yIndex;
		gridSquare = grid[x][y];
		parent = NULL;
		open = false;
		closed = false;
	}
	void calculateScores(PathSquare* goal) {
		h = std::abs(x - goal->x) + std::abs(y - goal->y);
		g = 1 + parent->g;
		f = g + h;
	}
	bool isWalkable() { return true; }
	int calculateG(PathSquare* p) { return p->g + 1; }
};

class Pathfinder : Component {
public:
	float moveSpeed;

	Pathfinder(GameObject *attachedGameObject, float speed) : Component(attachedGameObject) { 
		moveSpeed = speed;
	}
	void Update();

	list<GridSquare*> FindPath(PathSquare*** grid, int goalX, int goalY);
private:
	int currentX, currentY; 
};

#endif