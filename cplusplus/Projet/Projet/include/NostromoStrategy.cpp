#include "NostromoStrategy.h"
#include "SpacecraftFactory.h"

class SpacecraftFactory;

Spacecraft * NostromoStrategy::getSpacecraft(int x, int y, GraphicalDrawingBoard * gdb, Environment * environment)
{
	return SpacecraftFactory::getInstance().getNostromoSpacecraft(x, y, gdb, environment);
}
