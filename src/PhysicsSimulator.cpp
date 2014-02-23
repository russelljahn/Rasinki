#include <PhysicsSimulator.h>
using namespace std;


Ogre::Vector3 PhysicsSimulator::gravity = Ogre::Vector3(0, -98, 0);

bool PhysicsSimulator::OnCollision(btManifoldPoint& p, void * obj1, void * obj2){
	GameObject * o1 = (GameObject*)((btCollisionObject*)obj1)->getUserPointer();
	GameObject * o2 = (GameObject*)((btCollisionObject*)obj2)->getUserPointer();
	if (o1 != NULL)
		o1->OnCollision(Ogre::Vector3(p.getPositionWorldOnA().x(), p.getPositionWorldOnA().y(), p.getPositionWorldOnA().z()), o2);
	if (o2 != NULL)
		o2->OnCollision(Ogre::Vector3(p.getPositionWorldOnA().x(), p.getPositionWorldOnA().y(), p.getPositionWorldOnA().z()), o1);
	std::cout << "Collision between: ";
	std::cout << (o1!=NULL ? o1->name : "NULL") << " and " << (o2!=NULL ? o2->name : "NULL");
	std::cout << " at " << p.getPositionWorldOnA().x() << " " << p.getPositionWorldOnA().y() << " " << p.getPositionWorldOnA().z() << std::endl;
	Ogre::Vector3 pos; 
	if (o1 != NULL) {
		pos = o1->physics->getWorldPosition();
		std::cout << (o1!=NULL ? o1->name : "NULL") << " at " << pos.x << ", " << pos.y << ", " << pos.z <<std::endl;
	}
	if (o2 != NULL) {
		pos = o2->physics->getWorldPosition();
		std::cout << (o2!=NULL ? o2->name : "NULL") << " at " << pos.x << ", " << pos.y << ", " << pos.z << std::endl;
	}
	return true;
}

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
	dynamicsWorld->setGravity(btVector3(gravity.x, gravity.y, gravity.z));
	 //keep track of the shapes, we release memory at exit.
	 //make sure to re-use collision shapes among rigid bodies whenever possible!
	btAlignedObjectArray<btCollisionShape*> collisionShapes;
	gContactProcessedCallback = OnCollision;
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

	// for(list<GameObject*>::iterator i = objList.begin(); i != objList.end(); ++i) {
	// 		Ogre::Vector3 pos = (*i)->transform->getWorldPosition();
	// 		(*i)->physics->setWorldPosition(pos); //mRigidBody->getWorldTransform().setOrigin(btVector3(pos.x, pos.y, pos.z));
	// 	}

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