#pragma once
#include "libs.h"

enum key_binds { LEFT_KEY = 0, RIGHT_KEY, JUMP_KEY, CROUCH_KEY };
enum joystick_keys { JOY_A = 0, JOY_B, JOY_X, JOY_Y, JOY_LB, JOY_RB, JOY_SELECT, JOY_START, JOY_LS, JOY_RS};

class InputComponent
{
private:
	//Variables
	//Keyboard
	unsigned short leftKey;
	unsigned short rightKey;
	unsigned short jumpKey;
	unsigned short crouchKey;

	//Joystick
	unsigned short jumpJoy;

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
		unsigned short crouchKey = Keyboard::Key::S,
		unsigned short jumpJoy = JOY_A)
	{
		//Keyboard
		this->leftKey = leftKey;
		this->rightKey = rightKey;
		this->jumpKey = jumpKey;
		this->crouchKey = crouchKey;

		//Joystick
		this->jumpJoy = jumpJoy;
	}
	
	virtual ~InputComponent() {}

	//Accessors

	//Modifiers

	//Functions
	bool isKeyPressed(const enum key_binds KEY)
	{
		//Joystick controls
		if (Joystick::isConnected(0)) 
		{
			switch (KEY)
			{
			case LEFT_KEY:

				if (Joystick::getAxisPosition(0, Joystick::Axis::PovX) <= -100)
					return true;
				else
					return false;	

				break;
			
			case RIGHT_KEY:

				if (Joystick::getAxisPosition(0, Joystick::Axis::PovX) >= 100)
					return true;
				else
					return false;

				break;
			
			case JUMP_KEY:

				if (Joystick::isButtonPressed(0, this->jumpJoy))
					return true;
				else
					return false;

				break;
			
			case CROUCH_KEY:

				if (Joystick::getAxisPosition(0, Joystick::Axis::PovY) <= -100)
					return true;
				else
					return false;

				break;
			
			default:
				return false;
				break;
			}
		}
		
		//Keyboard controls
		else 
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
	}
};
