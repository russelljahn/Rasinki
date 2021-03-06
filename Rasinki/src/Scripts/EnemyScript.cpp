#include "EnemyScript.h"
#include "GridSquare.h"
#include "Time.h"
#include "Objects/Explosion.h"
#include "EnemySpawner.h"

EnemyScript::EnemyScript(GameObject *attachedGameObject) : Script(attachedGameObject) {
	//moveSpeed = 500.0f;
	//hitPoints = 5;
	destination = gameObject->transform->getWorldPosition();
	// gameObject->renderer->setMaterial("Examples/Chrome_Red");
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
	// std::cout << "FINDING PATH TO 0, 0" << std::endl;
	_currentPath = pathfinder->FindPath(0, 0);
}
void EnemyScript::Update() {
	gameObject->renderer->mAnimationState->addTime(0.5f*Time::deltaTime);

	Ogre::Vector3 veloc = Ogre::Vector3::ZERO;
	if (_currentPath.size() == 0) {
	 	//_currentPath = pathfinder->FindPath(0, 0);
	 	gameObject->renderer->setEnabled(false);
	 	gameObject->physics->setLinearVelocity(veloc);
	 	gameObject->game->playerList[0]->loseHealth();
	 	gameObject->Kill();
	 	return;
	 }
	if (_currentPath.size() > 0) {
		lastSquare = currentSquare;
		GridSquare* square = grid->gridSquareAtPos(gameObject->physics->getWorldPosition());
		if (square != currentSquare) {
			if (lastSquare != NULL) {
				lastSquare->RemoveEnemy(this);
				lastSquare = currentSquare;
			}
			currentSquare = square;
			if (currentSquare != NULL) {
				currentSquare->AddEnemy(this);
			}
		}
	}
	while (veloc.squaredLength () < Time::deltaTime*moveSpeed*2 && _currentPath.size() > 0) {
		veloc = (_currentPath.front()->getPosition() - gameObject->physics->getWorldPosition());
		veloc.y = 0;
		if (veloc.squaredLength () < Time::deltaTime*moveSpeed*2) {

			assert (grid != NULL);
			lastSquare = currentSquare;
			currentSquare = grid->gridSquareAtPos(gameObject->physics->getWorldPosition());
			pathfinder->setCurrentGridSquare(gameObject->physics->getWorldPosition());
			_currentPath.pop_front();
		}
	}
	veloc.y = 0;
	veloc.normalise();
	Ogre::Vector3 src = gameObject->transform->sceneNode->getOrientation() * Ogre::Vector3::UNIT_Z;
	src.y = 0;
	src.normalise();
	Ogre::Quaternion quat = src.getRotationTo(veloc);
	gameObject->transform->sceneNode->rotate(quat);
	gameObject->transform->sceneNode->yaw(Ogre::Degree(180));

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
void EnemyScript::Attacked(int damage) {
// 	std::cout << "ENEMY SHOT ID: " << gameObject->id << " HP BEFORE HIT: " << hitPoints << std::endl;
// 	std::cout << "ENEMY SHOT ID: " << gameObject->id << " DAMAGE: " << damage << std::endl;
	hitPoints -= damage;
	std::cout << "ENEMY SHOT ID: " << gameObject->id << " HP REMAINING: " << hitPoints << std::endl;
	Explosion* ex = new Explosion(gameObject->game);
	ex->transform->setWorldPosition(gameObject->transform->getWorldPosition() + Ogre::Vector3(0, 120, 0));
	ex->transform->setWorldScale(Ogre::Vector3(4,4,4));
  if (gameObject->destroyed)
    return;
	if (hitPoints <= 0) {
		gameObject->game->playerList[0]->changeGold(gameObject->game->enemySpawner->waveVector[gameObject->game->enemySpawner->waveNum].reward);
		currentSquare->RemoveEnemy(this);
		gameObject->game->playerList[0]->scored();
		gameObject->Kill();
		gameObject->renderer->setEnabled(false);
	}
}
