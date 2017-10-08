
#include "MyControlEngine.h"


void MyControlEngine::MouseCallback(int button, int state, int x, int y){
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        paps->push_back(new Papillon((x-400) / 400.f, (y-300)/ -300.f ));
        
    }

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		frmis->push_back(new Fourmi((x - 400) / 400.f, (y - 300) / -300.f));

	}
}
