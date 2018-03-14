#include "Game.h"

#define DEBUG
/*
Debug keybinds
C = Show cursor
G = Show grid
T = Show text
*/

//Initializers
void Game::initDebugOptions()
{
	//Debug options
	this->debug_showDebugText = true;
	this->debug_showGrid = true;
	this->debug_showCursor = true;

	//Debug text
	if (this->debugFont.loadFromFile("Fonts/Prime_Light.otf"))
	{
		this->debugText.setString("EMPTY");
		this->debugText.setCharacterSize(22);
		this->debugText.setFillColor(Color::White);
		this->debugText.setFont(this->debugFont);
		this->debugText.setPosition(10.f, 10.f);
	}
	else
	{
		std::cout << "ERROR::GAME::INITDEBUGOPTIONS::DEBUG_FONT_LOADING_FAILED" << "\n";
		throw("ERROR::GAME::INITDEBUGOPTIONS::DEBUG_FONT_LOADING_FAILED");
	}
}

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
	this->textTagHandler = nullptr;

	//Physics
		//Gravity Defined in libs

	//World

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

void Game::initWorld()
{
	this->gridBox.setSize(Vector2f(GLOBAL_WORLD_GRIDSIZE, GLOBAL_WORLD_GRIDSIZE));
	this->gridBox.setFillColor(Color::Transparent);
	this->gridBox.setOutlineThickness(2.f);
	this->gridBox.setOutlineColor(Color(255, 255, 255, 50));
	this->gridBox.setPosition(0.f, 0.f);
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
		this->textTagHandler,
		this->textureHandler->getTexture(texture_list::PLAYER_SHEET)
	);
}

void Game::initialize()
{
	//Random
	srand(time(static_cast<unsigned>(0)));

#ifdef DEBUG
	//Debug options
	this->initDebugOptions();
#endif

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

	//World
	this->initWorld();

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
void Game::updateDebugOptions()
{
	//Show cursor
	if(this->debug_showCursor)
		this->window->setMouseCursorVisible(true);
	else
		this->window->setMouseCursorVisible(false);

	//Debug Text
	//Mouse Positions
	this->debugText.setString
	(
		"Mouse Position Screen: " +
		std::to_string(this->mousePosScreen.x) +
		" " +
		std::to_string(this->mousePosScreen.y) +
		"\n" +

		"Mouse Position Window: " +
		std::to_string(this->mousePosWindow.x) +
		" " +
		std::to_string(this->mousePosWindow.y) +
		"\n" +

		"Mouse Position View: " +
		std::to_string(this->mousePosView.x) +
		" " +
		std::to_string(this->mousePosView.y) +
		"\n" +

		"Mouse Position Grid: " +
		std::to_string(this->mousePosGrid.x) +
		" " +
		std::to_string(this->mousePosGrid.y) +
		"\n" +

		"Grid Size: " +
		std::to_string(GLOBAL_WORLD_GRIDSIZE) +
		"\n"

		"Delta Time: " +
		std::to_string(this->dt) +
		"\n"

		"Player Position Grid: " +
		std::to_string(this->player->getGridPosition().x) +
		" " +
		std::to_string(this->player->getGridPosition().y) +
		"\n"
	);
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
	//Debug
	if (Keyboard::isKeyPressed(Keyboard::G) && this->checkKeyTime())
		this->debug_showGrid = this->debug_showGrid ? false : true; //If true then false else true

	if (Keyboard::isKeyPressed(Keyboard::C) && this->checkKeyTime())
		this->debug_showCursor = this->debug_showCursor ? false : true; //If true then false else true

	if (Keyboard::isKeyPressed(Keyboard::T) && this->checkKeyTime())
		this->debug_showDebugText = this->debug_showDebugText ? false : true; //If true then false else true

	//Window
	if (Keyboard::isKeyPressed(Keyboard::Escape) && this->checkKeyTime())
		this->window->close();
}

void Game::updateMousePositions()
{
	/*
	Updated mouse positions.
	*/

	this->mousePosScreen = Mouse::getPosition();
	this->mousePosWindow = Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
	this->mousePosGrid.x = this->mousePosView.x / GLOBAL_WORLD_GRIDSIZE;
	this->mousePosGrid.y = this->mousePosView.y / GLOBAL_WORLD_GRIDSIZE;
}

void Game::updatePlayer()
{
	//Player
	this->player->update(this->dt, this->window);
}

void Game::updateTextTags()
{
	this->textTagHandler->update(this->dt);
}

void Game::update()
{
#ifdef DEBUG
	//Debug Options
	this->updateDebugOptions();
#endif
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

	//Player
	this->updatePlayer();

	//Text Tags
	this->updateTextTags();
}

//Render
void Game::renderDebugOptions()
{
	//Debug text
	if(this->debug_showDebugText)
		this->window->draw(this->debugText);

	//Draw the grid
	if (this->debug_showGrid)
	{
		unsigned nrOfCol = this->window->getSize().x / GLOBAL_WORLD_GRIDSIZE;
		unsigned nrOfRow = this->window->getSize().y / GLOBAL_WORLD_GRIDSIZE;

		for (size_t i = 0; i < nrOfCol; i++)
		{
			for (size_t k = 0; k < nrOfRow; k++)
			{
				this->gridBox.setPosition(i*GLOBAL_WORLD_GRIDSIZE, k*GLOBAL_WORLD_GRIDSIZE);
				this->window->draw(this->gridBox);
			}
		}
	}
}

void Game::renderWorld()
{
	
}

void Game::renderPlayer()
{
	this->player->render(this->window);
}

void Game::renderTextTags()
{
	this->textTagHandler->render(this->window);
}

void Game::render()
{
	this->window->clear(Color(0, 0, 0, 0));
	
#ifdef DEBUG
	//Render debug options
	this->renderDebugOptions();
#endif

	//Render world
	this->renderWorld();

	//Render player
	this->renderPlayer();

	//Text tags
	this->renderTextTags();

	this->window->display();
}

