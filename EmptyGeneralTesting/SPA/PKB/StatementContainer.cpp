#include "StatementContainer.h"

void StatementContainer::setParentContainer(StatementContainer* p) {
	pContainer = p;
}

StatementContainer* StatementContainer::getParentContainer() {
	return pContainer;
}

void StatementContainer::updateVarUsed(vector<Variable*>* vars) {
	//Shermine to fill in here
}

void StatementContainer::updateVarModified(Variable* vars) {
	//Shermine to fill in here
}

Statement* StatementContainer::addAssignStatement(int index, Variable* v, Expression* exp) {
	vector<Variable*>* expVars = exp->getUsedVariable();
	updateVarUsed(expVars);
	updateVarModified(v);
	return stmtLst->addAssignStatement(index, v, exp->getUsedVariable(), exp);
}

StatementContainer* StatementContainer::addWhileStatement(int index, Variable* controlVar) {
	StatementContainer* stmt = stmtLst->addWhileStatement(index, controlVar);
	stmt->setParentContainer(this);
	return stmtLst->addWhileStatement(index, controlVar);
}