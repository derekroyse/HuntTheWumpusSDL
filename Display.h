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
	
		Image* background;
		Image* cave;
		Image* bat;
		Image* wumpus;
		Image* pit;
		Image* face;

	public:
		~Display() {}

		// Create world and all images
		Display::Display(int sH, int sW, int lH, int lW) : SCREEN_HEIGHT(sH), SCREEN_WIDTH(sW){
			// Background/UI
			background = new Image("assets/wumpusFrame.png", 0, 0, 700, 800, 0, 0, 1, false, 1, 1, true);
			// Standard cave
			cave = new Image("assets/cave.png", 49, 49, 602, 302, 0, 0, 1, false, 1, 1, true);
			// Bat
			bat = new Image("assets/bat.png", 49, 49, 602, 302, 0, 0, 1, false, 1, 1, true);
			// Wumpus
			wumpus = new Image("assets/wumpus.png", 49, 49, 602, 302, 0, 0, 1, false, 1, 1, true);
			// Pit
			pit = new Image("assets/pit.png", 49, 49, 602, 302, 0, 0, 1, false, 1, 1, true);
			// Face
			//std::vector<SDL_Rect> faceSpriteData(5);
			//	faceSpriteData[0].x = 17;
			//	faceSpriteData[0].y = 94;
			//	faceSpriteData[0].w = 68;
			//	faceSpriteData[0].h = 68;

			//	faceSpriteData[1].x = 18;
			//	faceSpriteData[1].y = 172;
			//	faceSpriteData[1].w = 68;
			//	faceSpriteData[1].h = 68;

			//	faceSpriteData[2].x = 101;
			//	faceSpriteData[2].y = 173;
			//	faceSpriteData[2].w = 68;
			//	faceSpriteData[2].h = 68;

			//	faceSpriteData[3].x = 177;
			//	faceSpriteData[3].y = 173;
			//	faceSpriteData[3].w = 68;
			//	faceSpriteData[3].h = 68;

			//	faceSpriteData[4].x = 252;
			//	faceSpriteData[4].y = 173;
			//	faceSpriteData[4].w = 68;
			//	faceSpriteData[4].h = 68;
			face = new Image("assets/doomguy.gif", 300, 400, 97, 100, 0, 0, 1, false, 1, 1, true);
			//face = new Image("assets/doomguy.gif", 300, 400, 97, 100, 0, 0, 1, false, 1, 1, true, faceSpriteData);
			// Start
			// Lose
			// Win
		}

		// Populate image vector in game
		void Display::getImages(std::vector < Image * > &f_Images, std::string input) {
			// Always use the background and face
			f_Images.push_back(background);
			f_Images.push_back(face);
			
			// Select a view image based on where the player is.
			if (input.find("PIT") != std::string::npos)
				f_Images.push_back(pit);
			else if (input.find("Wumpus") != std::string::npos)
				f_Images.push_back(wumpus);
			else if (input.find("bat") != std::string::npos)
				f_Images.push_back(bat);
			else
				f_Images.push_back(cave);
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