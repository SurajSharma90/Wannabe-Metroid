#pragma once
#include "libs.h"

enum key_binds { LEFT_KEY = 0, RIGHT_KEY, JUMP_KEY, CROUCH_KEY, SPRINT_KEY };
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
	unsigned short sprintKey;

	//Joystick
	bool joystick_connected;

	unsigned short jumpJoy;
	unsigned short sprintJoy;

	//Private Functions
	void loadKeyMapFromFile()
	{
		std::string fileName = "";
	}
	void updateJoystickConnection()
	{
		if (Joystick::isConnected(0) && !this->joystick_connected)
		{
			this->joystick_connected = true;
			std::cout << "INPUTCOMPONENT::JOYSTICK_0_CONNECTED" << "\n";
		}
		
		if(!Joystick::isConnected(0) && this->joystick_connected)
		{
			this->joystick_connected = false;
			std::cout << "INPUTCOMPONENT::JOYSTICK_0_DISCONNECTED" << "\n";
		}
	}

public:
	//Constructors / Destructors
	InputComponent(
		unsigned short leftKey = Keyboard::Key::A,
		unsigned short rightKey = Keyboard::Key::D,
		unsigned short jumpKey = Keyboard::Key::Space,
		unsigned short crouchKey = Keyboard::Key::S,
		unsigned short sprintKey = Keyboard::Key::LShift,
		unsigned short jumpJoy = JOY_A,
		unsigned short sprintJoy = JOY_B)
	{
		//Keyboard
		this->leftKey = leftKey;
		this->rightKey = rightKey;
		this->jumpKey = jumpKey;
		this->crouchKey = crouchKey;
		this->sprintKey = sprintKey;

		//Joystick
		this->joystick_connected = false;

		this->jumpJoy = jumpJoy;
		this->sprintJoy = sprintJoy;
	}
	
	virtual ~InputComponent() {}

	//Accessors

	//Modifiers

	//Functions
	bool isKeyPressed(const enum key_binds KEY)
	{
		//Check if joystick is still connected
		this->updateJoystickConnection();

		//Joystick controls
		if (this->joystick_connected) 
		{
			switch (KEY)
			{
			case LEFT_KEY:

				if (Joystick::getAxisPosition(0, Joystick::Axis::PovX) <= -100)
					return true;

				break;
			
			case RIGHT_KEY:

				if (Joystick::getAxisPosition(0, Joystick::Axis::PovX) >= 100)
					return true;

				break;
			
			case JUMP_KEY:

				if (Joystick::isButtonPressed(0, this->jumpJoy))
					return true;

				break;
			
			case CROUCH_KEY:

				if (Joystick::getAxisPosition(0, Joystick::Axis::PovY) <= -100)
					return true;

				break;

			case SPRINT_KEY:

				if (Joystick::isButtonPressed(0, this->sprintJoy))
					return true;

				break;
			
			default:
				return false;
				break;
			}
		}
		
		//Keyboard controls
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
		case SPRINT_KEY:
			return Keyboard::isKeyPressed(Keyboard::Key(this->sprintKey));
			break;
		default:
			return false;
			break;
		}
		
		//No key was pressed
		return false;
	}
};
