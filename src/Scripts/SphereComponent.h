#ifndef __Sphere_SCRIPT_H__
#define __Sphere_SCRIPT_H__

#include "../Components/Script.h"

/* 
	Ball in the scene that bounces off of blocks to score points.
*/
class SphereComponent : public Script {

	public:
		SphereComponent(GameObject *attachedGameObject);

		void Update();
		void OnCollision(Ogre::Vector3 point, GameObject* collidedWith);

		static int numSpheres;

	private:
		float speed;


};
#endif