#include "Sprite.h"
#include "Graphics.h"

Sprite::Sprite() {

}

Sprite::Sprite(Graphics& graphics, const std::string& filePath, float posX, float posY, float width, float height) :
	_rect(posX, posY, width, height)
{
	//if image was loaded, will just grab that one > loadImage or load it 
	//then create the texture with renderer and image > store in spritesheet
	this->_spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath));
	if (this->_spriteSheet == NULL) {
		printf("\nError: Unable to load image\n");
	}
}

Sprite::~Sprite() {
	//SDL_DestroyTexture(_spriteSheet);
}

float Sprite::getSY() {
	return this->_rect.y;
}