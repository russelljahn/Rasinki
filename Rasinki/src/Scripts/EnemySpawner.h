#ifndef ENEMYSPAWNER__INCLUDE__
#define ENEMYSPAWNER__INCLUDE__
#include "../Components/Script.h"
#include "GameObject.h"

class Grid;

struct Wave {
public:
	int moveSpeed;
	int hitPoints;
	int numToSpawn;
	float timeBetweenSpawns;
	Wave(int moveSpeed, int hitPoints, int numToSpawn, float timeBetweenSpawns) {
		this->moveSpeed = moveSpeed;
		this->hitPoints = hitPoints;
		this->numToSpawn = numToSpawn;
		this->timeBetweenSpawns = timeBetweenSpawns; 
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
private:
	float timeSinceLastSpawn;
	int numSpawned;
	int waveNum;
	std::vector<Wave> waveVector; 
	bool spawning;
};
#endif