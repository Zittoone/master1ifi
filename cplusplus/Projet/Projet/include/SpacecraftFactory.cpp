#include "SpacecraftFactory.h"

Elysium * SpacecraftFactory::getElysiumSpacecraft(int x, int y, GraphicalDrawingBoard * gdb)
{
	return new Elysium(gdb->getXCoordFor(x), gdb->getYCoordFor(y), 0.055, 0.055, 0.5, 15, 0.25, 125, 250, 0.09, 0.8, 0.9);
}

Hispania * SpacecraftFactory::getHispaniaSpacecraft(int x, int y, GraphicalDrawingBoard * gdb)
{

	return new Hispania(gdb->getXCoordFor(x), gdb->getYCoordFor(y), 0.055, 0.055, 0.5, 15, 0.25, 125, 250, 0.09, 0.9, 0.45);
}

Nostromo * SpacecraftFactory::getNostromoSpacecraft(int x, int y, GraphicalDrawingBoard * gdb)
{
	return new Nostromo(gdb->getXCoordFor(x), gdb->getYCoordFor(y), 0.055, 0.055, 0.5, 15, 0.25, 125, 250, 0.9, 0.5, 0.1);
}
