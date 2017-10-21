#pragma once
#include "Engine.h"
#include "Papillon.h"

class MyControlEngine : public ControlEngineBase {
    std::vector<Papillon*>* paps;
public:
    MyControlEngine(std::vector<Papillon*>* paps_):paps(paps_){}
    
    virtual void MouseCallback(int button, int state, int x, int y) ;
};
