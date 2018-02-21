#include "ElysiumStrategy.h"
#include "SpacecraftFactory.h"

class SpacecraftFactory;

Spacecraft * ElysiumStrategy::getSpacecraft(int x, int y, GraphicalDrawingBoard * gdb, Environment * environment)
{
	return SpacecraftFactory::getInstance().getElysiumSpacecraft(x, y, gdb, environment);
}
