#ifndef __TOWER_H__
#define __TOWER_H__

#include <vector>
#include <string>
#include "../Scripts/GridSquare.h"
#include "../Scripts/Grid.h"



#include "GameObject.h"

class Tower : public GameObject {
	public:
		Tower(Game *attachedGame);
		Tower(Game *attachedGame, std::string entityName);
		~Tower();

		void Start();
		void Update();
		void FixedUpdate();
		void Initialize();

		void OnCollision(Ogre::Vector3 point, GameObject* collidedWith);

		std::vector<GridSquare *> inRangeSquares;
		std::vector<Cube *> glowTiles;
		Grid *grid;
	private:
		float weaponCooldownTime;
		float timeLastAttack;
};




#endif