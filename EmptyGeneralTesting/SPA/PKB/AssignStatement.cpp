#include "AssignStatement.h"

AssignStatement::AssignStatement(int index, StatementContainer parent, Statement follows, Variable* v, vector<Variable>* usedVars, Expression* exp) {
	Statement(index,&parent,&follows);
	addModVar(*v);
	useVar = *(new vector<Variable>(*usedVars));
	this->exp = exp;
}

bool AssignStatement::isExpEqual(Expression exp) {
	return *(this->exp) == exp;
}

bool AssignStatement::isContainExp(Expression exp) {
	return (this->exp)->contains(exp);
}