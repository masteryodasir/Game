#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <string>

class Graphics;

class Sprite {
public:
	Sprite();
	Sprite(Graphics &graphics, const std::string &filePath, float posX, float posY, float width, float height);
	~Sprite();
	float getSY();

protected:
	SDL_Texture* _spriteSheet;

	struct Rect {
		float x, y, w, h;

		Rect() :
			x(0), y(0), w(0), h(0) {
		}

		Rect(float x, float y, float width, float height) :
			x(x), y(y), w(width), h(height) {
		}
	};

	Rect _rect;

private:
};

#endif

