#include "BoundingBox.h"

BoundingBox::BoundingBox() {

}

//set for player currently, played around
//this seems to work for now
BoundingBox::BoundingBox(float x, float y, float w, float h) :
	_bx(x + 44), 
	_by(y + 90), 
	_bw(w - 46),
	_bh(h - 53)
{

}

BoundingBox::~BoundingBox() {

}

float BoundingBox::getX() {
	return this->_bx;
}

float BoundingBox::getY() {
	return this->_by;
}

float BoundingBox::getW() {
	return this->_bw;
}

float BoundingBox::getH() {
	return this->_bh;
}