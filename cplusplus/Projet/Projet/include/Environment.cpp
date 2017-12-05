#include "Environment.h"

void Environment::idle()
{
	int size = tickables->size();

	for (int i = 0; i < size; i++) {
		(*tickables)[i]->Tick();
	}
}

bool Environment::RequestCreation(int x, int y)
{
	return true;
}

void Environment::addTickable(ITickable* tickable) { 
	tickables->push_back(tickable);
}


void Environment::removeTickable(ITickable* tickable) {
	tickables->erase(
		std::remove(
			tickables->begin(), tickables->end(), tickable
		), tickables->end()
	);
}

void Environment::addDrawable(IDrawable * drawable)
{
	gdp->addDrawable(drawable);
}

void Environment::removeTickable(IDrawable * drawable)
{
	gdp->removeDrawable(drawable);
}
