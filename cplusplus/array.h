#ifndef ARRAY_H
#define ARRAY_H

class Array {

  private:
    int *a;
    int aSize;

  public:
    //with default value
    Array(int n=10);
    Array(const Array&);

    ~Array();

    void set(const int, const int);
    int get(const int);
    int capacity();
    void print();
    void nonDecreasingSort();
    int& operator[](const int);
    void expand(const int);

};


#endif
