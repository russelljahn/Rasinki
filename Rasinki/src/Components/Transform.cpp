
#include "Transform.h"

Transform::Transform(GameObject *attachedGameObject, Ogre::SceneNode *parent) {
	this->gameObject = attachedGameObject;
	this->parent = parent;
	this->sceneNode = parent->createChildSceneNode();
};

Transform::~Transform() {
	if ( sceneNode != NULL )
	{
		// parent->detachObject(sceneNode->getName());
		// gameObject->game->getSceneManager()->destroySceneNode( sceneNode ); // Shouldn't normally manually destroy scenenodes, should allow scenemanager to do it on scenemanager.clear.
	}
}

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
	if (gameObject->physics == NULL) {
		std::cout<< "SEG FAULTING IN getLocalPosition" << std::endl;
	}
	assert (sceneNode !=  NULL);
	return gameObject->physics->getWorldPosition();
}
Ogre::Vector3 Transform::getWorldPosition() const {
	if (gameObject->physics == NULL) {
		std::cout << "SEG FAULTING IN GETWORLDPOSITION? " << std::endl;
		Ogre::Vector3 pos = sceneNode->getPosition();
		std::cout << "Nope" << std::endl;
		return pos;	
	}
	assert (sceneNode !=  NULL);
	return gameObject->physics->getWorldPosition();
}
void Transform::setLocalPosition(const Ogre::Vector3& newLocalPosition) {
	if (gameObject->physics == NULL) {
		std::cout<< "SEG FAULTING IN getLocalPosition" << std::endl;
	}
	assert (sceneNode !=  NULL);
	gameObject->physics->setWorldPosition(newLocalPosition);
}
void Transform::setWorldPosition(const Ogre::Vector3& newWorldPosition) {
	if (gameObject->physics == NULL) {
		sceneNode->setPosition(newWorldPosition);
		return;
	}
	assert (sceneNode !=  NULL);
	// std::cout << "setting transform WorldPosition: " << newWorldPosition.x << " " << newWorldPosition.y << " " << newWorldPosition.z << std::endl;
	gameObject->physics->setWorldPosition(newWorldPosition);
}



Ogre::Vector3 Transform::getLocalScale() const {
	if (gameObject->physics == NULL) {
		std::cout<< "SEG FAULTING IN getLocalScale" << std::endl;
	}
	assert (sceneNode !=  NULL);
	return sceneNode->getScale();
}
Ogre::Vector3 Transform::getWorldScale() const {
	if (gameObject->physics == NULL) {
		std::cout<< "SEG FAULTING IN getWorldScale" << std::endl;
	}
	assert (sceneNode !=  NULL);
	return sceneNode->getScale();
}
void Transform::setLocalScale(const Ogre::Vector3& newLocalScale) {
	if (gameObject->physics == NULL) {
		std::cout<< "SEG FAULTING IN setLocalScale" << std::endl;
	}
	assert (sceneNode !=  NULL);
	sceneNode->setScale(newLocalScale);
	gameObject->physics->setColliderScale(newLocalScale);
}
void Transform::setWorldScale(const Ogre::Vector3& newWorldScale) {
	if (gameObject->physics == NULL) {
		sceneNode->setScale(newWorldScale);
		return;
	}
	assert (sceneNode !=  NULL);
	sceneNode->setScale(newWorldScale);
	gameObject->physics->setColliderScale(newWorldScale);
}




Ogre::Vector3 Transform::getLocalRotationEuler() const {

}
Ogre::Vector3 Transform::getWorldRotationEuler() const {
	
}
void Transform::setLocalRotationEuler(const Ogre::Vector3& newLocalRotationEuler) {

}
void Transform::setWorldRotationEuler(const Ogre::Vector3& newWorldRotationEuler) {
	
}
