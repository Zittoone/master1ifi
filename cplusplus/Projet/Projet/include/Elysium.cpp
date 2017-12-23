#include "Elysium.h"
#include "GraphicPrimitives.h"

void Elysium::Draw()
{

	// test rotate
	float xp1, xp2, yp;

	rotate_point(x - (width / 2), y - height, 0, &xp1, &yp);
	rotate_point(x + (width / 2), y - height, 0, &xp2, &yp);

	float x2 = x - (width / 2);
	float y2 = y - height;

	float x3 = x + (width / 2);


	GraphicPrimitives::drawFillTriangle2D(x, y, x2, y2, x3, y2, r, g, b);
	GraphicPrimitives::drawFillTriangle2D(x, y, xp1, yp, xp2, yp, 1, 0, 0);
	//GraphicPrimitives::drawFillRect2D(x, y, width, height, r, g, b);

}

void Elysium::Tick()
{

}