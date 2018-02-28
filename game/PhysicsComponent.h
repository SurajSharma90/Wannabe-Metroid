#pragma once
#include"libs.h"

class PhysicsComponent
{
private:
	Vector2f xVelocity;
	Vector2f yVelocity;
	float maxSpeed;

	Vector2f xDegeneration;
	Vector2f yDegeneration;

	void calculateDegeneration()
	{

	}

public:
	//Constructors / Destructors
	PhysicsComponent(
		const Vector2f& xVelocity = Vector2f(0.f, 0.f),
		const Vector2f& yVelocity = Vector2f(0.f, 0.f),
		const float& maxSpeed = 0.f,
		const Vector2f& xDegeneration = Vector2f(0.f, 0.f),
		const Vector2f& yDegeneration = Vector2f(0.f, 0.f))
	{
		this->xVelocity = xVelocity;
		this->yVelocity = yVelocity;
		this->maxSpeed = maxSpeed;
		this->xDegeneration = xDegeneration;
		this->yDegeneration = yDegeneration;
	}

	//Accessors
	inline Vector2f getVelocityVector() const
	{
		return this->xVelocity + this->yVelocity;
	}

	inline Vector2f getDirectionVector() const
	{
		Vector2f vector = this->getVelocityVector();
		return vector / (pow(vector.x, 2) + pow(vector.y, 2));
	}

	inline float getMaxSpeed() const
	{
		return this->maxSpeed;
	}

	//Modifiers
	inline void setXDegeneration(const Vector2f& xDegeneration)
	{
		this->xDegeneration = xDegeneration;
	}

	inline void setYDegeneration(const Vector2f& yDegeneration)
	{
		this->yDegeneration = yDegeneration;
	}

	//Functions
	void update()
	{

	}
};