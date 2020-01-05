#include <math.h>

#include "Player.h"
#include "Graphics.h"
#include "Input.h"

#include <iostream>

namespace player_constants {
	const float WALK_SPEED = 0.3f;
}

Player::Player() {

}

Player::Player(Graphics& graphics, Input& input, float x, float y, float width, float height, int id) :
	CollidingSprite(graphics, "Pokemon.png", x, y, width, height, 120, id),
	_facing(DOWN), 
	_xOffset(0), 
	_yOffset(0), 
	_updateX(true), 
	_updateY(true)
{
	this->_left = input.getDir('l');
	this->_right = input.getDir('r');
	this->_up = input.getDir('u');
	this->_down = input.getDir('d');

	//slice up spritesheet into 
	//smaller textures depending on animation type
	this->setupAnimations();
}

void Player::setupAnimations() {
	this->addAnimation(1, 0, 64, "IdleLeft", (int)this->_rect.w, (int)this->_rect.h, Vector2(0, 0));
	this->addAnimation(1, 0, 128, "IdleRight", (int)this->_rect.w, (int)this->_rect.h, Vector2(0, 0));
	this->addAnimation(4, 0, 64, "RunLeft", (int)this->_rect.w, (int)this->_rect.h, Vector2(0, 0));
	this->addAnimation(4, 0, 128, "RunRight", (int)this->_rect.w, (int)this->_rect.h, Vector2(0, 0));
	this->addAnimation(1, 0, 192, "IdleUp", (int)this->_rect.w, (int)this->_rect.h, Vector2(0, 0));
	this->addAnimation(1, 0, 0, "IdleDown", (int)this->_rect.w, (int)this->_rect.h, Vector2(0, 0));
	this->addAnimation(4, 0, 192, "RunUp", (int)this->_rect.w, (int)this->_rect.h, Vector2(0, 0));
	this->addAnimation(4, 0, 0, "RunDown", (int)this->_rect.w, (int)this->_rect.h, Vector2(0, 0));
}

float* Player::getXoffset() {
	return &this->_xOffset;
}

float* Player::getYoffset() {
	return &this->_yOffset;
}

void Player::move() {
	//get direction
	this->_hspeed = (*this->_left + *this->_right) * player_constants::WALK_SPEED;
	this->_vspeed = (*this->_up + *this->_down) * player_constants::WALK_SPEED;
	this->_xOffset = 0;
	this->_yOffset = 0;

	if (this->_hspeed == 0 && this->_vspeed == 0) {
		this->stopMoving();
		return;
	}

	if (this->_hspeed != 0 && this->_vspeed != 0) {
		//diagnol
		this->xaxis(*this->_left + *this->_right);
		this->yaxis(*this->_up + *this->_down);
		//has to do with animating diagnol
		if (*this->_left + *this->_right == 1) {
			this->moveRight();
		}
		else {
			this->moveLeft();
		}
		return;
	}

	//1 direction
	if (this->_hspeed != 0) {
		if (this->_hspeed > 0) {
			//right
			this->moveRight();
		}
		else {
			this->moveLeft();
		}
	}
	else {
		if (this->_vspeed > 0) {
			//down
			this->moveDown();
		}
		else {
			this->moveUp();
		}
	}
}

void Player::sort(CollidingSprite* sprites[], int arr[], float elapsedTime) {
	//up
	if (this->_vspeed < 0) {
		//temp vector to hold key/value 
		//for shifting ints in draw array
		std::vector<Map> tempArr;
		//this x ensures the check is always 
		//the element next to the player
		int x;
		//4 is length of array ***NEED BETTER WAY
		//to have array length
		//[1, 0, 2, 3]
		for (x = -1; x + this->_id + this->_sOffset > -1; x--) {
			if (this->_rect.y + (this->_vspeed * elapsedTime) < sprites[arr[this->_id + x + this->_sOffset]]->getSY()) {
				//which array element to shift to
				int element = this->_id + x + this->_sOffset + 1;
				//value in that array element
				int value = arr[this->_id + x + this->_sOffset];
				Map map = Map(element, value);
				tempArr.push_back(map);
			}
			else {
				//done checking those moving past
				break;
			}
		}

		//done checking as not moving past anything period
		//was in for loop but needs to be here becase may 
		//be case where loop doesn't run due to "out of bounds"
		if (x == -1) {
			return;
		}

		for (int i = 0; i < tempArr.size(); i++) {
			arr[tempArr[i].element] = tempArr[i].value;
		}
		//-2 + 3 + 0 + 1
		x += this->_id + this->_sOffset + 1;
		arr[x] = this->_id;
		this->_sOffset = x;
	}
	//down
	else if (this->_vspeed > 0) {
	
		//temp vector to hold key/value 
		//for shifting ints in draw array
		std::vector<Map> tempArr;
		//this x ensures the check is always 
		//the element next to the player
		int x; 
		//4 is length of array ***NEED BETTER WAY
		//to have array length
		//[0, 1, 2, 3]
		for (x = 1; x + this->_id + this->_sOffset < 4; x++) {
			if (this->_rect.y + (this->_vspeed * elapsedTime) > sprites[arr[this->_id + x + this->_sOffset]]->getSY()) {
				//which array element to shift to
				int element = (this->_id + x + this->_sOffset) - 1;
				//value in that array element
				int value = arr[this->_id + x + this->_sOffset];
				Map map = Map(element, value);
				tempArr.push_back(map);
			}
			else {
				//done checking those moving past
				break;
			}
		}

		//done checking as not moving past anything period
		//was in for loop but needs to be here becase may 
		//be case where loop doesn't run due to "out of bounds"
		if (x == 1) {
			return;
		}

		for (int i = 0; i < tempArr.size(); i++) {
			arr[tempArr[i].element] = tempArr[i].value;
		}

		x += this->_id + this->_sOffset - 1;
		arr[x] = this->_id;
		this->_sOffset = x;
	}
}

void Player::xaxis(int dir) {
	this->_hspeed = (dir * player_constants::WALK_SPEED) * (sqrt(2) / 2);
}

void Player::yaxis(int dir) {
	this->_vspeed = (dir * player_constants::WALK_SPEED) * (sqrt(2) / 2);
}

void Player::moveLeft() {
	this->playAnimation("RunLeft");
	this->_facing = LEFT;
}

void Player::moveRight() {
	this->playAnimation("RunRight");
	this->_facing = RIGHT;
}

void Player::moveUp() {
	this->playAnimation("RunUp");
	this->_facing = UP;
}

void Player::moveDown() {
	this->playAnimation("RunDown");
	this->_facing = DOWN;
}

void Player::stopMoving() {
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

void Player::seCol(float sprite[]) {

	//deal with x and y collision
	if (this->_bx < sprite[0] && this->_bx + (this->_bw * globals::SPRITE_SCALE) > sprite[0] && this->_by < sprite[1] && this->_by + (this->_bh * globals::SPRITE_SCALE) > sprite[1]) {

		return;
	}

	//deal with x collision
	if (this->_bx < sprite[0] && this->_bx + (this->_bw * globals::SPRITE_SCALE) > sprite[0]) {

		return;
	}

	//deal with y collision
	if (this->_by < sprite[1] && this->_by + (this->_bh * globals::SPRITE_SCALE) > sprite[1]) {

		return;
	}
}

void Player::collision(CollidingSprite* sprites[], int arr[], float elapsedTime, bool isStatic) {
	//don't collide if not moving
	if (this->_hspeed == 0 && this->_vspeed == 0) {
		return;
	}

	//1 dir
	if (this->_hspeed != 0) {
		if (this->_hspeed > 0) {
			//right
			for (int i = 0; i < 4; i++) {
				float other[] = { sprites[i]->getX(), sprites[i]->getY(), sprites[i]->getW(), sprites[i]->getH() };
				if (this->collR(other, elapsedTime)) {
					break;
				}
			}
		}
		else {
			for (int i = 0; i < 4; i++) {
				
				float other[] = { sprites[i]->getX(), sprites[i]->getY(), sprites[i]->getW(), sprites[i]->getH() };
				if (this->collL(other, elapsedTime)) {
					break;
				}
			}
		}
	}
	if(this->_vspeed != 0) {
		if (this->_vspeed > 0) {
			//down
			for (int i = 0; i < 4; i++) {
				float other[] = { sprites[i]->getX(), sprites[i]->getY(), sprites[i]->getW(), sprites[i]->getH() };
				if (this->collD(other, elapsedTime)) {
					break;
				}
			}
		}
		else {
			for (int i = 0; i < 4; i++) {
				float other[] = { sprites[i]->getX(), sprites[i]->getY(), sprites[i]->getW(), sprites[i]->getH() };
				if (this->collU(other, elapsedTime)) {
					break;
				}
			}
		}
		this->sort(sprites, arr, elapsedTime);
	}
}

bool Player::collR(float rect[], float elapsedTime) {
	if (this->_bx + (this->_bw * globals::SPRITE_SCALE) + (this->_hspeed * elapsedTime) >= globals::SCREEN_WIDTH) {
		//handle right bounds
		this->_rect.x += _hspeed * elapsedTime;
		this->_bx += _hspeed * elapsedTime;
		float tempx = this->_bx;
		this->_bx = (globals::SCREEN_WIDTH - (this->_bw * globals::SPRITE_SCALE)) - 0.1f;
		this->_rect.x -= tempx - this->_bx;
		this->_updateX = false;
		return true;
	}
	if (this->_bx < rect[0] && this->_bx + (this->_bw * globals::SPRITE_SCALE) + (this->_hspeed * elapsedTime) >= rect[0]) {
		float y2 = (this->_by + (this->_bh * globals::SPRITE_SCALE));
		float ey2 = (rect[1] + (rect[3] * globals::SPRITE_SCALE));
		if ((this->_by <= rect[1] && y2 >= rect[1]) || (this->_by <= ey2 && y2 >= ey2) || (this->_by > rect[1] && y2 < ey2)) {
			this->_rect.x += _hspeed * elapsedTime;
			this->_bx += _hspeed * elapsedTime;
			float tempx = this->_bx;
			this->_bx = (rect[0] - (this->_bw * globals::SPRITE_SCALE)) - 0.1f;
			this->_rect.x -= tempx - this->_bx;
			this->_updateX = false;
			return true;
		}
	}
	return false;
}

bool Player::collL(float rect[], float elapsedTime) {
	if (this->_bx + (this->_hspeed * elapsedTime) <= 0) {
		this->_rect.x += _hspeed * elapsedTime;
		this->_bx += _hspeed * elapsedTime;
		float tempx = this->_bx;
		this->_bx = 0.1f;
		this->_rect.x += this->_bx - tempx;
		this->_updateX = false;
		return true;
	}
	if (this->_bx > rect[0] && this->_bx + (this->_hspeed * elapsedTime) <= rect[0] + (rect[2] * globals::SPRITE_SCALE)) {
		float y2 = (this->_by + (this->_bh * globals::SPRITE_SCALE));
		float ey2 = (rect[1] + (rect[3] * globals::SPRITE_SCALE));
		if ((this->_by <= rect[1] && y2 >= rect[1]) || (this->_by <= ey2 && y2 >= ey2) || (this->_by > rect[1] && y2 < ey2)) {
			this->_rect.x += _hspeed * elapsedTime;
			this->_bx += _hspeed * elapsedTime;
			float tempx = this->_bx;
			this->_bx = (rect[0] + (rect[2] * globals::SPRITE_SCALE)) + 0.1f;
			this->_rect.x += this->_bx - tempx;
			this->_updateX = false;
			return true;
		}
	}
	return false;
}

bool Player::collU(float rect[], float elapsedTime) {
	if (this->_by + (this->_vspeed * elapsedTime) <= 0) {
		this->_rect.y += _vspeed * elapsedTime;
		this->_by += _vspeed * elapsedTime;
		float tempy = this->_by;
		this->_by = 0.1f;
		this->_rect.y += this->_by - tempy;
		this->_updateY = false;
		return true;
	}
	if (this->_by > rect[1] && this->_by + (this->_vspeed * elapsedTime) <= rect[1] + (rect[3] * globals::SPRITE_SCALE)) {
		float x2 = (this->_bx + (this->_bw * globals::SPRITE_SCALE));
		float ex2 = (rect[0] + (rect[2] * globals::SPRITE_SCALE));
		if ((this->_bx <= rect[0] && x2 >= rect[0]) || (this->_bx <= ex2 && x2 >= ex2) || (this->_bx > rect[0] && x2 < ex2)) {
			this->_rect.y += _vspeed * elapsedTime;
			this->_by += _vspeed * elapsedTime;
			float tempy = this->_by;
			this->_by = (rect[1] + (rect[3] * globals::SPRITE_SCALE)) + 0.1f;
			this->_rect.y += this->_by - tempy;
			this->_updateY = false;
			return true;
		}
	}
	return false;
}

bool Player::collD(float rect[], float elapsedTime) {
	if (this->_by + (this->_bh * globals::SPRITE_SCALE) + (this->_vspeed * elapsedTime) >= globals::SCREEN_HEIGHT) {
		
		this->_rect.y += _vspeed * elapsedTime;
		this->_by += _vspeed * elapsedTime;
		float tempy = this->_by;
		this->_by = (globals::SCREEN_HEIGHT - (this->_bh * globals::SPRITE_SCALE)) - 0.1f;
		this->_rect.y -= tempy - this->_by;
		this->_updateY = false;
		return true;
	}
	if (this->_by < rect[1] && this->_by + (this->_bh * globals::SPRITE_SCALE) + (this->_vspeed * elapsedTime) >= rect[1]) {
		float x2 = (this->_bx + (this->_bw * globals::SPRITE_SCALE));
		float ex2 = (rect[0] + (rect[2] * globals::SPRITE_SCALE));
		if ((this->_bx <= rect[0] && x2 >= rect[0]) || (this->_bx <= ex2 && x2 >= ex2) || (this->_bx > rect[0] && x2 < ex2)) {
			this->_rect.y += _vspeed * elapsedTime;
			this->_by += _vspeed * elapsedTime;
			float tempy = this->_by;
			this->_by = (rect[1] - (this->_bh * globals::SPRITE_SCALE)) - 0.1f;
			this->_rect.y -= tempy - this->_by;
			this->_updateY = false;
			return true;
		}
	}
	return false;
}

void Player::update(float elapsedTime) {

	if (this->_updateX) {
		this->_rect.x += _hspeed * elapsedTime;
		this->_bx += _hspeed * elapsedTime;
	}
	this->_updateX = true;

	if (this->_updateY) {
		this->_rect.y += _vspeed * elapsedTime;
		this->_by += _vspeed * elapsedTime;
	}
	this->_updateY = true;

	AnimatedSprite::update(elapsedTime);
}

void Player::draw(Graphics &graphics) {
	AnimatedSprite::draw(graphics);
	//note rect is struct and variables are ints
	//here floats are being assigned to ints so 
	//type conversion can be issue but it works
	//because of antialiasing since it only needs to 
	//draw a rect at specific pixels 
	SDL_Rect rect;
	rect.x = (int) (this->_bx);
	rect.y = (int) (this->_by);
	rect.w = (int) (this->_bw * globals::SPRITE_SCALE);
	rect.h = (int) (this->_bh * globals::SPRITE_SCALE);

	SDL_SetRenderDrawColor(graphics.getRenderer(), 255, 0, 0, 255);
	SDL_RenderDrawRect(graphics.getRenderer(), &rect);
}