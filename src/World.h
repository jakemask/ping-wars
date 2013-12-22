#pragma once

#include <SFML\Graphics.hpp>

#include <unordered_set>
#include <unordered_map>

#include "Engine.h"

class World
{
private:
	sf::RenderWindow window;

	std::string currentState;
	std::string onDeck;
	std::unordered_map<std::string, Engine> states;
	std::unordered_map<std::string, std::unordered_set<sf::Drawable*>> drawables;

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

	void add(sf::Drawable*);
	bool contains(sf::Drawable*);
	void remove(sf::Drawable*);

};

