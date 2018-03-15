#pragma once

#include"libs.h"
#include"TextTag.h"

enum textTag_list { 
	TEXTTAG_EXP_GAIN = 0, 
	TEXTTAG_EXP_LOSS, 
	TEXTTAG_LEVEL_UP,
	TEXTTAG_HP_GAIN, 
	TEXTTAG_HP_LOSS, 
	TEXTTAG_DAMAGE_DONE };

class TextTagHandler
{
private:
	//Variables
	Container<TextTag> premade_textTags;
	Container<TextTag> textTags;

	//Private functions
	void initPremadeTextTags(const Font* font)
	{
		//EXP_GAIN
		this->premade_textTags.push(TextTag(
			font,
			"EMPTY",
			Vector2f(0.f, 0.f),	
			Color::Cyan,
			14,
			10.f,
			0.f,
			-1000.f,
			0.f,
			2200.f,
			0.f,
			10.f
		));

		//EXP_LOSS
		this->premade_textTags.push(TextTag(
			font,
			"EMPTY",
			Vector2f(0.f, 0.f),
			Color::Magenta,
			14,
			10.f,
			0.f,
			-1000.f,
			0.f,
			2200.f,
			0.f,
			10.f
		));

		//LEVEL_UP
		this->premade_textTags.push(TextTag(
			font,
			"EMPTY",
			Vector2f(0.f, 0.f),
			Color(190, 120, 0, 255),
			24,
			11.f,
			0.f,
			-1200.f,
			0.f,
			2000.f,
			0.f,
			20.f
		));

		//HP_GAIN
		this->premade_textTags.push(TextTag(
			font,
			"EMPTY",
			Vector2f(0.f, 0.f),
			Color::Green,
			20,
			8.f,
			0.f,
			-1000.f,
			0.f,
			2000.f,
			0.f,
			20.f																		//Color
		));

		//HP_LOSS
		this->premade_textTags.push(TextTag(
			font,
			"EMPTY",
			Vector2f(0.f, 0.f),
			Color::Red,
			24,
			6.f,
			0.f,
			-1200.f,
			0.f,
			2500.f,
			30.f,
			30.f																	//Color
		));
	}

public:
	//Constructors/Destructors
	TextTagHandler(const Font* font)
	{
		this->initPremadeTextTags(font);
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
	
	void add(enum textTag_list tag, const Vector2f position, const std::string& str)
	{
		if (tag >= this->premade_textTags.size() || tag < 0)
		{
			std::cout << "ERROR::GAME::ADDTEXTTAG::INDEX_OUT_OF_BOUNDS" << "\n";
		}
		else
		{
			this->premade_textTags[tag].setPosition(position);
			this->premade_textTags[tag].setString(str);
			this->add(this->premade_textTags[tag]);
		}
	}
	
	void add(enum textTag_list tag, const Vector2f position, const int& nr)
	{
		if (tag >= this->premade_textTags.size() || tag < 0)
		{
			std::cout << "ERROR::GAME::ADDTEXTTAG::INDEX_OUT_OF_BOUNDS" << "\n";
		}
		else
		{
			this->premade_textTags[tag].setPosition(position);
			this->premade_textTags[tag].setString(std::to_string(nr));
			this->add(this->premade_textTags[tag]);
		}
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
