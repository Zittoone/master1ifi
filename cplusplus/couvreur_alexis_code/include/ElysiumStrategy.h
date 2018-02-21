#pragma once
#pragma once

#include "ISpacecraftStrategy.h"

class ElysiumStrategy : public ISpacecraftStrategy {
public:
	virtual Spacecraft * getSpacecraft(int x, int y, GraphicalDrawingBoard* gdb, Environment* environment);
};