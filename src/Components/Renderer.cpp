
#include "Renderer.h"

Renderer::Renderer(GameObject *attachedGameObject) {
	gameObject = attachedGameObject;
	this->enabled = true;
};
Renderer::~Renderer() {
	delete entity;
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