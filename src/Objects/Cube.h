#include "GameObject.h"

class Cube : public GameObject {
	public:

		Cube(Game *attachedGame);
		void Start();
		void Update();
		void FixedUpdate();

		void Kill();
};