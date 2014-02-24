
#include "Transform.h"

Transform::Transform(GameObject *attachedGameObject, Ogre::SceneNode *parent) {
	this->gameObject = attachedGameObject;
	this->parent = parent;
	this->sceneNode = parent->createChildSceneNode();
};



// void Transform::Start() {
// 	// Component::Start();
// }



// void Transform::Update() {
// 	// Component::Update();
	
// }



// void Transform::FixedUpdate() {
// 	// Component::FixedUpdate();
	
// }


Ogre::Vector3 Transform::getLocalPosition() const {
	assert (sceneNode !=  NULL);
	gameObject->physics->getWorldPosition();
}
Ogre::Vector3 Transform::getWorldPosition() const {
	assert (sceneNode !=  NULL);
	gameObject->physics->getWorldPosition();
}
void Transform::setLocalPosition(const Ogre::Vector3& newLocalPosition) {
	assert (sceneNode !=  NULL);
	gameObject->physics->setWorldPosition(newLocalPosition);
}
void Transform::setWorldPosition(const Ogre::Vector3& newWorldPosition) {
	assert (sceneNode !=  NULL);
	std::cout << "setting transform WorldPosition: " << newWorldPosition.x << " " << newWorldPosition.y << " " << newWorldPosition.z << std::endl;
	gameObject->physics->setWorldPosition(newWorldPosition);
}



Ogre::Vector3 Transform::getLocalScale() const {
	assert (sceneNode !=  NULL);
	return sceneNode->getScale();
}
Ogre::Vector3 Transform::getWorldScale() const {
	assert (sceneNode !=  NULL);
	return sceneNode->getScale();
}
void Transform::setLocalScale(const Ogre::Vector3& newLocalScale) {
	assert (sceneNode !=  NULL);
	sceneNode->setScale(newLocalScale);
	gameObject->physics->setColliderScale(newLocalScale * gameObject->physics->getColliderScale());
}
void Transform::setWorldScale(const Ogre::Vector3& newWorldScale) {
	assert (sceneNode !=  NULL);
	sceneNode->setScale(newLocalScale);
	gameObject->physics->setColliderScale(newWorldScale * gameObject->physics->getColliderScale());
}




Ogre::Vector3 Transform::getLocalRotationEuler() const {

}
Ogre::Vector3 Transform::getWorldRotationEuler() const {
	
}
void Transform::setLocalRotationEuler(const Ogre::Vector3& newLocalRotationEuler) {

}
void Transform::setWorldRotationEuler(const Ogre::Vector3& newWorldRotationEuler) {
	
}
