#pragma once

#include "SFML\Graphics.hpp"

#include <unordered_map>

#include "Engine.h"

class World
{
private:
	sf::RenderWindow window;

	std::string currentState;
	std::unordered_map<std::string, Engine> states;

	bool running;

	const int fps;

public:
	static const int DEFAULT_FPS;

	World(int, int, std::string);
	World(int, int, std::string, int);
	~World();

	void start();
	void stop();

	Engine& addState(std::string);
	Engine& getState(std::string);
	void setState(std::string);
};

