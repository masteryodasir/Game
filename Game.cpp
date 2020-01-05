#include <algorithm>

#include "Game.h"
#include "Graphics.h"
#include "Input.h"
#include <iostream>

/* Game class
*  This class holds all info for game loop
*/

namespace {
	const int FPS = 50;
	const int MAX_FRAME_TIME = 5 * 1000 / FPS;
}

Game::Game() {
	//initializes audio, events, graphics, etc
	//all subsystems
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameLoop();
}

Game::~Game() {
	SDL_Quit();
}

void Game::gameLoop() {
	Graphics graphics;
	Input input;
	SDL_Event event;

	Player pl = Player(graphics, input, 10, 10, 64, 64, 0);
	Enemy en1 = Enemy(graphics, 100, 75, 64, 64, 1, pl.getXoffset(), pl.getYoffset());
	Enemy en2 = Enemy(graphics, 200, 100, 64, 64, 2, pl.getXoffset(), pl.getYoffset());
	Enemy en3 = Enemy(graphics, 300, 300, 64, 64, 3, pl.getXoffset(), pl.getYoffset());

	int arr[4] = {0, 1, 2, 3};

	this->_player = &pl;
	this->_enemy1 = &en1;
	this->_enemy2 = &en2;
	this->_enemy3 = &en3;
	this->_level = Level("map 1", Vector2(100, 100), graphics);

	CollidingSprite* sprites[4] = { this->_player , this->_enemy1, this->_enemy2, this->_enemy3 };

	//get the last time since sdl library loaded
	int LAST_UPDATE_TIME = SDL_GetTicks();
	//while running in loop
	while (true) {
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				//this check is to ensure 
				//doesn't keep checking if 
				//key is held down
				if (event.key.repeat == 0) {
					input.keyDownEvent(event);
				}
			}
			else if (event.type == SDL_KEYUP) {
				input.keyUpEvent(event);
			}
			else if (event.type == SDL_QUIT) {
				return;
			}
		}

		for (int i = 0; i < 4; i++) {
			sprites[i]->move();
		}

		const int CURRENT_TIME_MS = SDL_GetTicks();
		// Get the amount of time passed since beginning of 
		// frame to now.
		const int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
		//pass in minimum of the 2

		this->update((float)std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME), sprites, arr);
		LAST_UPDATE_TIME = CURRENT_TIME_MS;

		this->draw(graphics, sprites, arr);
	}
}

void Game::draw(Graphics &graphics, CollidingSprite* sprites[], int arr[]) {
	graphics.clear();
	this->_level.draw(graphics);
	for (int i = 0; i < 4; i++) {
		sprites[arr[i]]->draw(graphics);
	}
	graphics.flip();
}

void Game::update(float elapsedTime, CollidingSprite* sprites[], int arr[]) {
	/*physics is based on elapsed time
	*as to have the time from a > b 
	*be exactly the same between slow and fast
	*computers
	*but this can look choppy
	*/
	
	for (int i = 0; i < 4; i++) {
		//default isStatic = true
		sprites[i]->collision(sprites, arr, elapsedTime);
	}
	this->_level.update(elapsedTime);
	for (int i = 0; i < 4; i++) {
		sprites[i]->update(elapsedTime);
	}
	
}