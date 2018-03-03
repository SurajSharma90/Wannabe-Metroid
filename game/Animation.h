#pragma once

#include"libs.h"

class Animation
{
private:
	//Variables
	std::string name;
	Sprite* sprite;					//Sprite including a texture sheet
	IntRect originalTextureRect;	//Starting texture rect saved(frame)
	IntRect currentTextureRect;		//Starting texture rect (frame)
	unsigned maxWidth;				//Max width of animation texture strip
	unsigned maxHeight;				//As above but for height
	float frameWidth;				//Width of one frame
	float frameHeight;				//Height of one frame
	float spaceBetweenFrames;		//Space between frames
	float animationTime;			//The time it takes between frames
	float timer;					//Timer to handle animation transistions
	bool stopped;					//Used to stop animation mid-sequence
	short nrOfFrames;				//The maximum number of frames
	short currentFrame;				//The frame the animation is on
	bool hasBeenReset;				//Keeps track of if the animation has been reset

	//Private functions
	void updateTimer(const float& dt)
	{
		if (this->timer <= this->animationTime)
			this->timer += 10.f * dt;
	}

public:
	//Constructors/Destructors
	Animation(
		std::string name,
		Sprite* sprite,
		IntRect currentTextureRect,
		unsigned maxWidth,
		unsigned maxHeight,
		float spaceBetweenFrames,
		float animationTime
		)
	{
		this->name = name;
		this->sprite = sprite;
		this->originalTextureRect = currentTextureRect;
		this->currentTextureRect = currentTextureRect;
		this->maxWidth = maxWidth;
		this->maxHeight = maxHeight;
		this->frameWidth = currentTextureRect.width;
		this->frameHeight = currentTextureRect.height;
		this->spaceBetweenFrames = spaceBetweenFrames;
		this->animationTime = animationTime;
		this->timer = this->animationTime;
		this->stopped = false;
		this->nrOfFrames = this->maxWidth / this->originalTextureRect.width;
		this->currentFrame = 0;
		this->hasBeenReset = false;
	}

	virtual ~Animation()
	{

	}

	//Accessors

	//Modifiers

	//Functions
	void animate(const float& dt)
	{
		//If the animation is not stopped
		if (!this->stopped)
		{
			//Update animation timer
			this->updateTimer(dt);

			//Set Texture rect to display
			this->sprite->setTextureRect(this->currentTextureRect);

			//Animate ONE row
			if (this->currentFrame < this->nrOfFrames && this->timer >= this->animationTime)
			{
				this->timer = 0.f;
				this->currentTextureRect.left += this->frameWidth;
				this->currentFrame++;
			}

			//After row is complete, reset position for looped animation
			if (this->currentFrame >= this->nrOfFrames)
			{
				this->currentTextureRect = this->originalTextureRect;
				this->currentFrame = 0;
			}

			this->hasBeenReset = false;
		}
	}

	void animateOnce(const float& dt)
	{
		//If the animation is not stopped
		if (!this->stopped)
		{
			//Update animation timer
			this->updateTimer(dt);

			//Set Texture rect to display
			this->sprite->setTextureRect(this->currentTextureRect);

			//Animate ONE row
			if (this->currentFrame < this->nrOfFrames - 1 && this->timer >= this->animationTime)
			{
				this->timer = 0.f;
				this->currentTextureRect.left += this->frameWidth;
				this->currentFrame++;
			}

			//After row is complete, reset position for looped animation

			this->hasBeenReset = false;
		}
	}
	
	bool isDone()
	{
		if (this->currentFrame >= this->nrOfFrames)
		{
			return true;
		}

		return false;
	}

	void stop(short frame = -1)
	{
		if (!this->stopped)
		{
			if (frame > this->nrOfFrames)
				std::cout << "ERROR::ANIMATION::STOP::FRAME_GREATER_THAN_NROFFRAMES" << "\n";
			else if (this->currentFrame == frame || frame < 0)			
				this->stopped = true;
		}
	}

	void start()
	{
		if (this->stopped)
		{
			this->stopped = false;
			this->hasBeenReset = false;
		}
	}

	void reset()
	{
		if (!this->hasBeenReset)
		{
			this->currentTextureRect = this->originalTextureRect;
			this->timer = this->animationTime;
			this->currentFrame = 0;
			this->stopped = false;

			this->hasBeenReset = true;
		}
	}
};