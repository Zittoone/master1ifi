#include "GraphicalDrawingBoard.h"
#include "HispaniaStrategy.h"
#include "ElysiumStrategy.h"
#include "NostromoStrategy.h"
#include <cmath>
#include <algorithm>
#include <stdio.h>  


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
	char* buffer = new char[256];
	sprintf_s(buffer, 256,  "%.2f $", env->getMoney());
	GraphicPrimitives::drawText2D(buffer, -0.98f, 0.92f, 1, 1, 1);

	// LEVEL
	if(env->getLevel() != nullptr){
		sprintf_s(buffer, 256,  "Level %d", env->getLevel()->getN());
		GraphicPrimitives::drawText2D(buffer, -0.98f, 0.72f, 1, 1, 1);
		sprintf_s(buffer, 256,  "(%d ast. left)", env->getLevel()->getNAsteroidLeft() + env->getNbAsteroids());
		GraphicPrimitives::drawText2D(buffer, -0.98f, 0.65f, 1, 1, 1);
	}
	// HEALTH
	sprintf_s(buffer, 256,  "%d HP", env->getHealth());
	GraphicPrimitives::drawText2D(buffer, -0.98f, 0.82f, 1, 1, 1);

	/* Strategy */
	GraphicPrimitives::drawOutlinedRect2D(x1, y2, width / 4, -1, 1, 1, 0);
	sprintf_s(buffer, 256,  "Hispania (250$)");
	GraphicPrimitives::drawText2D(buffer, x1, y2 - 0.05, 1, 1, 1);
	sprintf_s(buffer, 256,  "15 Dmg");
	GraphicPrimitives::drawText2D(buffer, x1, y2 - 0.1, 1, 1, 1);
	sprintf_s(buffer, 256,  "Medium range");
	GraphicPrimitives::drawText2D(buffer, x1, y2 - 0.15, 1, 1, 1);

	GraphicPrimitives::drawOutlinedRect2D(x1 + width / 4, y2, width / 4, -1, 1, 1, 0);
	sprintf_s(buffer, 256,  "Elysium (1000$)");
	GraphicPrimitives::drawText2D(buffer, x1 + width / 4, y2 - 0.05, 1, 1, 1);
	sprintf_s(buffer, 256,  "30 Dmg");
	GraphicPrimitives::drawText2D(buffer, x1 + width / 4, y2 - 0.1, 1, 1, 1);
	sprintf_s(buffer, 256,  "Medium range");
	GraphicPrimitives::drawText2D(buffer, x1 + width / 4, y2 - 0.15, 1, 1, 1);

	GraphicPrimitives::drawOutlinedRect2D(x1 + 2 * width / 4, y2, width / 4, -1, 1, 1, 0);
	sprintf_s(buffer, 256,  "Nostromo (2000$)");
	GraphicPrimitives::drawText2D(buffer, x1 + 2 * width / 4, y2 - 0.05, 1, 1, 1);
	sprintf_s(buffer, 256,  "60 Dmg");
	GraphicPrimitives::drawText2D(buffer, x1 + 2 * width / 4, y2 - 0.1, 1, 1, 1);
	sprintf_s(buffer, 256,  "Long range");
	GraphicPrimitives::drawText2D(buffer, x1 + 2 * width / 4, y2 - 0.15, 1, 1, 1);

	if (!env->getLevel()->hasStarted()) {
		GraphicPrimitives::drawOutlinedRect2D(-1, 0.60f, x1 + 1, -0.2, 1, 1, 0);
		sprintf_s(buffer, 256,  "Start!");
		GraphicPrimitives::drawText2D(buffer, -0.98f, 0.5, 1, 1, 1);
	}
}

void GraphicalDrawingBoard::addDrawable(IDrawable * drawable)
{
	drawables->push_back(drawable); 
}

void GraphicalDrawingBoard::removeDrawable(IDrawable * drawable)
{
	drawables->erase(
		std::remove(
			drawables->begin(), drawables->end(), drawable
		), drawables->end()
	);

	/*asteroids->erase(
		std::remove(
			asteroids->begin(), asteroids->end(), asteroid
		), asteroids->end()
	);*/
}

float GraphicalDrawingBoard::isStartButton(float x, float y) {
	float _x = xCoordToPercent(x); 
	float _y = yCoordToPercent(y);
	std::cout << _x << ":" << _y << std::endl;
	return _x >= -1 && _x < x1 && _y < 0.6 && _y > 0.4;
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

bool GraphicalDrawingBoard::isCheckboardPercent(float x, float y)
{
	return (x > x1 && x < x2) && (y < y1 && y > y2);
}

bool GraphicalDrawingBoard::isLeftMenu(float x, float y)
{
	x = xCoordToPercent(x);
	y = yCoordToPercent(y);
	return (x < x1);
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

ISpacecraftStrategy* GraphicalDrawingBoard::getStrategyFor(float x, float y) {
	float _x = xCoordToPercent(x);
	float _y = yCoordToPercent(y);

	float width = x2 - x1;

	if (_x > x1 && _x < x1 + width / 4) {
		return new HispaniaStrategy();
	}
	else if(_x > x1 + width / 4 && _x < x1 + 2 * width / 4) {
		return new ElysiumStrategy();
	}
	else if (_x > x1 + 2 * width / 4 && _x < x1 + 3 * width / 4) {
		return new NostromoStrategy();
	}
	else {

	}

	return nullptr;
}

void GraphicalDrawingBoard::endGame() {
	delete drawables;
	drawables = new std::vector<IDrawable*>;
}

