
#ifndef __PHYSICS_COMPONENT_H__
#define __PHYSICS_COMPONENT_H__

#include "GameObject.h"
#include "Component.h"
#include <btBulletDynamicsCommon.h>

/* Forward Declarations */
class GameObject;
/* 
	A Component encapsulates some functionality of a GameObject, such as the
	rendering, physics, or sound.
*/
class Physics : public Component {
	
	public:
		Physics(GameObject& attachedGameObject, btCollisionShape* collider = new btSphereShape(1), btTransform trans = btTransform(), float mass = 0 );
		~Physics();

		void Start();
		void FixedUpdate();

		void setLinearVelocity(const btVector3& veloc) { mRigidBody->setLinearVelocity(veloc); }
		const btVector3& getLinearVelocity() const { return mRigidBody->getLinearVelocity(); }

		void setAngularVelocity(const btVector3& veloc) { mRigidBody->setAngularVelocity(veloc); }
		const btVector3& getAngularVelocity() const { return mRigidBody->getAngularVelocity(); }
	
	private:
		btRigidBody* mRigidBody;
		Transform* mTransform;
};


#endif