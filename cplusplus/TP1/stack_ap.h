#ifndef STACK_AP_H
#define STACK_AP_H

#include "array.h"

// Stack Array Pointer
// We need to delete Array in destructor

class Stack {

  private:
    Array* a;
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
