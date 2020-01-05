#ifndef LEVEL_H
#define LEVEL_H

#include "globals.h"
#include <string>

class Graphics;
struct SDL_Texture;

class Level{
public:
	Level();
	Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics);
	~Level();
	void update(float elapsedTime);
	void draw(Graphics &graphics);

private:
	std::string _mapName;
	Vector2 _spawnPoint;
	Vector2 _size;
	SDL_Texture* _backgroundTexture;

	//will only be called within the class
	void loadMap(std::string mapName, Graphics &graphics);
};

#endif
