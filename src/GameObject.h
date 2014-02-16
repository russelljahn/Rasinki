
#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <vector>
#include <string>

#include <OgreEntity.h>

#include "Game.h"
#include "Components/Component.h"
#include "Components/Transform.h"

/* Forward declarations. */
class Game;
class Component;
class Transform;



/* 
	A GameObject is an aggregation of components with different functionality.
	Components that a GameObject is required to have are as follows:

	Transform
	Scripting
*/
class GameObject {
	
	
	public:
		std::string name;
		bool enabled;

		GameObject(Game &attachedGame);

		void Start();
		void Update();
		void FixedUpdate();

		void Kill();

		template <typename ComponentType>
		ComponentType GetComponentOfType();

		template <typename ComponentType>
		ComponentType AddComponentOfType();

		template <typename ComponentType>
		void KillComponentOfType();


	protected:
		std::vector<Component> components;
		Game &game;

		Transform *transform;
		Ogre::Entity *entity;
};


#endif