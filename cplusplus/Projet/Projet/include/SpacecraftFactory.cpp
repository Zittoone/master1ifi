#include "SpacecraftFactory.h"

Elysium * SpacecraftFactory::getElysiumSpacecraft(int x, int y, GraphicalDrawingBoard * gdb, Environment* environment)
{
	return new Elysium(gdb->getXCoordFor(x), gdb->getYCoordFor(y), 0.055, 0.055, 0.5, 30, 0.50, 125, 1000, 0.09, 0.2, 1., environment);
}

Hispania * SpacecraftFactory::getHispaniaSpacecraft(int x, int y, GraphicalDrawingBoard * gdb, Environment* environment)
{

	return new Hispania(gdb->getXCoordFor(x), gdb->getYCoordFor(y), 0.055, 0.055, 0.5, 15, 0.5, 125, 250, 0.09, 0.9, 0.45, environment);
}

Nostromo * SpacecraftFactory::getNostromoSpacecraft(int x, int y, GraphicalDrawingBoard * gdb, Environment* environment)
{
	return new Nostromo(gdb->getXCoordFor(x), gdb->getYCoordFor(y), 0.075, 0.075, 0.3, 60, 0.8, 125, 2000, 0.9, 0.5, 0.1, environment);
}
