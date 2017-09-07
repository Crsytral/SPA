#pragma once

#include <string>
using namespace std;

class Token
{

private:
	string type;
	string value;
public:
	Token(string type, string value);
	string getType();
	string getValue();
	void print();

};