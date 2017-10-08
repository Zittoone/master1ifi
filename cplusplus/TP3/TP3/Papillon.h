#pragma once
#include "GraphicPrimitives.h"


class Papillon {
    
public:
    Papillon(float posX_ = 0.0f,float posY_ = 0.0f):posX(posX_),posY(posY_),width(0.1f),height(0.1f),VposX(0.01f),VposY(0.02f),Vwidth(0.01f),Vheight(-0.02f), R (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)), G(static_cast <float> (rand()) / static_cast <float> (RAND_MAX)), B(static_cast <float> (rand()) / static_cast <float> (RAND_MAX)){}
    // Random float : https://stackoverflow.com/questions/686353/c-random-float-number-generation

    float posX,posY,width,height;
    float VposX,VposY,Vwidth,Vheight;
    float R,G,B;
    
    void draw();
    void tick();
    
};
