#include "Hispania.h"
#include "GraphicPrimitives.h"

void Hispania::Draw()
{
	float x1 = x;
	float y1 = y + (height / 2);
	float x2 = x - (width / 2);
	float y2 = y - (height / 2);
	float x3 = x + (width / 2);
	float y3 = y2;

	float angle = angle_to_drawble(environment->closestAsteroidFromSpacecraft(this));
	// look towards the closest asteroid to hit
	rotate_point(x1, y1, angle, &x1, &y1);
	rotate_point(x2, y2, angle, &x2, &y2);
	rotate_point(x3, y3, angle, &x3, &y3);


	GraphicPrimitives::drawFillTriangle2D(x1, y1, x2, y2, x3, y3, r, g, b);
	
}

void Hispania::Tick()
{
	Asteroid* closest = environment->closestAsteroidFromSpacecraft(this);
	Shot(closest);
}