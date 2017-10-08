
#include "MyGraphicEngine.h"
#include <string>

void MyGraphicEngine::Draw(){
    
    
    GraphicPrimitives::drawLine2D(x1,0.5f,x2,-0.5f,1.0f,0.0f,1.0f);
    GraphicPrimitives::drawText2D(str,-1.0f,0.9f,0.0f,0.0f, 1.0f);

	strcpy(nb, std::to_string(paps->size() + frmis->size()).c_str());
	GraphicPrimitives::drawText2D(nb, 0.7f, 0.9f, 0.0f, 0.0f, 1.0f);
    
    for (int i = 0; i < paps->size(); i++) {
        (*paps)[i]->draw();
    }

	for (int i = 0; i < frmis->size(); i++) {
		(*frmis)[i]->draw();
	}
    
    
    x1 += vx1;
    if (x1 > 0.9f || x1 < -0.9f) {
        vx1 = -vx1;
        x1 += vx1;
    }
    
    x2 += vx2;
    if (x2 > 0.9f || x2 < -0.9f) {
        vx2 = -vx2;
        x2 += vx2;
    }
    
}