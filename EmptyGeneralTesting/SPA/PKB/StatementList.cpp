#include "StatementList.h"
#include "AssignStatement.h"
#include "WhileStatement.h"

StatementList::StatementList(StatementContainer* p) {
	parentContainer = p;
	curr = nullptr;
}

void StatementList::addStatement(int stmtNo) {
	Statement stmt(stmtNo, parentContainer, curr);
	statementList.push_back(&stmt);
	if(curr != nullptr)
		curr->setFollowedBy(&stmt);
	curr = &stmt;
}

StatementContainer* StatementList::getParentContainer() {
	return parentContainer;
}

Statement* StatementList::addAssignStatement(int index, Variable* v, vector<Variable*>* usedVars, Expression* exp) {
	
	AssignStatement stmt(index, parentContainer, curr, v, usedVars, exp);
	statementList.push_back(&stmt);
	if (curr != nullptr)
		curr->setFollowedBy(&stmt);
	curr = &stmt;
	return &stmt;
}

StatementContainer* StatementList::addWhileStatement(int index, Variable* controlVar) {
	
	WhileStatement stmt(index, parentContainer, curr, controlVar);
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