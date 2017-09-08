#include "AssignStatement.h"

AssignStatement::AssignStatement(int index, Variable* v, vector<Variable*>* usedVars, Expression* exp) {
	stmtNo = index;
	varModified = v;
	varUsed = usedVars;
	this->exp = exp;
}