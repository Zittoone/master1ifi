#include "GraphicalDrawingBoard.h"

#include <cmath>

void GraphicalDrawingBoard::Draw()
{
	/*
	CHECKBOARD
	*/
	float width = x2 - x1;
	float height = y2 - y1;

	// Lignes & Colonnes
	for (int i = 1; i <= size; i++) {
		// Lignes
		float y = (height / size) * i;
		GraphicPrimitives::drawLine2D(x1, y1 + y, x2, y1 + y, 0, 1, 0);

		// Colonnes
		float x = (width / size) * i;
		GraphicPrimitives::drawLine2D(x1 + x, y1, x1 + x, y2, 0, 1, 0);
		//GraphicPrimitives::drawLine2D(-x, y1, -x, y2, 0, 1, 0);

	}

	// Rectangle
	GraphicPrimitives::drawOutlinedRect2D(x1, y1, width, height, 1, 1, 0);

	/*
	DRAWABLES
	*/

	// Prevent calling the method each iteration
	int size = drawables->size();
	
	for (int i = 0; i < size; i++) {
		(*drawables)[i]->Draw();
	}

	// MONEY
	char* buffer = new char[10];
	sprintf(buffer, "%.2f $", env->getMoney());
	GraphicPrimitives::drawText2D(buffer, -0.98f, 0.92f, 1, 1, 1);

	// LEVEL


	// HEALTH
	sprintf(buffer, "%d HP", env->getHealth());
	GraphicPrimitives::drawText2D(buffer, -0.98f, 0.82f, 1, 1, 1);

	/*
	GraphicPrimitives::drawLine2D(0, 0, 1, 1, 1, 1, 0);
	GraphicPrimitives::drawLine2D(0, 0, -1, 1, 1, 1, 0);
	GraphicPrimitives::drawLine2D(0, 0, 1, -1, 1, 1, 0);
	GraphicPrimitives::drawLine2D(0, 0, -1, -1, 1, 0, 0);*/
}

void GraphicalDrawingBoard::addDrawable(IDrawable * drawable)
{
	drawables->push_back(drawable); 
}

void GraphicalDrawingBoard::removeDrawable(IDrawable * drawable)
{
}

float GraphicalDrawingBoard::xCoordToPercent(int x)
{

	float width = glutGet(GLUT_WINDOW_WIDTH);
	x = x - (width / 2);
	
	return (x / (width / 2));
}

float GraphicalDrawingBoard::yCoordToPercent(int y)
{
	float height = glutGet(GLUT_WINDOW_HEIGHT);
	y = y - (height / 2);

	return (-y / (height / 2));
}

int GraphicalDrawingBoard::getCheckboardX(float x)
{
	x = xCoordToPercent(x);
	if (x < x1 || x > x2) {
		return -1;
	}

	float result = (x - x1) / ((x2 - x1) / size);
	return std::ceil(result);
}

int GraphicalDrawingBoard::getCheckboardY(float y)
{
	y = yCoordToPercent(y);
	if (y > y1 || y < y2) {
		return -1;
	}

	float result = (y - y1) / ((y2 - y1) / size);
	return std::ceil(result);
}

float GraphicalDrawingBoard::getXCoordFor(int x)
{
	float width = x2 - x1;
	float offset = x1 - (-1);
	float widthF = width / size;
	return ((widthF * (x - 1)) - 1) + offset + (widthF / 2);
}

float GraphicalDrawingBoard::getYCoordFor(int y)
{
	float height = y2 - y1;
	float offset = y1 - 1;
	float heightF = height / size;
	return ((heightF * (y - 1)) + 1) + offset + (heightF / 2);
}

bool GraphicalDrawingBoard::isCheckboard(float x, float y)
{
	x = xCoordToPercent(x);
	y = yCoordToPercent(y);
	return (x > x1 && x < x2) && (y < y1 && y > y2);
}

bool GraphicalDrawingBoard::isLeftMenu(float x, float y)
{
	x = xCoordToPercent(x);
	y = yCoordToPercent(y);
	return (x < x1) && (y < y2);
}

bool GraphicalDrawingBoard::isDownMenu(float x, float y)
{
	y = yCoordToPercent(y);
	return y < y2;
}

float GraphicalDrawingBoard::distanceBetweenTwoPoints(float x1, float y1, float x2, float y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}


