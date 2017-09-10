#include "StatementList.h"

StatementList::StatementList(StatementContainer* p) {
	parentContainer = p;
	curr = nullptr;
}

void StatementList::addStatement(int stmtNo) {
	Statement* stmt = new Statement(stmtNo, parentContainer, curr);
	statementList.push_back(*stmt);
	if(curr != nullptr)
		curr->setFollowedBy(stmt);
	curr = stmt;
}

StatementContainer* StatementList::getParentContainer() {
	return parentContainer;
}

Statement* StatementList::addAssignStatement(int index, Variable* v, vector<Variable*>* usedVars, Expression* exp) {
	
	return nullptr;
}

StatementContainer* StatementList::addWhileStatement(int index, Variable* controlVar) {
	
	return nullptr;
}

vector<Statement> StatementList::getAllStatement() {
	return statementList;
}

bool StatementList::isChild(int stmtNo) {
	Statement stmt(stmtNo, nullptr, nullptr);
	vector<Statement>::iterator it = find(statementList.begin(),statementList.end(),stmt);

	return it != statementList.end();
}