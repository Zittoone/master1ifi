#include "Chat.cpp"
#include "Chien.cpp"
#include "Lapin.cpp"
#include "Lion.cpp"


int main(){

    // Tableau de pointeurs sur animaux
    Animal* animaux[4] = { new Chat(), new Chien(), new Lapin(), new Lion() };

    for(int i = 0; i < 4; i++){
        animaux[i]->exprimer();
    }

}
