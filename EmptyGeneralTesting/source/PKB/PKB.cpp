#include <vector>
using namespace std;

#include "PKB.h"
#include "Procedure.h"
/*
Represents a parsed SIMPLE program
*/

PKB::PKB() {

}

void PKB::addProcedure(string procName) {
	Procedure proc(procName);
	allProcedures.push_back(&proc);
	currentStmtContainer.push(&proc);
}

/*
Add a Variable object into the PKB.
Ignore if a Variable object with the same name has
already been added into the PKB earlier.
*/
void PKB::addVariable(Variable* var) {
	if (allVariables.empty()) {
		allVariables.push_back(var);
	}
	else {
		bool alrAdded = false;
		for (Variable* v : allVariables) {
			if (v->equals(*var)) {
				alrAdded = true;
				break;
			}
		}
		if (!alrAdded) allVariables.push_back(var);
	}
}

/*
Add assign statement with variable* v and expression* exp to the AST.
*/
void PKB::addAssignStatement(Variable* v, Expression* exp) {
	//currentStmtContainer stack guaranteed to be non-empty by parser
	StatementContainer * stmt = currentStmtContainer.top();
	AssignStatement* aStmt = static_cast<AssignStatement*> (stmt->addAssignStatement(++currIndex, v, exp));
	allStatements.push_back(aStmt);
	addVariable(v);
	vector<Variable*>* expVars = exp->getUsedVariable();
	for (Variable* vb : *expVars) {
		addVariable(vb);
	}
}

/*
Add WhileStatement stmt to the AST.
*/
void PKB::addWhileStatement(Variable* controlVar) {
	//currentStmtContainer stack guaranteed to be non-empty
	StatementContainer * stmtContainer = currentStmtContainer.top();
	WhileStatement* wStmt = static_cast<WhileStatement*> (stmtContainer->addWhileStatement(++currIndex, controlVar));
	allStatements.push_back(wStmt);
	addVariable(controlVar);
	currentStmtContainer.push(wStmt);
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
bool PKB::follows(int stmt1, int stmt2) {
	return false;
}
int PKB::follows(int stmt1) {
	return -1;
}
int PKB::followsBy(int stmt2) {
	return -1;
}
bool PKB::followStar(int stmt1, int stmt2) {
	return false;
}
vector<int> PKB::followStar(int stmt1) {
	vector<int> result(1, -1);
	return result;
}
vector<int> PKB::followStarBy(int stmt2) {
	vector<int> result(1, -1);
	return result;
}
vector<pair<int, int>> PKB::follows() {
	vector<pair<int, int>> result;
	pair<int, int> ans(-1, -1);
	result.push_back(ans);
	return result;
}
vector<pair<int, int>> PKB::followStar() {
	vector<pair<int, int>> result;
	pair<int, int> ans(-1, -1);
	result.push_back(ans);
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