
#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <vector>
#include <string>
#include "Component.h"

class Component;

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

		GameObject();

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
		// std::vector<Component> components;
		;
		

};


#endif