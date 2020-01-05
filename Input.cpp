#include "Input.h"

//gets called when a key is pressed
void Input::keyDownEvent(const SDL_Event &event) {

	switch (event.key.keysym.scancode) {
		case SDL_SCANCODE_LEFT:
			this->_left = -1;
			break;
		case SDL_SCANCODE_RIGHT:
			this->_right = 1;
			break;
		case SDL_SCANCODE_UP:
			this->_up = -1;
			break;
		case SDL_SCANCODE_DOWN:
			this->_down = 1;
			break;
		default:
			break;
	}
}

//gets called when a key is released
void Input::keyUpEvent(const SDL_Event &event) {
	switch (event.key.keysym.scancode) {
		case SDL_SCANCODE_LEFT:
			this->_left = 0;
			break;
		case SDL_SCANCODE_RIGHT:
			this->_right = 0;
			break;
		case SDL_SCANCODE_UP:
			this->_up = 0;
			break;
		case SDL_SCANCODE_DOWN:
			this->_down = 0;
			break;
		default:
			break;
	}
}

//sets axis stuff in player
int* Input::getDir(char dir) {
	switch (dir) {
	case 'l':
		return &this->_left;
		break;
	case 'r':
		return &this->_right;
		break;
	case 'u':
		return &this->_up;
		break;
	case 'd':
		return &this->_down;
		break;
	default:
		break;
	}
}