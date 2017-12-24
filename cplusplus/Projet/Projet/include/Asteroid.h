#pragma once

#include "MovableObject.h"
#include "GraphicPrimitives.h"


class Asteroid : public MovableObject {

protected:

	double health;
	double maxHealth;
	double value;

public:
	Asteroid(float x, float y, double health, float direction, float speed, float width, float height, float r, float g, float b, double value)
		: health(health), maxHealth(health), value(value), MovableObject(x, y, direction, speed, width, height, r, g, b) {};

	double getHealth() { return health; }
	double getValue()  { return value; }

	// Pure virtual so Asteroid is abstract and any asteroid can redefine the way they handle damages
	virtual void damageReceived(double v) = 0;
	virtual void Tick() = 0;
	virtual void Draw() = 0;
};