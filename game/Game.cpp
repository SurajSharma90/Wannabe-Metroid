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
	this->keyTimeMax = 0.f;
	this->keyTimeIncrement = 10.f;

	//Window
	this->window = nullptr;
	this->frameLimit = 120;

	//Inputs

	//TESTING
	testBone.setSize(Vector2f(400.f, 100.f));
	testBone.setPosition(400.f, 200.f);
	testBone.setOrigin(testBone.getGlobalBounds().width, testBone.getGlobalBounds().height / 2);
	testBone.setPosition(400.f + testBone.getGlobalBounds().width, 200.f);

	testJoint.setSize(Vector2f(10.f, 10.f));
	testJoint.setFillColor(Color::Green);
	testJoint.setPosition(testBone.getGlobalBounds().left, testBone.getGlobalBounds().top + testBone.getGlobalBounds().height / 2.f);
	testJoint.setOrigin(Vector2f(testBone.getGlobalBounds().width, 0.f));
	testJoint.setPosition(testBone.getGlobalBounds().left + testBone.getGlobalBounds().width, testBone.getGlobalBounds().top + testBone.getGlobalBounds().height / 2.f);
}

void Game::initWindow()
{
	//Load from file
	this->loadWindowSettingsFile();

	//Context Settings
	this->window_context_settings.antialiasingLevel = 4;
	this->window_context_settings.majorVersion = 4;
	this->window_context_settings.minorVersion = 5;

	//Create window
	this->window = new RenderWindow(
		VideoMode(this->WINDOW_WIDTH, this->WINDOW_HEIGHT),
		"WANNABE_METROID", 
		Style::Default, 
		this->window_context_settings
	);

	//Window Settings
	this->window->setFramerateLimit(this->frameLimit);
	this->window->setMouseCursorVisible(false);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initialize()
{
	//Variables
	this->initVariables();

	//Window
	this->initWindow();

	//Complete
	std::cout << "GAME::INITIALIZATION_COMPLETE" << "\n";
}

//Cleanup
void Game::cleanup()
{
	delete this->window;
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

//Constructors / Destructors
Game::Game()
	: WINDOW_WIDTH(1920), WINDOW_HEIGHT(1080)
{
	//Init game
	this->initialize();
}

Game::~Game()
{

}

//Accessors

//Modifiers

//Functions
bool Game::windowIsOpen()
{
	return this->window->isOpen();
}

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

//Update
void Game::updateDT()
{
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateKeyTime()
{
	if (this->keyTime < this->keyTimeMax)
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
	if (Keyboard::isKeyPressed(Keyboard::Escape))
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
}

void Game::update()
{
	//Debug
	this->updateDebugPrint();

	//Delta Time
	this->updateDT();

	//Events
	this->updateEvents();

	//Input
	this->updateKeyboardInput();

	//Mouse positions
	this->updateMousePositions();
}

//Render
void Game::render()
{
	this->window->clear(Color(0, 0, 0, 0));

	RectangleShape originBox;
	originBox.setSize(Vector2f(5.f, 5.f));
	originBox.setFillColor(Color::Red);

	testBone.rotate(10.f * dt);
	testJoint.rotate(10.f * dt);

	this->window->draw(testBone);
	this->window->draw(testJoint);

	originBox.setPosition(testBone.getPosition());
	this->window->draw(originBox);

	originBox.setPosition(testJoint.getPosition());
	this->window->draw(originBox);

	this->window->display();
}

