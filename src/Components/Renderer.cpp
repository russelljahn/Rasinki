
#include "Renderer.h"


Renderer::Renderer(GameObject *attachedGameObject) {
	this->gameObject = attachedGameObject;
};



void Renderer::Start() {
	Component::Start();
}



void Renderer::Update() {
	Component::Update();
	
}



void Renderer::FixedUpdate() {
	Component::FixedUpdate();
	
}
