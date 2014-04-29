#include "Grid.h"
#include "GridSquare.h"
#include "../Objects/Cube.h"
#include "EnemySpawner.h"
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
    EnemySpawner *enemySpawnerScript = squares[width*depth - 1]->gameObject->AddComponentOfType<EnemySpawner>();
    enemySpawnerScript->grid = this;
    
    Ogre::Vector3 bounds = squares[0]->getBounds();
    float height = 50;

    Cube *floorCollider = new Cube(this->gameObject->game, 0);
    floorCollider->renderer->setEnabled(false);
    floorCollider->transform->setWorldScale(Ogre::Vector3((bounds.x/50)*width, 2*bounds.y, (bounds.z/50)*depth));
    floorCollider->physics->setWorldPosition(Ogre::Vector3(bounds.x*(width - 1)/2, -100*bounds.y, bounds.z*(depth - 1)/2));
    floorCollider->renderer->setEnabled(false);
    this->gameObject->game->gameObjects.push_back(floorCollider);

    Cube *ceilingCollider = new Cube(this->gameObject->game, 0);
    ceilingCollider->renderer->setEnabled(false);
    ceilingCollider->transform->setWorldScale(Ogre::Vector3((bounds.x/100)*width,bounds.y/400,(bounds.z/100)*depth));
    ceilingCollider->physics->setWorldPosition(Ogre::Vector3(bounds.x*(width - 1)/2, 5000, bounds.z*(depth - 1)/2));
    ceilingCollider->renderer->setEnabled(false);
    this->gameObject->game->gameObjects.push_back(ceilingCollider);

    west = new Cube(this->gameObject->game, 0);
    west->transform->setWorldScale(Ogre::Vector3((bounds.x/100)*width, height,10));
    west->physics->setWorldPosition(Ogre::Vector3(bounds.x*(width - 1)/2, 50.0*height, -625));
    west->renderer->setMaterial("BoundaryGlow1");
    west->renderer->setEnabled(false);
    this->gameObject->game->gameObjects.push_back(west);

    east = new Cube(this->gameObject->game, 0);
    east->transform->setWorldScale(Ogre::Vector3((bounds.x/100)*width,height,10));
    east->physics->setWorldPosition(Ogre::Vector3(bounds.x*(width - 1)/2, 50.0*height, bounds.x*(depth-1) + 625));
    east->renderer->setMaterial("BoundaryGlow1");
    east->renderer->setEnabled(false);
    this->gameObject->game->gameObjects.push_back(east);

    north = new Cube(this->gameObject->game, 0);
    north->transform->setWorldScale(Ogre::Vector3( 10, height, (bounds.x/100*depth)+10 ) );
    north->physics->setWorldPosition(Ogre::Vector3(bounds.x*(width - 1) + 625, 50.0*height, bounds.x*(depth-1)/2));
    north->renderer->setMaterial("BoundaryGlow1");
    north->renderer->setEnabled(false);
    this->gameObject->game->gameObjects.push_back(north);

    south = new Cube(this->gameObject->game, 0);
    south->transform->setWorldScale(Ogre::Vector3( 10, height, (bounds.x/100*depth)+10 ) );
    south->physics->setWorldPosition(Ogre::Vector3( -625, 50.0*height, bounds.x*(depth-1)/2));
    south->renderer->setMaterial("BoundaryGlow1");
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


    if (this->gameObject->game->viewMode == true)
    {
        std::cout << "disable walls" << std::endl;
        north->renderer->setEnabled(false);
        east->renderer->setEnabled(false);
        west->renderer->setEnabled(false);
        south->renderer->setEnabled(false);
    }
    else
    {
        north->renderer->setEnabled(true);
        east->renderer->setEnabled(true);
        west->renderer->setEnabled(true);
        south->renderer->setEnabled(true);
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

    // std::cout << "bounds: " << bounds << std::endl;
    // std::cout << "worldPos.x: " << worldPos.x << std::endl;
    // std::cout << "worldPos.z: " << worldPos.z << std::endl;
    // std::cout << "worldPos.x<bounds.x*width: " << bounds.x*width << std::endl;
    // std::cout << "worldPos.z<bounds.z*depth: " << bounds.z*depth << std::endl;
    // std::cout << "(int)( (worldPos.x + bounds.x*.5)/bounds.x): " << (int)( (worldPos.x + bounds.x*.5)/bounds.x) << std::endl;
    // std::cout << "(int)( (worldPos.x + bounds.x*.5)/bounds.x) * width: " << (int)( (worldPos.x + bounds.x*.5)/bounds.x) * width << std::endl;
    // std::cout << " (int) ( ( worldPos.z + bounds.z*.5 ) /bounds.z): " <<  (int) ( ( worldPos.z + bounds.z*.5 ) /bounds.z) << std::endl;
    // std::cout << "sum: " << ((int)( (worldPos.x + bounds.x*.5)/bounds.x) * width + (int) ( ( worldPos.z + bounds.z*.5 ) /bounds.z)) << std::endl;

    float epsilon = 0.001;
    int squareIndex = ((int)( (worldPos.x + bounds.x*.5)/bounds.x) * width + (int) ( ( worldPos.z + bounds.z*.5 ) /bounds.z));

    /* Will need to offeset if the grid gets moved off the origin */
    if (squareIndex < width*depth && 
        worldPos.x > epsilon && 
        worldPos.z > epsilon &&
        worldPos.x<(bounds.x*width-epsilon) && 
        worldPos.z<(bounds.z*depth-epsilon)
        ) {
        // std::cout << "Am I null? Nope." << std::endl; 
        return squares[squareIndex];
    }

    // std::cout << "Am I null? THUNDERCATS HOOOOOOOOOOOOOOOOOOOOOO!" << std::endl; 
    return NULL;


}
