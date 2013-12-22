#include <iostream>

#include "PingWars.h"
#include "SplashSystem.h"

SoundComponent::SoundComponent(std::string filename) : timesPlayed(0) {
	if (!buffer.loadFromFile(filename))
		std::cerr << "Error loading " << filename << std::endl;
	sound.setBuffer(buffer);

	
}

ImageComponent::ImageComponent(std::string filename) {
	if (!texture.loadFromFile(filename))
		std::cerr << "Error loading " << filename << std::endl;
	sprite.setTexture(texture);
}

SplashSystem::SplashSystem() : System<SoundComponent, ImageComponent>() {}

SplashSystem::~SplashSystem() {}

void SplashSystem::entityAdded(Node<SoundComponent, ImageComponent>* n) {
	n->getComponent<SoundComponent>()->sound.play();
	theWorld.add(&n->getComponent<ImageComponent>()->sprite);
}

void SplashSystem::entityRemoved(Node<SoundComponent, ImageComponent>* n) {
	theWorld.remove(&n->getComponent<ImageComponent>()->sprite);
}


bool SplashSystem::start() {
	return true;
}

void SplashSystem::update(float dt) {
	for (Node<SoundComponent, ImageComponent>* n : this->family->getNodeList()) {

		if (n->getComponent<SoundComponent>()->sound.getStatus() == sf::Sound::Status::Stopped) {
			theWorld.setState("menu");
		}

		ImageComponent* ic = n->getComponent<ImageComponent>();
		ic->sprite.setPosition(110, 0);
		ic->sprite.setScale(9, 9);
	}
	std::cout << std::endl;
	
}

void SplashSystem::stop() {
	//TODO
}