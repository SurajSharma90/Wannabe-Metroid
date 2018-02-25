#pragma once
#include"libs.h"

class Entity
{
private:
	Sprite sprite;
	Texture* texture;

public:
	//Constructor / Destructor
	Entity(float xPos, float yPos, Texture* texture = nullptr);
	~Entity();

	//Accessors
	inline Vector2f getPosition() const { return this->sprite.getPosition(); };

	//Modifiers
	void setPosition(const float& xPos, const float& yPos) { this->sprite.setPosition(xPos, yPos); };
};