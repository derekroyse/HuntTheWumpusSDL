#include "Game.h"
#include "Display.h"
#include "wumpus.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <time.h>

// Constructor
Game::Game(int w, int h):m_brunning(false), SCREEN_HEIGHT(h), SCREEN_WIDTH(w), m_icommand(0) {}

// Initialize SDL
void Game::init(const char* title) {
	// Set main game loop sentinel
	m_brunning = true;

	// Start SDL
	if (SDL_INIT_EVERYTHING >= 0) {
		// Create window w/error messages
		m_pWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (m_pWindow) {
			// Create renderer
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (!m_pRenderer) {
				std::cout << "Renderer creation failed" << std::endl;
			}
		}
		else {
			std::cout << "Window failed to load" << std::endl;
		}
	}
	else {
		std::cout << "SDL failed to initialize" << std::endl;
	}

	for (int i = 0; i < 8; i++)
		m_Text[i] = "";
}

void Game::run() {
	std::string locationImage;
	// Create game objects
	srand(time(NULL));
	Board test;
	Player player1;
	Wumpus wumpus1;
	TManager = new TextureManager();
	keyboard = new Input();
	gameDisplay = new Display(SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT * 2, SCREEN_WIDTH * 2);

	// Creation of start, end, and help screens.

	// Generate a new board and randomize locations.
	test.generateBoard();
	test.populateBoard();
	player1.updateLocation(test);

	// Set background color to white.
	SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
	
	do {
		// Get input
		m_icommand = keyboard->getInput(0);
		
		// Update board to reflect player/wumpus location
		player1.updateLocation(test);
		wumpus1.updateLocation(test);

		// Display status text messages
		gameDisplay->addText(player1.displayBatWarning(test), m_Text, 1);
		gameDisplay->addText(player1.displayWumpusWarning(test), m_Text, 2);
		gameDisplay->addText(player1.displayPitWarning(test), m_Text, 3);
		gameDisplay->addText(player1.displayActions1(), m_Text, 4);
		gameDisplay->addText(player1.displayActions2(), m_Text, 5);
		gameDisplay->addText("Please enter a direction to move or 'A' to shoot an arrow. ", m_Text, 7);
		
		// Use player input to move character
		if (m_icommand){
			// Print error message if user enters invalid input.
			if (m_icommand != 'w' && m_icommand != 'e' && m_icommand != 'n' && m_icommand != 's' && m_icommand != 'a')
			{
				//gameDisplay->addText("Invalid input.", m_Text, 0);
			}
			else if (m_icommand == QUIT)
				m_brunning = false;
			// Shoot
			else if (m_icommand == 'a')
			{
				if (player1.getArrows() > 0)
				{
					gameDisplay->addText("In which direction would you like to shoot? (N) (S) (E) (W)", m_Text, 6);
				}
				else
					gameDisplay->addText("You don't have any arrows!", m_Text, 6);
			}
			// Standard move
			else
			{
				locationImage = player1.move(m_icommand, test);
				gameDisplay->addText(locationImage, m_Text, 0);
			}

		}

		//get Images
		gameDisplay->getImages(m_Images, locationImage);

		// clear window
		SDL_RenderClear(m_pRenderer);

		// draw images
		TManager->draw(m_pRenderer, m_Images);
		m_Images.clear();

		// write text
		TManager->write(m_pRenderer, m_Text);

		// render window
		SDL_RenderPresent(m_pRenderer);

		// clear old text
		gameDisplay->clearText(m_Text);

		// Triggers upon game end.
		// Print end screen
		// return to title screen

	} while (m_brunning);
}