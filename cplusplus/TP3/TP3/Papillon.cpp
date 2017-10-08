
#include "Papillon.h"

void Papillon::draw(){
    
    GraphicPrimitives::drawFillRect2D(posX,posY,width,height,R,G,B);
}



void Papillon::tick(){
    posX += VposX;
    if (posX > 1.0f - height || posX < -1.0f) {
        VposX = -VposX;
        posX += VposX;
    }
    
    posY += VposY;
    if (posY > 1.0f - width || posY < -1.0f) {
        VposY = -VposY;
        posY += VposY;
    }
    
    width += Vwidth;
    if (width > 0.4f || width < 0.05) {
        Vwidth = - Vwidth;
        width += Vwidth;
    }
    
    height += Vheight;
    if (height > 0.2f || height < 0.02) {
        Vheight = - Vheight;
        height += Vheight;
    }
}
