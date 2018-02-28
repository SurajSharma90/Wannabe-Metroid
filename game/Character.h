#pragma once

#include "libs.h"
#include "Entity.h"

class Character : public Entity
{
private:
	std::string name;
	int maxHealth;
	int currHealth;
	bool facingRight;
	// PhysicsComponent
	// LevelComponent

public:
	//Constructor / Destructor
	Character(float xPos, float yPos, Texture* texture = nullptr) : 
		Entity(xPos, yPos, texture) {

	}
	virtual ~Character() {}

	//Accessors


	//Modifiers

	//Functions
};