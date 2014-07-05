#include "Game.h"

int main(int argc, char** args) {
	// Create game instance; width/height of window
	Game* HuntTheWumpus = new Game(700, 800);

	// Initialize SDL
	HuntTheWumpus->init("Hunt the Wumpus");

	// Start main game loop
	HuntTheWumpus->run();
	
	return 0;
}