#include "Player.h"

//Private functions

void Player::initializeVariables()
{
	this->moving = false;
	this->jumping = false;
}

void Player::initializeComponents()
{
	//INPUT COMPONENT
	this->input_c = new InputComponent(
		Keyboard::Key::A,				//LEFT KEYBOARD
		Keyboard::Key::D,				//RIGHT KEYBOARD
		Keyboard::Key::Space,			//JUMP KEYBOARD
		Keyboard::Key::S,				//CROUCH KEYBOARD
		Keyboard::Key::LShift,			//SPRINT KEYBOARD
		JOY_A,							//JUMP JOYSTICK
		JOY_B							//SPRINT JOYSTICK
	);

	//ANIMATION COMPONENT
	this->animation_c = new AnimationComponent();

	//PHYSICS COMPONENT
	this->physics_c = new PhysicsComponent
	(
		Vector2f(0.f, 0.f),				//Velocity
		Vector2f(2000.f, 2000.f),		//Max speed
		Vector2f(8000.f, 10000.f),		//Acceleration
		Vector2f(1.f, 1.f),				//AccelerationMultiplier
		4000.f,							//Degen Left
		4000.f,							//Degen Right
		0.f,							//Degen Up
		0.f								//Degen Down
	);

	//LEVELING COMPONENT
	this->leveling_c = new LevelingComponent(1);
}

void Player::initializeAnimations()
{
	this->animation_c->addAnimation(Animation("Running", this->getSprite(), IntRect(0, 0, 40.f, 50.f), 400, 50, 0.f, 0.5f));
	this->animation_c->addAnimation(Animation("Idle", this->getSprite(), IntRect(0, 100, 40.f, 50.f), 200, 50, 0.f, 1.5f));
	this->animation_c->addAnimation(Animation("Jumping", this->getSprite(), IntRect(0, 200, 40.f, 50.f), 360, 50, 0.f, 0.9f));
}

void Player::initializeSprite()
{
	this->setScale(this->ORIGINAL_SCALE_X, this->ORIGINAL_SCALE_Y);
}

void Player::initialize()
{
	this->initializeVariables();

	this->initializeComponents();

	this->initializeAnimations();

	this->initializeSprite();
}

//Cleanup
void Player::cleanup()
{
	//Variables

	//Components
	delete this->input_c;
	delete this->animation_c;
	delete this->physics_c;
	delete this->leveling_c;
}

//Constructors / Destructors
Player::Player(std::string name, int maxHealth, float xPos, float yPos, float xScale, float yScale, IntRect textureRect, const Texture* texture)
	: Character(name, maxHealth, xPos, yPos, xScale, yScale, textureRect, texture)
{
	this->initialize();
}

Player::~Player()
{
	this->cleanup();
}

//Accessors
LevelingComponent * Player::getLevelingComponent()
{
	return this->leveling_c;
}



//Modifiers
void Player::updateCollision(const float & dt, const RenderWindow * window)
{
	//COLLISION WITH SCREEN TO BE REMOVED!!! =============================== !!!

	//Gravity & Collision with screen
	if (this->getPosition().y + this->getBounds().height < window->getSize().y) //Not touching bottom of screen
	{
		this->physics_c->incrementVelocityOuterForce(0.f, GLOBAL_PHYSICS_GRAVITY, dt);
	}
	else //Collision with bottom of screen
	{
		this->physics_c->stopVelocityY();
		this->setPosition(this->getPosition().x, window->getSize().y - this->getBounds().height);
		this->animation_c->getAnimation(ANIMATION_JUMP)->reset();

		this->jumping = false; //Reset jumping
	}

	if (this->getPosition().y < 0.f) //Collision top of screen
	{
		this->physics_c->stopVelocityY();
		this->setPosition(this->getPosition().x, 0.f);
	}

	if (this->getPosition().x < 0.f) //Collision left of screen
	{
		this->physics_c->stopVelocityX();
		this->setPosition(0.f, this->getPosition().y);
	}

	if (this->getPosition().x + this->getBounds().width > window->getSize().x) //Collision right of screen
	{
		this->physics_c->stopVelocityX();
		this->setPosition(window->getSize().x - this->getBounds().width, this->getPosition().y);
	}
}

void Player::updateAnimation(const float& dt)
{
	if (moving && !jumping)
	{
		this->animation_c->getAnimation(ANIMATION_IDLE)->reset();
		this->animation_c->getAnimation(ANIMATION_RUNNING)->animate(dt);
	}
	else if (!moving && !jumping)
	{
		this->animation_c->getAnimation(ANIMATION_RUNNING)->reset();
		this->animation_c->getAnimation(ANIMATION_IDLE)->animate(dt);
	}

	if (physics_c->isMovingUp())
	{
		this->animation_c->getAnimation(ANIMATION_JUMP)->animateOnce(dt);
		this->animation_c->getAnimation(ANIMATION_JUMP)->stop(4);
	}
	else if (physics_c->isMovingDown())
	{
		this->animation_c->getAnimation(ANIMATION_JUMP)->animateOnce(dt);
		this->animation_c->getAnimation(ANIMATION_JUMP)->start();
		this->animation_c->getAnimation(ANIMATION_JUMP)->stop(6);
	}
}

void Player::updateInput(const float & dt)
{
	// INPUT ====================================== INPUT
	if (this->input_c->isKeyPressed(RIGHT_KEY)) // MOVEMENT RIGHT
	{
		if (!this->jumping)
			physics_c->incrementVelocity(1.f, 0.f, dt);
		else
		{
			physics_c->incrementVelocity(1.f, 0.f, 0.6f, dt);
		}
	}

	if (this->input_c->isKeyPressed(LEFT_KEY)) // MOVEMENT LEFT
	{
		if (!jumping)
			physics_c->incrementVelocity(-1.f, 0.f, dt);
		else
		{
			physics_c->incrementVelocity(-1.f, 0.f, 0.6f, dt);
		}
	}

	if (this->input_c->isKeyPressed(JUMP_KEY) && !jumping) // MOVEMENT JUMP
	{
		physics_c->setVelocityY(-1200.f);// TO BE CHANGED!!!!! ======================= !!!!!!!!!

		jumping = true; // Set jumping
						//phys->incrementVelocity(0.f, -1.f, dt);
	}

	if (this->input_c->isKeyPressed(SPRINT_KEY)) // TO BE CHANGED!!!!! ====================== !!!!!!!!
		this->physics_c->setAccelerationMultiplier(Vector2f(1.2f, 1.f));
	else
		this->physics_c->setAccelerationMultiplier(Vector2f(1.f, 1.f));

	//Change movement variables and sprite facing direction
	if (physics_c->isMovingLeft())
	{
		this->setScale(-this->ORIGINAL_SCALE_X, this->ORIGINAL_SCALE_Y);
		this->setOrigin(this->getTextureRect().width, 0.f);
		moving = true;
	}
	else if (physics_c->isMovingRight())
	{
		this->setScale(this->ORIGINAL_SCALE_X, this->ORIGINAL_SCALE_Y);
		this->setOrigin(0.f, 0.f);
		moving = true;
	}
	else
	{
		moving = false;
	}

	//Final move and update
	this->physics_c->update(dt);
	this->move(this->physics_c->getVelocity() * dt);
}

//Functions
void Player::update(const float & dt, const RenderWindow* window)
{
	//Collision
	this->updateCollision(dt, window);

	//Animation
	this->updateAnimation(dt);

	//Input
	this->updateInput(dt);
}

void Player::render(RenderTarget * target)
{
	target->draw(*this->getSprite());
}
