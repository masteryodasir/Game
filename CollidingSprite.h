#ifndef COLLIDING_SPRITE_H
#define COLLIDING_SPRITE_H

#include "AnimatedSprite.h"
#include "BoundingBox.h"

class CollidingSprite : public AnimatedSprite, public BoundingBox {
public:
	CollidingSprite();
	CollidingSprite(Graphics& graphics, const std::string& filePath, float x, float y, float width, float height, float timeToUpdate, int id);
	~CollidingSprite();

	virtual void move() = 0;
	virtual void collision(CollidingSprite* sprites[], int arr[], float elapsedTime, bool isStatic = true) = 0;

protected:
	int _id;
	

private:
	
};

#endif