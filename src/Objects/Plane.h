#include "GameObject.h"

class Plane : public GameObject {
	public:
		Ogre::Vector3 normal;
		float pos;
		Ogre::Plane plane;
		Plane(Game *attachedGame, Ogre::Vector3 normal = Ogre::Vector3::UNIT_Y, float pos = 0);
		void Start();
		void Update();
		void FixedUpdate();

		void Kill();
};