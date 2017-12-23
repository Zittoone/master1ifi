#pragma once
#include "Spacecraft.h"

class Nostromo : public Spacecraft {

public:
	Nostromo(float x, float y, float width, float height, double frequency, double power, double range, double health, double cost, float r, float g, float b, Environment* environment)
		: Spacecraft(x, y, width, height, frequency, power, range, health, cost, r, g, b, environment) {};

	virtual void Tick();
	virtual void Draw();
};