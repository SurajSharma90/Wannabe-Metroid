#pragma once

#include "libs.h"
#include "Character.h"

class Player : public Character
{
private:
	//Variables
	Vector2i gridPosition;
	bool moving;
	bool jumping;
	bool falling;
	bool sprinting;
	float sprintMultiplier;

	bool collision_top;
	bool collision_bottom;
	bool collision_left;
	bool collision_right;

	//Components
	InputComponent *input_c;
	PhysicsComponent *physics_c;
	AnimationComponent *animation_c;
	LevelingComponent *leveling_c;
	TextTagComponent *texttag_c;

	//Enumerations
	enum animations { ANIMATION_RUNNING, ANIMATION_IDLE, ANIMATION_JUMP };

	//Private functions
	void initializeVariables();
	void initializeComponents(TextTagHandler* handler);
	void initializeAnimations();
	void initializeSprite();
	void initialize(TextTagHandler* texttaghandler);

	//Cleanup
	void cleanup();

public:
	//Constructors / Destructors
	Player(
		std::string name,
		int maxHealth, 
		float xPos,
		float yPos,
		float xScale, 
		float yScale,
		IntRect textureRect,
		TextTagHandler* texttaghandler,
		const Texture* texture = nullptr	
	);

	virtual ~Player();

	//Accessors
	Vector2f getCenter() 
	{
		return Vector2f (
			this->getSprite()->getPosition().x + this->getBounds().width / 2.f,
			this->getSprite()->getPosition().y + this->getBounds().height / 2.f
		);
	}

	Vector2f getBottomCenter() 
	{
		return Vector2f(
			this->getSprite()->getPosition().x + this->getBounds().width / 2.f,
			this->getSprite()->getPosition().y + this->getBounds().height
		);
	}

	LevelingComponent* getLevelingComponent();

	const Vector2i& getGridPosition() const;

	std::string getCollisionStatus() const;

	std::string getMovementStatus() const;

	Vector2f getSpeedPercent()
	{
		return Vector2f(
			abs(this->physics_c->getVelocity().x) / this->physics_c->getMaxSpeedX(),
			abs(this->physics_c->getVelocity().y) / this->physics_c->getMaxSpeedY()
		);
	}

	//Modifiers

	//Component shortcuts
	void gainExperience(const unsigned& experience);

	//Functions
	void updateGridPosition();

	void updateInput(const float& dt);

	void updateCollision(const float& dt, const RenderWindow* window);

	void updateAnimation(const float& dt);

	void update(const float& dt, const RenderWindow* window);

	void render(RenderTarget* target);
};