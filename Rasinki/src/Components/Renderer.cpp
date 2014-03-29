
#include "Renderer.h"

Renderer::Renderer(GameObject *attachedGameObject) {
	gameObject = attachedGameObject;
	this->enabled = true;
};
Renderer::~Renderer() {

}

void Renderer::setMaterial(string materialName) {
	entity->setMaterialName(materialName);
}


void Renderer::setEnabled(bool enabled) {
	entity->setVisible(enabled);
	this->enabled = enabled;
}


bool Renderer::isEnabled() {
	return enabled;
}


void Renderer::setAnimationState(std::string animationStateName) {
	animationState = entity->getAnimationState(animationStateName);
}


void Renderer::setAnimationLoop(bool loop) {
    animationState->setLoop(loop);
}


void Renderer::setAnimationEnabled(bool enabled) {
    animationState->setEnabled(enabled);
}


bool Renderer::isAnimationEnabled() {
	return animationState->getEnabled();
}

