#include "Environment.h"
#include "Spacecraft.h"
#include <algorithm> // remove func

Environment::Environment(GraphicalDrawingBoard * gdb) : gdb(gdb)
{
	spacecrafts = new std::vector<Spacecraft*>;
	asteroids = new std::vector<Asteroid*>;
	level = new Level(1);

	health = 100;
	money = 1000.;

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
	if (moneyLeft >= 0) {
		setMoney(moneyLeft);
	}
		
	return moneyLeft >= 0;
}

int Environment::getNbAsteroids() {
	return asteroids->size();
}

void Environment::idle()
{
	int size = spacecrafts->size();

	if (level->getNAsteroidLeft() <= 0 && asteroids->size() == 0) {
		Level* pBuf = level;
		level = new Level(pBuf->getN() + 1);
		delete pBuf;
	}

	// seconds
	std::time_t now = std::time(nullptr);
	if (lastSpawn == NULL || (now - lastSpawn) >= 5 - (5 / (level->getN() * 2))) {
		lastSpawn = now;
		Asteroid* asteroid = level->getAsteroid(gdb);
		if (asteroid != nullptr) {
			addAsteroid(asteroid);
			// Ajout graphique
			gdb->addDrawable(asteroid);
		}

		// hardcoded because im tired
		if (level->getN() >= 5) {
			Asteroid* asteroid = level->getAsteroid(gdb);
			if (asteroid != nullptr) {
				addAsteroid(asteroid);
				// Ajout graphique
				gdb->addDrawable(asteroid);
			}
		}

		if (level->getN() >= 10) {
			Asteroid* asteroid = level->getAsteroid(gdb);
			if (asteroid != nullptr) {
				addAsteroid(asteroid);
				// Ajout graphique
				gdb->addDrawable(asteroid);
			}
		}

	}
	for (int i = 0; i < size; i++) {
		(*spacecrafts)[i]->Tick();
	}

	/* ASTEROIDS*/
	size = asteroids->size();
	std::vector<Asteroid*>* toRemove = new std::vector<Asteroid*>; // To remove

	for (int i = 0; i < size; i++) {
		if ((*asteroids)[i]->getX() <= gdb->getX1()){
			toRemove->push_back((*asteroids)[i]);
			loseHealth((*asteroids)[i]->getValue() / 10.);
		}
		else if ((*asteroids)[i]->getHealth() <= 0) {
			toRemove->push_back((*asteroids)[i]);
			addMoney((*asteroids)[i]->getValue());
		} else {
			(*asteroids)[i]->Tick();
		}
	}

	size = toRemove->size();
	for (int i = 0; i < size; i++)
	{
		
		removeAsteroid((*toRemove)[i]);
	}
	delete toRemove;

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
	// TODO: remove from board
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
	gdb->removeDrawable(asteroid);
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

void Environment::setLevel(int level)
{
	this->level = new Level(level);
}

Level * Environment::getLevel()
{
	return level;
}

void Environment::loseHealth(int amount)
{
	if (health < amount)
		endGame();
	else health -= amount;
}

void Environment::giveHealth(int amount)
{
	health += amount;
}

void Environment::endGame()
{
	Level* ptr = level;
	level = new Level(1);
	delete ptr;
	health = 100;
	money = 1000.;

	int size = spacecrafts->size();
	for (int i = 0; i < size; i++)
	{
		delete (*spacecrafts)[i];
	}

	delete spacecrafts;

	size = asteroids->size();
	for (int i = 0; i < size; i++)
	{
		delete (*asteroids)[i];
	}

	delete asteroids;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			board[i][j] = false;
		}
	}

	gdb->endGame();


	spacecrafts = new std::vector<Spacecraft*>;
	asteroids = new std::vector<Asteroid*>;
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
		if (distance == -1 || tdistance < distance) {
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

bool Environment::isDrawableInGdb(DrawableObject* drawable) {
	return gdb->isCheckboardPercent(drawable->getX(), drawable->getY());
}