#include "StatementContainer.h"

StatementContainer::StatementContainer() {

}

vector<Statement*> StatementContainer::getAllStatements() {
	return stmtLst->getAllStatement();
}

void StatementContainer::setParentContainer(StatementContainer* p) {
	pContainer = p;
}

StatementContainer* StatementContainer::getParentContainer() {
	return pContainer;
}


Statement* StatementContainer::addAssignStatement(int index, Variable* v, Expression* exp) {
	return stmtLst->addAssignStatement(index, v, &(exp->getUsedVariable()), exp);
}

StatementContainer* StatementContainer::addWhileStatement(int index, Variable* controlVar) {
	return stmtLst->addWhileStatement(index, controlVar);
}