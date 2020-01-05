#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <map>
#include <vector>

#include "Sprite.h"
#include "Globals.h"

class Graphics;

class AnimatedSprite : public Sprite {
public: 
	AnimatedSprite();
	AnimatedSprite(Graphics &graphics, const std::string &filePath, float posX, float posY, float width, float height,
		float timeToUpdate);

	//can pass something into once or not as default will 
	//take over
	void playAnimation(std::string animation, bool once = false);

	//timer for animations
	virtual void update(float elapsedTime);

	//draw it
	virtual void draw(Graphics &graphics);

protected:
	float _timeToUpdate;
	bool _currentAnimationOnce;
	std::string _currentAnimation;

	//adds an animation to the map of animations for the sprite
	void addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset);

	//reset map
	void resetAnimations();

	//stop curr animation
	void stopAnimtion();

	//change visibility of animation
	void setVisible(bool visible);

	//required function to set up 
	//different sprites to animate thru
	virtual void setupAnimations() = 0;

private:
	std::map<std::string, std::vector<SDL_Rect>> _animations;
	std::map<std::string, Vector2> _offsets;

	int _frameIndex;
	double _timeElapsed;
	bool _visible;
};

#endif