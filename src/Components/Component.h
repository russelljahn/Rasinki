
#ifndef __GAMEOBJECT_COMPONENT_H__
#define __GAMEOBJECT_COMPONENT_H__

#include "GameObject.h"
#include "Transform.h"

/* Forward declarations. */
class GameObject;



/* 
	A Component encapsulates some functionality of a GameObject, such as the
	rendering, physics, or sound.
*/
class Component {
	
	
	public:
		GameObject *gameObject;

		Component(GameObject *attachedGameObject);

		void virtual Start();
		void virtual Update();
		void virtual FixedUpdate();
		void virtual OnCollision(Ogre::Vector3 point, GameObject* collidedWith);
		void virtual SetEnabled(bool enabled);
		bool IsEnabled();

	protected:
		bool enabled;
};


#endif