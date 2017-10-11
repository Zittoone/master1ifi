#ifndef ANIMAL_LAPIN
#define ANIMAL_LAPIN

#include "Animal.cpp"

class Lapin : public Animal {

	public :
    void exprimer(){

		std::cout << "Quoi 2 9 Dr. ?" << std::endl;
	}

	Lapin(){
		std::cout << "Constructeur Lapin appelé" << std::endl;
	}

	~Lapin(){
		std::cout << "Destructeur Lapin appelé" << std::endl;
	}

};

#endif
