#pragma once

#include "Asteroid.h"

// Asteroid cat. 3
class Zephyr
	: public Asteroid {

	// Stronger asteroid has shield
	double shield;

public:

	Zephyr(float x, float y, double health, double shield, float direction, float speed, float width, float height, float r, float g, float b, double value)
		: shield(shield), Asteroid(x, y, health, direction, speed, width, height, r, g, g, value) {} ;

	double getShield() { return shield; }

	// Inherited
	virtual void damageReceived(double v);
	virtual void Tick();
	virtual void Draw();
};