#pragma once

#include "libs.h"
#include "Character.h"

class Player : public Character
{
private:
	//Variables
	bool moving;
	bool jumping;

	//Components
	InputComponent *input_c;
	PhysicsComponent *physics_c;
	AnimationComponent *animation_c;
	LevelingComponent *leveling_c;

	//Enumerations
	enum animations { ANIMATION_RUNNING, ANIMATION_IDLE, ANIMATION_JUMP };

	//Private functions
	void initializeVariables();
	void initializeComponents();
	void initializeAnimations();
	void initializeSprite();
	void initialize();

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

	LevelingComponent* getLevelingComponent();

	//Modifiers

	//Functions
	void updateCollision(const float& dt, const RenderWindow* window);

	void updateAnimation(const float& dt);

	void updateInput(const float& dt);

	void update(const float& dt, const RenderWindow* window);

	void render(RenderTarget* target);
};