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

public:
	Level(int level);

	virtual void startLevel();
	virtual Asteroid* getAsteroid(GraphicalDrawingBoard* gdb);
};