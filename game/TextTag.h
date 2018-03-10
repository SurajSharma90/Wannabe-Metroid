#pragma once

#include"libs.h"

class TextTag
{
private:
	//Variables
	bool to_be_removed;

	const Font* font;
	Text text;

	float timeToLive;
	Vector2f velocity;
	Vector2f degeneration;
	float rotation;

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
		Color color,
		unsigned int size,
		float timeToLive,
		Vector2f position,
		float velocityX,
		float velocityY,
		float degenX,
		float degenY,
		float rotation
		)
	{
		this->to_be_removed = false;

		this->font = font;
		this->text.setFont(*this->font);
		this->text.setFillColor(color);
		this->text.setCharacterSize(size);
		this->text.setString(str);
		this->text.setPosition(position);
		
		this->timeToLive = timeToLive;
		this->velocity = Vector2f(velocityX, velocityY);
		this->degeneration = Vector2f(degenX, degenY);
		this->rotation = rotation;
	}

	~TextTag() {}

	//Operators

	//Accessors
	bool isToBeRmoved()const
	{
		return this->to_be_removed;
	}

	//Modifiers

	//Functions
	void update(const float& dt)
	{
		this->text.move(this->velocity * dt);
		this->text.rotate(this->rotation * dt);

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