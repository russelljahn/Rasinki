#include "GameObject.h"

class Paddle : public GameObject {
	public:
		Paddle(Game *attachedGame);
		Paddle(Game *attachedGame, int pNum);
		void Start();
		void Update();
		void FixedUpdate();

		void Kill();
		void OnCollision(Ogre::Vector3 point, GameObject* collidedWith);
};