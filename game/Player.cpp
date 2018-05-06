#include "Player.h"

//Private functions

void Player::initializeVariables()
{
	this->moving = false;
	this->jumping = false;
	this->jumpStrength = 0.f;
	this->maxJumpStrength = 1.f;
	this->jump_released = false;
	this->jump_release_done = false;
	this->falling = false;
	this->sprinting = false;
	this->sprintMultiplier = 1.5f;
}

void Player::initializeComponents(TextTagHandler* texttaghandler)
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

	//TEXT TAG COMPONENT
	this->texttag_c = new TextTagComponent(texttaghandler);
}

void Player::initializeAnimations()
{
	this->animation_c->addAnimation(Animation("Running", this->getSprite(), IntRect(0, 0, 40.f, 50.f), 400, 50, 0.f, 0.45f));
	this->animation_c->addAnimation(Animation("Idle", this->getSprite(), IntRect(0, 100, 40.f, 50.f), 200, 50, 0.f, 1.5f));
	this->animation_c->addAnimation(Animation("Jumping", this->getSprite(), IntRect(0, 200, 40.f, 50.f), 360, 50, 0.f, 0.9f));
}

void Player::initializeSprite()
{
	this->setScale(this->ORIGINAL_SCALE_X, this->ORIGINAL_SCALE_Y);
}

void Player::initialize(TextTagHandler* texttaghandler)
{
	this->initializeVariables();

	this->initializeComponents(texttaghandler);

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
	delete this->texttag_c;
}

//Constructors / Destructors
Player::Player(
	std::string name, 
	int maxHealth, 
	float xPos, 
	float yPos, 
	float xScale, 
	float yScale, 
	IntRect textureRect,
	TextTagHandler* texttaghandler,
	const Texture* texture)
	: Character(name, maxHealth, xPos, yPos, xScale, yScale, textureRect, texture)
{
	this->initialize(texttaghandler);
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

const Vector2i& Player::getGridPosition() const
{
	return this->gridPosition;
}

std::string Player::getMovementStatus() const
{
	std::string movement_status = "";
	
	if (this->moving)
		movement_status += " moving";

	if (this->jumping)
		movement_status += " jumping";

	if (this->falling)
		movement_status += " falling";

	if (this->sprinting)
		movement_status += " sprinting";

	return movement_status;
}

//Modifiers

//Component shortcuts
void Player::gainExperience(const unsigned& experience)
{
	this->texttag_c->add(TEXTTAG_EXP_GAIN, this->getCenter(), std::to_string(experience) + " EXP");

	if (this->leveling_c->gainExperience(experience))
	{
		this->texttag_c->add(TEXTTAG_LEVEL_UP, this->getCenter(), "LEVEL UP");
	}
}

//Functions
void Player::updateGridPosition()
{
	this->gridPosition.x = this->getCenter().x / GLOBAL_WORLD_GRIDSIZE;
	this->gridPosition.y = this->getCenter().y / GLOBAL_WORLD_GRIDSIZE;
}

void Player::updateInput(const float & dt)
{
	this->jumping = false;
	this->moving = false;
	this->falling = false;

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

	if (this->physics_c->isMovingUp())
	{
		this->jumping = true;
	}
	else if (this->physics_c->isMovingDown())
	{
		this->jumping = false;
		this->falling = true;
	}
	else
	{
		this->falling = false;
	}

	// INPUT ====================================== INPUT
	if (this->input_c->isKeyPressed(RIGHT_KEY)) // MOVEMENT RIGHT
	{
		if (!this->jumping && !this->falling)
			physics_c->incrementVelocity(1.f, 0.f, dt);
		else
		{
			physics_c->incrementVelocity(1.f, 0.f, 0.6f, dt);
		}
	}

	if (this->input_c->isKeyPressed(LEFT_KEY)) // MOVEMENT LEFT
	{
		if (!jumping && !this->falling)
			physics_c->incrementVelocity(-1.f, 0.f, dt);
		else
		{
			physics_c->incrementVelocity(-1.f, 0.f, 0.6f, dt);
		}
	}

	if (this->input_c->isKeyPressed(JUMP_KEY) && !this->jumping && !this->falling)
	{
		this->jump_released = false;
		this->jump_release_done = false;
		
		if (this->jumpStrength < this->maxJumpStrength)
			this->jumpStrength += 13.f * dt;

		if (this->jumpStrength >= this->maxJumpStrength)
		{
			jump_released = true;
			jump_release_done = false;
		}
	}
	else
	{
		jump_released = true;
	}

	//JUMP
	if (jump_released && !jump_release_done && !this->jumping && !this->falling)
	{
		this->jump_release_done = true;
		physics_c->setVelocityY(-1200.f * this->jumpStrength);// TO BE CHANGED!!!!! ======================= !!!!!!!!!
		this->jumpStrength = 0.f;
	}

	if (this->input_c->isKeyPressed(SPRINT_KEY)) // TO BE CHANGED!!!!! ====================== !!!!!!!!
		this->physics_c->setAccelerationMultiplier(Vector2f(1.2f, 1.f));
	else
		this->physics_c->setAccelerationMultiplier(Vector2f(1.f, 1.f));

	//Final move and update
	this->physics_c->update(dt);
	this->move(this->physics_c->getVelocity() * dt);
}

void Player::updateCollision(const float & dt, const RenderWindow * window)
{
	//COLLISION WITH SCREEN TO BE REMOVED!!! =============================== !!!

	this->setCollisionBottom(false);
	this->setCollisionTop(false);
	this->setCollisionLeft(false);
	this->setCollisionRight(false);

	//Gravity & Collision with screen
	if (this->getPosition().y + this->getBounds().height >= window->getSize().y) //Not touching bottom of screen
	{
		this->physics_c->stopVelocityY();
		this->setPosition(this->getPosition().x, window->getSize().y - this->getBounds().height);

		this->setCollisionBottom(true);
	}

	if (this->getPosition().y <= 0.f) //Collision top of screen
	{
		this->physics_c->stopVelocityY();
		this->setPosition(this->getPosition().x, 0.f);

		this->setCollisionTop(true);
	}

	if (this->getPosition().x <= 0.f) //Collision left of screen
	{
		this->physics_c->stopVelocityX();
		this->setPosition(0.f, this->getPosition().y);

		this->setCollisionLeft(true);
	}

	if (this->getPosition().x + this->getBounds().width >= window->getSize().x) //Collision right of screen
	{
		this->physics_c->stopVelocityX();
		this->setPosition(window->getSize().x - this->getBounds().width, this->getPosition().y);

		this->setCollisionRight(true);
	}

	if (!this->getCollisionBottom())
	{
		this->physics_c->incrementVelocityOuterForce(0.f, GLOBAL_PHYSICS_GRAVITY, dt);
	}
}

void Player::updateAnimation(const float& dt)
{
	if (this->moving && !this->jumping && !this->falling)
	{
		this->animation_c->getAnimation(ANIMATION_IDLE)->reset();
		this->animation_c->getAnimation(ANIMATION_RUNNING)->animate(dt, this->getSpeedPercent().x);
	}
	else if (!this->moving && !this->jumping && !this->falling)
	{
		this->animation_c->getAnimation(ANIMATION_RUNNING)->reset();
		this->animation_c->getAnimation(ANIMATION_IDLE)->animate(dt);
	}

	if (this->jumping)
	{
		this->animation_c->getAnimation(ANIMATION_JUMP)->animateOnce(dt);
		this->animation_c->getAnimation(ANIMATION_JUMP)->stop(4);
	}
	else if (this->falling)
	{
		this->animation_c->getAnimation(ANIMATION_JUMP)->animateOnce(dt);
		this->animation_c->getAnimation(ANIMATION_JUMP)->start();
		this->animation_c->getAnimation(ANIMATION_JUMP)->stop(6);
	}
	else
		this->animation_c->getAnimation(ANIMATION_JUMP)->reset();

	if (this->getCollisionBottom())
	{
		this->animation_c->getAnimation(ANIMATION_JUMP)->reset();
	}
	else if (this->getCollisionTop())
	{

	}

	if (this->getCollisionLeft() && !this->jumping && !this->falling)
	{
		this->animation_c->getAnimation(ANIMATION_RUNNING)->reset();
		this->animation_c->getAnimation(ANIMATION_IDLE)->animate(dt);
	}
	else if (this->getCollisionRight() && !this->jumping && !this->falling)
	{
		this->animation_c->getAnimation(ANIMATION_RUNNING)->reset();
		this->animation_c->getAnimation(ANIMATION_IDLE)->animate(dt);
	}
}

void Player::update(const float & dt, const RenderWindow* window)
{
	//Grid position
	this->updateGridPosition();

	//Input
	this->updateInput(dt);

	//Hitbox
	this->updateHitbox();

	//Collision
	this->updateCollision(dt, window);

	//Animation
	this->updateAnimation(dt);

}

void Player::render(RenderTarget * target)
{
	target->draw(*this->getSprite());

	if(this->getShowHitbox())
		target->draw(this->getHitbox());
}
