#pragma once
#include"libs.h"

class Entity
{
private:
	Sprite sprite;
	const Texture* texture;

public:
	//Constructor / Destructor
	Entity(float xPos, float yPos, float xScale, float yScale, IntRect textureRect, const Texture* texture = nullptr)
		:ORIGINAL_SCALE_X(xScale), ORIGINAL_SCALE_Y(yScale)
	{
		this->sprite.setPosition(xPos, yPos);
		this->texture = texture;
		this->sprite.setTexture(*this->texture);
		this->sprite.setTextureRect(textureRect);
		this->setScale(this->ORIGINAL_SCALE_X, this->ORIGINAL_SCALE_Y);
	}

	virtual ~Entity() {}

	//Constants
	const float ORIGINAL_SCALE_X;
	const float ORIGINAL_SCALE_Y;

	//Accessors
	virtual const Texture* getTexture()
	{
		return this->texture;
	}

	virtual const IntRect getTextureRect() const
	{
		return this->sprite.getTextureRect();
	}

	virtual Sprite* getSprite()
	{
		return &this->sprite;
	}

	virtual Vector2f getScale() const
	{
		return this->sprite.getScale();
	}

	virtual Vector2f getOrigin() const
	{
		return this->sprite.getOrigin();
	}

	virtual Vector2f getPosition() const 
	{
		return this->sprite.getPosition();
	}

	virtual FloatRect getBounds() const
	{
		return this->sprite.getGlobalBounds();
	}

	//Modifiers
	virtual void setTextureRect(const int& left, const int& top, const int& width, const int& height)
	{
		this->sprite.setTextureRect(IntRect(left, top, width, height));
	}

	virtual void setScale(const float& x, const float& y)
	{
		this->sprite.setScale(Vector2f(x, y));
	}

	virtual void setOrigin(const float& x, const float& y)
	{
		this->sprite.setOrigin(Vector2f(x, y));
	}

	virtual void setPosition(const float& xPos, const float& yPos) 
	{
		this->sprite.setPosition(xPos, yPos);
	}

	//Functions
	virtual void move(const float&x, const float& y)
	{
		this->sprite.move(x, y);
	}
	
	virtual void move(const Vector2f& offset)
	{
		this->sprite.move(offset);
	}
};