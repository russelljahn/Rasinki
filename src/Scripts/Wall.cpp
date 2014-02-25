
#include "Wall.h"



Wall::Wall(GameObject *attachedGameObject) : Script(attachedGameObject) {

};



void Wall::Start() {
	Script::Start();
}



void Wall::Update() {


	Script::Update();

	Ogre::Vector3 newPos = this->gameObject->game->getCamera()->getPosition();
    if(newPos.x > 0 & newPos.z > 0)
    {
        if(this->gameObject->name == "east" || this->gameObject->name == "south")
            this->gameObject->renderer->setEnabled(false);
        else
            this->gameObject->renderer->setEnabled(true);
    }
    else if(newPos.x > 0 & newPos.z < 0)
    {
        if(this->gameObject->name == "east" || this->gameObject->name == "north")
            this->gameObject->renderer->setEnabled(false);
        else
            this->gameObject->renderer->setEnabled(true);
    }
    else if(newPos.x < 0 & newPos.z > 0)
    {
        if(this->gameObject->name == "west" || this->gameObject->name == "south")
            this->gameObject->renderer->setEnabled(false);
        else
            this->gameObject->renderer->setEnabled(true);
    }
    else if(newPos.x < 0 & newPos.z < 0)
    {
        if(this->gameObject->name == "west" || this->gameObject->name == "north")
            this->gameObject->renderer->setEnabled(false);
        else
            this->gameObject->renderer->setEnabled(true);
    }
}
