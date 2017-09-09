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
bool PKB::isValidStmtNo(int s) {
	return (0 < s && s < currIndex + 1 ? true : false);
}
bool PKB::follows(int stmt1, int stmt2) {
	if (isValidStmtNo(stmt1) && isValidStmtNo(stmt2)) {
		Statement* s1 = allStatements[stmt1 - 1];
		Statement* s2 = s1->getFollowBy();
		if (s2 != NULL && s2->getStmtNo() == stmt2) return true;
		else return false;
	}
	return false;
}
int PKB::follows(int stmt1) {
	if (isValidStmtNo(stmt1)) {
		Statement* s1 = allStatements[stmt1 - 1];
		Statement* s2 = s1->getFollowBy();
		if (s2 != NULL) return s2->getStmtNo();
	}
	return -1;
}
int PKB::followsBy(int stmt2) {
	if (isValidStmtNo(stmt2)) {
		Statement* s1 = allStatements[stmt2 - 1];
		Statement* s2 = s1->getFollow();
		if (s2 != NULL) return s2->getStmtNo();
	}
	return -1;
}
bool PKB::followStar(Statement* s1, Statement* s2) {
	if (s1 == NULL) return false;
	if (s1 == s2) return true;
	else return followStar(s1->getFollowBy(), s2);
}
bool PKB::followStar(int stmt1, int stmt2) {
	if (isValidStmtNo(stmt1) && isValidStmtNo(stmt2) && stmt1 < stmt2) {
		Statement* s1 = allStatements[stmt1 - 1];
		Statement* s2 = allStatements[stmt2 - 1];
		return followStar(s1, s2);
	}
	return false;
}
vector<int> PKB::followStar(int stmt1) {
	vector<int> result;
	if (isValidStmtNo(stmt1)) {
		Statement* s1 = allStatements[stmt1 - 1];
		while (s1->getFollowBy() != NULL) {
			s1 = s1->getFollowBy();
			result.push_back(s1->getStmtNo());
		}
		if (!result.empty()) return result;
	}
	result.push_back(-1);
	return result;
}
vector<int> PKB::followStarBy(int stmt2) {
	vector<int> result;
	if (isValidStmtNo(stmt2)) {
		Statement* s2 = allStatements[stmt2 - 1];
		while (s2->getFollow() != NULL) {
			s2 = s2->getFollowBy();
			result.push_back(s2->getStmtNo());
		}
		if (!result.empty()) return result;
	}
	result.push_back(-1);
	return result;
}
vector<pair<int, int>> PKB::follows() {
	vector<pair<int, int>> result;
	for (Statement* s : allStatements) {
		int s1 = s->getStmtNo();
		int followStmt = follows(s1);
		if (followStmt != -1) {
			pair<int, int> p(s1, followStmt);
			result.push_back(p);
		}
	}
	if (!result.empty()) {
		return result;
	}
	else {
		pair<int, int> ans(-1, -1);
		result.push_back(ans);
		return result;
	}
}
vector<pair<int, int>> PKB::followStar() {
	vector<pair<int, int>> result;
	for (Statement* s : allStatements) {
		int s1 = s->getStmtNo();
		vector<int> followStmt = followStar(s1);
		if (followStmt[0] != -1) {
			for (int s2 : followStmt) {
				pair<int, int> p(s1, s2);
				result.push_back(p);
			}
		}
	}
	if (!result.empty()) {
		return result;
	}
	else {
		pair<int, int> ans(-1, -1);
		result.push_back(ans);
		return result;
	}
}

/*
Dummy implementation
*/
bool PKB::parents(int stmt1, int stmt2) {

}

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