#include "Entity.h"

#include "Engine.h"

/* Entity::State */

Entity::State::State() {}

Entity::State::~State()
{
	for (std::pair<const std::type_info*, Component*> pair : components) {
		delete pair.second;
	}
}







/* Entity */

Entity::Entity(std::string name) : currentState(""), engine(NULL), name(name) {
	this->states[currentState];
}
Entity::~Entity() {}

std::string Entity::getName() { return name; }

void Entity::addState(std::string state) {
	this->states[state];
}

void Entity::setState(std::string state) {
	this->currentState = state;
	if(engine) engine->updateEntity(this);
}

void Entity::setEngine(Engine* e) {
	this->engine = e;
}


std::unordered_map<const type_info*, Component*> Entity::getComponents(std::initializer_list<const type_info*> list) {

	std::unordered_map<const type_info*, Component*> map;
	for (const type_info* i : list) {
		map[i] = states[currentState].components[i];
	}
	return map;
}

bool Entity::hasComponents(std::initializer_list<const type_info*> list) {
	bool has = true;
	for (const type_info* i : list) {
		has &= (states[currentState].components.count(i) > 0);
	}

	return has;
}