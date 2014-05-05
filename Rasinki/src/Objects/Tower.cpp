#include "Tower.h"
#include "GameObject.h"
#include "Cube.h"
#include "../Scripts/EnemyScript.h"
#include <btBulletDynamicsCommon.h>
#include "Time.h"

Tower::Tower(Game *attachedGame) : GameObject(attachedGame){
	weaponCooldownTime = 1;
	Start();
}
Tower::Tower(Game *attachedGame, int pNum) : GameObject(attachedGame, pNum){
	weaponCooldownTime = 1;
	Start();
}
Tower::~Tower() {
	for (int i = 0; i < glowTiles.size(); ++i)
	{
		delete glowTiles[i]->gameObject;
	}
	glowTiles.clear();
}
void Tower::Start() {

	ostringstream nameCoverter;
	nameCoverter << "tower ";
	nameCoverter << id;
	grid = NULL;

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

void Tower::Initialize() {
	Ogre::Vector3 bounds = grid->squares[0]->getBounds();
	GridSquare *gs0 = grid->gridSquareAtPos( physics->getWorldPosition() );
	GridSquare *gs1 = grid->gridSquareAtPos( physics->getWorldPosition() + Ogre::Vector3(bounds.x,0,0) );
	GridSquare *gs2 = grid->gridSquareAtPos( physics->getWorldPosition() + Ogre::Vector3(bounds.x,0,bounds.z) );
	GridSquare *gs3 = grid->gridSquareAtPos( physics->getWorldPosition() + Ogre::Vector3(0,0,bounds.z) );
	GridSquare *gs4 = grid->gridSquareAtPos( physics->getWorldPosition() + Ogre::Vector3(-bounds.x,0,bounds.z) );
	GridSquare *gs5 = grid->gridSquareAtPos( physics->getWorldPosition() + Ogre::Vector3(-bounds.x,0,0) );
	GridSquare *gs6 = grid->gridSquareAtPos( physics->getWorldPosition() + Ogre::Vector3(-bounds.x,0,-bounds.z) );
	GridSquare *gs7 = grid->gridSquareAtPos( physics->getWorldPosition() + Ogre::Vector3(0,0,-bounds.z) );
	GridSquare *gs8 = grid->gridSquareAtPos( physics->getWorldPosition() + Ogre::Vector3(bounds.x,0,-bounds.z) );
	GridSquare *gs9 = grid->gridSquareAtPos( physics->getWorldPosition() + Ogre::Vector3(bounds.x*2,0,0) );
	GridSquare *gs10 = grid->gridSquareAtPos( physics->getWorldPosition() + Ogre::Vector3(-bounds.x*2,0,0) );
	GridSquare *gs11 = grid->gridSquareAtPos( physics->getWorldPosition() + Ogre::Vector3(0,0,-bounds.z*2) );
	GridSquare *gs12 = grid->gridSquareAtPos( physics->getWorldPosition() + Ogre::Vector3(0,0,bounds.z*2) );


	if (gs0 != NULL)
	{
		Cube *glowTile = new Cube(this->gameObject->game, 0);
    	glowTile->transform->setWorldScale(Ogre::Vector3(2.5, .125, 2.5));
    	glowTile->physics->disableCollider();
    	glowTile->renderer->setMaterial("SquareGlow2");
    	glowTile->transform->setWorldPosition(gs0->gameObject->physics->getWorldPosition() + Ogre::Vector3(0,10,0));
    	glowTile->renderer->setEnabled(false);
    	glowTiles.push_back(glowTile);
		inRangeSquares.push_back(gs0);
	}

	if (gs1 != NULL)
	{
		Cube *glowTile = new Cube(this->gameObject->game, 0);
    	glowTile->transform->setWorldScale(Ogre::Vector3(2.5, .125, 2.5));
    	glowTile->physics->disableCollider();
    	glowTile->renderer->setMaterial("SquareGlow2");
    	glowTile->transform->setWorldPosition(gs1->gameObject->physics->getWorldPosition() + Ogre::Vector3(0,10,0));
    	glowTile->renderer->setEnabled(false);
    	glowTiles.push_back(glowTile);
		inRangeSquares.push_back(gs1);
	}

	if (gs2 != NULL)
	{
		Cube *glowTile = new Cube(this->gameObject->game, 0);
    	glowTile->transform->setWorldScale(Ogre::Vector3(2.5, .125, 2.5));
    	glowTile->physics->disableCollider();
    	glowTile->renderer->setMaterial("SquareGlow2");
    	glowTile->transform->setWorldPosition(gs2->gameObject->physics->getWorldPosition() + Ogre::Vector3(0,10,0));
    	glowTile->renderer->setEnabled(false);
    	glowTiles.push_back(glowTile);
		inRangeSquares.push_back(gs2);
	}

	if (gs3 != NULL)
	{
		Cube *glowTile = new Cube(this->gameObject->game, 0);
    	glowTile->transform->setWorldScale(Ogre::Vector3(2.5, .125, 2.5));
    	glowTile->physics->disableCollider();
    	glowTile->renderer->setMaterial("SquareGlow2");
    	glowTile->transform->setWorldPosition(gs3->gameObject->physics->getWorldPosition() + Ogre::Vector3(0,10,0));
    	glowTile->renderer->setEnabled(false);
    	glowTiles.push_back(glowTile);
		inRangeSquares.push_back(gs3);
	}

	if (gs4 != NULL)
	{
		Cube *glowTile = new Cube(this->gameObject->game, 0);
    	glowTile->transform->setWorldScale(Ogre::Vector3(2.5, .125, 2.5));
    	glowTile->physics->disableCollider();
    	glowTile->renderer->setMaterial("SquareGlow2");
    	glowTile->transform->setWorldPosition(gs4->gameObject->physics->getWorldPosition() + Ogre::Vector3(0,10,0));
    	glowTile->renderer->setEnabled(false);
    	glowTiles.push_back(glowTile);
		inRangeSquares.push_back(gs4);
	}

	if (gs5 != NULL)
	{
		Cube *glowTile = new Cube(this->gameObject->game, 0);
    	glowTile->transform->setWorldScale(Ogre::Vector3(2.5, .125, 2.5));
    	glowTile->physics->disableCollider();
    	glowTile->renderer->setMaterial("SquareGlow2");
    	glowTile->transform->setWorldPosition(gs5->gameObject->physics->getWorldPosition() + Ogre::Vector3(0,10,0));
    	glowTile->renderer->setEnabled(false);
    	glowTiles.push_back(glowTile);
		inRangeSquares.push_back(gs5);
	}

	if (gs6 != NULL)
	{
		Cube *glowTile = new Cube(this->gameObject->game, 0);
    	glowTile->transform->setWorldScale(Ogre::Vector3(2.5, .125, 2.5));
    	glowTile->physics->disableCollider();
    	glowTile->renderer->setMaterial("SquareGlow2");
    	glowTile->transform->setWorldPosition(gs6->gameObject->physics->getWorldPosition() + Ogre::Vector3(0,10,0));
    	glowTile->renderer->setEnabled(false);
    	glowTiles.push_back(glowTile);
		inRangeSquares.push_back(gs6);
	}

	if (gs7 != NULL)
	{
		Cube *glowTile = new Cube(this->gameObject->game, 0);
    	glowTile->transform->setWorldScale(Ogre::Vector3(2.5, .125, 2.5));
    	glowTile->physics->disableCollider();
    	glowTile->renderer->setMaterial("SquareGlow2");
    	glowTile->transform->setWorldPosition(gs7->gameObject->physics->getWorldPosition() + Ogre::Vector3(0,10,0));
    	glowTile->renderer->setEnabled(false);
    	glowTiles.push_back(glowTile);
		inRangeSquares.push_back(gs7);
	}

	if (gs8 != NULL)
	{
		Cube *glowTile = new Cube(this->gameObject->game, 0);
    	glowTile->transform->setWorldScale(Ogre::Vector3(2.5, .125, 2.5));
    	glowTile->physics->disableCollider();
    	glowTile->renderer->setMaterial("SquareGlow2");
    	glowTile->transform->setWorldPosition(gs8->gameObject->physics->getWorldPosition() + Ogre::Vector3(0,10,0));
    	glowTile->renderer->setEnabled(false);
    	glowTiles.push_back(glowTile);
		inRangeSquares.push_back(gs8);
	}

	if (gs9 != NULL)
	{
		Cube *glowTile = new Cube(this->gameObject->game, 0);
    	glowTile->transform->setWorldScale(Ogre::Vector3(2.5, .125, 2.5));
    	glowTile->physics->disableCollider();
    	glowTile->renderer->setMaterial("SquareGlow2");
    	glowTile->transform->setWorldPosition(gs9->gameObject->physics->getWorldPosition() + Ogre::Vector3(0,10,0));
    	glowTile->renderer->setEnabled(false);
    	glowTiles.push_back(glowTile);
		inRangeSquares.push_back(gs9);
	}

	if (gs10 != NULL)
	{
		Cube *glowTile = new Cube(this->gameObject->game, 0);
    	glowTile->transform->setWorldScale(Ogre::Vector3(2.5, .125, 2.5));
    	glowTile->physics->disableCollider();
    	glowTile->renderer->setMaterial("SquareGlow2");
    	glowTile->transform->setWorldPosition(gs10->gameObject->physics->getWorldPosition() + Ogre::Vector3(0,10,0));
    	glowTile->renderer->setEnabled(false);
    	glowTiles.push_back(glowTile);
		inRangeSquares.push_back(gs10);
	}

	if (gs11 != NULL)
	{
		Cube *glowTile = new Cube(this->gameObject->game, 0);
    	glowTile->transform->setWorldScale(Ogre::Vector3(2.5, .125, 2.5));
    	glowTile->physics->disableCollider();
    	glowTile->renderer->setMaterial("SquareGlow2");
    	glowTile->transform->setWorldPosition(gs11->gameObject->physics->getWorldPosition() + Ogre::Vector3(0,10,0));
    	glowTile->renderer->setEnabled(false);
    	glowTiles.push_back(glowTile);
		inRangeSquares.push_back(gs11);
	}

	if (gs12 != NULL)
	{
		Cube *glowTile = new Cube(this->gameObject->game, 0);
    	glowTile->transform->setWorldScale(Ogre::Vector3(2.5, .125, 2.5));
    	glowTile->physics->disableCollider();
    	glowTile->renderer->setMaterial("SquareGlow2");
    	glowTile->transform->setWorldPosition(gs12->gameObject->physics->getWorldPosition() + Ogre::Vector3(0,10,0));
    	glowTile->renderer->setEnabled(false);
    	glowTiles.push_back(glowTile);
		inRangeSquares.push_back(gs12);
	}

}

void Tower::Update() {
	GameObject::Update();

	for (int i = 0; i < inRangeSquares.size(); ++i) {
		GridSquare *square = inRangeSquares[i];
		Ogre::Vector3 tilePosition = square->gameObject->transform->getWorldPosition();

		if (square != NULL && square->enemy != NULL) {
			// Rotate tower to face first enemy it can find
			Ogre::Vector3 enemyPosition = square->enemy->gameObject->transform->getWorldPosition();
			Ogre::Vector3 towerPosition = this->gameObject->transform->getWorldPosition();
			this->gameObject->transform->sceneNode->lookAt(enemyPosition, Ogre::Node::TransformSpace::TS_WORLD, Ogre::Vector3::NEGATIVE_UNIT_X);	

			if (Time::time > timeLastAttack + weaponCooldownTime) {
				timeLastAttack = Time::time;
				square->enemy->Attacked();
			}
			// Lock lookAt() rotation to only along the y-axis
			Ogre::Quaternion newRotation = this->gameObject->transform->sceneNode->getOrientation();
			newRotation.x = 0.0f;
			newRotation.z = 0.0f;
			this->gameObject->transform->sceneNode->setOrientation(newRotation);
			return;
		}
	}

	if (this->gameObject->game->viewMode == true)
	{
		for (int i = 0; i < glowTiles.size(); ++i)
		{
			glowTiles[i]->renderer->setEnabled(true);
		}
	}
	else
	{
		for (int i = 0; i < glowTiles.size(); ++i)
		{
			glowTiles[i]->renderer->setEnabled(false);
		}
	}
}

void Tower::FixedUpdate() {

}

