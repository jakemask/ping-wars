
#include "PingWars.h"

#include "SplashSystem.h"

World PingWars::world(800, 600, "Ping Wars");

int main(char* args[]) {

	Engine& splash = theWorld.addState("splash");

	splash.addSystem(new SplashSystem(),0);

	Entity* e = new Entity("SplashScreen");

	e->addComponent(new SoundComponent("../music/dirigible.wav"));
	e->addComponent(new ImageComponent("../images/dirigible.png")); //TODO

	splash.addEntity(e);
	
	theWorld.start();

}