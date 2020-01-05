#include "Enemy.h"

#include <math.h>

#include "Graphics.h"


namespace player_constants {
	const float WALK_SPEED = 0.3f;
}

Enemy::Enemy() {

}

Enemy::Enemy(Graphics& graphics, float x, float y, float width, float height, int id, float* pxOffset, float* pyOffset) :
	CollidingSprite(graphics, "Pokemon.png", x, y, width, height, 120, id),
	_updateX(true),
	_updateY(true),
	_facing(DOWN),
	_pxOffset(pxOffset), 
	_pyOffset(pyOffset), 
	_hspeed(0),
	_vspeed(0)
{
	//slice up spritesheet into 
	//smaller textures depending on animation type
	this->setupAnimations();
}

void Enemy::setupAnimations() {
	this->addAnimation(1, 0, 64, "IdleLeft", (int)this->_rect.w, (int)this->_rect.h, Vector2(0, 0));
	this->addAnimation(1, 0, 128, "IdleRight", (int)this->_rect.w, (int)this->_rect.h, Vector2(0, 0));
	this->addAnimation(4, 0, 64, "RunLeft", (int)this->_rect.w, (int)this->_rect.h, Vector2(0, 0));
	this->addAnimation(4, 0, 128, "RunRight", (int)this->_rect.w, (int)this->_rect.h, Vector2(0, 0));
	this->addAnimation(1, 0, 192, "IdleUp", (int)this->_rect.w, (int)this->_rect.h, Vector2(0, 0));
	this->addAnimation(1, 0, 0, "IdleDown", (int)this->_rect.w, (int)this->_rect.h, Vector2(0, 0));
	this->addAnimation(4, 0, 192, "RunUp", (int)this->_rect.w, (int)this->_rect.h, Vector2(0, 0));
	this->addAnimation(4, 0, 0, "RunDown", (int)this->_rect.w, (int)this->_rect.h, Vector2(0, 0));
}

void Enemy::move() {
	this->stopMoving();
}

void Enemy::xaxis(int dir) {
	
}

void Enemy::yaxis(int dir) {
	
}

void Enemy::moveLeft() {
	
}

void Enemy::moveRight() {
	
}

void Enemy::moveUp() {
	
}

void Enemy::moveDown() {
	
}

void Enemy::stopMoving() {
	switch (this->_facing) {
	case LEFT:
		this->playAnimation("IdleLeft");
		break;
	case RIGHT:
		this->playAnimation("IdleRight");
		break;
	case UP:
		this->playAnimation("IdleUp");
		break;
	case DOWN:
		this->playAnimation("IdleDown");
		break;
	default:
		break;
	}
}

void Enemy::collision(CollidingSprite* sprites[], int arr[], float elapsedTime, bool isStatic) {
	
}

bool Enemy::collR(float rect[]) {
	return 0;
}

bool Enemy::collL(float rect[]) {
	return 0;
}

bool Enemy::collU(float rect[]) {
	return 0;
}

bool Enemy::collD(float rect[]) {
	return 0;
}

void Enemy::update(float elapsedTime) {

	if (this->_updateX) {
		//_hspeed * elapsedTime;
		this->_rect.x += (this->_hspeed * elapsedTime);// -*this->_pxOffset;
		this->_bx += (this->_hspeed * elapsedTime);// -*this->_pxOffset;
	}
	_updateX = true;
	if (this->_updateY) {
		this->_rect.y += (this->_vspeed * elapsedTime);// -*this->_pyOffset;
		this->_by += (this->_vspeed * elapsedTime);// -*this->_pyOffset;
	}
	_updateY = true;

	AnimatedSprite::update(elapsedTime);
}

void Enemy::draw(Graphics& graphics) {
	AnimatedSprite::draw(graphics);
	//note rect is struct and variables are ints
	//here floats are being assigned to ints so 
	//type conversion can be issue but it works
	//because of antialiasing since it only needs to 
	//draw a rect at specific pixels 
	SDL_Rect rect;
	rect.x = (int)(this->_bx);
	rect.y = (int)(this->_by);
	rect.w = (int)(this->_bw * globals::SPRITE_SCALE);
	rect.h = (int)(this->_bh * globals::SPRITE_SCALE);

	SDL_SetRenderDrawColor(graphics.getRenderer(), 255, 0, 0, 255);
	SDL_RenderDrawRect(graphics.getRenderer(), &rect);
}