
#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <vector>
#include <string>

#include <OgreEntity.h>

#include "Game.h"
#include "Components/Component.h"
#include "Components/Transform.h"
#include "Components/Physics.h"

/* Forward declarations. */
class Game;
class Component;
class Transform;
class Physics;

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
		Game &game;

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
		Transform *transform;

	protected:
		std::vector<Component> components;
		Physics* physics;
		Ogre::Entity *entity;
};


#endif