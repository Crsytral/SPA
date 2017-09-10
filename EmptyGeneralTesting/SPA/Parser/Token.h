#pragma once

#include <string>
using namespace std;

class Token
{

protected:
	string type;
	string value;
public:
	Token(string value);
	Token();
	string getType();
	string getValue();
	void print();

	bool isNum();
	bool isVar();
	bool isOperand();
	bool isOperator();


};