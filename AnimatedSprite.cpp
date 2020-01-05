#include "AnimatedSprite.h"
#include "Graphics.h"
#include "Sprite.h"
#include "Windows.h"

AnimatedSprite::AnimatedSprite() {

}

AnimatedSprite::AnimatedSprite(Graphics &graphics, const std::string &filePath, float posX, float posY,
	float width, float height, float timeToUpdate) : 
			Sprite(graphics, filePath, posX, posY, width, height),
			_frameIndex(0),
			_timeElapsed(0),
			_timeToUpdate(timeToUpdate), 
			_visible(true),
			_currentAnimationOnce(false),
			_currentAnimation("")
{

}

void AnimatedSprite::addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset) {
	std::vector<SDL_Rect> rectangles;
	for (int i = 0; i < frames; i++) {
		SDL_Rect newRect = {(i + x) * width, y, width, height};
		rectangles.push_back(newRect);
	}
	this->_animations.insert(std::pair<std::string, std::vector<SDL_Rect>>(name, rectangles));
	this->_offsets.insert(std::pair<std::string, Vector2>(name, offset));
}

void AnimatedSprite::resetAnimations() {
	this->_animations.clear();
	this->_offsets.clear();
}

void AnimatedSprite::playAnimation(std::string animation, bool once) {
	this->_currentAnimationOnce = once;
	if (this->_currentAnimation != animation) {
		this->_currentAnimation = animation;
		this->_frameIndex = 0;
	}
}

void AnimatedSprite::setVisible(bool visible) {
	this->_visible = visible;
}

void AnimatedSprite::stopAnimtion() {
	this->_frameIndex = 0;
}

void AnimatedSprite::update(float elapsedTime) {

	this->_timeElapsed += elapsedTime;
	if (this->_timeElapsed > this->_timeToUpdate) {
		this->_timeElapsed -= this->_timeToUpdate;
		if (this->_frameIndex < this->_animations[this->_currentAnimation].size() - 1) {
			this->_frameIndex++;
		}
		else {
			if (this->_currentAnimationOnce == true) {
				this->setVisible(false);
			}
			this->_frameIndex = 0;
		}
	}
}

void AnimatedSprite::draw(Graphics &graphics) {
	if (this->_visible) {
		SDL_Rect destinationRectangle;
		destinationRectangle.x = (int) (this->_rect.x + this->_offsets[this->_currentAnimation].x);
		destinationRectangle.y = (int) (this->_rect.y + this->_offsets[this->_currentAnimation].y);
		destinationRectangle.w = (int) (this->_rect.w * globals::SPRITE_SCALE);
		destinationRectangle.h = (int) (this->_rect.h * globals::SPRITE_SCALE);

		SDL_Rect sourceRect = this->_animations[this->_currentAnimation][this->_frameIndex];
		graphics.blitSurface(this->_spriteSheet, &sourceRect, &destinationRectangle);
	}
}