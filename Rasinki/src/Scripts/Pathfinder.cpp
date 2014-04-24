#include "Pathfinder.h"
#include <cmath>

PathSquare** Pathfinder::_grid = NULL;
int Pathfinder::gridWidth = 0;
int Pathfinder::gridDepth = 0;

void Pathfinder::Initialize(Grid* grid) {
  gridWidth = grid->getWidth();
  gridDepth = grid->getDepth();
  _grid = new PathSquare* [grid->getWidth() * grid->getDepth()];
  for (int i = 0; i < grid->getWidth(); i++) {
    for (int j = 0; j < grid->getDepth(); j++) {
      _grid[i*gridWidth + j] = new PathSquare(i, j, grid->getSquareAtIndex(i, j));
    }
  } 
}
list<PathSquare*> Pathfinder::FindPath(int goalX, int goalY) {
  PathSquare* current;
  list<PathSquare*> openSet;
  list<PathSquare*> closedSet;
  list<PathSquare*>::iterator i;
  openSet.push_back(_grid[currentX*gridWidth + currentY]);
  _grid[currentX*gridWidth + currentY]->open = true;
  _grid[currentX*gridWidth + currentY]->closed = false;
  _grid[currentX*gridWidth + currentY]->parent = NULL;
  current = _grid[currentX*gridWidth + currentY];
  while (current != _grid[goalX*gridWidth + goalY]) {
    current = *openSet.begin();
    for (i = openSet.begin(); i != openSet.end(); i++) {
       if ((*i)->f < current->f)
        current = (*i);
    }
    if (current == _grid[goalX*gridWidth + goalY])
      break;
    current->open = false;
    current->closed = true;
    openSet.remove(current);
    closedSet.push_back(current);
    list<PathSquare*> neighbors;
    //Need to check for out of bounds
    if (current->x > 0) {
      if (current->y > 0) {
        neighbors.push_back(_grid[(current->x - 1)*gridWidth + (current->y - 1)]);
      }
      if (current->y < gridDepth) {
        neighbors.push_back(_grid[(current->x - 1)*gridWidth + (current->y + 1)]);
      }
      neighbors.push_back(_grid[(current->x - 1)*gridWidth + (current->y)]);
    }
    if (current->x < gridWidth) {
      if (current->y > 0) {
        neighbors.push_back(_grid[(current->x + 1)*gridWidth + (current->y - 1)]);
      }
      if (current->y < gridDepth) {
        neighbors.push_back(_grid[(current->x + 1)*gridWidth + (current->y + 1)]);
      }
      neighbors.push_back(_grid[(current->x + 1)*gridWidth + (current->y)]);
    }
    if (current->y > 0)
      neighbors.push_back(_grid[(current->x)*gridWidth + (current->y - 1)]);
    if (current->y < gridDepth)
      neighbors.push_back(_grid[(current->x)*gridWidth + (current->y + 1)]);
    for (i = neighbors.begin(); i != neighbors.end(); i++) {
      if (!(*i)->isWalkable() || (*i)->closed)
        continue;
      if ((*i)->open) {
        if ((*i)->calculateG(current) < (*i)->g) {
          (*i)->parent = current;
          (*i)->calculateScores(_grid[goalX*gridWidth + goalY]);
        }
      }
      else {
        (*i)->parent = current;
        (*i)->calculateScores(_grid[goalX*gridWidth + goalY]);
        openSet.push_back((*i));
        (*i)->open = true;
        (*i)->closed = false;
      }
    }
  }
  list<PathSquare*> path = *(new list<PathSquare*>);
  while(current->parent != NULL) {
    path.push_front(current);
    current = current->parent;
  }
  return path;
}