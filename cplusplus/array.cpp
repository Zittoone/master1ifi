#include<iostream>

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
    int* aNew = new int[n];

    for(int i = 0; i < aSize; i++){
        aNew[i] = a[i];
    }

    aSize = n;

    // delete [] a;
    a = aNew;
}


