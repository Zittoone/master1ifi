#include<iostream>
#include "str.h"
#include <string.h>

Str::Str(){
	string = new char[1];
	string[0] = '\0';
}

Str::Str(char* s){
	string = new char[strlen(s) + 1];
	for(uint i = 0; i < strlen(s) + 1; i++)
		string[i] = s[i];
}

Str::Str(const Str& s){

}

Str::~Str(){
	
}

void Str::print(){

	std::cout << string << std::endl;

}

void Str::printDebug(){

	std::cout << this << __FUNCTION__ << std::endl;

}
char* Str::ch(){
	return string;
}

void Str::concat(/*const int i,*/ const char* c){
	char* newStr = new char[strlen(string) + strlen(c) + 1];
	uint i, j;
	for(i = 0; i < strlen(string); i++)
		newStr[i] = string[i];
	for(j=i, i=0; i < strlen(c) + 1; i++, j++)
		newStr[j] = c[i];

	string = newStr;

}
