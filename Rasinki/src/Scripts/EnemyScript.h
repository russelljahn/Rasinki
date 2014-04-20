
#ifndef __ENEMY_SCRIPT_H__
#define __ENEMY_SCRIPT_H__

#include "../Components/Script.h"

/* 
	Code to control Gameplay behavior.
*/
class EnemyScript : public Script {

	public:
		EnemyScript(GameObject *attachedGameObject);
		~EnemyScript();


		void Start(void);
		void Update(void);
		Ogre::Vector3 destination;
	private:
		float moveSpeed;
};
#endif
