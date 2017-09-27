#include<iostream>
#include "array.h"
//#include "stack.h"
//#include "stack_ap.h"
//#include "stack_e.h"
#include "stack_s.h"

using namespace std;

int main() {

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
    s.push(8);
    s.push(5);
	cout << s.top() << endl;

    return 0;
}
