
#include "Wall.h"



Wall::Wall(GameObject *attachedGameObject) : Script(attachedGameObject) {

};



void Wall::Start() {
	Script::Start();
}



void Wall::Update() {


	Script::Update();

    int quad = this->gameObject->game->camQuadrant();

    switch(quad)
    {
        case 1:
            if(this->gameObject->name == "east" || this->gameObject->name == "south")
                this->gameObject->renderer->setEnabled(false);
            else
                this->gameObject->renderer->setEnabled(true);
            break;
        case 2:
            if(this->gameObject->name == "east" || this->gameObject->name == "north")
                this->gameObject->renderer->setEnabled(false);
            else
                this->gameObject->renderer->setEnabled(true);
            break;
        case 3:
            if(this->gameObject->name == "west" || this->gameObject->name == "south")
                this->gameObject->renderer->setEnabled(false);
            else
                this->gameObject->renderer->setEnabled(true);
            break;
        case 4:
            if(this->gameObject->name == "west" || this->gameObject->name == "north")
                this->gameObject->renderer->setEnabled(false);
            else
                this->gameObject->renderer->setEnabled(true);
            break;
        default:
            break;
    }
}
