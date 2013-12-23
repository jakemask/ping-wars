#include <chrono>
#include <thread>

#include "World.h"

#define FPS(X) (1000/X)

typedef std::chrono::milliseconds milliseconds;

/* Static Members */

const int World::DEFAULT_FPS = 60;

/* Constructors/Deconstructor */

World::World(int w, int h, std::string name) : World(w, h, name, DEFAULT_FPS) {}

World::World(int w, int h, std::string name, int fps)
	: window(sf::VideoMode(w, h), name),
	  currentState(""),
	  onDeck(""),
	  destructOld(false),
	  fps(fps) {}

World::~World() {}

/* Methods */

void World::start() {
	if (states.size() == 0) throw new std::exception("World has no states");

	this->running = true;
	float dt = 0;

	while (this->running) {
		// Start Timer
		auto startTime = std::chrono::steady_clock::now();

		// Poll all events
		sf::Event event;
		while (this->window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				this->stop();
				break;
			}
		}

		// Clear the Screen
		window.clear(sf::Color::Black);

		// Update & Render
		this->states[this->currentState].update(dt);

		for (sf::Drawable* d : this->drawables[currentState])
			this->window.draw(*d);

		// Draw
		window.display();

		// Sleep
		std::this_thread::sleep_until(startTime + milliseconds(FPS(this->fps)));

		// Calculate next dt
		auto timeElapsed = std::chrono::steady_clock::now() - startTime;
		dt = std::chrono::duration_cast<milliseconds>(timeElapsed).count() / 1000.0f;

		if (onDeck != currentState) {
			if (destructOld) {
				this->states.erase(currentState);
				destructOld = false;
			}
			currentState = onDeck;

		}
	}
}

void World::stop() {
	this->running = false;
	this->window.close();
}

Engine& World::addState(std::string state) {
	if (state == "") throw std::exception("Empty string is an invalid state name");

	if (states.size() == 0) currentState = onDeck = state;
	return this->states[state];
}

Engine& World::getState(std::string state) {
	return this->states.at(state);
}

void World::setState(std::string state, bool destructOld = false) {
	this->onDeck = state;
	this->destructOld = destructOld;
}

void World::add(sf::Drawable* d) {
	drawables[currentState].insert(d);
}

bool World::contains(sf::Drawable* d) {
	return drawables[currentState].count(d) > 0;
}

void World::remove(sf::Drawable* d) {
	drawables[currentState].erase(d);
}