
#include "Renderer.h"


Renderer::Renderer(GameObject *attachedGameObject) : Component(attachedGameObject) {
	
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
