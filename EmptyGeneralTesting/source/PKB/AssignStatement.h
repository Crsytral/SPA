#pragma once
/*
Represents an AssignStatement object.
Constructor: Variable varModified, vector<Variable> varUsed, Expression ex
*/
#include <vector>
using namespace std;

#include "Statement.h"
#include "Variable.h"
#include "Expression.h"

class Statement;

class AssignStatement : public Statement {
private:
	Variable* varModified;
	vector<Variable*>* varUsed;
	Expression* exp;
public:
	AssignStatement(int index, Variable* v, vector<Variable*>* usedVars, Expression* exp);
};