#include <PhysicsSimulator.h>
using namespace std;

PhysicsSimulator::PhysicsSimulator(Ogre::Real fixedTimeStep) {
	mFixedTimeStep = fixedTimeStep;
	 ///collision conﬁguration contains default setup for memory, collision setup.
	collisionConfiguration = new btDefaultCollisionConfiguration();
	 ///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher
	 dispatcher = new btCollisionDispatcher(collisionConfiguration);
	 ///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	overlappingPairCache = new btDbvtBroadphase();
	 ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	 solver = new btSequentialImpulseConstraintSolver();
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,overlappingPairCache,solver,collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0,-98, 0));
	 //keep track of the shapes, we release memory at exit.
	 //make sure to re-use collision shapes among rigid bodies whenever possible!
	btAlignedObjectArray<btCollisionShape*> collisionShapes;
}
void PhysicsSimulator::addObject(btRigidBody* body) {
	dynamicsWorld->addRigidBody(body);
	if (body->getUserPointer() == NULL)
		return;
	objList.push_back((GameObject*)(body->getUserPointer()));
}
void PhysicsSimulator::removeObject(btRigidBody* body) {
	objList.remove((GameObject*)body->getUserPointer());
	dynamicsWorld->removeRigidBody(body);
}
void PhysicsSimulator::stepSimulation(Ogre::Real elapsedTime) {
	/*	I may have overcomplicated this:
	 *	Trying to keep track of number of stepSimulations
	 *	to run on my own rather than letting bullet do it
	 *	so that FixedUpdate can be called on everything
	 *	on each physics step
	 */
	for(list<GameObject*>::iterator i = objList.begin(); i != objList.end(); ++i) {
			Ogre::Vector3 pos = (*i)->transform->getWorldPosition();
			(*i)->physics->mRigidBody->getWorldTransform().setOrigin(btVector3(pos.x, pos.y, pos.z));
		}
	mRemainingTime += elapsedTime;
	while (mRemainingTime > mFixedTimeStep) {
		mRemainingTime -= mFixedTimeStep;
		dynamicsWorld->stepSimulation(mFixedTimeStep, 0);
		for(list<GameObject*>::iterator i = objList.begin(); i != objList.end(); ++i) {
			(*i)->FixedUpdate();
		}
	}
}
PhysicsSimulator::~PhysicsSimulator() {
	delete collisionConfiguration;
	delete dispatcher;
	delete overlappingPairCache;
	delete solver;
	delete dynamicsWorld;
	delete mConstraintsolver;
}