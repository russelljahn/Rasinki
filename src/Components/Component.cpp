
#include "Component.h"

Component::Component(GameObject *attachedGameObject) {
	this->gameObject = attachedGameObject;
	this->enabled = true;
};



void Component::Start() {

}



void Component::Update() {
	
}



void Component::FixedUpdate() {
	
}
void Component::OnCollision(Ogre::Vector3 point, GameObject* collidedWith) {

}