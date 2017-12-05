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

public:
	Environment(GraphicalDrawingBoard* gdp) : gdp(gdp) {
		tickables = new std::vector<ITickable*>;
	};

	virtual void idle();
	virtual bool RequestCreation(int x, int y);

	virtual void addTickable(ITickable* tickable);
	virtual void removeTickable(ITickable* tickable);

	virtual void addDrawable(IDrawable* drawable);
	virtual void removeTickable(IDrawable* drawable);
};