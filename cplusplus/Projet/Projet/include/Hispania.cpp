#include "Hispania.h"
#include "GraphicPrimitives.h"

void Hispania::Draw()
{
	// test rotate
	float xp1, xp2, yp;

	rotate_point(x - (width / 2), y - height, M_PI, &xp1, &yp);
	rotate_point(x + (width / 2), y - height, M_PI, &xp2, &yp);

	float x2 = x - (width / 2);
	float y2 = y - height;

	float x3 = x + (width / 2);


	GraphicPrimitives::drawFillTriangle2D(x, y, x2, y2, x3, y2, r, g, b);
	GraphicPrimitives::drawFillTriangle2D(x, y, xp1, yp, xp2, yp, 1, 0, 0);
	
}

void Hispania::Tick()
{

}