#include "Physics.h"

Physics::Physics(GameObject* attachedGameObject, float mass, btCollisionShape* collider, Ogre::Vector3 opos) {
	//Create rigidbody
	// std::cout << "attachedGameObject " << (&attachedGameObject != NULL) << std::endl;
	gameObject = attachedGameObject;
	mTransform = gameObject->transform;
	btQuaternion rot = btQuaternion(0,0,0);
	btVector3 pos = btVector3(opos.x,opos.y,opos.z);
	btTransform transform = btTransform(rot, pos);
	btDefaultMotionState* motionState = new btDefaultMotionState(transform);
	// std::cout << "<2>" << std::endl;
	btVector3 inertia = btVector3(0, 0, 0);
	btRigidBody::btRigidBodyConstructionInfo
		rigidBodyCI(mass, motionState, collider, inertia); //Last argument is inertia
	mRigidBody = new btRigidBody(rigidBodyCI);
	mRigidBody->setUserPointer(gameObject);
	mRigidBody->setCollisionFlags(mRigidBody->getCollisionFlags() |
  	  btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
	mRigidBody->setRestitution(1);
	mRigidBody->setDamping(0, 0);
	mRigidBody->setActivationState(DISABLE_DEACTIVATION);
	// std::cout << "<3>" << std::endl;
	//Add rigidbody to world
	//instance of btDiscreteDynamicsWorld->addRigidBody(mRigidBody)
	gameObject->game->getPhysicsSimulator()->addObject(mRigidBody);
	//std::cout << "COLLIDER AT " << pos.x() << ", " << pos.y() << ", " << pos.z() << std::endl;	
	// std::cout << "<4>" << std::endl;
	enabled = true;
}


Physics::~Physics() {
	// instance of btDiscreteDynamicsWorld->removeRigidBody(mRigidBody)
	if (gameObject != NULL) {
		gameObject->game->getPhysicsSimulator()->removeObject(mRigidBody);
		delete mRigidBody->getMotionState();
	}
	delete mRigidBody;
}


void Physics::setEnabled(bool enabled) {
	
	if (!enabled && this->enabled) {
		gameObject->game->getPhysicsSimulator()->removeObject(mRigidBody);
	}
	else if (enabled && !this->enabled) {
		gameObject->game->getPhysicsSimulator()->addObject(mRigidBody);
	}
	this->enabled = enabled;
}


bool Physics::isEnabled() {
	return enabled;
}
void Physics::disableCollider() {
	mRigidBody->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
}

void Physics::Start() {}


void Physics::FixedUpdate() {
	btVector3 pos = btVector3(getWorldPosition().x,getWorldPosition().y,getWorldPosition().z);
	btVector3 scale = mRigidBody->getCollisionShape()->getLocalScaling();
	// std::cout << "position in fixedupdate: " << pos.x() << " " << pos.y() << " " << pos.z() << " SCALE IN FIXEDUPDATE: " << scale.x() << " " << scale.y() << " " << scale.z()<< std::endl;
	mTransform->sceneNode->setPosition(Ogre::Vector3(pos.x(), pos.y(), pos.z()));
}


Ogre::Vector3 Physics::getWorldPosition() { 
	assert (mRigidBody != NULL);
	btVector3 bulletPos = mRigidBody->getWorldTransform().getOrigin();
	return Ogre::Vector3(bulletPos.x(), bulletPos.y(), bulletPos.z());
}


void Physics::setMass(float newMass) {
	/*
		To change the mass in Bullet, you have to do this weird trick where you
		remove the physics object, change mass, then re-add physics object
		for correct behavior.
	*/
	//Remove the rigid body from the dynamics world
	gameObject->game->getPhysicsSimulator()->removeObject(mRigidBody);
	 
	btVector3 inertia;
	mRigidBody->getCollisionShape()->calculateLocalInertia( newMass, inertia );
	mRigidBody->setMassProps(newMass, inertia);
	 
	//Add the rigid body to the dynamics world
	gameObject->game->getPhysicsSimulator()->addObject(mRigidBody);
}


void Physics::setGravity(const Ogre::Vector3& newGravity) {
	mRigidBody->setGravity(btVector3(newGravity.x, newGravity.y, newGravity.z));
}


void Physics::setWorldPosition(const Ogre::Vector3& pos) { 
	assert (mRigidBody != NULL); 
	// std::cout << "position we want to set to: " << pos.x << " " << pos.y << " " << pos.z << std::endl;
	mRigidBody->getWorldTransform().setOrigin(btVector3(pos.x,pos.y,pos.z));
	mTransform->sceneNode->setPosition(pos); // TODO: setPosition() is local, need to eventually make it world.
	// std::cout << "after physics WorldPosition: " << mRigidBody->getWorldTransform().getOrigin().x() << " " << mRigidBody->getWorldTransform().getOrigin().y() << " " << mRigidBody->getWorldTransform().getOrigin().z() << std::endl;
	// std::cout << "after transform WorldPosition: " << mTransform->sceneNode->getPosition().x << " " << mTransform->sceneNode->getPosition().y << " " << mTransform->sceneNode->getPosition().z << std::endl;
}


void Physics::setColliderScale(const Ogre::Vector3& scale) { 
	mRigidBody->getCollisionShape()->setLocalScaling(btVector3(scale.x, scale.y, scale.z)); 
}


Ogre::Vector3 Physics::getColliderScale() { 
	btVector3 scale = mRigidBody->getCollisionShape()->getLocalScaling();
	return Ogre::Vector3(scale.x(), scale.y(), scale.z()); 
}
