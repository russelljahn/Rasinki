
#ifndef __WALL_SCRIPT_H__
#define __WALL_SCRIPT_H__

#include "../Components/Script.h"

/* 
	Blocks that add points to player when hit.
*/
class Wall : public Script {

	public:
		Wall(GameObject *attachedGameObject);

		void Start(void);
		void Update(void);

};


#endif