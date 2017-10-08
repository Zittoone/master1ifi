
#include "Fourmi.h"

void Fourmi::draw() {

	// avec la pointe qui pointe vers la direction actuelle.
	// vecteur u (0.01, 0.02) -> u = 1i + 2j
	// vecteur v (0.01, 0.00) -> v = 1i + 0j = 1i

	int vx = VposX * 100;
	int vy = VposY * 100;
	float a = 60;
	std::cout << a << std::endl;
	a = a * (3.14 / 180);
	

	float x2 = posX - width / 2;
	float y2 = posY - height;

	x2 = (x2 * cos(a)) - (y2 * sin(a));
	y2 = (x2 * sin(a)) + (y2 * cos(a));

	float x3 = posX + width / 2;
	float y3 = posY - height;

	x3 = (x3 * cos(a)) - (y3 * sin(a));
	y3 = (x3 * sin(a)) + (y3 * cos(a));
	

	GraphicPrimitives::drawFillTriangle2D(
		posX, posY,
		x2, y2,
		x3, y3,
		R, G, B);
}



void Fourmi::tick() {
	posX += VposX;
	if (posX > 1.0f - height || posX < -1.0f) {
		VposX = -VposX;
		posX += VposX;
	}

	posY += VposY;
	if (posY > 1.0f - width || posY < -1.0f) {
		VposY = -VposY;
		posY += VposY;
	}

	/*
	width += Vwidth;
	if (width > 0.4f || width < 0.05) {
		Vwidth = -Vwidth;
		width += Vwidth;
	}

	height += Vheight;
	if (height > 0.2f || height < 0.02) {
		Vheight = -Vheight;
		height += Vheight;
	}*/
}