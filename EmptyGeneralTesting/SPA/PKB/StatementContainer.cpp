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


Statement* StatementContainer::addAssignStatement(int index, StatementContainer* parent,Variable* v, Expression* exp) {
	return stmtLst->addAssignStatement(index, parent,v, &(exp->getUsedVariable()), exp);
}

StatementContainer* StatementContainer::addWhileStatement(int index, StatementContainer* parent,Variable* controlVar) {
	return stmtLst->addWhileStatement(index, parent,controlVar);
}