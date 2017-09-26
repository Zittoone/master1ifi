#include "stack_e.h"

Stack::Stack(int n): Array(n) {
  max = 0;
}

Stack::Stack(const Stack&){

}

Stack::~Stack() {

}


bool Stack::empty() {
    return max == 0;
}

int Stack::top() {
    return this->get(max);
}

void Stack::pop() {
    if(empty())
        return;

    // check if this has problem
    max--;
}

void Stack::push(const int i) {
    if((max + 1) == this->capacity())
        this->expand(10); // valeur arbitraire

    this->set(++max, i);
}

int Stack::size() {
    return max;
}
