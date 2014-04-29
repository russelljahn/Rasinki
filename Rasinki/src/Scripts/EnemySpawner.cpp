#include "EnemySpawner.h"
#include "Pathfinder.h"
#include "EnemyScript.h"
#include "../Objects/Cube.h"

EnemySpawner::EnemySpawner(GameObject* game) : Script(game) {
	spawnPeriod = 5;
	timeSinceLastSpawn = 0;
}
void EnemySpawner::Start(){}

void EnemySpawner::Update() {
	timeSinceLastSpawn += gameObject->game->getDeltaTime();
	if (timeSinceLastSpawn > spawnPeriod) {
		Cube *enemy = new Cube(gameObject->game, 1);
	    Pathfinder *enemyPathfinder = enemy->AddComponentOfType<Pathfinder>();
	    enemyPathfinder->Initialize(grid);
	    EnemyScript *enemyScript = enemy->AddComponentOfType<EnemyScript>();
	    enemy->transform->setWorldPosition(gameObject->transform->getWorldPosition());
	    enemyScript->Initialize(enemyPathfinder);
	    enemy->transform->setLocalScale(Ogre::Vector3(1, 1, 1));
	    enemyScript->grid = grid;
	    enemy->name = "enemy";
	    gameObject->game->gameObjects.push_back(enemy);
	    timeSinceLastSpawn = 0;
	}
}