#include "Physics.h"

Physics::Physics(GameObject& attachedGameObject, btCollisionShape* collider, btTransform trans, float mass) : Component(attachedGameObject) {
	//Create rigidbody
	btDefaultMotionState* motionState = new btDefaultMotionState(transform);
	btVector3 inertia(0,0,0);
	collider->calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo
		rigidBodyCI(mass, motionState, collider, inertia); //Last argument is inertia
	mRigidBody = new btRigidBody(rigidBodyCI);

	//Add rigidbody to world
	//instance of btDiscreteDynamicsWorld->addRigidBody(mRigidBody)

	mTransform = attachedGameObject.GetComponentOfType<Transform>();
	mRigidBody->setUserPointer(&attachGameobject);
}
Physics::~Physics() {
	// instance of btDiscreteDynamicsWorld->removeRigidBody(mRigidBody)
	delete mRigidBody->getMotionState();
	delete mRigidBody;
}
void Transform::Start() {}
void Transform::Update() {}
void Transform::FixedUpdate() {
	btTransform trans;
	mRigidBody->getMotionState()->getWorldTransform(trans);  // sets trans to rigidBody's transform

	//Need to convert btVector3 and btQuaternion to Ogre types
	// mTransform -> setPosition(trans.getOrigin())
	// mTransform -> setRotation(trans.getRotation()) 
}