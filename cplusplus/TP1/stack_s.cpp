#include "stack_s.h"

Stack::Stack(int n) {
	tab = new int[n];
	max = 0;
	capacity = n;	
}

Stack::Stack(const Stack& s) : 
	tab( new int[s.max] ),
	capacity( s.capacity),
	max( s.max)	
{}

Stack::~Stack() {
	delete [] tab;
}


bool Stack::empty() {
    return max == 0;
}

int Stack::top() {
    return tab[max - 1];
}

void Stack::pop() {
    if(empty())
        return;

    max--;
}

void Stack::push(const int i) {
    if((max ) == capacity)
        expand(2 * capacity); // valeur arbitraire

    tab[max++] = i;
}

int Stack::size() {
    return max;
}

void Stack::expand(const int n){
	if(n < 1)
        return;

    // On recopie d'abord les valeurs dans le nouvel objet avec sa nouvelle taille
    int* aNew = new int[capacity + n];

    for(int i = 0; i < capacity; i++){
        aNew[i] = tab[i];
    }

    capacity = capacity + n;

    tab = aNew;
}

