#ifndef PLAYER_H
#define PLAYER_H

#include "CollidingSprite.h"

class Graphics;
class Input;
class CollidingSprite;

class Player : public CollidingSprite {
public:
	Player();
	Player(Graphics &graphics, Input &input, float x, float y, float width, float height, int id);
	void draw(Graphics &graphics);
	void update(float elapsedTime);

	void move();
	void collision(CollidingSprite* sprites[], int arr[], float elapsedTime, bool isStatic = true);
	void xaxis(int dir);
	void yaxis(int dir);
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void stopMoving();

	void seCol(float sprite[]);


	bool collR(float rect[], float elapsedTime);
	bool collL(float rect[], float elapsedTime);
	bool collU(float rect[], float elapsedTime);
	bool collD(float rect[], float elapsedTime);

	void setupAnimations();
	void sort(CollidingSprite* sprites[], int arr[], float elapsedTime);

	float* getXoffset();
	float* getYoffset();

	struct Map {
		int element, value;
		Map(int element, int value) :
			element(element), value(value) {
		}
	};
private:
	float _hspeed, _vspeed, _xOffset, _yOffset;
	int *_left, *_right, *_up, *_down;
	bool _updateX, _updateY;
	int _sOffset = 0;

	Direction _facing;
};

#endif
