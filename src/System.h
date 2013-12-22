#pragma once

#include "Family.h"

class ISystem {
public:
	virtual bool start() = 0;
	virtual void update(float dt) = 0;
	virtual void stop() = 0;

};

template<class... Cs>
class System : public ISystem
{
friend class Engine;

protected:
	Family<Cs...>* family;

};

