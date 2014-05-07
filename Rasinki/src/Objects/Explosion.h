#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__


#include "GameObject.h"
#include "OgreParticleSystem.h"
#include "OgreSceneManager.h"


class Explosion : public GameObject {
	public:
		Explosion(Game *attachedGame);
		~Explosion();

		void Start();
		void Update();
		void FixedUpdate();

		void OnCollision(Ogre::Vector3 point, GameObject* collidedWith);
	private:
		Ogre::ParticleSystem* particleSystem;
		float timeRemaining;

};




#endif