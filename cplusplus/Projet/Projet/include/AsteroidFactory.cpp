#include "AsteroidFactory.h"
#include <cstdlib>
#include <ctime>

# define M_PI           3.14159265358979323846  /* pi */

// Pourquoi utiliser la factory avec des valeurs en dur :
// Car je ne veux pas coder les valeurs en dur dans les classes et on peut espèrer voir
// un fichier de configuration voir le jour, dans ce cas on viendra effectuer cela dans la factory
float AsteroidFactory::randomFloatRange(float min, float max)
{
	// Seed to get more random
	//srand(time(NULL));
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = max - min;
	float r = random * diff;
	return min + r;
}

Eros * AsteroidFactory::getErosAsteroid(GraphicalDrawingBoard* gdb)
{
	//float x, float y, double health, float direction, float speed, float width, float height, float r, float g, float b
	// X should be the very right of the game
	float x = gdb->getX2();
	float y = randomFloatRange(gdb->getY1() - 0.08, gdb->getY2() + 0.08);
	double health = 100.;
	float direction = M_PI; // always go total left
	float speed = 0.001;
	float width = 0.045;
	float height = 0.045;
	float r, g, b;
	r = g = b = 0.5;
	return new Eros(x, y, health, direction, speed, width, height, r, g, b, 50.);
}

Blume * AsteroidFactory::getBlumeAsteroid(GraphicalDrawingBoard* gdb)
{
	float x = gdb->getX2();
	float y = randomFloatRange(gdb->getY1() - 0.1, gdb->getY2() + 0.1);
	double health = 200.;
	float direction = M_PI; // always go total left
	float speed = 0.0008;
	float width = 0.1;
	float height = 0.1;
	return new Blume(x, y, health, direction, speed, width, height, 0, 1., 1., 200.);
}

Zephyr * AsteroidFactory::getZephyrAsteroid(GraphicalDrawingBoard* gdb)
{
	float x = gdb->getX2();
	float y = randomFloatRange(gdb->getY1() - 0.3, gdb->getY2() + 0.3);
	double health = 1000.;
	double shield = 500.;
	float direction = M_PI; // always go total left
	float speed = 0.0004;
	float width = 0.3;
	float height = 0.3;
	return new Zephyr(x, y, health, shield, direction, speed, width, height, 0.9, 0, 0, 500.);
}
