#pragma once

#include"libs.h"

//Enums
enum texture_list //Keep this updated (hardcoded) with main list of textures
{ 
	BLANK_TRANSPARENT = 0, PLAYER_SHEET, SPRITE_SHEET_BOX_01
};

class TextureHandler
{
private:
	//Variables
	std::vector<Texture> textures;

	//Initializers
	void initialize()
	{
		//Load all textures
		loadTexturesFromFile("Textures/textures.list");

		//Error check
	}

	//Private functions
	void loadTexturesFromFile(const std::string fileName) 
	{
		/*
			Loads all texture files from a pre-defined text file containing all
			paths.
		*/

		std::ifstream in_file(fileName.c_str()); //Open file

		std::string path = "";
		Texture texture;

		if (in_file.is_open()) //Check if file is valid
		{
			while (std::getline(in_file, path)) //Load one line at a time
			{
				if (path.find("*") == std::string::npos && path.length() > 0 && path.find(" ") == std::string::npos) //Skip comment lines and empty lines
				{
					if (texture.loadFromFile(path)) //Load the texture
						this->textures.push_back(texture); //Insert texture
					else
						std::cout << "ERROR::TEXTUREHANDLER::LOADTEXTURESFROMFILE::FAILED_TO_LOAD_TEXTURE:" << path << "\n";
				}
			}

			std::cout << "TEXTUREHANDLER::TEXTURE_FILE_LOADED" << "\n";
		}
		else //Error
		{
			std::cout << "ERROR::TEXTUREHANDLER::LOADTEXTURESFROMFILE::FAILED_TO_OPEN_TEXTURE_LIST" << "\n";
		}

		in_file.close(); //Close stream
	}

public:
	//Constructor / Destructor
	TextureHandler()
	{
		this->initialize();
	}

	virtual ~TextureHandler() {}

	//Accessors
	inline const Texture* getTexture(const enum texture_list TEXTURE) const
	{
		if (TEXTURE >= this->textures.size()) //Error
		{
			std::cout << "ERROR::TEXTUREHANDLER::GETTEXTURE::ENUM_OUT_OF_BOUNDS" << "\n";
			return nullptr;
		}
		else
		{
			return &this->textures[TEXTURE];
		}
	}

	//Modifiers

	//Functions
};