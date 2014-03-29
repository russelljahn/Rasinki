
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
		Ogre::AnimationState *animationState; // The current animation state of the object

		Renderer(GameObject *attachedGameObject);
		~Renderer();
		void setEnabled(bool enabled);
		bool isEnabled();

		void setMaterial(std::string materialName);
		void setAnimationState(std::string animationStateName);
		void setAnimationLoop(bool loop);
		void setAnimationEnabled(bool enabled);
		bool isAnimationEnabled();


	protected:
		bool enabled;
};


#endif