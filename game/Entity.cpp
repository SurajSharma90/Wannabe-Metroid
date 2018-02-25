#include "Entity.h"

//Constructor / Destructor
Entity::Entity(float xPos, float yPos, Texture* texture)
{
	this->sprite.setPosition(xPos, yPos);
	this->texture = texture;
}

Entity::~Entity() 
{
	delete this->texture;
}
