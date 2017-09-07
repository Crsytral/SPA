#include "StatementList.h"

StatementList::StatementList(StatementContainer* p) {
	parentContainer = p;
	curr = nullptr;
}

void StatementList::addStatement(int stmtNo) {
	Statement* stmt = new Statement(stmtNo, parentContainer, curr);
	if(curr != nullptr)
		curr->setFollowedBy(stmt);
	curr = stmt;
}

StatementContainer* StatementList::getParentContainer() {
	return parentContainer;
}

Statement* StatementList::getCurr() {
	return curr;
}

AssignStatement* StatementList::addAssignStatement(int index, Variable* v, vector<Variable*>* usedVars, Expression* exp) {
	//To be implemented by Shermine
}

WhileStatement* StatementList::addWhileStatement(int index, Variable* controlVar) {
	//To be implemented by Shermine
}

