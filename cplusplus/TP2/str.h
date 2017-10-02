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

	//Str& operator+(const Str);

};

#endif
