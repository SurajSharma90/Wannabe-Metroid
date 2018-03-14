#pragma once

#include"libs.h"

#include"TextureHandler.h"
#include"FontHandler.h"
#include"TextTagHandler.h"

#include"Player.h"

class Game
{
private:
	//Debug options
	bool debug_showDebugText;
	bool debug_showGrid;
	bool debug_showCursor;
	Font debugFont;
	Text debugText;

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
	Vector2i mousePosGrid;
	
	//Menus

	//Textures
	TextureHandler* textureHandler;

	//Fonts and Text
	FontHandler* fontHandler;
	TextTagHandler* textTagHandler;

	//Physics
		//Gravity Defined in libs

	//World
	RectangleShape gridBox; //Debug world

	//Player
	Player* player;

	//Initializers
	void initDebugOptions();
	void initVariables();
	void initWindow();
	void initTextures();
	void initFonts();
	void initTextTags();
	void initWorld();
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
	void updateDebugOptions();
	void updateDT();
	void updateKeyTime();
	void updateEvents();
	void updateKeyboardInput();
	void updateMousePositions();
	void updatePlayer();
	void updateTextTags();

	void update();

	//Render
	void renderDebugOptions();
	void renderWorld();
	void renderPlayer();
	void renderTextTags();
	void render();
};

