#ifndef ANIMAL
#define ANIMAL

#include<iostream>

class Animal {

	public:
	Animal(){
		std::cout << "Constructeur Animal appelé" << std::endl;
	}

	virtual ~Animal() {
		std::cout << "Destructeur Animal appelé" << std::endl;
	};

	virtual void exprimer() = 0;

};

#endif
