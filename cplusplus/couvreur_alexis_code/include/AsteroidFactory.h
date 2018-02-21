#pragma once

#include "Asteroid.h"
#include "GraphicalDrawingBoard.h"
#include "Eros.h"
#include "Blume.h"
#include "Zephyr.h"

// Inspired from https://stackoverflow.com/questions/1008019/c-singleton-design-pattern

class AsteroidFactory {
public:
	static AsteroidFactory& getInstance()
	{
		static AsteroidFactory    instance; // Guaranteed to be destroyed.
							  // Instantiated on first use.
		return instance;
	}
private:
	AsteroidFactory() {}                    // Constructor? (the {} brackets) are needed here.

							  // C++ 03
							  // ========
							  // Dont forget to declare these two. You want to make sure they
							  // are unacceptable otherwise you may accidentally get copies of
							  // your singleton appearing.
	AsteroidFactory(AsteroidFactory const&);              // Don't Implement
	void operator=(AsteroidFactory const&); // Don't implement

							  // C++ 11
							  // =======
							  // We can use the better technique of deleting the methods
							  // we don't want.

	virtual float randomFloatRange(float min, float max);

public:
	//AsteroidFactory(AsteroidFactory const&) = delete;
	//void operator=(AsteroidFactory const&) = delete;

	virtual Eros* getErosAsteroid(GraphicalDrawingBoard* gdb);
	virtual Blume* getBlumeAsteroid(GraphicalDrawingBoard* gdb);
	virtual Zephyr* getZephyrAsteroid(GraphicalDrawingBoard* gdb);

	// Note: Scott Meyers mentions in his Effective Modern
	//       C++ book, that deleted functions should generally
	//       be public as it results in better error messages
	//       due to the compilers behavior to check accessibility
	//       before deleted status
};