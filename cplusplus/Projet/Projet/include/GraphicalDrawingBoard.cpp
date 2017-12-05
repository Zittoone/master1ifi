#include "GraphicalDrawingBoard.h"

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
}

void GraphicalDrawingBoard::addDrawable(IDrawable * drawable)
{
	drawables->push_back(drawable); 
}

void GraphicalDrawingBoard::removeDrawable(IDrawable * drawable)
{
}
