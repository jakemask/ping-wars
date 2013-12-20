#include <iostream>

#include "SFML\Graphics.hpp"


int main(char* args[]) {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Ping Wars");

	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);

		//TODO - draw everything here

		window.display();
	}

	

}