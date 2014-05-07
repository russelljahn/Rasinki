#ifndef __TOWER_H__
#define __TOWER_H__

#include <vector>
#include "../Scripts/GridSquare.h"
#include "../Scripts/Grid.h"



#include "GameObject.h"

class Tower : public GameObject {
	public:
		Tower(Game *attachedGame);
		Tower(Game *attachedGame, int pNum);
		~Tower();

		void Start();
		void Update();
		void FixedUpdate();
		void Initialize();

		void OnCollision(Ogre::Vector3 point, GameObject* collidedWith);

		std::vector<GridSquare *> inRangeSquares;
		std::vector<Cube *> glowTiles;
		Grid *grid;

    //Upgrades
    bool upgraded;
	private:
		float weaponCooldownTime;
		float timeLastAttack;
};




#endif
