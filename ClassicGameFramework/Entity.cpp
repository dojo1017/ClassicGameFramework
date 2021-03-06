﻿#include "Entity.h"
#include "Boundaries.h"
#include "Image.h"

int Entity::getImageCount() const
{
	return this->imageCount;
}

// Generic entity type with graphics and basic attributes to place in the level.
//
// @image			Pointer to array of images containing all sprites needed for animation
// @movement_speed	Units the entity can move forward in one tick
// @boundaries		contains information about size and level position in pixels
// @movable		If true, can be moved. Used by Physics.
// @animation_speed	Amount of ticks before image with current sprite is replaced by the next
Entity::Entity(Image** image, int movement_speed, bool solid, Boundaries* boundaries, bool movable, int animation_speed): image(image),
                                                                                                                             movementSpeed(movement_speed),
                                                                                                                             solid(solid),
                                                                                                                             boundaries(boundaries),
                                                                                                                             movable(movable),
                                                                                                                             animationSpeed(animation_speed)
{
}

int Entity::getWidth()
{
	return this->boundaries->width;
}

int Entity::getHeight()
{
	return this->boundaries->height;
}

int Entity::getPosX()
{
	return this->boundaries->position.x;
}

int Entity::getPosY()
{
	return this->boundaries->position.y;
}

int Entity::getMovementSpeed()
{
	return this->movementSpeed;
}

bool Entity::isSolid()
{
	return this->solid;
}

Boundaries* Entity::getBoundaries()
{
	return this->boundaries;
}

// Setter for:	pixel position in the level.
void Entity::setPosition(int xPos, int yPos)
{
	this->boundaries->position.x = xPos;
	this->boundaries->position.y = yPos;
}

void Entity::setWidth(int width)
{
	boundaries->width = width;
}

void Entity::setHeight(int height)
{
	boundaries->height = height;
}

void Entity::setPosX(int posX)
{
	boundaries->position.x = posX;
}

void Entity::setPosY(int posY)
{
	boundaries->position.y = posY;
}

bool Entity::isMovable()
{
	return this->movable;
}

Entity* Entity::getEntity()
{
	return this;
}

// Getter for:	image to be displayed by view for current tick.
// Assumes:		internalCounter gets incremented by EngineModel with each tick.
Image* Entity::getImage()
{
	auto imageIndex = animationSpeed == 0 ? 0 : internalCounter / animationSpeed;
	auto maxCounter = imageCount * animationSpeed;

	Image* image = this->image[imageIndex];

	internalCounter++;
	if(internalCounter >= maxCounter)
	{
		internalCounter = 0;
	}

	return image;
}

Entity::~Entity()
{
	/**
	for (auto i = 0; i < imageCount; i++)
	{
		delete image[i];
	}*/
//	delete image;
}
