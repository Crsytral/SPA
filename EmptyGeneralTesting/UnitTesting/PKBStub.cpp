#include <queue>;
using namespace std;

#include "PKBStub.h"
#include "../PKB/Expression.h"
#include "../Parser/VarToken.h"
#include "../Parser/NumToken.h"
#include "../Parser/OperatorToken.h"

PKBStub::PKBStub() {
	//adding in var list
	vector<string> varNames = { "i", "x", "y", "z" };
	allVariables = {new Variable(varNames[0]),
		new Variable(varNames[1]),
		new Variable(varNames[2]),
		new Variable(varNames[3])
	};
	string proc = "Sun";
	//adding in procedure list
	allProcedures = { new Procedure(proc) };
	//adding in the statements
	//first construct the expressions for 3 assignment statements
	queue<Token> q1, q2, q3;
	//add to q1 & build expression 1
	q1.push(*(new NumToken("1")));
	Expression * ex1 = new Expression(q1);
	allProcedures[0]->addAssignStatement(1, allVariables[1], ex1);
	//add to q2
	q2.push(*(new VarToken("x")));
	q2.push(*(new NumToken("2")));
	q2.push(*(new OperatorToken("+")));
	q2.push(*(new VarToken("z")));
	q2.push(*(new OperatorToken("+")));
	Expression * ex2 = new Expression(q2);
	allProcedures[0]->addAssignStatement(2, allVariables[2], ex2);
	//add to q3 and build expression 3
	q3.push(*(new NumToken("3")));
	Expression * ex3 = new Expression(q3);
    //add a while statement
	WhileStatement * w1 = static_cast<WhileStatement *>(allProcedures[0]->addWhileStatement(3, allVariables[0]));
	w1->addAssignStatement(4, allVariables[3], ex3);
}

vector<string> PKBStub::getAllProcedures() {
	vector<string> result;
	result.push_back(allProcedures[0]->getName());
	return result;
}
/*
Return a vector of all indices of all statements in the program
Return a vector with 1 element -1 if there is no statement.
*/
vector<int> PKBStub::getAllStatements() {
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
vector<int> PKBStub::getAllAssignStatements() {
	vector<int> result = { 1, 2, 4 };
	return result;
}
/*
Return a vector of all indices of all while statements in the program
Return a vector with 1 element -1 if there is no while statement.
*/
vector<int> PKBStub::getAllWhileStatements() {
	vector<int> result = { 3 };
	return result;
}
/*
Return a vector of all indices of all if statements in the program
Return a vector with 1 element -1 if there is no if statement.
*/
vector<int> PKBStub::getAllIfStatements() {
	vector<int> result = { -1 };
	return result;
}
/*
Return a vector of names of all variables in the program.
Return a vector with 1 element "" if there is no variable.
*/
vector<string> PKBStub::getAllVariables() {
	vector<string> result = { "i", "x", "y", "z" };
	return result;
}

bool PKBStub::isValidStmtNo(int s) {
	return (0 < s && s < currIndex + 1 ? true : false);
}

bool PKBStub::follows(int stmt1, int stmt2) {
	if (isValidStmtNo(stmt1) && isValidStmtNo(stmt2)) {
		Statement* s1 = allStatements[stmt1 - 1];
		Statement* s2 = s1->getFollowBy();
		if (s2 != NULL && s2->getStmtNo() == stmt2) return true;
		else return false;
	}
	return false;
}
int PKBStub::follows(int stmt1) {
	if (isValidStmtNo(stmt1)) {
		Statement* s1 = allStatements[stmt1 - 1];
		Statement* s2 = s1->getFollowBy();
		if (s2 != NULL) return s2->getStmtNo();
	}
	return -1;
}
int PKBStub::followsBy(int stmt2) {
	if (isValidStmtNo(stmt2)) {
		Statement* s1 = allStatements[stmt2 - 1];
		Statement* s2 = s1->getFollow();
		if (s2 != NULL) return s2->getStmtNo();
	}
	return -1;
}
bool PKBStub::followStar(Statement* s1, Statement* s2) {
	if (s1 == NULL) return false;
	if (s1 == s2) return true;
	else return followStar(s1->getFollowBy(), s2);
}
bool PKBStub::followStar(int stmt1, int stmt2) {
	if (isValidStmtNo(stmt1) && isValidStmtNo(stmt2) && stmt1 < stmt2) {
		Statement* s1 = allStatements[stmt1 - 1];
		Statement* s2 = allStatements[stmt2 - 1];
		return followStar(s1, s2);
	}
	return false;
}
vector<int> PKBStub::followStar(int stmt1) {
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
vector<int> PKBStub::followStarBy(int stmt2) {
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
vector<pair<int, int>> PKBStub::follows() {
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
vector<pair<int, int>> PKBStub::followStar() {
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
bool PKBStub::parents(int stmt1, int stmt2) {
	if (isValidStmtNo(stmt1) && isValidStmtNo(stmt2)) {
		Statement* s2 = allStatements[stmt2 - 1];
		StatementContainer* sc2 = s2->getParentContainer();
		if (typeid(*sc2) == typeid(WhileStatement) && static_cast<WhileStatement*> (sc2)->getStmtNo() == stmt1) {
			return true;
		}
	}
	return false;
}

vector<int> PKBStub::parents(int stmt1) {
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
int PKBStub::parentedBy(int stmt2) {
	if (isValidStmtNo(stmt2)) {
		Statement* s2 = allStatements[stmt2 - 1];
		StatementContainer* sc2 = s2->getParentContainer();
		if (typeid(*sc2) == typeid(WhileStatement))
			return static_cast<WhileStatement*>(sc2)->getStmtNo();
	}
	return -1;
}

bool PKBStub::parentStar(WhileStatement* s1, StatementContainer* s2) {
	if (typeid(*s2) == typeid(Procedure)) return false;
	WhileStatement* w2 = static_cast<WhileStatement*>(s2);
	if (s1->getStmtNo() == w2->getStmtNo()) return true;
	if (s1->getStmtNo() > w2->getStmtNo()) return false;
	return parentStar(s1, s2->getParentContainer());
}

/*
Return true if parentStar(stmt1, stmt2). Return false otherwise.
*/
bool PKBStub::parentStar(int stmt1, int stmt2) {
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
vector<int> PKBStub::parentStar(int stmt1) {
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
vector<int> PKBStub::parentStarBy(int stmt2) {
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
vector<pair<int, int>> PKBStub::parents() {
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
vector<pair<int, int>> PKBStub::parentStar() {
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