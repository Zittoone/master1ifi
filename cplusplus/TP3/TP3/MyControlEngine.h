#pragma once
#include "Engine.h"
#include "Papillon.h"
#include "Fourmi.h"

class MyControlEngine:public ControlEngineBase {
    std::vector<Papillon * > *paps;
	std::vector<Fourmi * > *frmis;
public:
    MyControlEngine(std::vector<Papillon * > * paps_, std::vector<Fourmi * > * frmis_) :paps(paps_), frmis(frmis_){}
   
    virtual void MouseCallback(int button, int state, int x, int y) ;
};
