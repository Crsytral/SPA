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

void StatementList::addAssignmentStatement(int stmtNo, Variable varModified, vector<Variable> varUsed, Expression ex) {
	Statement* stmt = new AssignStatement(stmtNo, parentStatement, curr, varModified, varUsed, ex);
	if (curr != nullptr)
		curr->setFollowedBy(stmt);
	curr = stmt;
}

Statement* StatementList::getParent() {
	return parentStatement;
}

Statement* StatementList::getCurr() {
	return curr;
}