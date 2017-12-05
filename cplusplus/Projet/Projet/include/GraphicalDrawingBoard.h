#pragma once

#include <vector>
#include "GraphicEngineBase.h"
#include "IDrawable.h"

class GraphicalDrawingBoard : public GraphicEngineBase {

	std::vector<IDrawable *>* drawables;

	// Checkboard
	int size;
	float x1, y1, x2, y2;

public:

	GraphicalDrawingBoard(int n, float x1, float y1, float x2, float y2)
		: size(n), x1(x1), y1(y1), x2(x2), y2(y2) {
		drawables = new std::vector<IDrawable *>;
	};

	virtual void Draw();

	virtual void addDrawable(IDrawable* drawable);
	virtual void removeDrawable(IDrawable* drawable);

};