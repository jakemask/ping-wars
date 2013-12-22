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

		void addComponent(Component*);
		template<typename T> void removeComponent();
		template<typename T> T* getComponent();
	};

private:

	std::string currentState;
	std::unordered_map<std::string, State> states;

	Engine* engine;

public:
	Entity();
	~Entity();

	void addState(std::string);
	void setState(std::string);

	void addComponent(std::string, Component*);
	void addComponent(Component*);

	template<typename T> void removeComponent(std::string);
	template<typename T> void removeComponent();

	template<typename T> T* getComponent(std::string);
	template<typename T> T* getComponent();

	std::unordered_map<const type_info*, Component*> getComponents(std::initializer_list<const type_info*> list);

	template<typename... Ts> bool hasComponents();

};

/* State */

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

template<typename... Cs>
bool Entity::hasComponents() {
	bool has = true;

	[](...){}((has &= this->getComponent<Cs>() != NULL)...);

	return has;
}

