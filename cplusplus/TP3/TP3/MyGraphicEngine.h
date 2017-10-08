#pragma once
#include "Engine.h"
#include "GraphicPrimitives.h"
#include "Papillon.h"
#include "Fourmi.h"

class MyGraphicEngine:public GraphicEngineBase {
    
    std::vector<Papillon * > *paps;
	std::vector<Fourmi * > * frmis;
    
    char * str;
	char * nb;
public:
    
    MyGraphicEngine(std::vector<Papillon * > * paps_, std::vector<Fourmi * > * frmis_) : 
		frmis(frmis_),
        paps(paps_),
		str(new char[13]{'C','l','i','c',' ','&',' ','E','n','j','o','y','\0'}),
		nb(new char[5]{' ',' ',' ','0','\0'}), //max 9999 
        x1(0.5f),
        x2(-0.5f),
        vx1(0.01),
        vx2(-0.02)
        {}
    
    float x1,x2,vx1,vx2;
    
    virtual void Draw();
    
};
