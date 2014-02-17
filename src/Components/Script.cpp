
#include "Script.h"


Script::Script(GameObject *attachedGameObject) {
	this->gameObject = attachedGameObject;
};



void Script::Start() {
	Component::Start();
}



void Script::Update() {
	Component::Update();
	
}



void Script::FixedUpdate() {
	Component::FixedUpdate();
	
}
