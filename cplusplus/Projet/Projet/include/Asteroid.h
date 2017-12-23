#pragma once

#include "MovableObject.h"


class Asteroid : public MovableObject {

protected:

	double health;
	
public:
	Asteroid(float x, float y, double health, float direction, float speed, float width, float height, float r, float g, float b)
		: health(health), MovableObject(x, y, direction, speed, width, height, r, g, b) {};

	double getHealth() { return health; }

	// Pure virtual so Asteroid is abstract and any asteroid can redefine the way they handle damages
	virtual void damageReceived(double v) = 0;
	virtual void Tick() = 0;
	virtual void Draw() = 0;
};