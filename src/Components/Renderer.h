
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
class Renderer {
	
	public:
		GameObject *gameObject;
		Ogre::Entity *entity;


		Renderer(GameObject *attachedGameObject);
		void setEnabled(bool enabled);
		bool isEnabled();

		void setMaterial(std::string materialName);

	protected:
		bool enabled;
};


#endif