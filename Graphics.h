#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>

//forward declared here so stop compiler complaining
//need to clean this up
struct SDL_Window;
struct SDL_Renderer;

class Graphics {
public:
	Graphics();
	~Graphics();

	//load image into sprite into _spritesheets map
	//if that doesn't exist
	SDL_Surface* loadImage(const std::string &filePath);

	//draws a texture to a certain part of the screen
	void blitSurface(SDL_Texture* source, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle);

	//renders to screen
	//every frame of drawing > clear the renderer > 
	//blitsurface (draw) to the surface > flip >
	//which displays the drawing
	void flip();

	//clears the screen
	void clear();

	//return the renderer
	SDL_Renderer* getRenderer() const;

private:
	SDL_Window* _window;
	SDL_Renderer* _renderer; 
};

#endif

//clean up _spriteSheets?
