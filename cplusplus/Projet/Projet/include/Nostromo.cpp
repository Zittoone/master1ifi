#include "Nostromo.h"
#include "GraphicPrimitives.h"

void Nostromo::Draw()
{
	float x1 = x;
	float y1 = y + (height / 2);
	float x2 = x - (width / 2);
	float y2 = y - (height / 2);
	float x3 = x + (width / 2);
	float y3 = y2;

	Asteroid* closest = environment->closestAsteroidFromSpacecraft(this);
	if (closest != nullptr && distance_to(closest) <= range) {
		float angle = angle_to_drawble(closest);
		// look towards the closest asteroid to hit
		rotate_point(x1, y1, angle, &x1, &y1);
		rotate_point(x2, y2, angle, &x2, &y2);
		rotate_point(x3, y3, angle, &x3, &y3);
	}


	GraphicPrimitives::drawFillTriangle2D(x1, y1, x2, y2, x3, y3, r, g, b);

	int size = laserShots->size();
	for (int i = 0; i < size; i++) {
		(*laserShots)[i]->Draw();
	}
}

void Nostromo::Tick()
{
	Asteroid* closest = environment->closestAsteroidFromSpacecraft(this);
	Shot(closest);

	int size = laserShots->size();

	std::vector<LaserShot*>* toRemove = new std::vector<LaserShot*>;
	for (int i = 0; i < size; i++) {
		(*laserShots)[i]->Tick();
		if ((*laserShots)[i]->hasHit() || !environment->isDrawableInGdb((*laserShots)[i]))
			toRemove->push_back((*laserShots)[i]);
	}

	size = toRemove->size();
	for (int i = 0; i < size; i++)
	{
		deleteShot((*toRemove)[i]);
	}

	delete toRemove;
}