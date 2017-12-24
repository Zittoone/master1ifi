#include "Spacecraft.h"
#include <algorithm>

void Spacecraft::deleteShot(LaserShot *shot)
{
	laserShots->erase(
		std::remove(
			laserShots->begin(), laserShots->end(), shot
		), laserShots->end()
	);

	delete shot;
}

bool Spacecraft::Shot(Asteroid * asteroid)
{
	if (asteroid != nullptr) {

		if (distance_to(asteroid) <= range) {
			std::time_t now = std::time(nullptr);

			if (lastShot == NULL || ((now - lastShot) / frequency) >= 1) {
				float direction = angle_to_drawble(asteroid);
				std::cout << "shot !" << std::endl;
				laserShots->push_back(new LaserShot(x, y, direction, 0.02, 0.0015, 0.008, 1, 0, 0, this, asteroid));
				lastShot = now;
				return true;
			}
		}
	}
	return false;
}
