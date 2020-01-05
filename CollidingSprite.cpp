#include "CollidingSprite.h"

CollidingSprite::CollidingSprite() {

}

CollidingSprite::~CollidingSprite() {

}

CollidingSprite::CollidingSprite(Graphics& graphics, const std::string& filePath, float x, float y, float width, float height, float timeToUpdate, int id) :
	AnimatedSprite(graphics, filePath, x, y, width, height, timeToUpdate),
	BoundingBox(x, y, width, height),
	_id(id)
{
	
}