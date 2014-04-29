#include "EnemyScript.h"
#include "GridSquare.h"

EnemyScript::EnemyScript(GameObject *attachedGameObject) : Script(attachedGameObject) {
	moveSpeed = 500.0f;
	destination = gameObject->transform->getWorldPosition();
	gameObject->renderer->setMaterial("Examples/Chrome_Red");
	Start();
}
void EnemyScript::Start() {
	lastSquare = NULL;
	currentSquare = NULL;
	grid = NULL;
	//_currentPath = pathfinder->FindPath(0, 0);
}
void EnemyScript::Initialize(Pathfinder* pathfinder) {
	this->pathfinder = pathfinder;
	pathfinder->setCurrentGridSquare(gameObject->transform->getWorldPosition());
	// currentSquare = grid->gridSquareAtPos(gameObject->physics->getWorldPosition());
	// lastSquare = currentSquare;
	std::cout << "FINDING PATH TO 0, 0" << std::endl;
	_currentPath = pathfinder->FindPath(0, 0);
}
void EnemyScript::Update() {
	Ogre::Vector3 veloc = Ogre::Vector3::ZERO;
	if (_currentPath.size() > 0) {
		std::cout << _currentPath.front()->getPosition() << " " << gameObject->physics->getWorldPosition() << std::endl;
	}
	while (veloc.squaredLength () < 10 && _currentPath.size() > 0) {
		veloc = (_currentPath.front()->getPosition() - gameObject->physics->getWorldPosition());
		veloc.y = 0;
		if (veloc.squaredLength() < 10) {

			assert (grid != NULL);
			lastSquare = currentSquare;
			currentSquare = grid->gridSquareAtPos(gameObject->physics->getWorldPosition());

			if (lastSquare != currentSquare) {

				if (lastSquare != NULL) {
					lastSquare->RemoveEnemy(this);
				}
				if (currentSquare != NULL) {
					currentSquare->AddEnemy(this);
				}
			}

			pathfinder->setCurrentGridSquare(gameObject->physics->getWorldPosition());
			_currentPath.pop_front();
		}
	}
	veloc.normalise();
	veloc *= moveSpeed;
	//std::cout << "VELOC: " << veloc << std::endl;
	gameObject->physics->setLinearVelocity(veloc);
	 list<PathSquare*>::iterator i;
	for (i = _currentPath.begin(); i != _currentPath.end(); i++) {
    	if (!(*i)->isWalkable()) {
			_currentPath = pathfinder->FindPath(0, 0);
			break;
		}
	}
}
