#pragma once

#include <unordered_map>

#include "Entity.h"

template<class... Cs>
class Node {
public:
	Node(Entity* e) : components(e->getComponents({(&typeid(Cs))...})) {}

	template<class C> C* getComponent() {
		if (components.count(&typeid(C)) != 0)
			return static_cast<C*>(components[&typeid(C)]);
		else return NULL;
	}

private:
	std::unordered_map<const type_info*,Component*> components;
};