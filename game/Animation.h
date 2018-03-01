#pragma once

#include"libs.h"

class Animation
{
private:
	//Variables
	Sprite* sprite;					//Sprite including a texture sheet
	IntRect originalRect;			//Starting texture rect saved(frame)
	IntRect textureRect;			//Starting texture rect (frame)
	float rows;						//How many rows the animation spans
	float spaceBetween;				//Space between frames
	float animationTime;			//The time it takes between frames
	float timer;					//Timer to handle animation transistions

	//Private functions
	void updateTimer(const float& dt)
	{
		if (this->timer <= this->animationTime)
			this->timer += 10.f * dt;
	}

public:
	//Constructors/Destructors
	Animation(
		Sprite* sprite,
		IntRect textureRect,
		float rows,
		float spaceBetween,
		float animationTime
		)
	{
		this->sprite = sprite;
		this->originalRect = textureRect;
		this->textureRect = textureRect;
		this->rows = rows;
		this->spaceBetween = spaceBetween;
		this->animationTime = animationTime;
		this->timer = this->animationTime;
	}

	virtual ~Animation()
	{

	}

	//Accessors

	//Modifiers

	//Functions
	void animate(const float& dt)
	{
		//Update animation timer
		this->updateTimer(dt); 

		//Animate ONE row
		if (this->textureRect.left < this->sprite->getTexture()->getSize().x && this->timer >= this->animationTime)
		{
			this->timer = 0.f;
			this->textureRect.left += this->textureRect.width;
		}
		
		//After row is complete, reset position for looped animation
		if (this->textureRect.left >= this->sprite->getTexture()->getSize().x)
		{
			this->textureRect.left = 0;
		}

		//Set Texture rect to display
		this->sprite->setTextureRect(this->textureRect);
	}

	void reset()
	{
		this->textureRect = this->originalRect;
		this->sprite->setTextureRect(this->originalRect);
		this->timer = this->animationTime;
	}
};