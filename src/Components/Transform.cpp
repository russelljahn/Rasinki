
#include "Transform.h"

Transform::Transform(GameObject &attachedGameObject, SceneNode &parent) : Component(attachedGameObject), sceneNode(parent) {
};



void Transform::Start() {
	Component::Start();
}



void Transform::Update() {
	Component::Update();
	
}



void Transform::FixedUpdate() {
	Component::FixedUpdate();
	
}