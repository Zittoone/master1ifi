
#include "MyGameEngine.h"


void MyGameEngine::idle(){

    for (int i = 0; i < paps->size(); i++) {
        (*paps)[i]->tick();
    }

	for (int i = 0; i < frmis->size(); i++) {
		(*frmis)[i]->tick();
	}

}

