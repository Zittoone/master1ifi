#include "MyGameEngine.h"
#include "MyGraphicEngine.h"

void MyGameEngine::idle(){
    for (int i = 0; i < ships->size(); i++) {
        (*ships)[i]->tick();
    }
}

Spacecraft* MyGameEngine::requestCreation(int x, int y)
{
	MyGraphicEngine::
}