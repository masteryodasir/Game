#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>

class Input {
public:
	void keyUpEvent(const SDL_Event &event);
	void keyDownEvent(const SDL_Event &event);

	int* getDir(char dir);

private:
	int _left = 0, _right = 0, _up = 0, _down = 0;
};

#endif

