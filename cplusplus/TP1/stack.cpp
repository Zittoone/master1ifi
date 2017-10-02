#include "stack.h"

Stack::Stack(int n): a(n) {
  max = 0;
}

Stack::Stack(const Stack& s) : a(s.a), max(s.max) {

}

Stack::~Stack() {
}


bool Stack::empty() {
    return max == 0;
}

int Stack::top() {
    return a.get(max); // Or a[max]
}

void Stack::pop() {
    if(empty())
        return;

    // check if this has problem
    max--;
}

void Stack::push(const int i) {
    if((max + 1) == a.capacity())
        a.expand(10); // valeur arbitraire

    a.set(max++, i);
}

int Stack::size() {
    return max;
}
