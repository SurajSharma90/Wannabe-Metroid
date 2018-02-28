#pragma once
#include "libs.h"

enum key_binds { LEFT_KEY = 0, RIGHT_KEY, JUMP_KEY, CROUCH_KEY };

class InputComponent
{
private:
	//Variables
	unsigned short leftKey;
	unsigned short rightKey;
	unsigned short jumpKey;
	unsigned short crouchKey;

	//Private Functions
	void loadKeyMapFromFile()
	{
		std::string fileName = "";
	}

public:
	//Constructors / Destructors
	InputComponent(
		unsigned short leftKey = Keyboard::Key::A,
		unsigned short rightKey = Keyboard::Key::D,
		unsigned short jumpKey = Keyboard::Key::Space,
		unsigned short crouchKey = Keyboard::Key::S)
	{
		this->leftKey = leftKey;
		this->rightKey = rightKey;
		this->jumpKey = jumpKey;
		this->crouchKey = crouchKey;
	}
	
	virtual ~InputComponent() {}

	//Accessors

	//Modifiers

	//Functions
	bool isKeyPressed(const enum key_binds KEY)
	{
		switch (KEY)
		{
		case LEFT_KEY:
			return Keyboard::isKeyPressed(Keyboard::Key(this->leftKey));
				break;
		case RIGHT_KEY:
			return Keyboard::isKeyPressed(Keyboard::Key(this->rightKey));
			break;
		case JUMP_KEY:
			return Keyboard::isKeyPressed(Keyboard::Key(this->jumpKey));
			break;
		case CROUCH_KEY:
			return Keyboard::isKeyPressed(Keyboard::Key(this->crouchKey));
			break;
		default:
			return false;
			break;
		}
	}
};
