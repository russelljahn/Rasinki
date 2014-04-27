#include "Tower.h"
#include "GameObject.h"
#include <btBulletDynamicsCommon.h>

Tower::Tower(Game *attachedGame) : GameObject(attachedGame){
	Start();
}
Tower::Tower(Game *attachedGame, int pNum) : GameObject(attachedGame, pNum){
	Start();
}
void Tower::Start() {

	ostringstream nameCoverter;
	nameCoverter << "tower ";
	nameCoverter << id;

	float scale = 35;
	transform = new Transform(this, game->getSceneRoot());
	renderer->entity = game->getSceneManager()->createEntity(nameCoverter.str(), "turret_02.mesh");
	transform->sceneNode->attachObject(renderer->entity);
	Ogre::Vector3 halfExtents = transform->getLocalScale()/2.0f;
	physics = new Physics(this, 0, new btBoxShape(btVector3(scale, scale, scale)));
	physics->setLinearFactor(Ogre::Vector3(1,0,1));

	renderer->setMaterial("Turret_02");
	transform->setWorldScale(Ogre::Vector3(2.5, 2.5, 2.5));

}

void Tower::Update() {

}

void Tower::FixedUpdate() {

}

void Tower::Kill() {
	
}