#ifndef __PhysicsSim__H__
#define __PhysicsSim__H__
#include <btBulletDynamicsCommon.h>
#include <OgreRoot.h>
#include "GameObject.h"

class PhysicsSimulator {

	public:
		PhysicsSimulator(Ogre::Real fixedTimeStep = 1.0/60.0);
		~PhysicsSimulator();
		void addObject(btRigidBody* body);
		void removeObject(btRigidBody* body);
		void stepSimulation(Ogre::Real elapsedTime, int maxSubSteps = 1);
	private:
		Ogre::Real mFixedTimeStep;
		Ogre::Real mRemainingTime;
		btDefaultCollisionConfiguration* collisionConfiguration;
		btCollisionDispatcher* dispatcher;
		btBroadphaseInterface* overlappingPairCache;
		btSequentialImpulseConstraintSolver* solver;
		btDiscreteDynamicsWorld* dynamicsWorld;
		btConstraintSolver* mConstraintsolver;
		// btCollisionWorld* mWorld;
		std::list<GameObject*> objList;
};

#endif
