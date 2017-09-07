#include "StatementList.h"

StatementList::StatementList(Statement* parent) {
	parentStatement = parent;
	curr = nullptr;
}

void StatementList::addStatement(int stmtNo) {
	Statement* stmt = new Statement(stmtNo, parentStatement, curr);
	if(curr != nullptr)
		curr->setFollowedBy(stmt);
	curr = stmt;
}

Statement* StatementList::getParent() {
	return parentStatement;
}

Statement* StatementList::getCurr() {
	return curr;
}