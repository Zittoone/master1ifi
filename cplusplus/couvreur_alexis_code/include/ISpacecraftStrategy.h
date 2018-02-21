#pragma once

#include "Spacecraft.h"
#include "GraphicalDrawingBoard.h"

class ISpacecraftStrategy {
public:
	virtual Spacecraft* getSpacecraft(int x, int y, GraphicalDrawingBoard* gdb, Environment* environment) = 0;
};