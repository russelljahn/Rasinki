#include "Cube.h"
#include "GameObject.h"
#include "Game.h"

Cube::Cube(Game *attachedGame) : GameObject(attachedGame) {
	Start();
}

void Cube::Start() {
	scale = 100;
	transform = new Transform(this, game->getSceneRoot());

	entity = game->getSceneManager()->createEntity("cube"+this->id, "cube.mesh");
	transform->sceneNode->attachObject(entity);

	Ogre::Vector3 halfExtents = transform->getLocalScale()/2.0f;
	physics = new Physics(*this, 0 /*, new btBoxShape(btVector3(1,1,1)), Ogre::Vector3::ZERO*/);

}

void Cube::Update() {

}

void Cube::FixedUpdate() {

}

void Cube::Kill() {
	
}
