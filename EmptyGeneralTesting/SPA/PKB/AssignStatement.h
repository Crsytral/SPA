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
#include "StatementContainer.h"

class AssignStatement : public Statement {
private:
	Expression* exp;
public:
	AssignStatement(int index, StatementContainer* parent, Statement* follows,Variable* v, vector<Variable*>* usedVars, Expression* exp);
	bool isExpEqual(Expression exp);
	bool isContainExp(Expression exp);
};