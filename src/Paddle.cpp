#include "Paddle.h"
#include "GameObject.h"

Paddle::Paddle(Game *attachedGame) : GameObject(attachedGame){
	
}

void Paddle::Start() {
	entity = game->getSceneManager()->createEntity("Paddle", "cube.mesh");
	transform->sceneNode->attachObject(entity);
	physics = new Physics(*this, 0.2);
}