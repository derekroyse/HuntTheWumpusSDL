#ifndef DISPLAY_H
#define DISPLAY_H

#include "Image.h"
#include <vector>
#include <SDL.h>
#include "GLOBALS.h"

class Display {
	private:
		const int SCREEN_HEIGHT;
		const int SCREEN_WIDTH;
	
		Image* testBackground;
		Image* testCave;

	public:
		~Display() {}

		// Create world and all images
		Display::Display(int sH, int sW, int lH, int lW) : SCREEN_HEIGHT(sH), SCREEN_WIDTH(sW){
			// Background/UI
			testBackground = new Image("assets/wumpusFrame.png", 0, 0, 700, 800, 0, 0, 1, false, 1, 1, true);
			// Standard cave
			testCave = new Image("assets/cave.png", 49, 49, 602, 302, 0, 0, 1, false, 1, 1, true);
			// Bat
			// Wumpus
			// Pit
			// Start
			// Lose
			// Win
		}

		// Populate image vector in game
		void Display::getImages(std::vector < Image * > &f_Images) {
			f_Images.push_back(testBackground);
			f_Images.push_back(testCave);
		}

		void Display::getText(std::vector < std::string > &f_Text){
			//f_Text.clear();

			//f_Text.push_back("Player X: " + std::to_string(Dilbert->getX()));
			//f_Text.push_back("Player Y: " + std::to_string(Dilbert->getY()));
		}

		void Display::addText(std::string input, std::string f_Text[], int position)
		{
			f_Text[position] = input;
			//f_Text.push_back(input);
		}

		void Display::clearText(std::string f_Text[])
		{
			for (int i = 1; i < 8; i++)
				f_Text[i] = "";
		}
};

#endif