#pragma once

#include "ControlEngineBase.h"
#include "Environment.h"

class Controller : public ControlEngineBase {

	// Ref ton the environment
	Environment* environment;

public:
	Controller(Environment* environment) : environment(environment) {};

	virtual void MouseCallback(int button, int state, int x, int y);
	virtual void CreateSpacecraft(int x, int y);
};