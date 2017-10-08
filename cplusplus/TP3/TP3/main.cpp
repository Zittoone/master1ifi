/*
 * Copyright (C) 2016 Guillaume Perez
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; If not, see <http://www.gnu.org/licenses/>.
*/



#include <iostream>
#include "Engine.h"
#include "Papillon.h"
#include "MyGraphicEngine.h"
#include "MyGameEngine.h"
#include "MyControlEngine.h"
#include <chrono>
#include <thread>

int main(int argc, char * argv[])
{
    
	Engine e(argc, argv);

	std::vector<Papillon *> paps;
	std::vector<Fourmi *> frmis;
	GraphicEngineBase * ge = new MyGraphicEngine(&paps, &frmis);
	GameEngineBase * gme = new MyGameEngine(&paps, &frmis);
	ControlEngineBase * ce = new MyControlEngine(&paps, &frmis);

	e.setGraphicEngine(ge);
	e.setGameEngine(gme);
	e.setControlEngine(ce);
	e.start();
    
    return 0;
    
}

