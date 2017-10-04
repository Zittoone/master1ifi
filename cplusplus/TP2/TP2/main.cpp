#include<iostream>
#include "str.h"

int main() {

	Str a("tot");
	Str b("truc");
	Str c("Machin");

	a.concat(b.ch()); // tottruc
	a.concat(c.ch()); // tottrucmachin
	a.print();

	//a.concat2(b); // tottrucmachintruc
	/*
	 * Le constructeur par recopie est appelé -> création d'un objet temporaire car pas pointeur
	 * puis destruction de ce même objet
	 */

	b = a.concat3(c); // tottrucmachintrucmachin si concat2 tottrucmachinmachin sinon
	/*
	 * Constructeur avec paramètre a devient le nouvel objet construit et l'ancien a est détruit
	 * 5. *** Error in `main': double free or corruption (fasttop)
	 */

	//a = a.concat4(c);
	/*
	 * Création d'une nouvelle instance Str aucun constructeur par recopie n'est appelé //lorsqu'on retourne &Str\\
	 */

	std::cout << " > > value of a : " << a.ch() << "@" << &a << std::endl;

	//a = b + c;

	//std::cout << " > > value of a : " << a.ch() << "@" << &a << std::endl;
	// Testé avec fonction membre et amie
	//Str s = a + b; non conforme pour class
	// Str t = "hum" + c; aucun opérateur défini
	// Str u = "un" + " peu"; ne fonctionne pas, l'opérateur + n'étant pas défini pour une chaine de caractère

	//a = b = c;
	// a devient b, qui lui même devient c via l'overload de l'opérateur égal
	// On a donc a = Machin, b = Machin et c = Machin avec chacun des adresses distinctes
	
	//std::cout << " > > value of a : " << a.ch() << "@" << &a << std::endl;

	// system("PAUSE"); only windows

	return 0;
};
