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

void Entity::State::addComponent(Component* c) {
	this->components[&typeid(*c)] = c;
}





/* Entity */

Entity::Entity() {}
Entity::~Entity() {}

void Entity::addState(std::string state) {
	this->states[state];
}

void Entity::setState(std::string state) {
	this->currentState = state;
	engine->updateEntity(this);
}

void Entity::addComponent(std::string state, Component* c) {
	this->states.at(state).addComponent(c);
	if(state == currentState) engine->updateEntity(this);
}

void Entity::addComponent(Component* c) {
	this->addComponent(currentState, c);
}

std::unordered_map<const type_info*, Component*> Entity::getComponents(std::initializer_list<const type_info*> list) {

	std::unordered_map<const type_info*, Component*> map;
	for (const type_info* i : list) {
		map[i] = states[currentState].components[i];
	}
	return map;
}