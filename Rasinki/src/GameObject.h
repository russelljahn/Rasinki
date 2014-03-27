
#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <vector>
#include <string>

#include <OgreEntity.h>

#include <OISEvents.h>
#include <OISKeyboard.h>


#include "Game.h"
#include "Components/Component.h"
#include "Components/Transform.h"
#include "Components/Physics.h"
#include "Components/Renderer.h"



/* Forward declarations. */
class Game;
class Component;
class Transform;
class Physics;
class Renderer;

/* 
	A GameObject is an aggregation of components with different functionality.
	Components that a GameObject is required to have are as follows:

	Transform
	Scripting
*/
class GameObject {
	
	
	public:
		std::string name;
		int id;
		bool enabled;
		int playerNum;
		GameObject *gameObject; // Pointer to self.
		Transform *transform; // TODO: Make this protected but retrievable through GetComponentOfType<>()!
		Game *game; // TODO: Figure out how to make this unneeded to be public for abstraction-sake!
		Physics* physics;
		Renderer* renderer;
		
		GameObject(Game *attachedGame);
		GameObject(Game *atatchedGame, int playerNum);
		~GameObject();
		
		void Start();
		void Update();
		void FixedUpdate();
		void OnCollision(Ogre::Vector3 point, GameObject* collidedWith);
		void Kill();

		template <typename ComponentType>
		ComponentType* GetComponentOfType();

		template <typename ComponentType>
		ComponentType AddComponentOfType() {
			ComponentType *newComponent = new ComponentType(this);
			components.push_back(newComponent);
		}

		template <typename ComponentType>
		void KillComponentOfType();

	protected:
		std::vector<Component *> components;

		static int nextAvailableId;
};


#endif