#ifndef ENEMYSPAWNER__INCLUDE__
#define ENEMYSPAWNER__INCLUDE__
#include "../Components/Script.h"
#include "GameObject.h"

class Grid;

class EnemySpawner : public Script {
public:
	EnemySpawner(GameObject *attachedGameObject);

	void Start(void);
	void Update(void);

	float spawnPeriod;
	Grid *grid;

private:
	float timeSinceLastSpawn;
};
#endif