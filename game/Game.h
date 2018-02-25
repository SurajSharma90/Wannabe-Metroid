#pragma once

#include"libs.h"

#include"TextureHandler.h"

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
	const unsigned WINDOW_WIDTH;
	const unsigned WINDOW_HEIGHT;
	ContextSettings window_context_settings;
	Event windowEvent;
	unsigned int frameLimit;
	RenderWindow* window;

	//Inputs
	Vector2i mousePosScreen;
	Vector2i mousePosWindow;
	Vector2f mousePosView;
	
	//Textures
	TextureHandler textures;

	//TESTING
	RectangleShape testBone;
	RectangleShape testJoint;

	//Initializers
	void initVariables();
	void initWindow();
	void initialize();

	//Cleanup
	void cleanup();

	//Private functions
	void loadWindowSettingsFile();

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

