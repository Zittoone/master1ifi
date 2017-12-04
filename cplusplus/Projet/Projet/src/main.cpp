#include <iostream>

#include "Engine.h"
#include "ControlEngineBase.h"
#include "GameEngineBase.h"
#include "GraphicEngineBase.h"
#include "MyControlEngine.h"
#include "MyGameEngine.h"
#include "MyGraphicEngine.h"
#include "Spacecraft.h"

int main(int argc, char* argv[]){

    Engine e(argc,argv);
    
    std::vector<Spacecraft*> ships;
    
    GraphicEngineBase* ge = new MyGraphicEngine(&ships, 8);
    GameEngineBase* gme = new MyGameEngine(&ships);
    ControlEngineBase* ce = new MyControlEngine(&ships);
    
    e.setGraphicEngine(ge);
    e.setGameEngine(gme);
    e.setControlEngine(ce);
    
    e.start();
    return 0;
}
