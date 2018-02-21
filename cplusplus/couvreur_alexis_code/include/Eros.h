#pragma once

#include "Asteroid.h"

// Asteroid cat. 1
class Eros
	: public Asteroid {

public:
	Eros(float x, float y, double health, float direction, float speed, float width, float height, float r, float g, float b, double value)
		: Asteroid(x, y, health, direction, speed, width, height, r, g, g, value) {};

	virtual void damageReceived(double v);
	virtual void Tick();
	virtual void Draw();
};