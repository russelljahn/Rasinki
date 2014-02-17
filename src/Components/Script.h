
#ifndef __GAMEOBJECT_COMPONENT_SCRIPT_H__
#define __GAMEOBJECT_COMPONENT_SCRIPT_H__

#include <OgreVector3.h>
#include <OgreSceneNode.h>

#include "GameObject.h"


/* Forward declarations. */
class GameObject;

/* 
	A script allows you to code gameplay behavior for a GameObject.
*/
class Script : Component {
	
	public:
		GameObject *gameObject;
		Ogre::SceneNode *parent;
		Ogre::SceneNode *sceneNode;

		Script(GameObject *attachedGameObject, Ogre::SceneNode *parent);

};


#endif