#pragma once
#include "Spacecraft.h"
#include <iostream>

class Hispania : public Spacecraft {

public:
	Hispania(float x, float y, float width, float height, float r, float g, float b)
		: Spacecraft(x, y, width, height, r, g, b) {};

	~Hispania() {
		std::cout << "~Derived() is executed";
	};

	void Draw();
	void Tick();
};