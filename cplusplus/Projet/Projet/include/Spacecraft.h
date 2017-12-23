#pragma once

#include "DrawableObject.h"
#include "ITickable.h"
#include "LaserShot.h"
#include "Environment.h"
#include <vector>
#include <ctime>

class LaserShot;
//class Environment;

class Spacecraft : public DrawableObject, public ITickable {

protected:

	double frequency;
	double power;
	double range;
	double maxHealth;
	double health;
	double cost;
	Environment* environment;
	std::vector<LaserShot *>* laserShots;
	std::time_t lastShot;

public:
	
	Spacecraft(float x, float y, float width, float height, double frequency, double power, double range, double health, double cost, float r, float g, float b, Environment* environment)
		: environment(environment), DrawableObject(x, y, width, height, r, g, b), frequency(frequency), power(power), range(range), health(health), cost(cost) {
	lastShot = std::time(nullptr);
	};

	~Spacecraft() {};

	double getFrequency()	{ return frequency; }
	double getPower()		{ return power;		}
	double getRange()		{ return range;		}
	double getMaxHealth()	{ return maxHealth; }
	double getHealth()		{ return health;	}
	double getCost()		{ return cost;		}

	void setHealth(double health) { this->health = health; }
	virtual bool Shot(Asteroid* asteroid);

	virtual void Tick() = 0;
	virtual void Draw() = 0;

};

