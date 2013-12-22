#pragma once

#include "World.h"

#define theWorld PingWars::world
#define theEngine(state) theWorld.getState(state)

class PingWars {
private:
	PingWars();

public:
	static World world;
};