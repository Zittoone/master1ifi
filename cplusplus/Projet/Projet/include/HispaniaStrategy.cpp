#include "HispaniaStrategy.h"
#include "SpacecraftFactory.h"

Spacecraft * HispaniaStrategy::getSpacecraft(int x, int y, GraphicalDrawingBoard* gdb, Environment* environment)
{
	return SpacecraftFactory::getInstance().getHispaniaSpacecraft(x, y, gdb, environment);
}
