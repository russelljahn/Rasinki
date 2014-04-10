#include "Grid.h"
#include "GridSquare.h"
#include "../Objects/Cube.h"
#include <ctime>

Grid::Grid(GameObject *attachedGameObject) : Script(attachedGameObject) {
    
   	width = 25;
   	depth = 25;

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < depth; ++j) {
            Cube *cube = new Cube(this->gameObject->game, 0);
            GridSquare *square = cube->AddComponentOfType<GridSquare>();
            
            Ogre::Vector3 bounds = square->getBounds();
            Ogre::Vector3 position (i*bounds.x, 0, j*bounds.z);
            cube->transform->setLocalPosition(position);
            cube->name = "gridsquare";
            this->gameObject->game->gameObjects.push_back(cube);
        }
    }
};



void Grid::Start() {
	Script::Start();
}



void Grid::Update() {
	
	Script::Update();
	if (!this->gameObject->renderer->isEnabled()) {
		this->gameObject->physics->setEnabled(false);
	}
}



void Grid::OnCollision(Ogre::Vector3 point, GameObject* collidedWith) {
	// this->gameObject->renderer->setEnabled(false);
	// if (gameObject->game->getNetwork()->isServer) {
	// 	gameObject->game->getNetwork()->SendMessageToClient(ServerMessage(DISABLEOBJECT,gameObject->objIndex));
	// }
	// //hit = true;
	// //gameObject->physics->setGravity(Ogre::Vector3(0, -98, 0));
	// gameObject->game->getSoundManager()->playSound2();
}
