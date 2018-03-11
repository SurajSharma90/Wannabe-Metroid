#include "Game.h"

//#define DEBUG

//Initializers
void Game::initVariables()
{
	//Delta Time
	this->dt = 0.f;
	this->dtClock.restart();

	//Key Time
	this->keyTime = 0.f;
	this->keyTimeMax = 1.f;
	this->keyTimeIncrement = 10.f;

	//Window
	this->window = nullptr;
	this->frameLimit = 144;

	//Inputs
	

	//Textures
	this->textureHandler = nullptr;

	//Fonts and Text
	this->fontHandler = nullptr;

	//Physics
		//Gravity Defined in libs

	//Player
	this->player = nullptr;

}

void Game::initWindow()
{
	//Load from file
	this->loadWindowSettingsFile();

	//Context Settings
	this->window_context_settings.antialiasingLevel = 4;
	this->window_context_settings.majorVersion = 4;
	this->window_context_settings.minorVersion = 3;

	//Create window
	this->window = new RenderWindow(
		VideoMode(this->WINDOW_WIDTH, this->WINDOW_HEIGHT),
		"WANNABE_METROID", 
		Style::Titlebar | Style::Close,
		this->window_context_settings
	);

	//Window Settings
	this->window->setFramerateLimit(this->frameLimit);
	this->window->setMouseCursorVisible(false);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	this->textureHandler = new TextureHandler();
}

void Game::initFonts()
{
	this->fontHandler = new FontHandler();
}

void Game::initTextTags()
{
	this->textTagHandler = new TextTagHandler(this->fontHandler->getFont(PRIME_REGULAR));
}

void Game::initPlayer()
{
	this->player = new Player(
		"test",
		10.f,
		0.f,
		0.f,
		4.f,
		4.f,
		IntRect(0, 0, 40, 50),
		this->textureHandler->getTexture(texture_list::PLAYER_SHEET)
	);
}

void Game::initialize()
{
	//Random
	srand(time(static_cast<unsigned>(0)));

	//Variables
	this->initVariables();

	//Window
	this->initWindow();

	//Textures
	this->initTextures();

	//Fonts and Text
	this->initFonts();

	//Text Tags premade
	this->initTextTags();

	//Player
	this->initPlayer();

	//TEST =============== TO BE REMOVED!

	//Complete
	std::cout << "GAME::INITIALIZATION_COMPLETE" << "\n";
}

//Cleanup
void Game::cleanup()
{
	//Window
	delete this->window;

	//Textures
	delete this->textureHandler;

	//Fonts and Text
	delete this->fontHandler;
	
	//Text tags
	delete this->textTagHandler;

	//Player
	delete this->player;
}

//Private functions
void Game::loadWindowSettingsFile()
{
	//Load from file
	std::string fileName = "Initialization/window_settings.ini";

	//Open settings file
	std::ifstream in_file(fileName.c_str());

	//Temp variables


	//If file is open
	if (in_file.is_open())
	{
		std::cout << "GAME::SETTINGS_FILE_LOADED" << "\n";
	}
	else //Error in opening
	{
		std::cout << "ERROR::GAME::INITWINDOW::COULD_NOT_OPEN_INI_FILE" << "\n";

		//Create file if not found
		std::ofstream out_file(fileName.c_str());

		if (out_file.is_open()) //If file is created
		{
			std::cout << "SETTINGS_FILE_CREATED" << "\n";
		}
		else //Error in creating settings file
		{
			std::cout << "ERROR::GAME::INITWINDOW::COULD_NOT_CREATE_INI_FILE" << "\n";
		}

		//Close file
		out_file.close();
	}

	//Close file
	in_file.close();
}

bool Game::checkKeyTime()
{
	if (this->keyTime >= this->keyTimeMax)
	{
		this->keyTime = 0.f;
		return true;
	}
	else
		return false;
}

//Constructors / Destructors
Game::Game()
	: WINDOW_WIDTH(1600), WINDOW_HEIGHT(900)
{
	//Init game
	this->initialize();
}

Game::~Game()
{
	this->cleanup();
}

//Accessors

//Modifiers

//Functions
bool Game::windowIsOpen()
{
	return this->window->isOpen();
}

//Update
void Game::updateDebugPrint()
{
#ifdef DEBUG

	//Mouse Positions
	std::cout << "Mouse Position Screen: " << this->mousePosScreen.x << " " << this->mousePosScreen.y << "\n";
	std::cout << "Mouse Position Window: " << this->mousePosWindow.x << " " << this->mousePosWindow.y << "\n";
	std::cout << "Mouse Position View: " << this->mousePosView.x << " " << this->mousePosView.y << "\n";

	std::cout << "---" << "\n";

	//Delta Time
	std::cout << "Delta Time: " << this->dt << "\n";

	std::cout << "---" << "\n";

	system("CLS");

#endif
}

void Game::updateDT()
{
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateKeyTime()
{
	if (this->keyTime <= this->keyTimeMax)
		this->keyTime += this->keyTimeIncrement * dt;
}

void Game::updateEvents()
{
	while (this->window->pollEvent(this->windowEvent))
	{
		if (this->windowEvent.type == Event::Closed)
		{
			this->window->close();
		}
	}
}

void Game::updateKeyboardInput()
{
	if (Keyboard::isKeyPressed(Keyboard::Escape) && this->checkKeyTime())
		this->window->close();

	if (Keyboard::isKeyPressed(Keyboard::T) && this->checkKeyTime())
			this->textTagHandler->add(
				TEXTTAG_HP_LOSS, 
				this->player->getCenter(), 
				-100
			);
}

void Game::updateMousePositions()
{
	/*
	Updated mouse positions.
	*/

	this->mousePosScreen = Mouse::getPosition();
	this->mousePosWindow = Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::update()
{
	//Debug
	this->updateDebugPrint();

	//Delta Time
	this->updateDT();

	//Keytime
	this->updateKeyTime();

	//Events
	this->updateEvents();

	//Input
	this->updateKeyboardInput();

	//Mouse positions
	this->updateMousePositions();

	//Text Tags
	this->textTagHandler->update(this->dt);

	//Player
	this->player->update(this->dt, this->window);
}

//Render
void Game::render()
{
	this->window->clear(Color(0, 0, 0, 0));
	
	//Render player
	this->player->render(this->window);

	//Text tags
	this->textTagHandler->render(this->window);

	this->window->display();
}

