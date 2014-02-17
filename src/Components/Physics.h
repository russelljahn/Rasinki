
#ifndef __PHYSICS_COMPONENT_H__
#define __PHYSICS_COMPONENT_H__

#include <btBulletDynamicsCommon.h>
#include "GameObject.h"
#include "Transform.h"

/* Forward Declarations */
class GameObject;
class Transform;
/* 
	A Component encapsulates some functionality of a GameObject, such as the
	rendering, physics, or sound.
*/
class Physics{
	
	public:
		Physics(GameObject& attachedGameObject, float mass = 1, btCollisionShape* collider = new btSphereShape(1) );
		~Physics();

		void Start();
		void FixedUpdate();

		void setLinearVelocity(const btVector3& veloc) { mRigidBody->setLinearVelocity(veloc); }
		const btVector3& getLinearVelocity() const { return mRigidBody->getLinearVelocity(); }

		void setAngularVelocity(const btVector3& veloc) { mRigidBody->setAngularVelocity(veloc); }
		const btVector3& getAngularVelocity() const { return mRigidBody->getAngularVelocity(); }
		
		btRigidBody* mRigidBody;
	private:
		
		Transform* mTransform;
		GameObject* gameObject;
};


#endif