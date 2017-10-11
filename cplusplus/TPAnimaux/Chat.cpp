#ifndef ANIMAL_CHAT
#define ANIMAL_CHAT

#include "Animal.cpp"

class Chat : public Animal {

    void exprimer(){

		std::cout << "Meow~~" << std::endl;
	}

};

#endif
