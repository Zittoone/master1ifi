#pragma once
#include "GraphicalDrawingBoard.h"
#include "Asteroid.h"
#include <ctime>
#include <ratio>
#include <chrono>

// Circular dependency
class Environment;
class GraphicalDrawingBoard;

class Level {
	bool started;
	int nbAsteroid;
	int nbAsteroidLeft;
	int n;

public:
	Level(int level);

	virtual void startLevel();
	virtual Asteroid* getAsteroid(GraphicalDrawingBoard* gdb);
	bool hasStarted() { return started; }
	int getN() { return n; }
	int getNAsteroid() { return nbAsteroid; }
	int getNAsteroidLeft() { return nbAsteroidLeft; }
};