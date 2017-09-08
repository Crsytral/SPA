#include "Token.h"

#include <string>
#include <iostream>
using namespace std;

Token::Token(string type, string value) : type(type), value(value)
{
	/*if (raw == "while")
	{
	type = "keyword";
	value = raw;
	}*/
	/*type = type;
	value = value;*/

}

string Token::getType()
{
	return type;
}

string Token::getValue()
{
	return value;
}

void Token::print()
{
	cout << "The Token is of type " << type << ", of value " << value << endl;
}