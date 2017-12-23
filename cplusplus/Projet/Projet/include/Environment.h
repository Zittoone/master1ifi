#pragma once

// Circular dependency
class GraphicalDrawingBoard;
class Spacecraft;
class Level;

#include "Spacecraft.h"
#include "GameEngineBase.h"
#include "GraphicalDrawingBoard.h"
#include "Asteroid.h"
#include "Level.h"


class Environment : public GameEngineBase {

	// 2D array map
	bool** board;
	GraphicalDrawingBoard* gdb;

	std::vector<Spacecraft*>* spacecrafts;
	std::vector<Asteroid*>* asteroids;
	Level* level;

	double money;
	int health;

public:
	Environment(GraphicalDrawingBoard* gdb);

	void setMoney(double amount) { money = amount; }
	void addMoney(double amount) { money += amount; }
	double getMoney() { return money; }
	virtual bool withdrawMoney(double amount);

	virtual void idle();
	virtual bool RequestCreation(int x, int y);

	/* Spacecraft */
	virtual void addSpacecraft(Spacecraft* spacecraft, int x, int y);
	virtual void removeSpacecraft(Spacecraft* spacecraft);

	/* Asteroids */
	virtual void addAsteroid(Asteroid* asteroid);
	virtual void removeAsteroid(Asteroid* asteroid);

	/* Level */
	virtual void setLevel(Level* level);
	virtual void setLevel(int level);
	virtual Level* getLevel();
	
	/* Health */
	virtual void loseHealth(int amount);
	virtual void giveHealth(int amount);
	int getHealth() { return health; }

	/* Terminner la partie */
	virtual void endGame();

	virtual Asteroid* closestAsteroidFromSpacecraft(Spacecraft* spacecraft);
	virtual Asteroid* closestAsteroidToLeft(Spacecraft* spacecraft);
	virtual Asteroid* lowestHealthTouchableAsteroid(Spacecraft* spacecraft);
};