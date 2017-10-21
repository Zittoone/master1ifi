#pragma once
#include "GraphicPrimitives.h"

class Papillon {
    
public:
    Papillon(float fx = 0.0f, float fy = 0.0f)
		:x(fx), y(fy),
		width(0.1f), height(0.1f),
		dx(0.01f), dy(0.02f),
		dw(0.01f), dh(-0.02f){
	}
    
    float x, y, width, height;

	// pos variation
	float dx;
	float dy;
	// size variation
	float dw;
	float dh;
    
    void draw();
    void tick();
    
};