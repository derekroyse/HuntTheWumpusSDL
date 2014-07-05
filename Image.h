#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>
#include <SDL.h>

class Image {
	private:
		//location on screen
		int m_ix;
		int m_iy;
		//image attributes
		int m_iwidth;
		int m_iheight;
		//layer; z-index
		int m_ilayer;
		//animated
		bool m_banimated;
		int m_icurrentFrame;
		int m_itotalFrames;
		//file name
		const char* m_sfname;
		//image location
		int m_ispriteX;
		int m_ispriteY;
		//is flipped
		bool m_bflipped;
		//is static
		bool m_bstatic;
		// degrees rotated
		int m_rotation;
		// sprite animation data
		std::vector<SDL_Rect> animationArray;

	public:
		Image::Image() :m_banimated(false), m_bflipped(false), m_bstatic(false) {
		}
		Image::~Image() {
			delete this;
		}
		Image::Image(const char* fname, int x, int y, int width, int height, int sX, int sY, int layer, bool a, int cf, int tf, bool f_static) : m_bflipped(false) {
			m_sfname = fname;
			m_ix = x;
			m_iy = y;
			m_iwidth = width;
			m_iheight = height;
			m_ispriteX = sX;
			m_ispriteY = sY;
			m_ilayer = layer;
			m_banimated = a;
			m_icurrentFrame = cf;
			m_itotalFrames = tf;
			m_bstatic = f_static;
		}

		Image::Image(const char* fname, int x, int y, int width, int height, int sX, int sY, int layer, bool a, int cf, int tf, bool f_static, std::vector<SDL_Rect> animationData) {
			m_sfname = fname;
			m_ix = x;
			m_iy = y;
			m_iwidth = width;
			m_iheight = height;
			m_ispriteX = sX;
			m_ispriteY = sY;
			m_ilayer = layer;
			m_banimated = a;
			m_icurrentFrame = cf;
			m_itotalFrames = tf;
			m_bstatic = f_static;
			animationArray.resize(tf);
			for (int i = 0; i < animationArray.size(); i++)
				animationArray[i] = animationData[i];
		}

		//setters
		void Image::load(const char* fname, int x, int y, int width, int height, int sX, int sY, int layer, bool a, int cf, int tf, bool f_static) {
			m_sfname = fname;
			m_ix = x;
			m_iy = y;
			m_iwidth = width;
			m_iheight = height;
			m_ispriteX = sX;
			m_ispriteY = sY;
			m_ilayer = layer;
			m_banimated = a;
			m_icurrentFrame = cf;
			m_itotalFrames = tf;
		}
		void Image::setX(int x) {
			m_ix = x;
		}
		void Image::setY(int y) {
			m_iy = y;
		}
		void Image::setFlipped(bool b) {
			m_bflipped = b;
		}
		void Image::setCurrentFrame(int i) {
			m_icurrentFrame = i;
		}
		void Image::setStatic(bool b) {
			m_bstatic = b;
		}

		void Image::setRotation(int i)
		{
			m_rotation = i;
		}


		//getters
		bool Image::isFlipped() {
			return m_bflipped;
		}
		int Image::getX() {
			return m_ix;
		}
		int Image::getY() {
			return m_iy;
		}
		int Image::getWidth() {
			return m_iwidth;
		}
		int Image::getHeight() {
			return m_iheight;
		}
		int Image::getLayer() {
			return m_ilayer;
		}
		bool Image::isAnimated() {
			return m_banimated;
		}
		int Image::getFrame() {
			return m_icurrentFrame;
		}
		int Image::getTotalFrames() {
			return m_itotalFrames;
		}
		const char* Image::getFileName() {
			return m_sfname;
		}
		int Image::getSpriteX() {
			return m_ispriteX;
		}
		int Image::getSpriteY() {
			return m_ispriteY;
		}
		bool Image::isStatic() {
			return m_bstatic;
		}

		int Image::getRotation()
		{
			return m_rotation;
		}

		std::vector<SDL_Rect> Image::getAnimationArray(){
			return animationArray;
		}
};

#endif // Image.h