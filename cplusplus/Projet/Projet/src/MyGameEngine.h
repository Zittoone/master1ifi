#pragma once

#include "Engine.h"
#include "GameEngineBase.h"
#include "Papillon.h"

class MyGameEngine : public GameEngineBase {
private:
    std::vector<Papillon*>* paps;
public:
    MyGameEngine(std::vector<Papillon*>* papillons)
		:paps(papillons){
	}
    virtual void idle();
};

