#pragma once

#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Node.h"
#include "Entity.h"
#include "System.h"
#include "Family.h"

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
		system->family = new Family<Cs...>(this->entities);
		families[system] = system->family;

		if (system->start()) {
			systems[priority].insert(system);
			priorities[system] = priority;
		}
	}

	void removeSystem(ISystem*);

	void update(float dt);
};

