
#ifndef __GRIDSQUARE_SCRIPT_H__
#define __GRIDSQUARE_SCRIPT_H__

#include "../Components/Script.h"

class EnemyScript;

/* 
	Squares that towers can be placed on.
*/
class GridSquare : public Script {

	public:
		GridSquare(GameObject *attachedGameObject);

		void Start(void);
		void Update(void);
		void OnCollision(Ogre::Vector3 point, GameObject* collidedWith);
		
		Ogre::Vector3 getBounds();
        bool IsOccupied();
        bool HasEnemies();

        void RemoveEnemy(EnemyScript *enemyToRemove);
        void AddEnemy(EnemyScript *enemyToAdd);


		GameObject *occupant;
    int type;

		EnemyScript *enemy;

	private:
		Ogre::Vector3 scale;
};


#endif
