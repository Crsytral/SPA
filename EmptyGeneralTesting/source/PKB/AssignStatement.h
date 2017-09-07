#pragma once
/*
Represents an AssignStatement object.
Constructor: Variable varModified, vector<Variable> varUsed, Expression ex
*/
#include "Statement.h"
#include "Variable.h"
#include "Expression.h"

class AssignStatement : public Statement {
private:
	Variable modifiedVar;
	vector<Variable> usedVar;
	Expression exp;
public:
	AssignStatement(Variable varModified, vector<Variable> varUsed, Expression ex);
};