#pragma once

#include"libs.h"

class TextTag
{
private:
	//Variables
	bool to_be_removed;

	const Font* font;
	Text text;
	float size;

	float timeToLive;
	Vector2f velocity;
	Vector2f degeneration;
	float rotation;
	float sizeIncrement;

	//Private functions
	Vector2f normalize(const Vector2f& vector)
	{
		float vectorLength = sqrt((pow(vector.x, 2) + pow(vector.y, 2)));
		Vector2f normalizedVector = vector / vectorLength;

		if (vectorLength <= 0.f)
			return Vector2f(0.f, 0.f);
		else
			return normalizedVector;
	};

public:
	//Constructors/Destructors
	TextTag(
		const Font* font,
		std::string str,
		Vector2f position,
		Color color = Color::White,
		unsigned int size = 20,
		float timeToLive = 10.f,
		float velocityX = 0.f,
		float velocityY = -1000.f,
		float degenX = 0.f,
		float degenY = 1800.f,
		float rotation = 20.f,
		float sizeIncrement = 0
		)
	{
		this->to_be_removed = false;

		this->font = font;
		this->text.setFont(*this->font);
		this->text.setFillColor(color);
		this->text.setCharacterSize(size);
		this->text.setString(str);
		this->text.setPosition(position);
		this->size = size;
		
		this->timeToLive = timeToLive;
		this->velocity = Vector2f(velocityX, velocityY);
		this->degeneration = Vector2f(degenX, degenY);
		this->rotation = rotation;
		this->sizeIncrement = sizeIncrement;
	}

	~TextTag() {}

	//Operators

	//Accessors
	bool isToBeRmoved()const
	{
		return this->to_be_removed;
	}

	//Modifiers
	void setPosition(const Vector2f position)
	{
		this->text.setPosition(position);
	}

	void setString(const std::string& str)
	{
		this->text.setString(str);
	}

	//Functions
	void update(const float& dt)
	{
		this->text.move(this->velocity * dt);
		this->text.rotate(this->rotation * dt);

		if (this->sizeIncrement > 0.f)
		{
			this->size += this->sizeIncrement * dt;
			this->text.setCharacterSize(static_cast<unsigned>(this->size));
		}

		if (this->velocity.x < 0)
		{
			this->velocity.x += this->degeneration.x * dt;

			if (this->velocity.x > 0)
				this->velocity.x = 0.f;
		}
		else if (this->velocity.x > 0)
		{
			this->velocity.x -= this->degeneration.x * dt;

			if (this->velocity.x < 0)
				this->velocity.x = 0.f;
		}

		if (this->velocity.y < 0)
		{
			this->velocity.y += this->degeneration.y * dt;

			if (this->velocity.y > 0)
				this->velocity.y = 0.f;
		}
		else if (this->velocity.y > 0)
		{
			this->velocity.y -= this->degeneration.y * dt;

			if (this->velocity.y < 0)
				this->velocity.y = 0.f;
		}

		this->timeToLive -= 10 * dt;

		if (this->timeToLive <= 0.f)
		{
			this->to_be_removed = true;
		}
	}

	void render(RenderTarget* target)
	{
		target->draw(text);
	}
};