#pragma once

#include"libs.h"

#include"TextureHandler.h"
#include"FontHandler.h"
#include"PhysicsComponent.h"
#include"InputComponent.h"
#include"AnimationComponent.h"

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
	
	//Textures
	TextureHandler* textureHandler;

	//Donts and Text
	FontHandler* fontHandler;
	Text text; // TO BE REMOVED ===================== TO BE REMOVED

	//Player
	bool moving;
	bool jumping;
	Sprite shape; // TO BE REMOVED ===================== TO BE REMOVED
	PhysicsComponent* phys; // TO BE REMOVED ===================== TO BE REMOVED
	InputComponent* input; // TO BE REMOVED ===================== TO BE REMOVED
	Animation* animation_idle; //TO BE REMOVED ===================== TO BE REMOVED
	Animation* animation_run; //TO BE REMOVED ===================== TO BE REMOVED

	//Initializers
	void initVariables();
	void initWindow();
	void initTextures();
	void initFonts();
	void initTesting();
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
	void updateTesting();

	void update();

	//Render
	void renderTesting();

	void render();
};

