#pragma once

#include "Engine.h"
#include "GameEngineBase.h"
#include "Spacecraft.h"

class MyGameEngine : public GameEngineBase {

private:
    std::vector<Spacecraft*>* ships;

public:
    MyGameEngine(std::vector<Spacecraft*>* spaceships)
		:ships(spaceships){
	}
    virtual void idle();
	static Spacecraft* requestCreation(int x, int y);
};

