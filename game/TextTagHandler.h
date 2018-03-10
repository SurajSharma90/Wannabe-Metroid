#pragma once

#include"libs.h"
#include"TextTag.h"

class TextTagHandler
{
private:
	//Variables
	Container<TextTag> textTags;

	//Private functions

public:
	//Constructors/Destructors
	TextTagHandler()
	{

	}

	~TextTagHandler()
	{

	}
	//Operators

	//Accessors

	//Modifiers

	//Functions
	void add(const TextTag& tag)
	{
		this->textTags.push(tag);
	}

	void update(const float& dt)
	{
		for (size_t i = 0; i < this->textTags.size(); i++)
		{
			this->textTags[i].update(dt);

			if (this->textTags[i].isToBeRmoved())
				this->textTags.remove(i);
		}	
	}
	
	void render(RenderTarget* target)
	{
		for (size_t i = 0; i < this->textTags.size(); i++)
		{
			this->textTags[i].render(target);
		}
	}

	//Static variables
};
