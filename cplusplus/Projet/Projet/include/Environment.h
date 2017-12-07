#pragma once

#include <vector>
#include <algorithm> // remove func
#include"GameEngineBase.h"
#include "GraphicalDrawingBoard.h"
#include "ITickable.h"

class Environment : public GameEngineBase {

	// 2D array map
	bool** board;
	std::vector<ITickable*>* tickables;
	GraphicalDrawingBoard* gdp;

	double money;

public:
	Environment(GraphicalDrawingBoard* gdp);

	void setMoney(double amount) { money = amount; }
	void addMoney(double amount) { money += amount; }
	double getMoney() { return money; }
	virtual bool withdrawMoney(double amount);

	virtual void idle();
	virtual bool RequestCreation(int x, int y);

	virtual void addTickable(ITickable* tickable);
	virtual void removeTickable(ITickable* tickable);
};