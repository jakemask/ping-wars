#pragma once
#include <unordered_map>

#include "Node.h"
#include "Entity.h"
#include "Engine.h"

class ISystem {
public:
	virtual bool start() = 0;
	virtual void update(float dt) = 0;
	virtual void stop() = 0;

};

class IFamily {
public:
	virtual void newEntity(Entity*) = 0;
	virtual void updateEntity(Entity*) = 0;
	virtual void removeEntity(Entity*) = 0;
};

template<class... Cs>
class Family;

template<class... Cs>
class System : public ISystem
{
friend class Engine;

protected:
	Family<Cs...>* family = NULL;

public:
	virtual void entityAdded(Node<Cs...>*) {}
	virtual void entityRemoved(Node<Cs...>*) {}

};

template<class... Cs>
class Family : public IFamily
{
friend class Engine;
private:
	std::unordered_map<Entity*, Node<Cs...>*> nodeMap;
	std::unordered_set<Node<Cs...>*> nodeSet;

	System<Cs...>* system;
public:

	Family(System<Cs...>* s, const std::unordered_set<Entity*> entities) : system(s) {
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
		if (e->hasComponents({ (&typeid(Cs))... })) {
			Node<Cs...>* node = new Node<Cs...>(e);
			nodeMap[e] = node;
			nodeSet.insert(node);
			system->entityAdded(node);
		}
	}

	virtual void updateEntity(Entity* e) {
		// if we already have this entity, check for removal
		if (nodeMap.count(e) > 0) {

			if (!e->hasComponents({ (&typeid(Cs))... }))
				this->removeEntity(e);

			// else, we don't have this entity, treat it as new
		}
		else this->newEntity(e);
	}

	virtual void removeEntity(Entity* e) {
		if (nodeMap.count(e) > 0)
		{
			
			Node<Cs...>* node = nodeMap[e];
			system->entityRemoved(node);

			nodeMap.erase(e);
			nodeSet.erase(node);

			delete node;

		}
	}

	virtual const std::unordered_set<Node<Cs...>*>& getNodeList() {
		return nodeSet;
	}
};
