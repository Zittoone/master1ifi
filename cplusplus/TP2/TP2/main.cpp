#include<iostream>
#include "str.h"

int main() {

	Str a("tot");
	Str b("truc");
	Str c("Machin");

	a.concat(b.ch()); // tottruc
	a.concat(c.ch()); // tottrucmachin
	a.print();

	// a.concat2(b); // tottrucmachintruc
	/*
	 * Le constructeur par recopie est appelé
	 *  
	 */

	// a = a.concat3(c); // tottrucmachintrucmachin si concat2 tottrucmachinmachin sinon
	/*
	 * Constructeur avec paramètre a devient le nouvel objet construit et l'ancien a est détruit
	 */

	//a = a.concat4(c);
	/*
	 * Création d'une nouvelle instance Str aucun constructeur par recopie n'est appelé //lorsqu'on retourne &Str\\
	 */

	std::cout << "value of a : " << a.ch() << "@" << &a << std::endl;

	a = b + c;
	// Testé avec fonction membre et amie
	//Str s = a + b; non conforme pour class
	// Str t = "hum" + c; aucun opérateur défini
	// Str u = "un" + " peu"; ne fonctionne pas, l'opérateur + n'étant pas défini pour une chaine de caractère

	system("PAUSE");

	return 0;
};
