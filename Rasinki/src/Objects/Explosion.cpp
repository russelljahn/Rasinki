#include "Explosion.h"
#include "GameObject.h"
#include "Time.h"
Explosion::Explosion(Game *attachedGame) : GameObject(attachedGame){
	Start();
}
Explosion::~Explosion() {

}
void Explosion::Start() {
	//timeRemaining = 1;
	ostringstream nameCoverter;
	nameCoverter << "explosion";
	nameCoverter << id;
	transform = new Transform(this, game->getSceneRoot());
	particleSystem = game->getSceneManager()->createParticleSystem(nameCoverter.str(), "explosionTemplate");
	// create a particle system named explosions using the explosionTemplate
	// fast forward 1 second  to the point where the particle has been emitted
	particleSystem->fastForward(1);
	particleSystem->setSpeedFactor(40);
	// attach the particle system to a scene node
	transform->sceneNode->attachObject(particleSystem);
	physics = NULL;
}


void Explosion::Update() {
	GameObject::Update();
	timeRemaining -= Time::deltaTime;
	if (timeRemaining <= 0) {
		//particleSystem->fastForward(10);
	}
}

void Explosion::FixedUpdate() {

}

