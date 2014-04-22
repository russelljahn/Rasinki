#include "EnemyScript.h"

EnemyScript::EnemyScript(GameObject *attachedGameObject) : Script(attachedGameObject) {
	moveSpeed = 150.0f;
	destination = gameObject->physics->getWorldPosition();
	gameObject->renderer->setMaterial("Examples/Chrome_Red");
	Start();
}
void EnemyScript::Start() {

	//_currentPath = pathfinder->FindPath(0, 0);
}
void EnemyScript::Initialize(Pathfinder* pathfinder) {
	this->pathfinder = pathfinder;
	pathfinder->setCurrentGridSquare(gameObject->transform->getWorldPosition());
	std::cout << "FINDING PATH TO 0, 0" << std::endl;
	_currentPath = pathfinder->FindPath(0, 0);
}
void EnemyScript::Update() {
	Ogre::Vector3 veloc = Ogre::Vector3::ZERO;
	if (_currentPath.size() > 0) {
		std::cout << _currentPath.front()->getPosition() << " " << gameObject->physics->getWorldPosition() << std::endl;
	}
	while (veloc.squaredLength () < 10 && _currentPath.size() > 0) {
		veloc = (_currentPath.front()->getPosition() - gameObject->physics->getWorldPosition());
		veloc.y = 0;
		if (veloc.squaredLength() < 10) {
			_currentPath.pop_front();
		}
	}
	veloc.normalise();
	veloc *= moveSpeed;
	gameObject->physics->setLinearVelocity(veloc);
}