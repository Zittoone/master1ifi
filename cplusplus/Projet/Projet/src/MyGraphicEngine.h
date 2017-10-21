#pragma once
#include "Engine.h"
#include "GraphicPrimitives.h"
#include "Papillon.h"

class MyGraphicEngine : public GraphicEngineBase {
private:
    std::vector<Papillon*>* paps;
    char* str;

public:
    
    MyGraphicEngine(std::vector<Papillon * > * paps_):
        paps(paps_),
    str(new char[13]{'C','l','i','c',' ','&',' ','E','n','j','o','y','\0'}),
        x1(0.5f),
        x2(-0.5f),
        dx1(0.01),
        dx2(-0.02)
        {}
    
    float x1,x2, dx1, dx2;
    
    virtual void Draw();
    
};
