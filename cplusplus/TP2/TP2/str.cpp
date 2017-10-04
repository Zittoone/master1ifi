#include<iostream>
#include "str.h"
#include <string.h>

Str::Str() /*: ch(new char[1])*/ {
	string = new char[1];
	string[0] = '\0';
	print();
	printDebug("Constructeur par défaut");
}

Str::Str(char* s){
	int length = strlen(s);
	string = new char[length + 1];
	for(int i = 0; i < length; i++)
		string[i] = s[i];

	string[length] = '\0';

	print();
	printDebug("Constucteur avec un paramètre");
}

Str::Str(const Str& s){
	int length = strlen(s.string);
	string = new char[length + 1];
	for (int i = 0; i < length; i++)
		string[i] = s.string[i];
	string[length] = '\0';

	print();
	printDebug("Constructeur par recopie");
}

Str::~Str(){
	print();
	printDebug(__FUNCTION__);
	delete [] string;
}

void Str::print(){

	std::cout << string << std::endl;

}

void Str::printDebug(const char* fn){

	std::cout << this << " in " << fn << " with string " << string << "@" << &string << std::endl;

}
char* Str::ch(){
	return string;
}

void Str::concat(/*const int i,*/ const char* c){

	int cLength = strlen(c);
	int sLength = strlen(string);
	char* temp = new char[cLength + sLength + 1];

	for(int i = 0; i < sLength; i++)
	{
		temp[i] = string[i];
	}

	for(int i = 0; i < cLength; i++)
	{
		temp[i + sLength] = c[i];
	}

	temp[cLength + sLength] = '\0';

	delete [] string;

	string = temp;
}

/*
 * Le constructeur par recopie est appelé -> création d'un objet temporaire car pas pointeur
 * puis destruction de ce même objet
 * si b est modifié dans la fonction il n'est pas modifié globalement
 */
void Str::concat2(Str b){
	concat(b.ch());
}

Str Str::concat3(Str b){

	char* ch = b.ch();
	int cLength = strlen(ch);
	int sLength = strlen(string);
	char* temp = new char[cLength + sLength + 1];

	for(int i = 0; i < sLength; i++)
	{
		temp[i] = string[i];
	}

	for(int i = 0; i < cLength; i++)
	{
		temp[i + sLength] = ch[i];
	}
	
	temp[cLength + sLength] = '\0';

	return Str(temp);
}

Str Str::concat4(Str& b){

	char* ch = b.ch();
	int cLength = strlen(ch);
	int sLength = strlen(string);
	char* temp = new char[cLength + sLength + 1];

	for(int i = 0; i < sLength; i++)
	{
		temp[i] = string[i];
	}

	for(int i = 0; i < cLength; i++)
	{
		temp[i + sLength] = ch[i];
	}
	
	temp[cLength + sLength] = '\0';

	return Str(temp);
}

/*Str Str::operator+(const Str b) {
	return concat3(b);
}*/

Str Str::operator+(Str& b) {
	return concat4(b);
}

Str operator+(Str& a, Str& b) {
	return a.concat4(b);
}

Str operator<(Str& a, Str& b)
{
	return Str();
}

Str& Str::operator=(Str b)
{
	std::swap(string, b.string);
	return *this; 
}
