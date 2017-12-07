#include "Environment.h"

Environment::Environment(GraphicalDrawingBoard * gdp) : gdp(gdp)
{
		tickables = new std::vector<ITickable*>;
		
}

bool Environment::withdrawMoney(double amount)
{
	double moneyLeft = money - amount;
	if (moneyLeft > 0) {
		setMoney(moneyLeft);
	}
		
	return moneyLeft > 0;
}

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