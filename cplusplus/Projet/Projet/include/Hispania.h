#pragma once
#include "Spacecraft.h"

class Hispania : public Spacecraft {

public:
	Hispania(float x, float y, float width, float height, float r, float g, float b)
		: Spacecraft(x, y, width, height, r, g, b) {};

	// virtual ~Hispania();

	virtual void Draw();
	virtual void Tick();
};