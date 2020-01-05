#ifndef ENEMY_H
#define ENEMY_H

#include "CollidingSprite.h"

class Graphics;
class CollidingSprite;

class Enemy : public CollidingSprite {
public:
	Enemy();
	Enemy(Graphics& graphics, float x, float y, float width, float height, int id, float* pxOffset, float* pyOffset);
	void draw(Graphics& graphics);
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

	bool collR(float rect[]);
	bool collL(float rect[]);
	bool collU(float rect[]);
	bool collD(float rect[]);

	void setupAnimations();
private:
	float _hspeed, _vspeed;
	float *_pxOffset, *_pyOffset;
	bool _updateX, _updateY;

	Direction _facing;
};

#endif
