#include <algorithm>
#include <vector>
#include <typeinfo>
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
	AssignStatement* aStmt = static_cast<AssignStatement*> (stmt->addAssignStatement(++currIndex, stmt,v, exp));
	allStatements.push_back(aStmt);
	addVariable(v);
	vector<Variable*> expVars = exp->getUsedVariable();
	for (Variable* vb : expVars) {
		addVariable(vb);
	}
}

/*
Add WhileStatement stmt to the AST.
*/
void PKB::addWhileStatement(Variable* controlVar) {
	//currentStmtContainer stack guaranteed to be non-empty
	StatementContainer * stmtContainer = currentStmtContainer.top();
	WhileStatement* wStmt = static_cast<WhileStatement*> (stmtContainer->addWhileStatement(++currIndex, stmtContainer,controlVar));
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

//getAll APIS
/*
Return a vector of names of all procedures in the program.
Return an empty vector if the program has no procedure.
*/
vector<string> PKB::getAllProcedures() {
	vector<string> result;
	for (Procedure* p : allProcedures) {
		result.push_back(p->getName());
	}
	return result;
}
/*
Return a vector of all indices of all statements in the program
Return a vector with 1 element -1 if there is no statement.
*/
vector<int> PKB::getAllStatements() {
	vector<int> result;
	for (Statement* s : allStatements) {
		result.push_back(s->getStmtNo());
	}
	if (!result.empty()) {
		return result;
	}
	else {
		result.push_back(-1);
		return result;
	}
}
/*
Return a vector of all indices of all assignment statements in the program
Return a vector with 1 element -1 if there is no assignment statement.
*/
vector<int> PKB::getAllAssignStatements() {
	vector<int> result;
	for (Statement* s : allStatements) {
		if (typeid(*s) == typeid(AssignStatement)) {
			result.push_back(s->getStmtNo());
		}
	}
	if (result.empty()) {
		result.push_back(-1);
		return result;
	}
	else {
		return result;
	}
}
/*
Return a vector of all indices of all while statements in the program
Return a vector with 1 element -1 if there is no while statement.
*/
vector<int> PKB::getAllWhileStatements() {
	vector<int> result;
	for (Statement* s : allStatements) {
		if (typeid(*s) == typeid(WhileStatement)) {
			result.push_back(s->getStmtNo());
		}
	}
	if (result.empty()) {
		result.push_back(-1);
		return result;
	}
	else {
		return result;
	}
}
/*
Return a vector of all indices of all if statements in the program
Return a vector with 1 element -1 if there is no if statement.
*/
vector<int> PKB::getAllIfStatements() {
	vector<int> result(1, -1);
	return result;
}

vector<string> PKB::getAllVariables() {
	vector<string> result;
	for (Variable* v : allVariables) {
		result.push_back(v->getName());
	}
	if (result.empty()) {
		result.push_back("");
		return result;
	}
	else {
		return result;
	}
}

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
Now comes the parent methods
*/
bool PKB::parents(int stmt1, int stmt2) {
	if (isValidStmtNo(stmt1) && isValidStmtNo(stmt2)) {
		Statement* s2 = allStatements[stmt2 - 1];
		StatementContainer* sc2 = s2->getParentContainer();
		if (typeid(*sc2) == typeid(WhileStatement) && static_cast<WhileStatement*> (sc2)->getStmtNo() == stmt1) {
			return true;
		}
	}
	return false;
}

vector<int> PKB::parents(int stmt1) {
	vector<int> result;
	if (isValidStmtNo(stmt1)) {
		Statement* s1 = allStatements[stmt1 - 1];
		if (typeid(*s1) == typeid(WhileStatement)) {
			vector<Statement*> nestedStmt = static_cast<WhileStatement*>(s1)->getAllStatements();
			if (!nestedStmt.empty()) {
				for (Statement* s : nestedStmt)
					result.push_back(s->getStmtNo());
			}
			return result;
		}
	}
	result.push_back(-1);
	return result;
}

/*
Return index of the statement that stmt2 is directly nested under.
Return -1  if there is no such statement.
*/
int PKB::parentedBy(int stmt2) {
	if (isValidStmtNo(stmt2)) {
		Statement* s2 = allStatements[stmt2 - 1];
		StatementContainer* sc2 = s2->getParentContainer();
		if (typeid(*sc2) == typeid(WhileStatement))
			return static_cast<WhileStatement*>(sc2)->getStmtNo();
	}
	return -1;
}

bool PKB::parentStar(WhileStatement* s1, StatementContainer* s2) {
	if (typeid(*s2) == typeid(Procedure)) return false;
	WhileStatement* w2 = static_cast<WhileStatement*>(s2);
	if (s1->getStmtNo() == w2->getStmtNo()) return true;
	if (s1->getStmtNo() > w2->getStmtNo()) return false;
	return parentStar(s1, s2->getParentContainer());
}

/*
Return true if parentStar(stmt1, stmt2). Return false otherwise.
*/
bool PKB::parentStar(int stmt1, int stmt2) {
	if (isValidStmtNo(stmt1) && isValidStmtNo(stmt2) && stmt1 < stmt2) {
		if (parents(stmt1, stmt2)) {
			return true;
		}
		else {
			Statement* s1 = allStatements[stmt1 - 1];
			Statement* s2 = allStatements[stmt2 - 1];
			StatementContainer* sc2 = s2->getParentContainer();
			if (typeid(*s1) == typeid(WhileStatement) && typeid(*sc2) == typeid(WhileStatement)) {
				return parentStar(static_cast<WhileStatement*>(s1), sc2);
			}
		}
	}
	return false;
}

/*
Return a vector of indices of statements that are nested below stmt1, both directly and indirectly.
Return a vector of 1 element -1 if there are no statement nested below stmt1, both directly and indirectly.
*/
vector<int> PKB::parentStar(int stmt1) {
	vector<int> result;
	vector<int> nestedStmts = parents(stmt1);
	if (nestedStmts[0] == -1) {
		return nestedStmts;
	}
	else {
		for (int stmtNo : nestedStmts) {
			result.push_back(stmtNo);
			vector<int> nestedChildren = parentStar(stmtNo);
			if (nestedChildren[0] != -1) {
				for (int index : nestedChildren) {
					result.push_back(index);
				}
			}
		}
		return result;
	}
}

/*
Return a vector of indices of statements that stmt2 is nested below, both directly and indirectly.
*/
vector<int> PKB::parentStarBy(int stmt2) {
	vector<int> result;
	if (isValidStmtNo(stmt2)) {
		int directParent = parentedBy(stmt2);
		if (directParent != -1) {
			result.push_back(directParent);
			vector<int> parentsOfParent = parentStarBy(directParent);
			if (parentsOfParent[0] != -1) {
				for (int index : parentsOfParent) {
					result.push_back(index);
				}
			}
			return result;
		}
		else {
			result.push_back(-1);
			return result;
		}
	}
}

/*
Return a vector of all possible pairs (s1, s2) such that parent(s1, s2)
Return a vector of 1 element (-1, -1) if no nesting occurs.
*/
vector<pair<int, int>> PKB::parents() {
	vector<pair<int, int>> result;
	vector<Statement*> allWhileStatements(allStatements.size());
	auto it = copy_if(allStatements.begin(),
		allStatements.end(),
		allWhileStatements.begin(),
		[](Statement* s) { return (typeid(*s) == typeid(WhileStatement)); });
	allWhileStatements.resize(distance(allWhileStatements.begin(), it));
	if (allWhileStatements.empty()) {
		pair<int, int> p(-1, -1);
		result.push_back(p);
		return result;
	}
	else {
		for (Statement* s : allWhileStatements) {
			WhileStatement* w = static_cast<WhileStatement*>(s);
			vector<int> nested = parents(w->getStmtNo());
			if (nested[0] != -1) {
				for (int index : nested) {
					pair<int, int> p(w->getStmtNo(), index);
					result.push_back(p);
			    }
			}
		}
		return result;
	}
}

/*
Return a vector of all possible pairs (s1, s2) such that parentStar(s1, s2).
Return a vector of 1 element (-1, -1) if no nesting occurs.
*/
vector<pair<int, int>> PKB::parentStar() {
	vector<pair<int, int>> result;
	vector<Statement*> allWhileStatements(allStatements.size());
	auto it = copy_if(allStatements.begin(),
		allStatements.end(),
		allWhileStatements.begin(),
		[](Statement* s) { return (typeid(*s) == typeid(WhileStatement)); });
	allWhileStatements.resize(distance(allWhileStatements.begin(), it));
	if (allWhileStatements.empty()) {
		pair<int, int> p(-1, -1);
		result.push_back(p);
		return result;
	}
	else {
		for (Statement* s : allWhileStatements) {
			WhileStatement* w = static_cast<WhileStatement*>(s);
			vector<int> nested = parentStar(w->getStmtNo());
			if (nested[0] != -1) {
				for (int index : nested) {
					pair<int, int> p(w->getStmtNo(), index);
					result.push_back(p);
				}
			}
		}
		return result;
	}
}

bool uses(int stmtIndex, string varName) {
	return false;
}

vector<int> uses(string varName) {
	vector<int> result;
	result.push_back(-1);
	return result;
}
vector<string> usedBy(int stmtIndex) {
	vector<string> result;
	result.push_back("");
	return result;
}
vector<pair<int, string>> uses() {
	vector<pair<int, string>> result;
	pair<int, string> p(-1, "");
	result.push_back(p);
	return result;
}
//modifies relation
bool modifies(int stmtIndex, string varName) {
	return false;
}
vector<int> modifies(string varName) {
	vector<int> result;
	result.push_back(-1);
	return result;
}
vector<string> modifiedBy(int stmtIndex) {
	vector<string> result;
	result.push_back("");
	return result;
}
vector<pair<int, string>> modifies() {
	vector<pair<int, string>> result;
	pair<int, string> p(-1, "");
	result.push_back(p);
	return result;
}