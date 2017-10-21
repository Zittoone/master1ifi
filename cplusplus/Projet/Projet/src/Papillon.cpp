#include "Papillon.h"

void Papillon::draw(){
	GraphicPrimitives::drawFillRect2D(x, y, width, height, 0.5f, 0.5f, 0.5f, 1.0f);
}

void Papillon::tick(){
    x += dx;
    if (x > 1.0f - height || x < -1.0f) {
        dx = -dx;
        x += dx;
    }
    
    y += dy;
    if (y > 1.0f - width || y < -1.0f) {
        dy = -dy;
        y += dy;
    }
    
    width += dw;
    if (width > 0.4f || width < 0.05) {
        dw = - dw;
        width += dw;
    }
    
    height += dh;
    if (height > 0.2f || height < 0.02) {
        dh = - dh;
        height += dh;
    }
}