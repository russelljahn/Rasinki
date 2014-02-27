#ifndef __Sphere_SCRIPT_H__
#define __Sphere_SCRIPT_H__

#include "../Components/Script.h"

/* 
	Blocks that add points to player when hit.
*/
class SphereComponent : public Script {

	public:
		SphereComponent(GameObject *attachedGameObject);

		void OnCollision(Ogre::Vector3 point, GameObject* collidedWith);

		static int numSpheres;

};
#endif