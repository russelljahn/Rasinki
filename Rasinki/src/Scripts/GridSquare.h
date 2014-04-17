
#ifndef __GRIDSQUARE_SCRIPT_H__
#define __GRIDSQUARE_SCRIPT_H__

#include "../Components/Script.h"


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

		GameObject *occupant;


	private:
		Ogre::Vector3 scale;
};


#endif