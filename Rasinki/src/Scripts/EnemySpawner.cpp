#include "EnemySpawner.h"
#include "Pathfinder.h"
#include "../Objects/Enemy.h"
#include "EnemyScript.h"

EnemySpawner::EnemySpawner(GameObject* game) : Script(game) {
	timeSinceLastSpawn = 5;
	waveNum = 0;
	numSpawned = 0;
	//MoveSpeed, hitPoints, numToSpawn, timeBetweenSpawns
	spawning = false;
	Wave wave1(700, 1, 30, 0.4f);
	Wave wave2(500, 3, 20, 1);
	Wave wave3(300, 10, 5, 2);
	Wave wave4(700, 3, 20, 1);
	Wave wave5(500, 5, 20, 0.7f);
	waveVector.push_back(wave1);
	waveVector.push_back(wave2);
	waveVector.push_back(wave3);
	waveVector.push_back(wave4);
	waveVector.push_back(wave5);
}
void EnemySpawner::Start(){}

void EnemySpawner::Update() {
	if (!spawning) {
		return;
	}
	if (waveNum >= waveVector.size()) {
		waveNum = 0;
		std::cout << "FINISHED ALL WAVES" << std::endl;
		return;
	}
	timeSinceLastSpawn += gameObject->game->getDeltaTime();
	if (timeSinceLastSpawn > waveVector[waveNum].timeBetweenSpawns) {
		Enemy *enemy = new Enemy(gameObject->game, 1.0);
	    Pathfinder *enemyPathfinder = enemy->AddComponentOfType<Pathfinder>();
	    enemyPathfinder->Initialize(grid);
	    EnemyScript *enemyScript = enemy->AddComponentOfType<EnemyScript>();
	    enemyScript->hitPoints = waveVector[waveNum].hitPoints;
	    enemyScript->moveSpeed = waveVector[waveNum].moveSpeed;
	    Ogre::Vector3 pos = gameObject->transform->getWorldPosition();
	    pos.y += 50;
	    enemy->transform->setWorldPosition(pos);
	    enemyScript->Initialize(enemyPathfinder);
	    enemy->transform->setLocalScale(Ogre::Vector3(1, 1, 1));
	    enemyScript->grid = grid;
	    enemy->name = "enemy";
	    numSpawned++;
	    if (numSpawned >= waveVector[waveNum].numToSpawn) {
	    	numSpawned = 0;
	    	waveNum++;
	    	spawning = false;
	    }
	    timeSinceLastSpawn = 0;
	}
}