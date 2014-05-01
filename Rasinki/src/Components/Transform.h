
#ifndef __GAMEOBJECT_COMPONENT_TRANSFORM_H__
#define __GAMEOBJECT_COMPONENT_TRANSFORM_H__

#include <OgreVector3.h>
#include <OgreSceneNode.h>
#include <OgreNode.h>
#include <OgreQuaternion.h>

#include "GameObject.h"


/* Forward declarations. */
class GameObject;

/* 
	A Transform component encapsulates the position, scale, rotatation, and 
	parent/children hierachy of a GameObject.
*/
class Transform {
	
	public:
		GameObject *gameObject;
		Ogre::SceneNode *parent;
		Ogre::SceneNode *sceneNode;

		Transform(GameObject *attachedGameObject, Ogre::SceneNode *parent);
		~Transform();


		Ogre::Vector3 getLocalPosition() const;
		Ogre::Vector3 getWorldPosition() const;
		void setLocalPosition(const Ogre::Vector3& newLocalPosition);
		void setWorldPosition(const Ogre::Vector3& newWorldPosition);



		Ogre::Vector3 getLocalScale() const;
		Ogre::Vector3 getWorldScale() const;
		void setLocalScale(const Ogre::Vector3& newLocalScale);
		void setWorldScale(const Ogre::Vector3& newWorldScale);




		Ogre::Vector3 getLocalRotationEuler() const;
		Ogre::Vector3 getWorldRotationEuler() const;
		void setLocalRotationEuler(const Ogre::Vector3& newLocalRotationEuler);
		void setWorldRotationEuler(const Ogre::Vector3& newWorldRotationEuler);

};


#endif