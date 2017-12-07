#pragma once

#include "ControlEngineBase.h"
#include "Environment.h"
#include "ISpacecraftStrategy.h"

class Controller : public ControlEngineBase {

	// Ref ton the environment
	Environment* environment;
	GraphicalDrawingBoard* gdb;

	ISpacecraftStrategy* scStrategy;
	

public:
	Controller(Environment* environment, GraphicalDrawingBoard* gdb) : environment(environment), gdb(gdb) {};

	virtual void MouseCallback(int button, int state, int x, int y);
	virtual void CreateSpacecraft(int x, int y);

	virtual void setSpacecraftStrategy(ISpacecraftStrategy* scStrategy);
};