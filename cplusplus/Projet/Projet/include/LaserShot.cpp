#include "LaserShot.h"

bool LaserShot::hasHit() {
	return distance_to(destination) <= destination->getWidth() / 2;
}
void LaserShot::Draw()
{
	float x1 = x;
	float y1 = y;
	float x2 = x - 0.01;
	float y2 = y - 0.01;

	float angle = angle_to_drawble(destination);

	GraphicPrimitives::drawLine2D(x1, y1, x2, y2, r, g, b);
}

void LaserShot::Tick()
{
	x += speed * cos(direction);
	y += speed * sin(direction);

	if (hasHit()) {
		destination->damageReceived(origin->getPower());
	}
}
