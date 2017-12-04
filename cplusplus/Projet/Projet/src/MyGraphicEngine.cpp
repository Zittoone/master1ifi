#include <string>
#include "MyGraphicEngine.h"
#include "MyGameEngine.h"

void MyGraphicEngine::Draw(){

	// Damier
	damier.Draw();

	// Vaisseaux
    for (int i = 0; i < ships->size(); i++) {
        (*ships)[i]->draw();
    }
        
}

