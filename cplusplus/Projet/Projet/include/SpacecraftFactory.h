#pragma once

#include "GraphicalDrawingBoard.h"
#include "Environment.h"
#include "Elysium.h"
#include "Hispania.h"
#include "Nostromo.h"

class SpacecraftFactory {

public:
	static SpacecraftFactory& getInstance()
	{
		static SpacecraftFactory    instance; // Guaranteed to be destroyed.
											// Instantiated on first use.
		return instance;
	}
private:
	SpacecraftFactory() {}                    // Constructor? (the {} brackets) are needed here.

											// C++ 03
											// ========
											// Dont forget to declare these two. You want to make sure they
											// are unacceptable otherwise you may accidentally get copies of
											// your singleton appearing.
	SpacecraftFactory(SpacecraftFactory const&);              // Don't Implement
	void operator=(SpacecraftFactory const&); // Don't implement

											// C++ 11
											// =======
											// We can use the better technique of deleting the methods
											// we don't want.


public:
	//AsteroidFactory(AsteroidFactory const&) = delete;
	//void operator=(AsteroidFactory const&) = delete;

	virtual Elysium* getElysiumSpacecraft(int x, int y, GraphicalDrawingBoard* gdb, Environment* environment);
	virtual Hispania* getHispaniaSpacecraft(int x, int y, GraphicalDrawingBoard* gdb, Environment* environment);
	virtual Nostromo* getNostromoSpacecraft(int x, int y, GraphicalDrawingBoard* gdb, Environment* environment);

	// Note: Scott Meyers mentions in his Effective Modern
	//       C++ book, that deleted functions should generally
	//       be public as it results in better error messages
	//       due to the compilers behavior to check accessibility
	//       before deleted status
};