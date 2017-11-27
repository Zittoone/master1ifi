/*
    LI R0,0          => le registre R0 a pour valeur 0
    LI R1,1          => le registre R1 a pour valeur 1
    LI R7,5          => le registre R7 a pour valeur 5
    LW R0,R3,10      => le registre R3 prend la valeur de MEMOIRE[R0 + 10] donc MEMOIRE[10]
    LW R3,R4,1       => le registre R4 prend la valeur de MEMOIRE[R3 + 1]
    SLT R4,R7,R6     => R6 prend la valeur 1 si R4 < R7 sinon 0
    LW R3,R3,0       => R3 prend la valeur de MEMOIRE[R3 + 0]
    BNEZ R0,R6,-3    => PC = PC + R0 - 3 si R6 = 1 sinon PC = PC + 1

    Ce code recherche un élement dans une liste linéaire chainée d'une valeur
    supérieur ou égale à 5
*/

int main(void){

    ptr* = teteDeListe;

    do {

    data = ptr->data;
    ptr = ptr->suivant;

    } while(data < 5); 
}
