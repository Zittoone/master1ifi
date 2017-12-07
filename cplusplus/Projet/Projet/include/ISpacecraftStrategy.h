#pragma once

#include "Spacecraft.h"

class ISpacecraftStrategy {
public:
	virtual Spacecraft* getSpacecraft() = 0;
};