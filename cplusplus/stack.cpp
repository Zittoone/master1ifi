#include<iostream>

class Stack {

    Array a;
    int max;

  public:
    Stack(int n=10): a(n) {
        max = 0;
    }

    /*
    Stack(const Stack&){

    }
    */

    ~Stack() {

    delete &a;

    }

    bool empty();
    int top();
    void pop();
    void push(const int i);
    int size();
};

bool Stack::empty() {
    return max == 0;
}

int Stack::top() {
    return a.get(max);
}

void Stack::pop() {
    if(empty())
        return;

    // check if this has problem
    delete &a[max--];
}

void Stack::push(const int i) {
    if((max + 1) == a.capacity())
        a.expand(10); // valeur arbitraire

    a.set(++max, i);
}

int Stack::size() {
    return max;
}
