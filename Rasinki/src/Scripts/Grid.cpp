#include "Grid.h"
#include "GridSquare.h"
#include "../Objects/Cube.h"
#include <ctime>

Grid::Grid(GameObject *attachedGameObject) : Script(attachedGameObject) {
    
   	width = 25;
   	depth = 25;
   	squares = new GridSquare* [width*depth];

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < depth; ++j) {
            Cube *cube = new Cube(this->gameObject->game, 0);
            GridSquare *square = cube->AddComponentOfType<GridSquare>();
            
            Ogre::Vector3 bounds = square->getBounds();
            Ogre::Vector3 position (i*bounds.x, 0, j*bounds.z);
            cube->transform->setLocalPosition(position);
            cube->name = "gridsquare";

            squares[i*width + j] = square;
            this->gameObject->game->gameObjects.push_back(cube);
        }
    }

    Ogre::Vector3 bounds = squares[0]->getBounds();

    Cube *west = new Cube(this->gameObject->game, 0);
    west->transform->setWorldScale(Ogre::Vector3((bounds.x/100)*width,1,1));
    west->transform->setWorldPosition(Ogre::Vector3(bounds.x*(width - 1)/2, 0, -175));
    west->renderer->setEnabled(false);
    this->gameObject->game->gameObjects.push_back(west);

    Cube *east = new Cube(this->gameObject->game, 0);
    east->transform->setWorldScale(Ogre::Vector3((bounds.x/100)*width,1,1));
    east->transform->setWorldPosition(Ogre::Vector3(bounds.x*(width - 1)/2, 0, bounds.x*(depth-1) + 175));
    east->renderer->setEnabled(false);
    this->gameObject->game->gameObjects.push_back(east);

    Cube *north = new Cube(this->gameObject->game, 0);
    north->transform->setWorldScale(Ogre::Vector3( 1,1, (bounds.x/100*depth) ) );
    north->transform->setWorldPosition(Ogre::Vector3(bounds.x*(width - 1) + 175, 0, bounds.x*(depth-1)/2));
    north->renderer->setEnabled(false);
    this->gameObject->game->gameObjects.push_back(north);

    Cube *south = new Cube(this->gameObject->game, 0);
    south->transform->setWorldScale(Ogre::Vector3( 1,1, (bounds.x/100*depth) ) );
    south->transform->setWorldPosition(Ogre::Vector3( -175, 0, bounds.x*(depth-1)/2));
    south->renderer->setEnabled(false);
    this->gameObject->game->gameObjects.push_back(south);
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

GridSquare Grid::gridSquareAtPos(Ogre::Vector3 worldPos) {
    Ogre::Vector3 bounds = squares[0]->getBounds();

    /* Will need to offeset if the grid gets moved off the origin */
    if (worldPos.x > 0 && worldPos.z > 0)
        return squares[(int)(worldPos.x/bounds.x)][(int) (worldPos.z/bounds.z)];
    else
        return NULL;
}