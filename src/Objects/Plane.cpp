#include "Plane.h"
#include "GameObject.h"
#include "Game.h"

Plane::Plane(Game *attachedGame, Ogre::Vector3 normal, float pos) : GameObject(attachedGame){
	this->normal = normal;
	this->pos = pos;
	Start();
}

void Plane::Start() {
	float scale = 50;
	transform = new Transform(this, game->getSceneRoot());

	ostringstream nameCoverter;
	nameCoverter << "plane ";
	nameCoverter << id;

	//North
	this->plane = Ogre::Plane(normal,pos);
    Ogre::MeshManager::getSingleton().createPlane(nameCoverter.str(),
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        this->plane, 1500, 1000, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Y);

	renderer->entity = game->getSceneManager()->createEntity("plane"+this->id, "plane"+this->id);
	renderer->setMaterial("Examples/Rockwall");
  
	transform->sceneNode->attachObject(renderer->entity);

	physics = new Physics(this,0);


}

void Plane::Update() {

}

void Plane::FixedUpdate() {

}

void Plane::Kill() {
	
}
