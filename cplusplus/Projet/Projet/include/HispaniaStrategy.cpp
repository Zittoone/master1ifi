#include "HispaniaStrategy.h"
#include "Hispania.h"

Spacecraft * HispaniaStrategy::getSpacecraft()
{
	//TODO: replace with factory call
	return new Hispania(0.f, 0.f, 0.05f, 0.05f, 1, 0, 1);
}
