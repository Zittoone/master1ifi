#include<iostream>

using namespace std;

// Array ------------------

using namespace std;

class Array {

  private:
    int *a;
    int aSize;

  public:

    //  Constructeur allocation n éléments si spécifié, 10 sinon
    Array(int n=10) {
        aSize = n;
        a = new int[n];
    }

    // Constructeur par recopie
/*    Array(const Array& aCpy){
        aSize = aCpy.aSize;
        for(int i = 0; i < aSize; i++){
            set(i, aCpy->get(i));
        }
    }
*/
    // Destructeur
    ~Array() {
        delete [] a;
    }

    void set(const int, const int);
    int get(const int);
    int capacity();
    void print();
    void nonDecreasingSort();
    int& operator[](const int);
    void expand(const int);

};


void Array::set(const int i, const int val) {

    if(i > aSize || i < 0)
        return;

    a[i] = val;

};

// Retourne la valeur à l'emplacement du tableau ou -1
int Array::get(const int i){

    if(i > aSize || i < 0)
        return -1;

    return a[i];
};

int Array::capacity(){
    return aSize;
};

void Array::print(){
    for(int i = 0; i < aSize; i++)
        cout<<"Elem "<<i<<" "<<a[i]<<endl;
}

void Array::nonDecreasingSort(){

    int tmp;
    int done = 0;

    // Max n carré
    for(int i = 0; i < aSize; i++){
        done = 1;
        for(int j = 1; j < aSize; j++){
            if(a[j] < a[j-1]){
                done = 0;
                tmp = a[j];
                a[j] = a[j-1];
                a[j-1] = tmp;
            }
        }
        if(done == 1)
            return;
    }
}

int& Array::operator[](const int i){
    return a[i];
}

void Array::expand(const int n){
    if(n < 1)
        return;

    // On recopie d'abord les valeurs dans le nouvel objet avec sa nouvelle taille
    int* aNew = new int[aSize + n];

    for(int i = 0; i < aSize; i++){
        aNew[i] = a[i];
    }

    aSize = aSize + n;

    // delete [] a;
    a = aNew;
}


// Stack --------
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
    max--;
}

void Stack::push(const int i) {
    if((max + 1) == a.capacity())
        a.expand(10); // valeur arbitraire

    a.set(++max, i);
}

int Stack::size() {
    return max;
}


int main() {

    /*
Array a;

    a.set(1, 12);
    a.set(0, 5);
    a.set(2, 9);
    a.set(4, 35);
    cout<<a.get(1)<<endl;
    a.print();
    a.nonDecreasingSort();
    a.print(); */

    Array myArray(10);
    myArray.set(3, 5);
    cout << "valeur de 3:" << myArray.get(3) << endl;
    int j=myArray[3];
    cout << "valeur de j:" << j << endl;

    /* error: lvalue required as left operand of assignment

    myArray[3] = 2;
    cout << "valeur de 3:" << myArray.get(3) << endl;
    */

    myArray[3] = 2;
    cout << "valeur de 3:" << myArray.get(3) << endl;

    myArray.expand(10);
    myArray.print();

	Stack s;
    s.push(1);
    s.push(2);
    s.push(9);
    s.pop();
	s.push(44);
    s.push(4);
    s.push(8);
	s.push(2);
    s.push(1);
    s.push(4);
	s.push(8);
    s.push(6);
    s.push(5);
	s.pop();
	s.pop();
	s.pop();
	s.pop();
	s.pop();
	s.pop();
	s.pop();
	s.pop();
	cout << s.top() << endl;

    return 0;
}
