#pragma once

#include "System.h"

class SoundComponent : Component {};
class ImageComponent : Component {};

class SplashSystem : public System<SoundComponent,ImageComponent>
{
public:
	SplashSystem();
	~SplashSystem();

	virtual bool start();
	virtual void update(float);
	virtual void stop();
};

