#ifndef GLOBALS_H
#define GLOBALS_H

namespace globals {
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	const float SPRITE_SCALE = 2.0f;

	const int SCREEN_LEFT = 0;
	const int SCREEN_RIGHT = SCREEN_WIDTH;
	const int SCREEN_TOP = 0;
	const int SCREEN_BOTTOM = SCREEN_HEIGHT;

}

enum Direction {
	LEFT,
	RIGHT,
	UP,
	DOWN
};

struct Vector2 {
	float x, y;
	Vector2() :
		x(0), y(0) {
	}

	Vector2(float x, float y) :
		x(x), y(y) {
	}
};

#endif