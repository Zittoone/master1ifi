#include<iostream>
#include "array.h"
//#include "stack.h"
//#include "stack_ap.h"
#include "stack_e.h"

using namespace std;

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
  s.set(1, 2);
	cout << s.top() << endl;

    return 0;
}
