#pragma once

#include "System.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class SoundComponent : public Component {
public:
	sf::SoundBuffer buffer;
	sf::Sound sound;

	int timesPlayed;

	SoundComponent(std::string);
	~SoundComponent();
};
class ImageComponent : public Component {
public:
	sf::Texture texture;
	sf::Sprite sprite;

	ImageComponent(std::string);
	~ImageComponent();
};

class SplashSystem : public System<SoundComponent,ImageComponent>
{
public:
	SplashSystem();
	~SplashSystem();

	virtual void entityAdded(Node<SoundComponent,ImageComponent>*);
	virtual void entityRemoved(Node<SoundComponent, ImageComponent>*);

	virtual bool start();
	virtual void update(float);
	virtual void stop();
};

