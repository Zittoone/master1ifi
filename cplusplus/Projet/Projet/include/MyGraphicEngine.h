#pragma once
#include "Engine.h"
#include "GraphicPrimitives.h"
#include "Spacecraft.h"
#include "Damier.h"

class MyGraphicEngine : public GraphicEngineBase {
private:
    std::vector<Spacecraft*>* ships;

	Damier damier;

public:
    
    MyGraphicEngine(std::vector<Spacecraft * > * spaceships, int n):
		ships(spaceships), damier(n, -0.7f, 1.0f, 1.0f, -0.7f)
        {}
    
    virtual void Draw();
    
};
