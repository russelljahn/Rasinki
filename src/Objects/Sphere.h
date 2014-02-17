#include "GameObject.h"

class Sphere : public GameObject {
	public:
		Sphere(Game *attachedGame);
		void Start();
		void Update();
		void FixedUpdate();

		void Kill();
};