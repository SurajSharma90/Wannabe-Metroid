#pragma once

#include"libs.h"

class Animation
{
private:
	//Variables
	const Texture* animationSheet;
	float width;
	float height;
	float rows;
	float spaceBetween;

	//Private functions

public:
	//Constructors/Destructors
	Animation(
		const Texture* animationSheet,
		float width,
		float height,
		float rows,
		float spaceBetween
		)
	{
		this->animationSheet = animationSheet;
		this->width = width;
		this->height = height;
		this->rows = rows;
		this->spaceBetween = spaceBetween;
	}

	virtual ~Animation()
	{

	}

	//Accessors

	//Modifiers

	//Functions
	void animate()
	{

	}
};