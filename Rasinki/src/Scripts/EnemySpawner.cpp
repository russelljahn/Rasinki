#include "EnemySpawner.h"
#include "Pathfinder.h"
#include "../Objects/Enemy.h"
#include "EnemyScript.h"

EnemySpawner::EnemySpawner(GameObject* game) : Script(game) {
	timeSinceLastSpawn = 5;
	waveNum = -1;
	numSpawned = 0;
	//MoveSpeed, hitPoints, numToSpawn, timeBetweenSpawns, reward
	spawning = false;
  //Lots of fast easy to kill guys
	Wave wave1(1000, 3, 30, 0.4f, 2);
  //Normal
	Wave wave2(700, 5, 30, 0.4, 5);
  //Slow and tough
	Wave wave3(300, 30, 10, 1, 50);
  //Fast
	Wave wave4(1000, 10, 50, 0.4f, 5);
  //Boss
	Wave wave5(1000, 1, 200, 0.1f, 5);
  //Boss
	Wave wave6(500, 50, 50, 0.7f, 50);
  //Boss
	Wave wave7(500, 100, 40, 0.7f, 100);
  //Boss
	Wave wave8(100, 800, 10, 0.7f, 500);
  //Boss
	Wave wave9(500, 400, 50, 0.7f, 300);
  //Boss
	Wave wave10(1000, 400, 200, 0.1f,1000);
	waveVector.push_back(wave1);
	waveVector.push_back(wave2);
	waveVector.push_back(wave3);
	waveVector.push_back(wave4);
	waveVector.push_back(wave5);
	waveVector.push_back(wave6);
	waveVector.push_back(wave7);
	waveVector.push_back(wave8);
	waveVector.push_back(wave9);
	waveVector.push_back(wave10);
}
void EnemySpawner::Start(){}

void EnemySpawner::Update() {
	if (!spawning) {
		return;
	}
	if (waveNum >= waveVector.size()) {
		waveNum++;
		std::cout << "FINISHED ALL WAVES" << std::endl;
    gameObject->game->enableWinnerMenu();
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
	    	spawning = false;
	    }
	    timeSinceLastSpawn = 0;
      cout << "Wave: " << waveNum << endl;
	}
}
