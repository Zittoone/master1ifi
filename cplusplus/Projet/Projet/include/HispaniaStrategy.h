#pragma once

#include "ISpacecraftStrategy.h"

class HispaniaStrategy : public ISpacecraftStrategy {
public:
	virtual Spacecraft* getSpacecraft();
};