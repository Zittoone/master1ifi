#include "Controller.h"
#include "Spacecraft.h"
#include "Hispania.h"

void Controller::MouseCallback(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (environment->RequestCreation(1, 1)) {
			CreateSpacecraft((x - 400) / 400.f, (y - 300) / -300.f);
			//TODO: add request to get the x and y of the model from values
		}

	}
}

void Controller::CreateSpacecraft(int x, int y) {
	Spacecraft* sc = new Hispania(x, y, 0.005f, 0.005f, 1, 0, 0);
	environment->addTickable(sc);
	environment->addDrawable(sc);
}