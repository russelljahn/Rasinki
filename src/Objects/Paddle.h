#include "GameObject.h"

class Paddle : public GameObject {
	public:
		Paddle(Game *attachedGame);
		void Start();
};