#include "MyControlEngine.h"
#include "MyGameEngine.h"

void MyControlEngine::MouseCallback(int button, int state, int x, int y){
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		Spacecraft *pSpacecraft = MyGameEngine::requestCreation((x - 400) / 400.f, (y - 300) / -300.f);

		if (pSpacecraft == nullptr) {
			// On refuse la requête
		}
		else {
			// On accepte la requête
			ships->push_back(pSpacecraft);
		}
		
    }
}