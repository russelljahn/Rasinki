#include "GameObject.h"

class Plane : public GameObject {
	public:
		Ogre::Vector3 normal;
		float pos;
		float width;
		float height;
		Ogre::Plane plane;
		Plane(Game *attachedGame, Ogre::Vector3 normal = Ogre::Vector3::UNIT_Y, float pos = 0, float width = 1500 , float height = 1500);
		void Start();
		void Update();
		void FixedUpdate();

		void Kill();
};