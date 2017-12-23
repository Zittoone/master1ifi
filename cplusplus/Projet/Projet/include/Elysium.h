#pragma once
#include "Spacecraft.h"

class Elysium : public Spacecraft {

public:
	Elysium(float x, float y, float width, float height, double frequency, double power, double range, double health, double cost, float r, float g, float b)
		: Spacecraft(x, y, width, height, frequency, power, range, health, cost, r, g, b) {};

	virtual void Tick();
	virtual void Draw();
};