#ifndef STR_H
#define STR_H

class Str {

	char *string;

  public:
	Str();
	Str(char*);
	Str(const Str&);
	~Str();

	void print();
	void printDebug(const char*);
	char* ch();
	void concat(/*const int,*/ const char*);
	void concat2(Str);
	Str concat3(Str);
	Str concat4(Str&);

	// Operator overlaoading allows you to redefine various operators
	// Str operator+(const Str); // esté et fonctionnel
	Str operator+(Str&); // - non testé

	// Declaring the function to be a friend of the class, gives it access to protected and private members of the class without opening up access to anyone else.
	// friend Str operator+(Str, const Str); // testé et fonctionnel
	// friend Str operator+(Str&, Str&); // non testé
	friend Str operator<(Str&, Str&);


};

#endif
