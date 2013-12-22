
#include "PingWars.h"

#include "SplashSystem.h"

World PingWars::world(800, 600, "Ping Wars");

int main(char* args[]) {

	Engine& splash = theWorld.addState("splash");

	splash.addSystem(new SplashSystem(),0);
	
	theWorld.start();

}