#include "Graphics.h"
#include "Globals.h"

/* Graphics class implementation
*  Holds all info for game graphics
*/

Graphics::Graphics() {
	//0 for no flags
	SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 0, &this->_window, &this->_renderer);
	SDL_SetWindowTitle(this->_window, "Demo");
}

Graphics::~Graphics() {
	SDL_DestroyRenderer(this->_renderer);
	SDL_DestroyWindow(this->_window);
}

SDL_Surface* Graphics::loadImage(const std::string& filePath) {
	return IMG_Load(filePath.c_str());
}

void Graphics::blitSurface(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle) {
	//whatever you pass here will copy
	//to renderer
	SDL_RenderCopy(this->_renderer, texture, sourceRectangle, destinationRectangle);
}

void Graphics::flip() {
	//draws renderer to surface
	SDL_RenderPresent(this->_renderer);
}

void Graphics::clear() {
	//clears the renderer
	SDL_RenderClear(this->_renderer);
}

SDL_Renderer* Graphics::getRenderer() const {
	return this->_renderer;
}