#pragma once
#include"libs.h"

class Entity
{
private:
	Sprite sprite;
	Texture* texture;

public:
	//Constructor / Destructor
	Entity(float xPos, float yPos, Texture* texture = nullptr) {
		this->sprite.setPosition(xPos, yPos);
		this->texture = texture;
	}
	virtual ~Entity() {
		delete this->texture;
	}

	//Accessors
	virtual Vector2f getPosition() const {
		return this->sprite.getPosition();
	}

	//Modifiers
	virtual void setPosition(const float& xPos, const float& yPos) {
		this->sprite.setPosition(xPos, yPos);
	}

	//Functions
};