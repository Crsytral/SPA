#include "StatementList.h"
#include "AssignStatement.h"
#include "WhileStatement.h"

StatementList::StatementList() {
	curr = nullptr;
}

void StatementList::addStatement(int stmtNo, StatementContainer* parent) {
	Statement stmt(stmtNo, parent, curr);
	statementList.push_back(&stmt);
	if(curr != nullptr)
		curr->setFollowedBy(&stmt);
	curr = &stmt;
}

Statement* StatementList::addAssignStatement(int index, StatementContainer* parent, Variable* v, vector<Variable*>* usedVars, Expression* exp) {
	
	AssignStatement stmt(index, parent, curr, v, usedVars, exp);
	statementList.push_back(&stmt);
	if (curr != nullptr)
		curr->setFollowedBy(&stmt);
	curr = &stmt;
	return &stmt;
}

StatementContainer* StatementList::addWhileStatement(int index, StatementContainer* parent,Variable* controlVar) {
	
	WhileStatement stmt(index, parent, curr, controlVar);
	statementList.push_back(&stmt);
	if (curr != nullptr)
		curr->setFollowedBy(&stmt);
	curr = &stmt;
	return &stmt;
}

vector<Statement*> StatementList::getAllStatement() {
	return statementList;
}

bool StatementList::isChild(int stmtNo) {

	for each (Statement* stmt in statementList)
	{
		if (stmt->getStmtNo() == stmtNo) {
			return true;
		}
	}
	return false;
}