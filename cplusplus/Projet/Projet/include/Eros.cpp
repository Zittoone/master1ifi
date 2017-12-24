#include "Eros.h"

void Eros::damageReceived(double v)
{
	health -= v;
}

void Eros::Tick()
{
	x -= speed;
}

void Eros::Draw()
{

	std::vector<float>* xs = new std::vector<float>;
	std::vector<float>* ys = new std::vector<float>;

	/*	 __
	/  \
	\__/
	or at least i tried ...
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

	GraphicPrimitives::drawFillPolygone2D(*xs, *ys, r, g, b);
}
