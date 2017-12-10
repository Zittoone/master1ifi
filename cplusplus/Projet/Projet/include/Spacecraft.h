#pragma once

#include "DrawableObject.h"
#include "ITickable.h"
#include "LaserShot.h"
#include <vector>

class Spacecraft : public DrawableObject, public ITickable {

protected:

	double frequency;
	double power;
	double range;
	double health;
	double cost;
	std::vector<LaserShot *>* laserShots;

public:
	
	Spacecraft(float x, float y, float width, float height, float r, float g, float b)
		: DrawableObject(x, y, width, height, r, g, b) {};

	~Spacecraft() {};

	double getFrequency()	{ return frequency; }
	double getPower()		{ return power;		}
	double getRange()		{ return range;		}
	double getHealth()		{ return health;	}
	double getCost()		{ return cost;		}

	virtual void Tick() = 0;
	virtual void Draw() = 0;

};

