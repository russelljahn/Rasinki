
#ifndef __GAMEOBJECT_COMPONENT_SCRIPT_H__
#define __GAMEOBJECT_COMPONENT_SCRIPT_H__

#include <OgreVector3.h>
#include <OgreSceneNode.h>
#include <btBulletDynamicsCommon.h>

#include "GameObject.h"



/* 
	A script allows you to code gameplay behavior for a GameObject.
*/
class Script : public Component {
	
	public:
		Script(GameObject *attachedGameObject);

};


#endif