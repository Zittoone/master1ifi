#pragma once
#include "DrawableObject.h"
#include "ITickable.h"

class MovableObject :
	public DrawableObject, public ITickable
{
protected:

	// Vecteur de direction
	float direction, speed;
public:
	MovableObject(float x, float y, float direction, float speed, float width, float height, float r, float g, float b)
		: DrawableObject(x, y, width, height, r, g, b), direction(direction), speed(speed) {};

	virtual ~MovableObject() = 0;

	void setDirection(float direction)	{ this->direction = direction; }
	void setSpeed(float speed)			{ this->speed = speed;		   }

	float getDirection(){ return direction; }
	float getSpeed()	{ return speed;		}

};