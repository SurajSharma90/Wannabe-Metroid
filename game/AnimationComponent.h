#pragma once

#include"libs.h"
#include"Animation.h"

class AnimationComponent
{
private:
	//Variables
	std::vector<Animation> animations;

	//Private functions

public:
	//Constructors / Destructors
	AnimationComponent()
	{

	}

	virtual ~AnimationComponent() {}

	//Accessors

	//Modifiers

	//Functions
	inline void addAnimation(const Animation& anim)
	{
		this->animations.push_back(anim);
	}

	Animation* getAnimation(const short& animation)
	{
		return &this->animations[animation];
	}
};