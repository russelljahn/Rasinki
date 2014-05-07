#ifndef ENEMYSPAWNER__INCLUDE__
#define ENEMYSPAWNER__INCLUDE__
#include "../Components/Script.h"
#include "GameObject.h"

class Grid;
class EnemySpawner;

struct Wave {
public:
	int moveSpeed;
	int hitPoints;
	int numToSpawn;
	float timeBetweenSpawns;
  int reward;
	Wave(int moveSpeed, int hitPoints, int numToSpawn, float timeBetweenSpawns, int reward) {
		this->moveSpeed = moveSpeed;
		this->hitPoints = hitPoints;
		this->numToSpawn = numToSpawn;
		this->timeBetweenSpawns = timeBetweenSpawns; 
    this->reward = reward;
	}
};

class EnemySpawner : public Script {
public:
	EnemySpawner(GameObject *attachedGameObject);

	void Start(void);
	void Update(void);
	bool isSpawning() { return spawning; }
	void startSpawning() { spawning = true; }

	Grid *grid;
	int waveNum;
	std::vector<Wave> waveVector; 
private:
	float timeSinceLastSpawn;
	int numSpawned;
	bool spawning;
};
#endif
