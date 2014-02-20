#include "Physics.h"

Physics::Physics(GameObject& attachedGameObject, float mass, btCollisionShape* collider, Ogre::Vector3 gravity) {
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
	mRigidBody->setCollisionFlags(mRigidBody->getCollisionFlags() |
  	  btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
	mGravity = btVector3(gravity.x, gravity.y, gravity.z);
	mRigidBody->setGravity(btVector3(gravity.x, gravity.y, gravity.z));
	//Add rigidbody to world
	//instance of btDiscreteDynamicsWorld->addRigidBody(mRigidBody)
	gameObject->game->getPhysicsSimulator()->addObject(mRigidBody);
	std::cout << "COLLIDER AT " << pos.x() << ", " << pos.y() << ", " << pos.z() << std::endl;	
}
Physics::~Physics() {
	// instance of btDiscreteDynamicsWorld->removeRigidBody(mRigidBody)
	gameObject->game->getPhysicsSimulator()->removeObject(mRigidBody);
	delete mRigidBody->getMotionState();
	delete mRigidBody;
}
void Physics::Start() {}
void Physics::FixedUpdate() {

	mRigidBody->setGravity(mGravity);
	btTransform trans;
	mRigidBody->getMotionState()->getWorldTransform(trans);  // sets trans to rigidBody's transform
	//Need to convert btVector3 and btQuaternion to Ogre types
	btVector3 pos = trans.getOrigin();
	btQuaternion rot = trans.getRotation();
	if (pos.x() != pos.x())
		return;
	mTransform -> setWorldPosition(Ogre::Vector3(pos.x(), pos.y(), pos.z()));
	// mTransform -> setRotation(Ogre::Quaternion(rot.x(), rot.y(), rot.z(), rot.w())); 

	std::cout << gameObject->name << "COLLIDER AT " << pos.x() << ", " << pos.y() << ", " << pos.z() << std::endl;
	btVector3 scale = mRigidBody->getCollisionShape()->getLocalScaling();
	std::cout << gameObject->name << "COLLIDER EXTENTS " << scale.x() << ", " << scale.y() << ", " << scale.z() << std::endl;
}