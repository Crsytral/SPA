#include "Token.h"

#include <string>
#include <iostream>
using namespace std;

Token::Token(string value) :value(value)
{

}
Token::Token()
{

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

bool Token::isNum()
{
	return (getType() == "N");
}
bool Token::isVar()
{
	return (getType() == "V");
}
bool Token::isOperand()
{
	return (getType() != "O");
}
bool Token::isOperator()
{
	return (getType() == "O");
}