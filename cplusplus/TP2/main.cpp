#include<iostream>
#include "str.h"

int main() {

	Str a("tot");
	a.printDebug();
	Str b("truc");
	b.printDebug();
	Str c("machin");
	c.printDebug();

	a.concat(b.ch());
	a.concat(c.ch());
	a.print();

	return 0;
};
