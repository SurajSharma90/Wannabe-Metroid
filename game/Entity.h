#pragma once
#include"libs.h"

class Entity
{
private:
	Sprite sprite;
	const Texture* texture;
	RectangleShape hitbox;
	Vector2f hitboxOffset;

	bool showHitbox;

	bool collision_top;
	bool collision_bottom;
	bool collision_left;
	bool collision_right;

	//Private functions
	void initializeHitbox()
	{
		this->hitboxOffset.x = 45.f;
		this->hitboxOffset.y = 30.f;

		this->hitbox.setSize(Vector2f(80.f, this->sprite.getGlobalBounds().height - this->hitboxOffset.y));
		this->hitbox.setFillColor(Color::Transparent);
		this->hitbox.setOutlineThickness(2.f);
		this->hitbox.setOutlineColor(Color::Green);
		this->hitbox.setPosition(
			this->sprite.getPosition().x + this->hitboxOffset.x,
			this->sprite.getPosition().y + this->hitboxOffset.y
		);
	}

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

		this->showHitbox = false;

		this->collision_top = false;
		this->collision_bottom = false;
		this->collision_left = false;
		this->collision_right = false;

		this->initializeHitbox();
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

	virtual RectangleShape& getHitbox()
	{
		return this->hitbox;
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
		return this->hitbox.getPosition();
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
		return this->hitbox.getGlobalBounds();
	}

	virtual const float getHeight() const
	{
		return this->getBounds().height;
	}

	virtual const float getWidth() const
	{
		return this->getBounds().width;
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
		return this->getPosition().y + this->getHeight();
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

	const bool& getCollisionTop() const { return this->collision_top; }

	const bool& getCollisionBottom() const { return this->collision_bottom; }

	const bool& getCollisionLeft() const { return this->collision_left; }

	const bool& getCollisionRight() const { return this->collision_right; }

	std::string getCollisionStatus() const
	{
		std::string collision_status = "";
		if (this->getCollisionTop())
			collision_status += " top";
		if (this->getCollisionBottom())
			collision_status += " bottom";
		if (this->getCollisionLeft())
			collision_status += " left";
		if (this->getCollisionRight())
			collision_status += " right";

		return collision_status;
	}

	const bool getShowHitbox() const
	{
		return this->showHitbox;
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
		this->sprite.setPosition(xPos - this->hitboxOffset.x, yPos - this->hitboxOffset.y);
		this->hitbox.setPosition(xPos, yPos);
	}

	virtual void setPositionX(const float& xPos)
	{
		this->sprite.setPosition(xPos - this->hitboxOffset.x, this->sprite.getPosition().y);
		this->hitbox.setPosition(xPos, this->hitbox.getPosition().y);
	}

	virtual void setPositionY(const float& yPos)
	{
		this->sprite.setPosition(this->sprite.getPosition().x, yPos - this->hitboxOffset.y);
		this->hitbox.setPosition(this->hitbox.getPosition().x, yPos);
	}

	void setCollisionTop(const bool& status) { this->collision_top = status; }

	void setCollisionBottom(const bool& status) { this->collision_bottom = status; }

	void setCollisionLeft(const bool& status) { this->collision_left = status; }

	void setCollisionRight(const bool& status) { this->collision_right = status; }

	void setShowHitbox(const bool showHitbox)
	{
		this->showHitbox = showHitbox;
	}

	//Functions
	void updateHitbox()
	{
		this->hitbox.setPosition(
			this->sprite.getPosition().x + this->hitboxOffset.x,
			this->sprite.getPosition().y + this->hitboxOffset.y
		);
	}

	virtual void move(const float&x, const float& y)
	{
		this->sprite.move(x, y);
		this->hitbox.setPosition(this->sprite.getPosition() + this->hitboxOffset);
	}
	
	virtual void move(const Vector2f& offset)
	{
		this->sprite.move(offset);
		this->hitbox.setPosition(this->sprite.getPosition() + this->hitboxOffset);
	}
};