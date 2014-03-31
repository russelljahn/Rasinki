#include "GameObject.h"

class Cube : public GameObject {
	public:

		Cube(Game *attachedGame, float mass);
		void Start();
		float mass;

};