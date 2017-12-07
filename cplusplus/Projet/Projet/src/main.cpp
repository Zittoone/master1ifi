#include <iostream>

#include "Engine.h"
#include "ControlEngineBase.h"
#include "GameEngineBase.h"
#include "GraphicEngineBase.h"
#include "Controller.h"
#include "Environment.h"
#include "GraphicalDrawingBoard.h"
#include "HispaniaStrategy.h"

int main(int argc, char* argv[]){

    Engine e(argc,argv);

    GraphicEngineBase* ge = new GraphicalDrawingBoard(8, -0.7f, 1.0f, 1.0f, -0.7f);
    GameEngineBase* gme = new Environment((GraphicalDrawingBoard *)ge);
    ControlEngineBase* ce = new Controller((Environment *)gme, (GraphicalDrawingBoard *)ge);

	((Controller *)ce)->setSpacecraftStrategy(new HispaniaStrategy());
    
    e.setGraphicEngine(ge);
    e.setGameEngine(gme);
    e.setControlEngine(ce);
    
    e.start();
    return 0;
}
