
#ifndef __ENEMY_SCRIPT_H__
#define __ENEMY_SCRIPT_H__

#include "../Components/Script.h"
#include "Scripts/Pathfinder.h"

#include "Grid.h"

using namespace std;

class GridSquare;
class Pathfinder;
/* 
	Code to control Gameplay behavior.
*/
class EnemyScript : public Script {

	public:
		EnemyScript(GameObject *attachedGameObject);
		~EnemyScript();

		void Initialize(Pathfinder* pathfinder);		
		void Start(void);
		void Update(void);
		void Attacked();
		Ogre::Vector3 destination;

		Grid *grid;
		GridSquare *lastSquare;
		GridSquare *currentSquare;

	private:
		float moveSpeed;
		Pathfinder* pathfinder;
		list<PathSquare*> _currentPath;
};
#endif
