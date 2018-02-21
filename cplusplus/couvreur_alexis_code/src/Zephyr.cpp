#include "Zephyr.h"

void Zephyr::damageReceived(double v)
{
	if (shield <= 0) {
		health -= v;
	}
	else {
		shield -= v;
	}
}

void Zephyr::Tick()
{
	x -= speed;
}

void Zephyr::Draw()
{
	std::vector<float>* xs = new std::vector<float>;
	std::vector<float>* ys = new std::vector<float>;

	/*	 __
	/  \
	\__/
	
	*/
	xs->push_back(x - width / 3);
	ys->push_back(y + height / 2);

	xs->push_back(x + width / 3);
	ys->push_back(y + height / 2);

	xs->push_back(x + 5 * width / 6);
	ys->push_back(y);

	xs->push_back(x + width / 3);
	ys->push_back(y - height / 2);

	xs->push_back(x - width / 3);
	ys->push_back(y - height / 2);

	xs->push_back(x - 5 * width / 6);
	ys->push_back(y);

	if (shield > 0) {
		GraphicPrimitives::drawFillPolygone2D(*xs, *ys, 0, 1, 0);
	}
	else {
		GraphicPrimitives::drawFillPolygone2D(*xs, *ys, r, g, b);
	}

	
}
