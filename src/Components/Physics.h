
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
class Physics {
	
	public:
		Physics(){}
		Physics(GameObject& attachedGameObject, float mass = 1, btCollisionShape* collider = new btSphereShape(1), Ogre::Vector3 opos = Ogre::Vector3::ZERO);
		~Physics();

		void Start();
		void FixedUpdate();

		void setLinearVelocity(const Ogre::Vector3& veloc) { mRigidBody->setLinearVelocity(btVector3(veloc.x, veloc.y, veloc.z)); }
		const Ogre::Vector3 getLinearVelocity() const { 
			btVector3 veloc = mRigidBody->getLinearVelocity();
			return Ogre::Vector3(veloc.x(), veloc.y(), veloc.z());
		}
		void setLinearFactor(const Ogre::Vector3& factor) { mRigidBody->setLinearFactor(btVector3(factor.x, factor.y, factor.z)); }

		void setAngularVelocity(const btVector3& veloc) { mRigidBody->setAngularVelocity(veloc); }
		const btVector3& getAngularVelocity() const { return mRigidBody->getAngularVelocity(); }

		Ogre::Vector3 getColliderScale();
		void setColliderScale(const Ogre::Vector3& scale);

		Ogre::Vector3 getWorldPosition();
		void setWorldPosition(const Ogre::Vector3& pos);

	protected:
		btRigidBody* mRigidBody;
		Transform* mTransform;
		GameObject* gameObject;
};
#endif