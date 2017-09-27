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
	void printDebug();
	char* ch();
	void concat(/*const int,*/ const char*);

};

#endif
