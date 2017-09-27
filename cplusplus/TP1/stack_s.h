#ifndef STACK_S_H
#define STACK_S_H

#include "array.h"

// Stack from scratch
// Redondance de la fonction expand et de la valeur de capacité du tableau
// TODO: changer le max par -1 à l'initialisation

class Stack {

  private:
    int *tab;
	int capacity;
    int max;

  public:
    //with default value
    Stack(int n = 10);
    Stack(const Stack&);
    ~Stack();

    bool empty();
    int top();
    void pop();
    void push(const int);
    int size();
	void expand(const int);
};

#endif
