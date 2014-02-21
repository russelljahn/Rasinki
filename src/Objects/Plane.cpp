#include "Plane.h"
#include "GameObject.h"
#include "Game.h"

Plane::Plane(Game *attachedGame, Ogre::Vector3 normal, float pos) : GameObject(attachedGame){
	this->normal = normal;
	this->pos = pos;
	Start();
}

void Plane::Start() {
	scale = 50;
	transform = new Transform(this, game->getSceneRoot());

	//North
	this->plane = Ogre::Plane(normal,pos);
    Ogre::MeshManager::getSingleton().createPlane("plane"+this->id,
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        this->plane, 1500, 1000, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Y);

	entity = game->getSceneManager()->createEntity("Plane"+this->id, "plane"+this->id);
	entity->setMaterialName("Examples/Rockwall");
    entity->setCastShadows(false);
	transform->sceneNode->attachObject(entity);

	physics = new Physics(*this,0);


}

void Plane::Update() {

}

void Plane::FixedUpdate() {

}

void Plane::Kill() {
	
}
