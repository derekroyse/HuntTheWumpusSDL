#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "TextureManager.h"
#include "Display.h"
#include "wumpus.h"
#include "Input.h"
#include <vector>
#include "GLOBALS.h"

class Game {
private:
	// Game loop sentinel
	bool m_brunning;

	// Input variable
	int m_icommand;

	// Window size
	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;

	//SDL vars
	SDL_Renderer* m_pRenderer;
	SDL_Window* m_pWindow;

	// Game components
	TextureManager* TManager;
	Input* keyboard;
	Display* gameDisplay;

	// Image and text vectors
	std::vector < Image* > m_Images;
	std::string m_Text[8];

public:
	// Constructor & Destructor
	Game(int, int);
	~Game() {};

	// Main game loop
	void run(void);

	// Initialize SDL
	void init(const char*);
};

#endif