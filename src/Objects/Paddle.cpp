#include "Paddle.h"
#include "GameObject.h"

Paddle::Paddle(Game *attachedGame) : GameObject(attachedGame){
	Start();
}

void Paddle::Start() {
	transform = new Transform(this, game->getSceneRoot());
	entity = game->getSceneManager()->createEntity("Paddle", "cube.mesh");
	// transform->sceneNode->scale(2,0.25,2);
	transform->sceneNode->attachObject(entity);
	physics = new Physics(*this, 1);
}

void Paddle::Update() {

}

void Paddle::FixedUpdate() {

}

void Paddle::Kill() {
	
}

