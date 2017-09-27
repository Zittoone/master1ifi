#ifndef STACK_H
#define STACK_H

#include "array.h"

// Stack Value Member

class Stack {

  private:
    Array a;
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
