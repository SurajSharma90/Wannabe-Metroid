#pragma once
#include"libs.h"
#include"TextTagHandler.h"

class TextTagComponent
{
private:
	//Variables
	TextTagHandler* handler;

	//Private functions

public:
	//Constructors/Destructors
	TextTagComponent(TextTagHandler* handler)
	{
		this->handler = handler;
	}

	//Operators

	//Accessors

	//Modifiers

	//Functions

	void add(const TextTag& tag)
	{
		this->handler->add(tag);
	}

	void add(enum textTag_list tag, const Vector2f position, const std::string& str)
	{
		this->handler->add(tag, position, str);
	}

	void add(enum textTag_list tag, const Vector2f position, const int& nr)
	{
		this->handler->add(tag, position, nr);
	}
};