#ifndef ANIMAL_LION
#define ANIMAL_LION

#include "Animal.cpp"

class Lion : public Animal {

	public :
    void exprimer(){

		std::cout << "Roaar~~" << std::endl;
	}

	Lion(){
		std::cout << "Constructeur Lion appelé" << std::endl;
	}

	~Lion(){
		std::cout << "Destructeur Lion appelé" << std::endl;
	}

};

#endif
