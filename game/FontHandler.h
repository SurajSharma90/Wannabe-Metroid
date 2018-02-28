#pragma once

#include"libs.h"

enum font_list 
{
	PRIME_LIGHT = 0, 
	PRIME_REGULAR
};

class FontHandler
{
private:
	//Variables
	std::vector<Font> fonts;

	//Private functions
	inline void loadFontsFronFile()
	{
		std::string fileName = "Fonts/fonts.list";

		std::ifstream in_file(fileName.c_str());

		std::string path = "";

		if (in_file.is_open())
		{
			while (std::getline(in_file, path))
			{
				Font font;
				font.loadFromFile(path);

				this->fonts.push_back(font);
			}
		}
		else //Error
		{
			std::cout << "ERROR::FONTHANDLER::LOADFONTSFROMFILE::COULD_NOT_OPEN_FILE" << "\n";
		}

		in_file.close();

		std::cout << "FONTHANDLER::FONTS_LOADED_FROM_FILE" << "\n";
	}

	inline void initialize()
	{
		this->loadFontsFronFile();
	}

public:
	//Constructor / Destructor
	FontHandler()
	{
		this->initialize();
	}

	virtual ~FontHandler() {};

	//Accessors
	inline const Font* getFont(const enum font_list FONT)
	{
		if (FONT >= this->fonts.size()) //Error
		{
			std::cout << "ERROR::FONTHANDLER::GETFONT::ENUM_OUT_OF_BOUNDS" << "\n";
			return nullptr;
		}
		else
		{
			return &this->fonts[FONT];
		}
	}

	//Modifiers

	//Functions
};