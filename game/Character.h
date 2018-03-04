#pragma once

#include "libs.h"
#include "Entity.h"
#include "PhysicsComponent.h"
#include "InputComponent.h"
#include "AnimationComponent.h"

class Character : public Entity
{
private:
	std::string name;
	int maxHealth;
	int currHealth;

public:
	//Constructor / Destructor
	Character(
		std::string name, 
		int maxHealth, 
		float xPos, 
		float yPos,
		float xScale, 
		float yScale,
		IntRect textureRect, 
		const Texture* texture
	)
		: Entity(xPos, yPos, xScale, yScale, textureRect, texture) 
	{
		this->name = name;
		this->maxHealth = maxHealth;
		this->currHealth = this->maxHealth;
	}

	virtual ~Character() {}

	//Accessors


	//Modifiers

	//Functions
};