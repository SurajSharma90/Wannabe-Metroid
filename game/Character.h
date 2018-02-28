#pragma once

#include "libs.h"
#include "Entity.h"
#include "PhysicsComponent.h"

class Character : public Entity
{
private:
	std::string name;
	int maxHealth;
	int currHealth;
	bool facingRight;
	PhysicsComponent physicsCom;
	// LevelComponent

public:
	//Constructor / Destructor
	Character(std::string name, int health, float xPos, float yPos, Texture* texture = nullptr) : Entity(xPos, yPos, texture) {
		this->name = name;
		this->maxHealth = health;
		this->currHealth = health;
		this->facingRight = true;
	}
	virtual ~Character() {}

	//Accessors


	//Modifiers

	//Functions
};