#pragma once

class ITickable;

#include "DrawableObject.h"
#include "ITickable.h"
#include "LaserShot.h"
#include <vector>
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std::chrono;

class LaserShot;
class Environment;

class Spacecraft : public DrawableObject, public ITickable {

protected:

	double frequency;
	double power;
	double range;
	double maxHealth;
	double health;
	double cost;
	std::vector<LaserShot *>* laserShots;
	steady_clock::time_point  lastShot;

public:
	
	Spacecraft(float x, float y, float width, float height, double frequency, double power, double range, double health, double cost, float r, float g, float b)
		: DrawableObject(x, y, width, height, r, g, b), frequency(frequency), power(power), range(range), health(health), cost(cost) {};

	~Spacecraft() {};

	double getFrequency()	{ return frequency; }
	double getPower()		{ return power;		}
	double getRange()		{ return range;		}
	double getMaxHealth()	{ return maxHealth; }
	double getHealth()		{ return health;	}
	double getCost()		{ return cost;		}

	virtual void Tick() = 0;
	virtual void Draw() = 0;

};

