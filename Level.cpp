#include "Level.h"
#include "Graphics.h"
#include <SDL.h>

Level::Level() {

}

Level::Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics) :
			_mapName(mapName),
			_spawnPoint(spawnPoint),
			_size(Vector2(0, 0))
{
	this->loadMap(mapName, graphics);
}

Level::~Level() {

}

void Level::loadMap(std::string mapName, Graphics &graphics) {
	this->_backgroundTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("bkBlue.png"));
	this->_size = Vector2(1280, 960);
}

void Level::update(float elapsedTime) {

}

void Level::draw(Graphics &graphics) {
	//draw the background
	SDL_Rect sourceRect = {0, 0, 64, 64};
	SDL_Rect destRect;
	//"tiling" 
	for (int x = 0; x < this->_size.x / 64; x++) {
		for (int y = 0; y < this->_size.y / 64; y++) {
			destRect.x = (int) (x * 64 * globals::SPRITE_SCALE);
			destRect.y = (int) (y * 64 * globals::SPRITE_SCALE);
			destRect.w = (int) (64 * globals::SPRITE_SCALE);
			destRect.h = (int) (64 * globals::SPRITE_SCALE);
			graphics.blitSurface(this->_backgroundTexture, &sourceRect, &destRect);
		}
	}
}