#pragma once
#include "Engine.h"
#include "Spacecraft.h"

class MyControlEngine : public ControlEngineBase {

    std::vector<Spacecraft*>* ships;

public:
    MyControlEngine(std::vector<Spacecraft*>* spaceships):ships(spaceships){}
    
    virtual void MouseCallback(int button, int state, int x, int y) ;
};
