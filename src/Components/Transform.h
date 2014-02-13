
#ifndef __GAMEOBJECT_COMPONENT_TRANSFORM_H__
#define __GAMEOBJECT_COMPONENT_TRANSFORM_H__

#include <OgreVector3.h>
#include "Component.h"
#include "GameObject.h"


/* Forward declarations. */
class GameObject;



/* 
	A Transform component encapsulates the position, scale, rotatation, and 
	parent/children hierachy of a GameObject.
*/
class Transform : Component {
	
	public:

		Ogre::SceneNode &sceneNode;
		Transform(GameObject &attachedGameObject, SceneNode &parent);



		const Ogre::Vector3& getLocalPosition() const {
			return sceneNode.getPosition();
		}
		const Ogre::Vector3& getWorldPosition() const {
			return Ogre::Node::convertLocalToWorldPosition( sceneNode.getPosition() );
		}
		void setLocalPosition(const OgreVector3& newLocalPosition) {
			sceneNode.setPosition(newLocalPosition);
		}
		void setWorldPosition(const OgreVector3& newWorldPosition) {
			sceneNode.setPosition( Ogre::Node::convertWorldToLocalPosition(newWorldPosition) );
		}



		const Ogre::Vector3& getLocalScale() const {
			return sceneNode.getScale();
		}
		const Ogre::Vector3& getWorldScale() const {
			return Ogre::Node::convertLocalToWorldScale( sceneNode.getScale() );
		}
		void setLocalScale(const OgreVector3& newLocalScale) {
			sceneNode.setScale(newLocalScale);
		}
		void setWorldScale(const OgreVector3& newWorldScale) {
			sceneNode.setScale( Ogre::Node::convertWorldToLocalScale(newWorldScale) );
		}




		const Ogre::Vector3& getLocalRotationEuler() const {

		}
		const Ogre::Vector3& getWorldRotationEuler() const {
			
		}
		void setLocalRotationEuler(const OgreVector3& newLocalRotationEuler) {

		}
		void setWorldRotationEuler(const OgreVector3& newWorldRotationEuler) {
			
		}

};


#endif