
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
	return sceneNode->getPosition();
}
Ogre::Vector3 Transform::getWorldPosition() const {
	return sceneNode->convertLocalToWorldPosition( sceneNode->getPosition() );
}
void Transform::setLocalPosition(const Ogre::Vector3& newLocalPosition) {
	sceneNode->setPosition(newLocalPosition);
}
void Transform::setWorldPosition(const Ogre::Vector3& newWorldPosition) {
	sceneNode->setPosition( sceneNode->convertWorldToLocalPosition(newWorldPosition) );
}



Ogre::Vector3 Transform::getLocalScale() const {
	return sceneNode->getScale();
}
// Ogre::Vector3 Transform::getWorldScale() const {
//  TODO: Do this the right way!
// 	return sceneNode->convertLocalToWorldScale( sceneNode->getScale() );
// }
void Transform::setLocalScale(const Ogre::Vector3& newLocalScale) {
	sceneNode->setScale(newLocalScale);
}
// void Transform::setWorldScale(const Ogre::Vector3& newWorldScale) {
//  TODO: Do this the right way!
// 	sceneNode->setScale( sceneNode->convertWorldToLocalScale(newWorldScale) );
// }




Ogre::Vector3 Transform::getLocalRotationEuler() const {

}
Ogre::Vector3 Transform::getWorldRotationEuler() const {
	
}
void Transform::setLocalRotationEuler(const Ogre::Vector3& newLocalRotationEuler) {

}
void Transform::setWorldRotationEuler(const Ogre::Vector3& newWorldRotationEuler) {
	
}
