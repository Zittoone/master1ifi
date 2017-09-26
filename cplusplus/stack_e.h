#ifndef STACK_E_H
#define STACK_E_H

// Stack Extends Array

#include "array.h"

class Stack : public Array {

  private:
    int max;

  public:
    //with default value
    Stack(int n = 10);
    Stack(const Stack&);
    ~Stack();

    bool empty();
    int top();
    void pop();
    void push(const int i);
    int size();
};

#endif
