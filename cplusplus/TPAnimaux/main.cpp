#include "Chat.cpp"
#include "Chien.cpp"
#include "Lapin.cpp"
#include "Lion.cpp"


int main(){

    // Tableau de pointeurs sur animaux

    // Variante de déclaration
    // Animal* animaux[4] = { new Chat(), new Chien(), new Lapin(), new Lion() };

    Animal** animaux = new Animal*[4];
    animaux[0] = new Chat();
    animaux[1] = new Chien();
    animaux[2] = new Lapin();
    animaux[3] = new Lion();

    for(int i = 0; i < 4; i++){
        animaux[i]->exprimer();
    }

    for(int i = 0; i < 4; i++){
        delete animaux[i];
    }

    return 0;
}
