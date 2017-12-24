#pragma once

#include "GraphicEngineBase.h"
#include "Environment.h"
#include "IDrawable.h"
#include <vector>
#include "ISpacecraftStrategy.h"

// Circular dependency
class Environment;
class ISpacecraftStrategy;

class GraphicalDrawingBoard : public GraphicEngineBase {

	std::vector<IDrawable *>* drawables;

	Environment* env;

	// Checkboard
	int size;
	// x1 y1 is corner top left
	// x2 y2 et is bottom right
	float x1, y1, x2, y2;

public:

	GraphicalDrawingBoard(int n, float x1, float y1, float x2, float y2)
		: size(n), x1(x1), y1(y1), x2(x2), y2(y2) {
		drawables = new std::vector<IDrawable *>;
	};

	virtual void Draw();

	virtual void addDrawable(IDrawable* drawable);
	virtual void removeDrawable(IDrawable* drawable);
	virtual float isStartButton(float x, float y);
	void setEnvironment(Environment* env) { this->env = env; }

	int getSize() const { return size; }
	float getX1() const { return x1; }
	float getX2() const { return x2; }
	float getY1() const { return y1; }
	float getY2() const { return y2; }

	virtual int getCheckboardX(float x);
	virtual int getCheckboardY(float y);
	virtual float getXCoordFor(int x);
	virtual float getYCoordFor(int y);
	virtual float xCoordToPercent(int x);
	virtual float yCoordToPercent(int y);

	virtual bool isCheckboard(float x, float y);
	bool isCheckboardPercent(float x, float y);
	virtual bool isLeftMenu(float x, float y);
	virtual bool isDownMenu(float x, float y);

	virtual float distanceBetweenTwoPoints(float x1, float y1, float x2, float y2);

	ISpacecraftStrategy * getStrategyFor(float x, float y);

};