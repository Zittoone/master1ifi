#include "Environment.h"
#include "Spacecraft.h"
#include <algorithm> // remove func

Environment::Environment(GraphicalDrawingBoard * gdb) : gdb(gdb)
{
	spacecrafts = new std::vector<Spacecraft*>;
	asteroids = new std::vector<Asteroid*>;

	health = 100;
	money = 2000.;

	int size = gdb->getSize();
	board = (bool**)malloc(sizeof(bool*) * size);
	for (int i = 0; i < size; i++) {
		board[i] = (bool*)malloc(sizeof(bool) * size);
	}

	// Maybe useless
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			board[i][j] = false;
		}
	}
}

bool Environment::withdrawMoney(double amount)
{
	double moneyLeft = money - amount;
	if (moneyLeft > 0) {
		setMoney(moneyLeft);
	}
		
	return moneyLeft > 0;
}

void Environment::idle()
{
	int size = spacecrafts->size();

	for (int i = 0; i < size; i++) {
		(*spacecrafts)[i]->Tick();
	}

	size = asteroids->size();
	for (int i = 0; i < size; i++) {
		if ((*asteroids)[i]->getX() < gdb->getX1()) {
			removeAsteroid((*asteroids)[i]);
			loseHealth(5); // Transform this to level.getLosingHealth etc.
		}
		(*asteroids)[i]->Tick();
	}
}

bool Environment::RequestCreation(int x, int y)
{
	return !board[x - 1][y - 1];
}

void Environment::addSpacecraft(Spacecraft* spacecraft, int x, int y) {
	if (!RequestCreation(x, y))
		return;

	spacecrafts->push_back(spacecraft);
	spacecraft->setX(gdb->getXCoordFor(x));
	spacecraft->setY(gdb->getYCoordFor(y));

	board[x - 1][y - 1] = true;
	
}


void Environment::removeSpacecraft(Spacecraft* spacecraft) {
	spacecrafts->erase(
		std::remove(
			spacecrafts->begin(), spacecrafts->end(), spacecraft
		), spacecrafts->end()
	);
}

void Environment::addAsteroid(Asteroid * asteroid)
{
	asteroids->push_back(asteroid);
}

void Environment::removeAsteroid(Asteroid * asteroid)
{
	asteroids->erase(
		std::remove(
			asteroids->begin(), asteroids->end(), asteroid
		), asteroids->end()
	);
}

void Environment::setLevel(Level * level)
{
	if (this->level != 0) {
		delete this->level;
	}
	this->level = level;
}

Level * Environment::getLevel()
{
	return level;
}

void Environment::loseHealth(int amount)
{
	if (health > amount)
		endGame();
	else health -= amount;
}

void Environment::giveHealth(int amount)
{
	health += amount;
}

void Environment::endGame()
{
	//DO STUFF
}

Asteroid * Environment::closestAsteroidFromSpacecraft(Spacecraft * spacecraft)
{

	int size = asteroids->size();

	if (size == 0)
		return nullptr;

	int indexClosest = -1;
	float distance = -1;
	float tdistance = -1;

	for (int i = 0; i < size; i++) {
		tdistance = gdb->distanceBetweenTwoPoints(spacecraft->getX(), spacecraft->getY(), (*asteroids)[i]->getX(), (*asteroids)[i]->getY());
		if (tdistance < distance || distance == -1) {
			distance = tdistance;
			indexClosest = i;
		}
	}
	return (*asteroids)[indexClosest];
}

Asteroid * Environment::closestAsteroidToLeft(Spacecraft * spacecraft)
{
	return nullptr;
}

Asteroid * Environment::lowestHealthTouchableAsteroid(Spacecraft * spacecraft)
{
	return nullptr;
}
