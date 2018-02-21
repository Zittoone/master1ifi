#pragma once

#include "ISpacecraftStrategy.h"

class NostromoStrategy : public ISpacecraftStrategy {
public:
	virtual Spacecraft * getSpacecraft(int x, int y, GraphicalDrawingBoard* gdb, Environment* environment);
};