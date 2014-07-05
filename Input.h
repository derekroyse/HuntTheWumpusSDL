#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <string>
#include <SDL.h>
#include "GLOBALS.h"

class Input {
	private:
		int m_imouseX;
		int m_imouseY;

		SDL_Event e;
	public:
		Input::Input()
		{
			// Initialize event handler.
			SDL_PollEvent(&e);
		}

		int Input::getInput(bool flipped)
		{
			int returnValue = IDLE;
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_KEYDOWN)
				{
					switch (e.key.keysym.sym)
					{
					case SDLK_n:
						returnValue = 'n';
						break;
					case SDLK_s:
						returnValue = 's';
						break;
					case SDLK_e:
						returnValue = 'e';
						break;
					case SDLK_w:
						returnValue = 'w';
						break;
					case SDLK_ESCAPE:
						returnValue = QUIT;
						break;
					}
				}
				else if (e.type == SDL_KEYUP) {
					returnValue = IDLE;
				}
				else if (e.type == SDL_MOUSEMOTION) {
					SDL_GetMouseState(&m_imouseX, &m_imouseY);
				}
			}
			return returnValue;
		}
		int Input::getMouseX() {
			return m_imouseX;
		}
		int Input::getMouseY() {
			return m_imouseY;
		}
};

#endif // Input.h