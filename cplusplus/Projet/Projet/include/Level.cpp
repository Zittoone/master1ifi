#include "Level.h"
#include "AsteroidFactory.h"

Level::Level(int level)
{
	started = false;
	nbAsteroid = level * 10 + 5;
	nbAsteroidLeft = nbAsteroid;
}

void Level::startLevel()
{
	started = true;
}

Asteroid * Level::getAsteroid(GraphicalDrawingBoard* gdb)
{
	if (nbAsteroidLeft < 0)
		return nullptr;

	if ((nbAsteroidLeft % 25) == 0) {
		nbAsteroid--;
		return AsteroidFactory::getInstance().getZephyrAsteroid(gdb);
	}
	else if ((nbAsteroidLeft % 10) == 0) {
		nbAsteroid--;
		return AsteroidFactory::getInstance().getBlumeAsteroid(gdb);
	} else {
		nbAsteroid--;
		return AsteroidFactory::getInstance().getErosAsteroid(gdb);
	}
}
