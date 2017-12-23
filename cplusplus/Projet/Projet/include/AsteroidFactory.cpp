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
	srand(static_cast <unsigned> (time(0)));
	return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));;
}

Eros * AsteroidFactory::getErosAsteroid(GraphicalDrawingBoard* gdb)
{
	//float x, float y, double health, float direction, float speed, float width, float height, float r, float g, float b
	// X should be the very right of the game
	float x = gdb->getX2();
	float y = randomFloatRange(gdb->getY1() - 0.02, gdb->getY2() + 0.02);
	double health = 100.;
	float direction = M_PI; // always go total left
	float speed = 0.005;
	float width = 0.015;
	float height = 0.015;
	float r, g, b;
	r = g = b = 0.005;
	return new Eros(x, y, health, direction, speed, width, height, r, g, b);
}

Blume * AsteroidFactory::getBlumeAsteroid(GraphicalDrawingBoard* gdb)
{
	float x = gdb->getX2();
	float y = randomFloatRange(gdb->getY1() + 0.02, gdb->getY2() - 0.02);
	double health = 200.;
	float direction = M_PI; // always go total left
	float speed = 0.003;
	float width = 0.020;
	float height = 0.020;
	return new Blume(x, y, health, direction, speed, width, height, 0, 0, 0.5);
}

Zephyr * AsteroidFactory::getZephyrAsteroid(GraphicalDrawingBoard* gdb)
{
	float x = gdb->getX2();
	float y = randomFloatRange(gdb->getY1() + 0.02, gdb->getY2() - 0.02);
	double health = 200.;
	double shield = 100.;
	float direction = M_PI; // always go total left
	float speed = 0.001;
	float width = 0.040;
	float height = 0.040;
	return new Zephyr(x, y, health, shield, direction, speed, width, height, 0.55, 0, 0);
}
