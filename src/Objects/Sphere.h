#include "GameObject.h"

class Sphere : public GameObject {
	public:
		Sphere(Game *attachedGame, std::string objTyp = "sphere");
		void Start();
};