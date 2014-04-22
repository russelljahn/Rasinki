
#ifndef __ENEMY_SCRIPT_H__
#define __ENEMY_SCRIPT_H__

#include "../Components/Script.h"
#include "Scripts/Pathfinder.h"
using namespace std;

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
		Ogre::Vector3 destination;
	private:
		float moveSpeed;
		Pathfinder* pathfinder;
		list<PathSquare*> _currentPath;
};
#endif
