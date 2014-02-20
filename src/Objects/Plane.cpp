#include "Plane.h"
#include "GameObject.h"
#include "Game.h"
#include <btBulletDynamicsCommon.h>

Plane::Plane(Game *attachedGame, Ogre::Vector3 normal, float pos, float width, float height) : GameObject(attachedGame){
	this->normal = normal;
	this->pos = pos;
	this->width = width;
	this->height = height;
	Start();
}

void Plane::Start() {
	transform = new Transform(this, game->getSceneRoot());

	Ogre::Vector3 ortho = Ogre::Vector3::UNIT_Y;
	if( normal.x == 0 && normal.y != 0 && normal.z == 0)
		ortho = Ogre::Vector3::UNIT_Z;

	//North
	this->plane = Ogre::Plane(normal,0);
    Ogre::MeshManager::getSingleton().createPlane("plane"+this->id,
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        this->plane, width, height, 20, 20, true, 1, 5, 5, ortho);

	entity = game->getSceneManager()->createEntity("Plane"+this->id, "plane"+this->id);
	entity->setMaterialName("Examples/Rockwall");
    entity->setCastShadows(false);
	transform->sceneNode->attachObject(entity);
	transform->setWorldPosition(Ogre::Vector3(normal.x*pos,normal.y*pos,normal.z*pos));

 	btQuaternion rot = btQuaternion(transform->getLocalRotationEuler().x, transform->getLocalRotationEuler().y, transform->getLocalRotationEuler().z);
	btVector3 pos = btVector3(transform->getWorldPosition().x, transform->getWorldPosition().y, transform->getWorldPosition().z);
    btTransform transform = btTransform(rot, pos);
    btDefaultMotionState* motionState = new btDefaultMotionState(transform);
    btVector3 inertia(0,0,0);
    btVector3 colNorm = btVector3(normal.x, normal.y, normal.z);
	btCollisionShape* collider = new btStaticPlaneShape(colNorm, 100);
    btRigidBody::btRigidBodyConstructionInfo
        rigidBodyCI(0, motionState, collider, inertia); //Last argument is inertia
    btRigidBody* body = new btRigidBody(rigidBodyCI);
    //Add rigidbody to world
    //instance of btDiscreteDynamicsWorld->addRigidBody(mRigidBody)
    game->getPhysicsSimulator()->addObject(body);


	// physics = new Physics(*this,0, collider);
	//physics = new Physics(*this,0 );


}

void Plane::Update() {

}

void Plane::FixedUpdate() {

}

void Plane::Kill() {
	
}

