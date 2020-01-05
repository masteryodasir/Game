#ifndef GAME_H
#define GAME_H

#include <SDL.h>

#include "Player.h"
#include "Enemy.h"
#include "Level.h"

class Graphics;

class Game {
public:
	Game();
	~Game();

private:
	void gameLoop();
	void draw(Graphics &graphics, CollidingSprite* sprites[], int arr[]);
	void update(float elapsedTime, CollidingSprite* sprites[], int arr[]);

	CollidingSprite* _player;
	CollidingSprite* _enemy1;
	CollidingSprite* _enemy2;
	CollidingSprite* _enemy3;
	Level _level;
};

#endif

