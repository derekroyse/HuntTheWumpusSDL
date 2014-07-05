#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "Image.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>
#include <iostream>

class TextureManager {
private:
	//draw thingies
	SDL_Rect m_dstRect;
	SDL_Rect m_srcRect;
	SDL_Texture* m_pTexture;

	const int SCREEN_HEIGHT;
	const int SCREEN_WIDTH;

public:
	TextureManager() : SCREEN_HEIGHT(800), SCREEN_WIDTH(700) {}
	~TextureManager() {}

	//just for one image
	void TextureManager::draw(SDL_Renderer* f_pRenderer, std::vector < Image* > f_Images) {
		//get middle of the screen;
		int origX = 0;
		int origY = 0;

		//a lot of the stuff here will need removed from the loop
		for (int i = 0; i < f_Images.size(); i++) {

			const int WALKING_ANIMATION_FRAMES = 5;
			std::vector<SDL_Rect> gSpriteClips(WALKING_ANIMATION_FRAMES);
			gSpriteClips = f_Images[i]->getAnimationArray();

			const char* fileName = f_Images[i]->getFileName();
			SDL_Surface* pTempSurface = IMG_Load(fileName);

			//color keying/transparency
			SDL_SetColorKey(pTempSurface, SDL_TRUE, SDL_MapRGB(pTempSurface->format, 0, 128, 0));
			//rotation
			int m_toRotate = f_Images[i]->getRotation();
			m_pTexture = SDL_CreateTextureFromSurface(f_pRenderer, pTempSurface);

			if (f_Images[i]->isAnimated() == true)
			{
				m_srcRect.w = gSpriteClips[f_Images[i]->getFrame()].w;
				m_srcRect.h = gSpriteClips[f_Images[i]->getFrame()].h;
				m_srcRect.x = gSpriteClips[f_Images[i]->getFrame()].x;
				m_srcRect.y = gSpriteClips[f_Images[i]->getFrame()].y;
			}
			else
			{
				//source rectangle w and h = destination rectangle w and h
				m_srcRect.w = m_dstRect.w = f_Images[i]->getWidth();
				m_srcRect.h = m_dstRect.h = f_Images[i]->getHeight();
				m_srcRect.x = f_Images[i]->getSpriteX();
				m_srcRect.y = f_Images[i]->getSpriteY();
			}

			//free and destroy surface
			SDL_FreeSurface(pTempSurface);
			pTempSurface = NULL;

			//origX = f_Images[i]->getX();
			//origY = f_Images[i]->getY();

			//width and height
			m_dstRect.w = f_Images[i]->getWidth();
			m_dstRect.h = f_Images[i]->getHeight();
			m_dstRect.x = f_Images[i]->getX();
			m_dstRect.y = f_Images[i]->getY();

			// determine if image should be flipped
			SDL_RendererFlip m_toFlip = SDL_FLIP_NONE;
			if (f_Images[i]->isFlipped() == true)
				m_toFlip = SDL_FLIP_HORIZONTAL;

			//draw image
			SDL_RenderCopyEx(f_pRenderer, m_pTexture, &m_srcRect, &m_dstRect, m_toRotate, NULL, m_toFlip);

			// free and destroy texture
			SDL_DestroyTexture(m_pTexture);
			m_pTexture = NULL;
		}
	}

	void TextureManager::write(SDL_Renderer* f_pRenderer, std::string f_Text[]) {
		TTF_Init();
		TTF_Font* textFont = TTF_OpenFont("verdana.ttf", 14);
		SDL_Color textColor = { 255, 255, 255 };
		int counter = 0;

		for (int i = 0; i < 8; i++) {
			// If the text isn't blank.
			if (f_Text[i] != ""){
				// convert string to char array
				char* cstr = new char[f_Text[i].length() + 1];
				std::strcpy(cstr, f_Text[i].c_str());

				// create a surface with the text
				SDL_Surface* pTempSurface = TTF_RenderText_Solid(textFont, cstr, textColor);

				// create a texture from the surface
				m_pTexture = SDL_CreateTextureFromSurface(f_pRenderer, pTempSurface);

				//set image dimensions
				m_srcRect.w = pTempSurface->w;
				m_srcRect.h = pTempSurface->h;

				//color keying/transparency
				//SDL_SetColorKey(pTempSurface, SDL_TRUE, SDL_MapRGB(pTempSurface->format, 0, 128, 0));

				// set text position
				// each line starts 15 pixels below the last
				m_dstRect.w = pTempSurface->w;
				m_dstRect.h = pTempSurface->h;
				m_dstRect.x = 55;
				m_dstRect.y = (counter * 20) + 555;
				counter++;

				//draw text
				SDL_RenderCopyEx(f_pRenderer, m_pTexture, &m_srcRect, &m_dstRect, NULL, NULL, SDL_FLIP_NONE);

				// free and destroy texture
				SDL_DestroyTexture(m_pTexture);
				m_pTexture = NULL;

				//free and destroy surface
				SDL_FreeSurface(pTempSurface);
				pTempSurface = NULL;
			}
		}
		// free font
		TTF_CloseFont(textFont);
		textFont = NULL;
	}
};

#endif // TextureManager.h