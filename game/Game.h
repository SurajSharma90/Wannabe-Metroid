#pragma once
#include"libs.h"

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

	//Initializers
	void initVariables();
	void initWindow();
	void initialize();

	//Cleanup
	void cleanup();

public:
	//Constructors / Destructors
	Game();
	~Game();

	//Accessors

	//Modifiers

	//Functions
	bool windowIsOpen();

	//Uodate
	void updateDT();
	void updateKeyTime();
	void updateEvents();
	void updateKeyboardInput();

	void update();

	//Render
	void render();
};

