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
            cube->physics->disableCollider();

            squares[i*width + j] = square;
            this->gameObject->game->gameObjects.push_back(cube);
        }
    }
    Ogre::Vector3 bounds = squares[0]->getBounds();
    float height = 50;

    Cube *floorCollider = new Cube(this->gameObject->game, 0);
    floorCollider->renderer->setEnabled(false);
    floorCollider->transform->setWorldScale(Ogre::Vector3((bounds.x/100)*width,bounds.y/400,(bounds.z/100)*depth));
    floorCollider->physics->setWorldPosition(Ogre::Vector3(bounds.x*(width - 1)/2, 0.0, bounds.z*(depth - 1)/2));
    this->gameObject->game->gameObjects.push_back(floorCollider);

    Cube *ceilingCollider = new Cube(this->gameObject->game, 0);
    ceilingCollider->renderer->setEnabled(false);
    ceilingCollider->transform->setWorldScale(Ogre::Vector3((bounds.x/100)*width,bounds.y/400,(bounds.z/100)*depth));
    ceilingCollider->physics->setWorldPosition(Ogre::Vector3(bounds.x*(width - 1)/2, 5000, bounds.z*(depth - 1)/2));
    this->gameObject->game->gameObjects.push_back(ceilingCollider);


    Cube *west = new Cube(this->gameObject->game, 0);
    west->transform->setWorldScale(Ogre::Vector3((bounds.x/100)*width, height,1));
    west->physics->setWorldPosition(Ogre::Vector3(bounds.x*(width - 1)/2, 50.0*height, -175));
    west->renderer->setMaterial("BoundaryGlow1");
    this->gameObject->game->gameObjects.push_back(west);

    Cube *east = new Cube(this->gameObject->game, 0);
    east->transform->setWorldScale(Ogre::Vector3((bounds.x/100)*width,height,1));
    east->physics->setWorldPosition(Ogre::Vector3(bounds.x*(width - 1)/2, 50.0*height, bounds.x*(depth-1) + 175));
    east->renderer->setMaterial("BoundaryGlow1");
    this->gameObject->game->gameObjects.push_back(east);

    Cube *north = new Cube(this->gameObject->game, 0);
    north->transform->setWorldScale(Ogre::Vector3( 1, height, (bounds.x/100*depth) ) );
    north->physics->setWorldPosition(Ogre::Vector3(bounds.x*(width - 1) + 175, 50.0*height, bounds.x*(depth-1)/2));
    north->renderer->setMaterial("BoundaryGlow1");
    this->gameObject->game->gameObjects.push_back(north);

    Cube *south = new Cube(this->gameObject->game, 0);
    south->transform->setWorldScale(Ogre::Vector3( 1, height, (bounds.x/100*depth) ) );
    south->physics->setWorldPosition(Ogre::Vector3( -175, 50.0*height, bounds.x*(depth-1)/2));
    south->renderer->setMaterial("BoundaryGlow1");
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

GridSquare* Grid::gridSquareAtPos(Ogre::Vector3 worldPos) {
    Ogre::Vector3 bounds = squares[0]->getBounds();

    /* Will need to offeset if the grid gets moved off the origin */
    if (worldPos.x > 0 && worldPos.z > 0 && worldPos.x<bounds.x*width && worldPos.z<bounds.z*depth) {
        return squares[(int)( (worldPos.x + bounds.x*.5)/bounds.x) * width + (int) ( ( worldPos.z + bounds.z*.5 ) /bounds.z)];
    }
    return NULL;


}