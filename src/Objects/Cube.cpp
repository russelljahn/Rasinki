#include "Cube.h"
#include "GameObject.h"
#include "Game.h"

Cube::Cube(Game *attachedGame) : GameObject(attachedGame) {
	Start();
}

void Cube::Start() {
	transform = new Transform(this, game->getSceneRoot());

	renderer->entity = game->getSceneManager()->createEntity("cube"+this->id, "cube.mesh");
	transform->sceneNode->attachObject(renderer->entity);

	Ogre::Vector3 halfExtents = transform->getLocalScale()/2.0f;
	physics = new Physics(this, 0 , new btBoxShape(btVector3(50,50,50)), Ogre::Vector3::ZERO);
	renderer->setMaterial("Examples/Rockwall");
}

void Cube::Update() {

}

void Cube::FixedUpdate() {

}

void Cube::Kill() {
	
}
