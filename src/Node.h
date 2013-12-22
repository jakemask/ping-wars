#pragma once

#include <unordered_map>

#include "Entity.h"

template<class... Cs>
class Node {
public:
	Node(Entity* e) : components(e->getComponents({ (&typeid(Cs))... })), entity(e) {}

	template<class C> C* getComponent() {
		if (components.count(&typeid(C)) != 0)
			return static_cast<C*>(components[&typeid(C)]);
		else return NULL;
	}

	Entity* getEntity() { return entity; }

private:
	Entity* entity;
	std::unordered_map<const type_info*,Component*> components;
};