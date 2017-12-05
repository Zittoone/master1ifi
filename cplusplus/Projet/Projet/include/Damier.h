#pragma once
#include "Spacecraft.h"
#include "GraphicPrimitives.h"

// TODO: créer classe abstraite drawable
class Damier {

	// Matrice size x size
	int size;
	float x1, y1, x2, y2;
	Spacecraft*** damier;

	/* Private methods */
	virtual int xIndexOf(int x);
	virtual int yIndexOf(int y);

public:
	Damier(int n, float x1, float y1, float x2, float y2) 
		: size(n), x1(x1), y1(y1), x2(x2), y2(y2) {

		// 2D
		damier = new Spacecraft**[size];

		// 1D
		for (int i = 0; i < size; i++) {
			damier[i] = new Spacecraft *[size];
		}

		// No spaceships
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				damier[i][j] = NULL;
			}
		}
	}

	virtual void Draw();
	virtual Spacecraft* shipAt(float x, float y);
	virtual bool isShipOn(float x, float y);
};