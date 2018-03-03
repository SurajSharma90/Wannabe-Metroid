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
	this->frameLimit = 144;

	//Inputs
	

	//Textures
	this->textureHandler = nullptr;

	//Fonts and Text
	this->fontHandler = nullptr;

	//Player

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

	//TO BE REMOVED ======================= TO BE REMOVED
	this->text.setCharacterSize(20);
	this->text.setFillColor(Color::White);
	this->text.setFont(*this->fontHandler->getFont(font_list::PRIME_REGULAR));
	this->text.setString("TEST TEXT TO BE REMOVED!");
}

void Game::initTesting()
{
	// TO BE REMOVED ===================== TO BE REMOVED
	this->phys = new PhysicsComponent
	(
		Vector2f(0.f, 0.f),		//Velocity
		Vector2f(2000.f, 2000.f),	//Max speed
		Vector2f(8000.f, 10000.f),	//Acceleration
		Vector2f(1.f, 1.f), //AccelerationMultiplier
		4000.f,	//Degen Left
		4000.f,	//Degen Right
		0.f,	//Degen Up
		0.f	//Degen Down
	);

	this->input = new InputComponent();

	// TO BE REMOVED ===================== TO BE REMOVED
	this->anim = new AnimationComponent();

	moving = false;
	jumping = false;
	shape.setTexture(*this->textureHandler->getTexture(PLAYER_SHEET));
	shape.setTextureRect(IntRect(0, 0, 40.f, 50.f));
	shape.setScale(Vector2f(4.f, 4.f));
	this->anim->addAnimation(Animation("Running", &this->shape, IntRect(0, 0, 40.f, 50.f), 400, 50, 0.f, 0.5f));
	this->anim->addAnimation(Animation("Idle", &this->shape, IntRect(0, 100, 40.f, 50.f), 200, 50, 0.f, 1.5f));
	this->anim->addAnimation(Animation("Jumping", &this->shape, IntRect(0, 200, 40.f, 50.f), 360, 50, 0.f, 0.7f));
}

void Game::initialize()
{
	//Variables
	this->initVariables();

	//Window
	this->initWindow();

	//Textures
	this->initTextures();

	//Fonts and Text
	this->initFonts();

	//Testing =================== TO BE REMOVED!
	this->initTesting();

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

	//Player
	//TO BE REMOVED ===================== TO BE REMOVED
	delete this->phys;
	delete this->input;
	delete this->anim;
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
	: WINDOW_WIDTH(800), WINDOW_HEIGHT(600)
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
}

void Game::updateTesting()
{
	//Testing =========================== TO BE REMOVED
	this->text.move(Vector2f(100.f * dt, 0.f));
	if (this->text.getPosition().x >= this->window->getSize().x)
	{
		this->text.setPosition(Vector2f(-this->text.getGlobalBounds().width, 0.f));
	}

	//Gravity testing
	if (shape.getPosition().y + shape.getGlobalBounds().height < this->window->getSize().y)
	{
		this->phys->incrementVelocityOuterForce(0.f, 2500.f, this->dt);
	}
	else //Collision with bottom of screen
	{
		this->phys->stopVelocityY();
		this->shape.setPosition(Vector2f(shape.getPosition().x, this->window->getSize().y - shape.getGlobalBounds().height));
		this->anim->getAnimation(ANIMATION_JUMP)->reset();
	}

	if (shape.getPosition().y < 0.f) //Collision top of screen
	{
		this->phys->stopVelocityY();
		shape.setPosition(Vector2f(shape.getPosition().x, 0.f));
	}

	if (shape.getPosition().x < 0.f) //Collision left of screen
	{
		this->phys->stopVelocityX();
		shape.setPosition(Vector2f(0.f, shape.getPosition().y));
	}

	if (shape.getPosition().x + shape.getGlobalBounds().width > this->window->getSize().x) //Collision right of screen
	{
		this->phys->stopVelocityX();
		shape.setPosition(Vector2f(this->window->getSize().x - shape.getGlobalBounds().width, shape.getPosition().y));
	}

	//Move
	// TO BE REMOVED ===================== TO BE REMOVED
	if (this->input->isKeyPressed(RIGHT_KEY))
	{
		phys->incrementVelocity(1.f, 0.f, dt);
	}
	
	if (this->input->isKeyPressed(LEFT_KEY))
	{
		phys->incrementVelocity(-1.f, 0.f, dt);
	}
	
	if (this->input->isKeyPressed(JUMP_KEY))
	{
		phys->incrementVelocity(0.f, -1.f, dt);
	}

	if (this->input->isKeyPressed(SPRINT_KEY))
		this->phys->setAccelerationMultiplier(Vector2f(1.2f, 1.f));
	else
		this->phys->setAccelerationMultiplier(Vector2f(1.f, 1.f));

	if (phys->isMovingLeft())
	{
		this->shape.setScale(-4.f, 4.f);
		this->shape.setOrigin(Vector2f(shape.getTextureRect().width, 0.f));
	}
	else if (phys->isMovingRight())
	{
		this->shape.setScale(4.f, 4.f);
		this->shape.setOrigin(Vector2f(0.f, 0.f));
	}

	if (phys->isMovingHorizontal())
		moving = true;
	else
		moving = false;

	if (phys->isMovingVertical())
	{
		jumping = true;
	}
	else
		jumping = false;

	if (moving && !jumping)
	{
		this->anim->getAnimation(ANIMATION_IDLE)->reset();
		this->anim->getAnimation(ANIMATION_RUNNING)->animate(this->dt);
	}
	else if (!moving && !jumping)
	{
		this->anim->getAnimation(ANIMATION_RUNNING)->reset();
		this->anim->getAnimation(ANIMATION_IDLE)->animate(this->dt);
	}

	if (phys->isMovingUp())
	{
		this->anim->getAnimation(ANIMATION_JUMP)->animateOnce(this->dt);
		this->anim->getAnimation(ANIMATION_JUMP)->stop(4);
	}
	else if (phys->isMovingDown())
	{
		this->anim->getAnimation(ANIMATION_JUMP)->animateOnce(this->dt);
		this->anim->getAnimation(ANIMATION_JUMP)->start();
		this->anim->getAnimation(ANIMATION_JUMP)->stop(6);
	}

	this->phys->update(this->dt);
	shape.move(this->phys->getVelocity() * this->dt);
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

	//Testing ================== TO BE REMOVED
	this->updateTesting();
}

//Render
void Game::renderTesting()
{
	this->window->draw(shape); // TO BE REMOVED ===================== TO BE REMOVED

	this->window->draw(text); // TO BE REMOVED ===================== TO BE REMOVED
}

void Game::render()
{
	this->window->clear(Color(0, 0, 0, 0));

	//TO BE REMOVED =========================== TO BE REMOVED
	this->renderTesting();

	this->window->display();
}

