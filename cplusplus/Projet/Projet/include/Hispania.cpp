#include "Hispania.h"
#include "GraphicPrimitives.h"

void Hispania::Draw()
{
	float x2 = x - (width / 2);
	float y2 = y - height;

	float x3 = x + (width / 2);
	

	GraphicPrimitives::drawFillTriangle2D(x, y, x2, y2, x3, y2, r, g, b);
	GraphicPrimitives::drawFillRect2D(x, y, width, height, r, g, b);
	
}

void Hispania::Tick()
{

}