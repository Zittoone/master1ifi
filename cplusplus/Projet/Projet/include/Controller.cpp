#include "Controller.h"
#include "Spacecraft.h"
#include "Hispania.h"

void Controller::MouseCallback(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		
		if (gdb->isCheckboard(x, y)) {
			int _x = gdb->getCheckboardX(x);
			int _y = gdb->getCheckboardY(y);
			if (environment->RequestCreation(_x, _y)) {
				CreateSpacecraft(_x, _y);
			}
			else {
				// message d'erreur
				std::cout << "refused" << std::endl;
			}
		}
		else if (gdb->isLeftMenu(x, y)) {
			// Do stuff
		}
		else if (gdb->isDownMenu(x, y)) {
			// Do stuff
		}
	}
}

void Controller::CreateSpacecraft(int x, int y) {

	if (scStrategy == 0 || scStrategy == nullptr) {
		return;
	}

	Spacecraft* sc = scStrategy->getSpacecraft(x, y, gdb);
	if (environment->withdrawMoney(sc->getCost())) {
		// Ajout tick
		environment->addSpacecraft(sc, x, y);
		// Ajout graphique
		gdb->addDrawable(sc);
	}
	else {
		// error
	}

	
}

void Controller::setSpacecraftStrategy(ISpacecraftStrategy * scStrategy)
{
	if (this->scStrategy != 0) {
		delete this->scStrategy;
	}
	this->scStrategy = scStrategy;

}
