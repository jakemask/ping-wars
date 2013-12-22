#pragma once

#include <unordered_map>
#include <unordered_set>
#include <typeinfo>

#include "Component.h"

//forward declaration
class Engine;

class Entity
{
private:
	class State {
	public:
		std::unordered_map<const std::type_info*, Component*> components;

		State();
		~State();

		template<typename T> void addComponent(Component*);
		template<typename T> void removeComponent();
		template<typename T> T* getComponent();
	};

private:
	std::string name;
	std::string currentState;
	std::unordered_map<std::string, State> states;

	Engine* engine;

public:
	Entity(std::string);
	~Entity();

	std::string getName();

	void addState(std::string);
	void setState(std::string);

	void setEngine(Engine*);

	template<typename T> void addComponent(std::string, T*);
	template<typename T> void addComponent(T*);

	template<typename T> void removeComponent(std::string);
	template<typename T> void removeComponent();

	template<typename T> T* getComponent(std::string);
	template<typename T> T* getComponent();

	std::unordered_map<const type_info*, Component*> getComponents(std::initializer_list<const type_info*> list);
	bool hasComponents(std::initializer_list<const type_info*>);

};

/* State */

template<typename T>
void Entity::State::addComponent(Component* c) {
	this->components[&typeid(T)] = c;
}

template<typename T>
void Entity::State::removeComponent() {
	if (components.count(&typeid(T)) != 0) {

		delete this->components[&typeid(T)];
		this->components.erase(&typeid(T));
	}
}

template<typename T>
T* Entity::State::getComponent() {
	if (components.count(typeid(T)) != 0)
		return static_cast<T*>(components[&typeid(T)]);
	else return NULL;
}

/* Entity */

template<typename T>
void Entity::addComponent(std::string state, T* c) {
	this->states.at(state).addComponent<T>(c);
	if (state == currentState && engine) engine->updateEntity(this);
}

template<typename T>
void Entity::addComponent(T* c) {
	this->addComponent<T>(currentState, c);
}


template<typename T>
void Entity::removeComponent(std::string state) {
	this->states.at(state).removeComponent<T>();
	if (state == currentState) engine->updateEntity(this);
}
template<typename T>
void Entity::removeComponent() {
	this->removeComponent<T>(currentState);
}

template<typename T>
T* Entity::getComponent(std::string state) {
	return static_cast<T*>(this->states.at(state).getComponent<T>());
}

template<typename T>
T* Entity::getComponent() {
	return static_cast<T*>(this->getComponent<T>(currentState));
}

