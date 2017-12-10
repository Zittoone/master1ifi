#pragma once

#include "Spacecraft.h"
#include "GameEngineBase.h"
#include "GraphicalDrawingBoard.h"
#include "Asteroid.h"
#include "Level.h"

// Circular dependency
class GraphicalDrawingBoard;

class Environment : public GameEngineBase {

	// 2D array map
	bool** board;
	//std::vector<ITickable*>* tickables;
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

	virtual void addSpacecraft(Spacecraft* spacecraft, int x, int y);
	virtual void removeSpacecraft(Spacecraft* spacecraft);
	virtual void addAsteroid(Asteroid* asteroid);
	virtual void removeAsteroid(Asteroid* asteroid);
	virtual void setLevel(Level* level);
	virtual Level* getLevel();
	virtual void loseHealth(int amount);
	virtual void giveHealth(int amount);
	int getHealth() { return health; }
	virtual void endGame();

	virtual Asteroid* closestAsteroidFromSpacecraft(Spacecraft* spacecraft);
	virtual Asteroid* closestAsteroidToLeft(Spacecraft* spacecraft);
	virtual Asteroid* lowestHealthTouchableAsteroid(Spacecraft* spacecraft);
};