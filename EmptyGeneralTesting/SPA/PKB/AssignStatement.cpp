#include "AssignStatement.h"

AssignStatement::AssignStatement(int index, StatementContainer* parent, Statement* follows, Variable* v, vector<Variable*>* usedVars, Expression* exp) {
	Statement(index, parent, follows);
	addModVar(v);
	for each (Variable* var in *usedVars){
		addUseVar(var);
	}
	this->exp = exp;
}

bool AssignStatement::isExpEqual(Expression exp) {
	return this->exp->contains(&exp);
}

bool AssignStatement::isContainExp(Expression exp) {
	return (this->exp)->contains(&exp);
}