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

	virtual const float getPositionX() const
	{
		return this->getPosition().x;
	}

	virtual const float getPositionY() const
	{
		return this->getPosition().y;
	}

	virtual FloatRect getBounds() const
	{
		return this->sprite.getGlobalBounds();
	}

	virtual const float getHeight() const
	{
		return this->sprite.getGlobalBounds().height;
	}

	virtual const float getWidth() const
	{
		return this->sprite.getGlobalBounds().width;
	}

	Vector2f getCenter()
	{
		return Vector2f(
			this->getPositionX() + this->getWidth() / 2.f,
			this->getPositionY() + this->getHeight() / 2.f
		);
	}

	const float getBottom() const
	{
		return this->sprite.getPosition().y + this->getHeight();
	}

	Vector2f getBottomCenter() 
	{
		return Vector2f(
			this->getPositionX() + this->getWidth() / 2.f,
			this->getPositionY() + this->getHeight()
		);
	}

	Vector2f getBottomLeft() const 
	{
		return Vector2f(
			this->getPositionX(),
			this->getPositionY() + this->getHeight()
		);
	}

	Vector2f getBottomRight() const 
	{
		return Vector2f(
			this->getPositionX() + this->getWidth(),
			this->getPositionY() + this->getHeight()
		);
	}

	const float getTop() const
	{
		return this->getPosition().y;
	}

	Vector2f getTopRight() const
	{
		return Vector2f(
			this->getPositionX() + this->getWidth(),
			this->getPositionY()
		);
	}

	Vector2f getTopLeft() const
	{
		return this->getPosition();
	}

	const float getLeft() const
	{
		return this->getPosition().x;
	}

	const float getRight() const
	{
		return this->getPosition().x + this->getWidth();
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

	virtual void setPositionX(const float& xPos)
	{
		this->sprite.setPosition(xPos, this->sprite.getPosition().y);
	}

	virtual void setPositionY(const float& yPos)
	{
		this->sprite.setPosition(this->sprite.getPosition().x, yPos);
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