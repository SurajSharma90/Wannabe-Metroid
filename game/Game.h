#pragma once

#include"libs.h"

#include"TextureHandler.h"
#include"FontHandler.h"
#include"TextTagHandler.h"

#include"Player.h"

class Game
{
private:
	//Delta time
	Clock dtClock;
	float dt;

	//Key time
	float keyTime;
	float keyTimeMax;
	float keyTimeIncrement;

	//Window
	RenderWindow* window;
	const unsigned WINDOW_WIDTH;
	const unsigned WINDOW_HEIGHT;
	ContextSettings window_context_settings;
	Event windowEvent;
	unsigned int frameLimit;

	//Inputs
	Vector2i mousePosScreen;
	Vector2i mousePosWindow;
	Vector2f mousePosView;
	
	//Menus

	//Textures
	TextureHandler* textureHandler;

	//Fonts and Text
	FontHandler* fontHandler;
	TextTagHandler textTagHandler;

	//Physics
		//Gravity Defined in libs

	//Player
	Player* player;

	//Initializers
	void initVariables();
	void initWindow();
	void initTextures();
	void initFonts();
	void initPlayer();
	void initialize();

	//Cleanup
	void cleanup();

	//Private functions
	void loadWindowSettingsFile();
	bool checkKeyTime();

public:
	//Constructors / Destructors
	Game();
	~Game();

	//Accessors

	//Modifiers

	//Functions
	bool windowIsOpen();

	//Uodate
	void updateDebugPrint();
	void updateDT();
	void updateKeyTime();
	void updateEvents();
	void updateKeyboardInput();
	void updateMousePositions();

	void update();

	//Render
	void render();
};

