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
}

void Game::initWindow()
{
	//Context Settings
	this->window_context_settings.antialiasingLevel = 4;
	this->window_context_settings.majorVersion = 4;
	this->window_context_settings.minorVersion = 5;

	//Create window
	this->window = new sf::RenderWindow(
		sf::VideoMode(this->WINDOW_WIDTH, this->WINDOW_HEIGHT),
		"WANNABE_METROID", 
		sf::Style::Default, 
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
}

//Cleanup
void Game::cleanup()
{
	delete this->window;
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

//Update
void Game::updateDT()
{
	this->dt = this->dtClock.restart().asSeconds();
	
#ifdef DEBUG
	std::cout << this->dt << "\n";
#endif
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
		if (this->windowEvent.type == sf::Event::Closed)
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

void Game::update()
{
	//Delta Time
	this->updateDT();

	//Events
	this->updateEvents();

	//Input
	this->updateKeyboardInput();
}

//Render
void Game::render()
{
	this->window->clear(sf::Color(0.f, 0.f, 0.f, 0.f));

	this->window->display();
}

