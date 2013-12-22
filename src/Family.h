#pragma once

#include <unordered_map>

#include "Node.h"
#include "Entity.h"

class IFamily {
public:
	virtual void newEntity(Entity*) = 0;
	virtual void updateEntity(Entity*) = 0;
	virtual void removeEntity(Entity*) = 0;
};

template<class... Cs>
class Family : public IFamily
{
private:
	std::unordered_map<Entity*,Node<Cs...>*> nodeMap;
	std::unordered_set<Node<Cs...>*> nodeSet;

public:

	Family(const std::unordered_set<Entity*> entities) {
		for (Entity* e : entities) {
			this->newEntity(e);
		}
	}

	~Family() {
		for (Node<Cs...>* node : this->nodeSet) {
			delete node;
		}
	}

	virtual void newEntity(Entity* e) {
		if (e->hasComponents()) {
			Node<Cs...>* node = new Node<Cs...>(e);
			nodeMap[e] = node;
			nodeSet.insert(node);
		}
	}

	virtual void updateEntity(Entity* e) {
		// if we already have this entity, check for removal
		if (nodeMap.count(e) > 0) {

			if (!e->hasComponents())
				this->removeEntity(e);

			// else, we don't have this entity, treat it as new
		}
		else this->newEntity(e);
	}

	virtual void removeEntity(Entity* e) {
		if (nodeMap.count(e) > 0)
		{
			Node<Cs...>* node = nodeMap[e];

			nodeMap.erase(e);
			nodeSet.erase(node);

			delete node;

		}
	}
};

