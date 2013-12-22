#include "Engine.h"


Engine::Engine()
{
}


Engine::~Engine()
{
	for (Entity* e : entities) delete e;
	for (std::pair<ISystem*, IFamily*> f : families) delete f.second;

	for (std::pair<int, std::unordered_set<ISystem*>> p : systems)
		for (ISystem* s : p.second)
			delete s;
}

void Engine::addEntity(Entity* e) {
	entities.insert(e);
	e->setEngine(this);
	for (std::pair<ISystem*, IFamily*> f : families) {
		f.second->newEntity(e);
	}
}

void Engine::updateEntity(Entity* e) {
	for (std::pair<ISystem*, IFamily*> f : families) {
		f.second->updateEntity(e);
	}
}

void Engine::removeEntity(Entity* e) {
	entities.erase(e);
	for (std::pair<ISystem*, IFamily*> f : families) {
		f.second->removeEntity(e);
	}
}

void Engine::removeSystem(ISystem* system) {

	// get the priority of the system
	int priority = priorities.at(system);
	priorities.erase(system);

	// remove the system from it's priority level
	systems[priority].erase(system);

	// stop the system
	system->stop();


	// if there are no systems left at this level, remove it
	if (systems[priority].size() == 0)
		systems.erase(priority);


}

void Engine::update(float dt) {
	for (std::pair<int, std::unordered_set<ISystem*>> p : systems)
		for (ISystem* s : p.second)
			s->update(dt);
}