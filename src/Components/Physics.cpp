#include "Physics.h"

Physics::Physics(GameObject& attachedGameObject, btCollisionShape* collider, float mass) {
	//Create rigidbody
	gameObject = &attachedGameObject;
	mTransform = attachedGameObject.transform;
	btQuaternion rot = btQuaternion(mTransform->getLocalRotationEuler().x, mTransform->getLocalRotationEuler().y, mTransform->getLocalRotationEuler().z);
	btVector3 pos = btVector3(mTransform->getLocalPosition().x, mTransform->getLocalPosition().y, mTransform->getLocalPosition().z);
	btTransform transform = btTransform(rot, pos);
	btDefaultMotionState* motionState = new btDefaultMotionState(transform);
	btVector3 inertia(0,0,0);
	collider->calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo
		rigidBodyCI(mass, motionState, collider, inertia); //Last argument is inertia
	mRigidBody = new btRigidBody(rigidBodyCI);
	mRigidBody->setUserPointer(&attachedGameObject);
	

	//Add rigidbody to world
	//instance of btDiscreteDynamicsWorld->addRigidBody(mRigidBody)
	gameObject->game->getPhysicsSimulator()->addObject(mRigidBody);	
}
Physics::~Physics() {
	// instance of btDiscreteDynamicsWorld->removeRigidBody(mRigidBody)
	gameObject->game->getPhysicsSimulator()->removeObject(mRigidBody);
	delete mRigidBody->getMotionState();
	delete mRigidBody;
}
void Physics::Start() {}
void Physics::FixedUpdate() {
	btTransform trans;
	mRigidBody->getMotionState()->getWorldTransform(trans);  // sets trans to rigidBody's transform
	//Need to convert btVector3 and btQuaternion to Ogre types
	btVector3 pos = trans.getOrigin();
	btQuaternion rot = trans.getRotation();
	if (pos.x() != pos.x())
		return;
	mTransform -> setWorldPosition(Ogre::Vector3(pos.x(), pos.y(), pos.z()));
	// mTransform -> setRotation(Ogre::Quaternion(rot.x(), rot.y(), rot.z(), rot.w())); 
}