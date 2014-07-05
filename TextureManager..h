#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "Image.h"
#include <SDL.h>
#include <SDL_image.h>
#include <list>

class TextureManager {
private:
	//draw thingies
	SDL_Rect m_dstRect;
	SDL_Rect m_srcRect;
	SDL_Texture* m_pTexture;
public:
	TextureManager() {}
	~TextureManager() {}

	void draw(SDL_Renderer* f_pRenderer, Image* f_Image);
};

#endif // TextureManager.h