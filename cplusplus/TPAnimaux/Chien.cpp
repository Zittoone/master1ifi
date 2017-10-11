#ifndef ANIMAL_CHIEN
#define ANIMAL_CHIEN

#include "Animal.cpp"

class Chien : public Animal {

	public :
    void exprimer(){

		std::cout << "Ouaf~~" << std::endl;
	}

	Chien(){
		std::cout << "Constructeur Chien appelé" << std::endl;
	}

	~Chien(){
		std::cout << "Destructeur Chien appelé" << std::endl;
	}

};

#endif
