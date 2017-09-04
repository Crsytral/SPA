#include <vector>
using namespace std;

#include "PKB.h"
#include "Procedure.h"
/*
Represents a parsed SIMPLE program
*/
void PKB::addProcedure(Procedure &proc) {
	allProcedures.push_back(proc);
	currentStmtContainer.push(proc);
}

void PKB::addVariable(Variable &var) {
	allVariables.push_back(var);
}

void PKB::addStatement(Statement &stmt) {
	allStatements.push_back(stmt);
}

/*
Add AssignStatement stmt to the AST.
*/
void PKB::addAssignStatement(AssignStatement &stmt) {
	//currentStmtContainer stack guaranteed to be non-empty
	StatementContainer * stmtContainer = &currentStmtContainer.top();
	(*stmtContainer).addStatement(stmt);
}

/*
Add WhileStatement stmt to the AST.
*/
void PKB::addWhileStatement(WhileStatement &stmt) {
	StatementContainer * stmtContainer = &currentStmtContainer.top();
	(*stmtContainer).addStatement(stmt);
	currentStmtContainer.push(stmt);
}

/*
Signal to PKB a closing bracket i.e. remove top of currentStmtContainer
Return: true if possible, false if stack is empty i.e. extra closing bracket.
*/
bool PKB::endOfList() {
	if (currentStmtContainer.empty()) {
		return false;
	}
	else {
		currentStmtContainer.pop();
		return true;
	}
}

/*
Dummy implementation
*/
vector<int> PKB::follow(int stmtIndex) {
	vector<int> result(2, 2);
	return result;
}

/*
Dummy implementation
*/
vector<int> PKB::followBy(int stmtIndex) {
	vector<int> result(2, 2);
	return result;
}

/*
Dummy implementation
*/
vector<int> PKB::follows(int stmtIndex) {
	vector<int> result(2, 2);
	return result;
}

/*
Dummy implementation
*/
vector<int> PKB::followsBy(int stmtIndex) {
	vector<int> result(2, 2);
	return result;
}

/*
Dummy implementation
*/
vector<int> PKB::parent(int stmtIndex) {
	vector<int> result(2, 2);
	return result;
}

/*
Dummy implementation
*/
vector<int> PKB::parentBy(int stmtIndex) {
	vector<int> result(2, 2);
	return result;
}

/*
Dummy implementation
*/
vector<int> PKB::parents(int stmtIndex) {
	vector<int> result(2, 2);
	return result;
}

/*
Dummy implementation
*/
vector<int> PKB::parentsBy(int stmtIndex) {
	vector<int> result(2, 2);
	return result;
}