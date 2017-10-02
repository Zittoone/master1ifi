#include "stack_ap.h"

Stack::Stack(int n) {
  a = new Array(n);
  max = 0;
}

Stack::Stack(const Stack&) : a(new Array(*(s.a))), max(s.max){

}

Stack::~Stack() {
  delete a;
}


bool Stack::empty() {
    return max == 0;
}

int Stack::top() {
    return a->get(max);
}

void Stack::pop() {
    if(empty())
        return;

    max--;
}

void Stack::push(const int i) {
    if(max  == a->capacity())
        a->expand(2 * max); // valeur arbitraire

    a->set(max++, i);
}

int Stack::size() {
    return max;
}
