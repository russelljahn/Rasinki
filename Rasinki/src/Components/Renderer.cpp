
#include "Renderer.h"

Renderer::Renderer(GameObject *attachedGameObject) {
	gameObject = attachedGameObject;
	this->enabled = true;
};
Renderer::~Renderer() {
	std::cout << "			delete entity" << std::endl;
		
	// if (entity != NULL) {
	// 	gameObject->game->getSceneManager()->destroyEntity( entity ); // destroyEntity() is only supposed to be used when entity is not connected to a scenenode. Check into that if having weird segfaults later.
	// }
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