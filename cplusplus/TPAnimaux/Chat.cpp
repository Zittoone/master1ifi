#ifndef ANIMAL_CHAT
#define ANIMAL_CHAT

#include "Animal.cpp"

class Chat : public Animal {

	public :
    void exprimer(){

		std::cout << "Meow~~" << std::endl;
	}

	Chat(){
		std::cout << "Constructeur Chat appelé" << std::endl;
	}

	~Chat(){
		std::cout << "Destructeur Chat appelé" << std::endl;
	}

};

#endif
