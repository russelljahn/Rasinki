#include "GameObject.h"

class Sphere : public GameObject {
	public:
		float radius;

		Sphere(Game *attachedGame, float radius = 100);
		void Start();
		void Update();
		void FixedUpdate();

		void Kill();
};