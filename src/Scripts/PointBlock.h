
#ifndef __POINTBLOCK_SCRIPT_H__
#define __POINTBLOCK_SCRIPT_H__

#include "../Components/Script.h"

/* 
	Blocks that add points to player when hit.
*/
class PointBlock : public Script {

	public:
		PointBlock(GameObject *attachedGameObject);

		void Start(void);
		void Update(void);
		void OnCollision(Ogre::Vector3 point, GameObject* collidedWith);

		float pointsOnDeath;
		// Player *player; //TODO: Implement player add a reference to him.
};


#endif