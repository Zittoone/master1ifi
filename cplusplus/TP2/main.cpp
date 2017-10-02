#include<iostream>
#include "str.h"

int main() {

	Str a("tot");
	a.printDebug(__FUNCTION__);
	Str b("truc");
	b.printDebug(__FUNCTION__);
	Str c("machin");
	c.printDebug(__FUNCTION__);

	a.concat(b.ch()); // tottruc
	a.concat(c.ch()); // tottrucmachin
	a.print();

	 a.concat2(b); // tottrucmachintruc
	/*
	 * Le constructeur par recopie est appelé
	 *  
	 */

	// a = a.concat3(c); // tottrucmachintrucmachin si concat2 tottrucmachinmachin sinon
	/*
	 * Segfault
	 */

	//a = a.concat4(c);
	/*
	 * Création d'une nouvelle instance Str
	 */

	std::cout << "value of a : " << a.ch();

	return 0;
};
