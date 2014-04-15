#include "Pathfinder.h"
#include <cmath>

using namespace std;

list<GridSquare*> Pathfinder::FindPath(PathSquare*** grid, int goalX, int goalY) {
  PathSquare* current;

  list<PathSquare*> openSet;
  list<PathSquare*> closedSet;
  list<PathSquare*>::iterator i;
  openSet.push_back(grid[currentX][currentY]);
  grid[currentX][currentY]->open = true;
  grid[currentX][currentY]->closed = false;
  grid[currentX][currentY]->parent = NULL;
  while (current != grid[goalX][goalY]) {
    current = *openSet.begin();
    for (i = openSet.begin(); i != openSet.end(); i++) {
       if ((*i)->f < current->f)
        current = (*i);
    }
    if (current == grid[goalX][goalY])
      break;
    current->open = false;
    current->closed = true;
    openSet.remove(current);
    closedSet.push_back(current);
    list<PathSquare*> neighbors;
    //Need to check for out of bounds
    neighbors.push_back(grid[current->x - 1][current->y]);
    neighbors.push_back(grid[current->x + 1][current->y]);
    neighbors.push_back(grid[current->x][current->y - 1]);
    neighbors.push_back(grid[current->x][current->y + 1]);
    for (i = neighbors.begin(); i != neighbors.end(); i++) {
      if (!(*i)->isWalkable() || (*i)->closed)
        continue;
      if ((*i)->open) {
        if ((*i)->calculateG(current) < (*i)->g) {
          (*i)->parent = current;
          (*i)->calculateScores(grid[goalX][goalY]);
        }
      }
      else {
        (*i)->parent = current;
        (*i)->calculateScores(grid[goalX][goalY]);
        openSet.push_back((*i));
        (*i)->open = true;
        (*i)->closed = false;
      }
    }
  }
  list<GridSquare*> path = *(new list<GridSquare*>);
  while(current->parent != NULL) {
    path.push_front(current->gridSquare);
    current = current->parent;
  }
  return path;
}

  /*NodeCordinate *current;

  list<NodeCoordinate*> openSet;
  list<NodeCoordinate*> closedSet;
  list<NodeCoordinate*>::iterator i;
  openSet.push_back(&mCurrentPos);
  mCurrentPos.open = true;
  mCurrentPos.closed = false;
  while (current != &goal) {
    current = *openSet.begin();
    for (i = openSet.begin(); i != openSet.end(); i++) {
      if ((*i)->getF() < current -> getF())
        current = (*i);
    }
    if (current == goal)
      break;
    current->open = false;
    current->close = true; 
    openSet.remove(current);
    closedSet.push_back(current);
    // Add adjacent nodes to open set it they are
    // Walkable
    // Not in closed set
      //Compute each nodes f, g, and h value
      //if it is already in open set and has better g value this time, set its parent to current
  } 
  //Step through the closed set along our path and resolve into w/e we want to return
}
int Pathfinder::Heuristic(NodeCoordinate node, NodeCoordinate goal) {
	return std::abs(node.x - goal.x) + std::abs(node.y - goal.y);
}*/
