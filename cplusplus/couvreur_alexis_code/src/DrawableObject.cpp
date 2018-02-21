#include "DrawableObject.h"
#include <math.h>       /* sin */

DrawableObject::~DrawableObject()
{
}

void DrawableObject::rotate_point(float x, float y, float angle, float * px, float * py)
{
	float s = sin(angle);
	float c = cos(angle);

	// translate point back to origin:
	x -= this->x;
	y -= this->y;

	// rotate point
	float xnew = x * c - y * s;
	float ynew = x * s + y * c;

	// translate point back:
	*px = xnew + this->x;
	*py = ynew + this->y;
}

float DrawableObject::angle_to_drawble(DrawableObject * drawable)
{
	if (drawable == nullptr) return -M_PI / 2.;
	return atan2(drawable->getY() - y, drawable->getX() - x);
}

float DrawableObject::distance_to(DrawableObject * d)
{
	// merci Pythagore 
	return sqrt(pow(x - d->getX(), 2) + pow(y - d->getY(), 2));
}
