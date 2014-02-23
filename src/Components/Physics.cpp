#include "Physics.h"

Physics::Physics(GameObject& attachedGameObject, float mass, btCollisionShape* collider) {
	//Create rigidbody
	std::cout << "attachedGameObject " << (&attachedGameObject != NULL) << std::endl;
	gameObject = &attachedGameObject;
	mTransform = attachedGameObject.transform;
	btQuaternion rot = btQuaternion(0,0,0,0);
	btVector3 pos = btVector3(0,0,0);
	btTransform transform = btTransform(rot, pos);
	btDefaultMotionState* motionState = new btDefaultMotionState(transform);
	std::cout << "<2>" << std::endl;
	btVector3 inertia = btVector3(0, 0, 0);
	btRigidBody::btRigidBodyConstructionInfo
		rigidBodyCI(mass, motionState, collider, inertia); //Last argument is inertia
	mRigidBody = new btRigidBody(rigidBodyCI);
	mRigidBody->setUserPointer(&attachedGameObject);
	mRigidBody->setCollisionFlags(mRigidBody->getCollisionFlags() |
  	  btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
	mRigidBody->setRestitution(1.0f);
	mRigidBody->setActivationState(DISABLE_DEACTIVATION);
	std::cout << "<3>" << std::endl;
	//Add rigidbody to world
	//instance of btDiscreteDynamicsWorld->addRigidBody(mRigidBody)
	gameObject->game->getPhysicsSimulator()->addObject(mRigidBody);
	//std::cout << "COLLIDER AT " << pos.x() << ", " << pos.y() << ", " << pos.z() << std::endl;	
	std::cout << "<4>" << std::endl;
}
Physics::~Physics() {
	// instance of btDiscreteDynamicsWorld->removeRigidBody(mRigidBody)
	gameObject->game->getPhysicsSimulator()->removeObject(mRigidBody);
	delete mRigidBody->getMotionState();
	delete mRigidBody;
}
void Physics::Start() {}
void Physics::FixedUpdate() {
	btVector3 pos = btVector3(getWorldPosition().x,getWorldPosition().y,getWorldPosition().z);
	std::cout << "position in fixedupdate: " << pos.x() << " " << pos.y() << " " << pos.z() << std::endl;
}

Ogre::Vector3 Physics::getWorldPosition()
{ 
	assert (mRigidBody != NULL);
	btVector3 bulletPos = mRigidBody->getWorldTransform().getOrigin();
	return Ogre::Vector3(bulletPos.x(), bulletPos.y(), bulletPos.z());
}
void Physics::setWorldPosition(const Ogre::Vector3& pos) { 
	assert (mRigidBody != NULL); 
	std::cout << "position we want to set to: " << pos.x << " " << pos.y << " " << pos.z << std::endl;
	mRigidBody->getWorldTransform().setOrigin(btVector3(pos.x,pos.y,pos.z));
	mTransform->sceneNode->setPosition(pos); // TODO: setPosition() is local, need to eventually make it world.
	std::cout << "after physics WorldPosition: " << mRigidBody->getWorldTransform().getOrigin().x() << " " << mRigidBody->getWorldTransform().getOrigin().y() << " " << mRigidBody->getWorldTransform().getOrigin().z() << std::endl;
	std::cout << "after transform WorldPosition: " << mTransform->sceneNode->getPosition().x << " " << mTransform->sceneNode->getPosition().y << " " << mTransform->sceneNode->getPosition().z << std::endl;
}