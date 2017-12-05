#pragma once
#include "GraphicPrimitives.h"
#include "DrawableObject.h"
#include "ITickable.h"

class Spacecraft : public DrawableObject, public ITickable {

protected:

	double frequency;
	double power;
	double range;
	double health;
	double cost;

public:
	
	Spacecraft(float x, float y, float width, float height, float r, float g, float b)
		: DrawableObject(x, y, width, height, r, g, b) {};

	/*virtual */~Spacecraft()/* = 0*/;

	double getFrequency()	{ return frequency; }
	double getPower()		{ return power;		}
	double getRange()		{ return range;		}
	double getHealth()		{ return health;	}
	double getCost()		{ return cost;		}

};// Derived class -> to extract to different files

