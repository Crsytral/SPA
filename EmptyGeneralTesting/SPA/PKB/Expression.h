#pragma once
/*
To be implemented by Lu Yu
*/
#include <string>
#include <vector>
using namespace std;

#include "Variable.h"
class Variable;

class Expression {
private:
	string syntaxTree;
	vector<Variable*>* usedVariables;
public:
	Expression(string exp);
	string getSyntaxTree();
	vector<Variable*>* getUsedVariable();
};