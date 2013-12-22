#pragma once

#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Node.h"
#include "Entity.h"
#include "System.h"

class Engine
{
private:
	std::map<int, std::unordered_set<ISystem*>> systems;
	std::unordered_map<ISystem*, int> priorities;
	std::unordered_map<ISystem*, IFamily*> families;
	std::unordered_set<Entity*> entities;
	
public:

	Engine();
	~Engine();

	void addEntity(Entity* e);
	void updateEntity(Entity* e);
	void removeEntity(Entity* e);

	template<class... Cs>
	void addSystem(System<Cs...>* system, int priority) {
		
		system->family = new Family<Cs...>(system,this->entities);

		if (system->start()) {
			
			families[system] = system->family;
			
			systems[priority].insert(system);
			priorities[system] = priority;

		} else {
			delete system->family;
			system->family = NULL;
		}
	}

	void removeSystem(ISystem*);

	void update(float dt);
};

