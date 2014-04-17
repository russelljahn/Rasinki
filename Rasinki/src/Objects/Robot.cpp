#include "Robot.h"
#include "GameObject.h"
#include <btBulletDynamicsCommon.h>

Robot::Robot(Game *attachedGame) : GameObject(attachedGame){
	Start();
}

void Robot::Start() {

	ostringstream nameCoverter;
	nameCoverter << "Robot ";
	nameCoverter << id;

	float scale = 50;
	transform = new Transform(this, game->getSceneRoot());
	renderer->entity = game->getSceneManager()->createEntity(nameCoverter.str(), "robot.mesh");
	transform->sceneNode->attachObject(renderer->entity);
	Ogre::Vector3 halfExtents = transform->getLocalScale()/2.0f;
	physics = new Physics(this, 10000, new btSphereShape(scale) );
	physics->setLinearFactor(Ogre::Vector3(1,1,1));

	renderer->setMaterial("Examples/Rockwall");
}

void Robot::Update() {

}

void Robot::FixedUpdate() {

}

void Robot::Kill() {
	
}