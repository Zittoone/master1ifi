#pragma once

#include "MovableObject.h"
#include "Spacecraft.h"
#include "Asteroid.h"

class Spacecraft;
class Asteroid;


class LaserShot : public MovableObject {

	Spacecraft* origin;
	Asteroid* destination;

public:
	LaserShot(float x, float y, float direction, float speed, float width, float height, float r, float g, float b, Spacecraft* origin, Asteroid* destination)
		: origin(origin), destination(destination), MovableObject(x, y, direction, speed, width, height, r, g, b) {}

	//TODO: implement methods below
	virtual void Draw();
	virtual void Tick();
};