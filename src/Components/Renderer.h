
#ifndef __GAMEOBJECT_COMPONENT_RENDERER_H__
#define __GAMEOBJECT_COMPONENT_RENDERER_H__

#include <OgreVector3.h>
#include <OgreSceneNode.h>

#include "GameObject.h"


/* Forward declarations. */
class GameObject;

/* 
	A Renderer component encapsulates information on the rendering 
	and materials for a GameObject.
*/
class Renderer : Component {
	
	public:
		GameObject *gameObject;
		Ogre::SceneNode *parent;
		Ogre::SceneNode *sceneNode;

		Renderer(GameObject *attachedGameObject, Ogre::SceneNode *parent);

};


#endif