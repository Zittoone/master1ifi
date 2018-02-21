#include "Blume.h"

void Blume::damageReceived(double v)
{
	health -= v;
}

void Blume::Tick()
{
	x -= speed;
}

void Blume::Draw()
{
	//GraphicPrimitives::drawFillRect2D(x - width / 2, y - height / 2, width, height, r, g, b);
	float x1 = x;
	float y1 = y + (height / 2);
	float x2 = x - (width / 2);
	float y2 = y - (height / 2);
	float x3 = x + (width / 2);
	float y3 = y2;

	float p = health / maxHealth;
	p = p * 0.1;

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

	xs->push_back(x + 5* width / 6);
	ys->push_back(y);

	xs->push_back(x + width / 3);
	ys->push_back(y - height / 2);

	xs->push_back(x - width / 3);
	ys->push_back(y - height / 2);

	xs->push_back(x - 5 * width / 6);
	ys->push_back(y);

	GraphicPrimitives::drawFillPolygone2D(*xs, *ys, r, g, b);
	//GraphicPrimitives::drawFillTriangle2D(x1, y1, x2, y2, x3, y3, r, g, b);

	delete xs;
	delete ys;
}
