#include <iostream>

#include "Engine.h"
#include "ControlEngineBase.h"
#include "GameEngineBase.h"
#include "GraphicEngineBase.h"
#include "MyControlEngine.h"
#include "MyGameEngine.h"
#include "MyGraphicEngine.h"
#include "Papillon.h"

int main(int argc, char* argv[]){
    Engine e(argc,argv);
    
    std::vector<Papillon*> paps;
    
    GraphicEngineBase* ge = new MyGraphicEngine(&paps);
    GameEngineBase* gme = new MyGameEngine(&paps);
    ControlEngineBase* ce = new MyControlEngine(&paps);
    
    e.setGraphicEngine(ge);
    e.setGameEngine(gme);
    e.setControlEngine(ce);
    
    e.start();
    return 0;
}
