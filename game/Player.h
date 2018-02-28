#pragma once

#include "libs.h"
#include "Character.h"

class Player : public Character
{
private:


public:
	Player(std::string name, int health, float xPos, float yPos, Texture* texture = nullptr) : Character(name, health, xPos, yPos, texture) {

	}
	~Player() {}

};