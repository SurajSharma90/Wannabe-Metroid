#pragma once
#include"libs.h"

class PhysicsComponent
{
private:
	//Variables
	Vector2f velocity;
	Vector2f maxSpeed;
	Vector2f acceleration;
	Vector2f accelerationMultiplier;
	float degenerationLeft;
	float degenerationRight;
	float degenerationUp;
	float degenerationDown;

	//Private functions
	void calculateDegeneration(const float& dt)
	{
		//X degeneration
		if (velocity.x > 0.f) //Moving Right
		{
			this->velocity.x -= this->degenerationRight * dt;

			if (velocity.x <= 0.f)
				this->velocity.x = 0.f;
		}
		else if (velocity.x < 0.f) //Moving Left
		{
			this->velocity.x += this->degenerationLeft * dt;

			if (velocity.x >= 0.f)
				this->velocity.x = 0.f;
		}
		else //Standing still
		{
			this->velocity.x = 0.f;
		}

		//Y degeneration
		if (velocity.y > 0.f) //Moving Down
		{
			this->velocity.y -= this->degenerationDown * dt;

			if (velocity.y <= 0.f)
				this->velocity.y = 0.f;
		}
		else if (velocity.y < 0.f) //Moving Up
		{
			this->velocity.y += this->degenerationUp * dt;

			if (velocity.y >= 0.f)
				this->velocity.y = 0.f;
		}
		else //Standing still
		{
			this->velocity.y = 0.f;
		}

	}

	Vector2f normalize(const Vector2f& vector)
	{
		float vectorLength = sqrt((pow(vector.x, 2) + pow(vector.y, 2)));
		Vector2f normalizedVector = vector / vectorLength;

		if (vectorLength <= 0.f)
			return Vector2f(0.f, 0.f);
		else
			return normalizedVector;
	}

public:
	//Constructors / Destructors
	PhysicsComponent(
		const Vector2f& velocity = Vector2f(0.f, 0.f),
		const Vector2f& maxSpeed = Vector2f(0.f, 0.f),
		const Vector2f& acceleration = Vector2f(0.f, 0.f),
		const Vector2f& accelerationMultiplier = Vector2f(0.f, 0.f),
		const float& degenerationLeft = 0.f,
		const float& degenerationRight = 0.f,
		const float& degenerationUp = 0.f,
		const float& degenerationDown = 0.f)
	{
		this->velocity = velocity;
		this->maxSpeed = maxSpeed;
		this->acceleration = acceleration;
		this->accelerationMultiplier = accelerationMultiplier;
		this->degenerationLeft = degenerationLeft;
		this->degenerationRight = degenerationRight;
		this->degenerationUp = degenerationUp;
		this->degenerationDown = degenerationDown;
	}

	//Accessors
	inline const Vector2f& getVelocity() const
	{
		return this->velocity;
	}

	inline const Vector2f& getMaxSpeed() const
	{
		return this->maxSpeed;
	}

	inline const Vector2f& getAcceleration() const
	{
		return this->acceleration;
	}

	inline const Vector2f& getAccelerationMultiplier() const
	{
		return this->accelerationMultiplier;
	}

	inline const float& getDegenerationLeft() const
	{
		return this->degenerationLeft;
	}

	inline const float& getDegenerationRight() const
	{
		return this->degenerationRight;
	}

	inline const float& getDegenerationUp() const
	{
		return this->degenerationUp;
	}

	inline const float& getDegenerationDown() const
	{
		return this->degenerationDown;
	}

	inline const Vector2f& getDirectionVector()
	{
		return this->normalize(this->velocity);
	}


	//Modifiers
	inline void setVelocity(const float& x, const float& y)
	{
		this->velocity.x = x;
		this->velocity.y = y;
	}

	inline void incrementVelocity(
		const float& dirX,
		const float& dirY,
		const float& dt)
	{
		/* ASSUMES DIRECTION IS NORMALIZED!!!*/

		//Velocity X increment and clamp
		this->velocity.x += this->acceleration.x * this->accelerationMultiplier.x * dirX * dt;

		if (this->velocity.x > this->maxSpeed.x)
		{
			this->velocity.x = this->maxSpeed.x;
		}
		else if (this->velocity.x < -this->maxSpeed.x)
		{
			this->velocity.x = -this->maxSpeed.x;
		}

		//Velocity Y increment and clamp
		this->velocity.y += this->acceleration.y * this->accelerationMultiplier.y * dirY * dt;

		if (this->velocity.y > this->maxSpeed.y)
		{
			this->velocity.y = this->maxSpeed.y;
		}
		else if (this->velocity.y < -this->maxSpeed.y)
		{
			this->velocity.y = -this->maxSpeed.y;
		}
	}

	inline void incrementVelocityOuterForce(
		const float& outerAccelerationX,
		const float& outerAccelerationY,
		const float& dt)
	{
		/* ASSUMES DIRECTION IS NORMALIZED!!!*/

		//Velocity X increment and clamp
		this->velocity.x += outerAccelerationX * dt;

		if (this->velocity.x > this->maxSpeed.x)
		{
			this->velocity.x = this->maxSpeed.x;
		}
		else if (this->velocity.x < -this->maxSpeed.x)
		{
			this->velocity.x = -this->maxSpeed.x;
		}

		//Velocity Y increment and clamp
		this->velocity.y += outerAccelerationY * dt;

		if (this->velocity.y > this->maxSpeed.y)
		{
			this->velocity.y = this->maxSpeed.y;
		}
		else if (this->velocity.y < -this->maxSpeed.y)
		{
			this->velocity.y = -this->maxSpeed.y;
		}
	}

	inline void setMaxSpeed(const Vector2f& maxSpeed)
	{
		this->maxSpeed = maxSpeed;
	}

	inline void setAcceleration(const Vector2f& acceleration)
	{
		this->acceleration = acceleration;
	}

	inline void setAccelerationMultiplier(const Vector2f& accelerationMultiplier)
	{
		this->accelerationMultiplier = accelerationMultiplier;
	}

	inline void setDegenerationLeft(const float& degeneration)
	{
		this->degenerationLeft = degeneration;
	}

	inline void setDegenerationRight(const float& degeneration)
	{
		this->degenerationRight = degeneration;
	}

	inline void setDegenerationUp(const float& degeneration)
	{
		this->degenerationUp = degeneration;
	}

	inline void setDegenerationDwown(const float& degeneration)
	{
		this->degenerationDown = degeneration;
	}

	//Functions
	void stopVelocityY()
	{
		this->velocity.y = 0.f;
	}

	void stopVelocityX()
	{
		this->velocity.x = 0.f;
	}

	bool isMovingHorizontal()
	{
		if (this->velocity.x > 0.f || this->velocity.x < 0.f)
			return true;
		else
			return false;
	}
	
	bool isMovingLeft()
	{
		if (this->velocity.x < 0.f)
			return true;
		else
			return false;
	}
	
	bool isMovingRight()
	{
		if (this->velocity.x > 0.f)
			return true;
		else
			return false;
	}

	void update(const float& dt)
	{
		//Slow the entity down
		this->calculateDegeneration(dt);
	}
};