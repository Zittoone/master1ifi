#pragma once

#include "Engine.h"
#include "Papillon.h"
#include "Fourmi.h"
class MyGameEngine:public GameEngineBase {
    std::vector<Papillon * > *paps;
	std::vector<Fourmi * > *frmis;
public:
    
	MyGameEngine(std::vector<Papillon * > * paps_, std::vector<Fourmi * > * frmis_) :paps(paps_), frmis(frmis_){}
    
    virtual void idle();
    
};
