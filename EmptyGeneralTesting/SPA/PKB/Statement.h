#pragma once
#include <string>
#include <vector>
using namespace std;

class StatementContainer;
class Variable;

/*
Abstract representation of the commonalities of all types of statements
*/
class Statement {

protected:
	int stmtNo;
	Statement* follow;
	Statement* followBy;
	StatementContainer* parentContainer;
	vector<Variable> useVar;
	vector<Variable> modVar;

public:
	Statement();
	Statement(int stmtNo, StatementContainer* p, Statement *following);
	void setFollowedBy(Statement* followBy);
	Statement* getFollow();
	bool isFollow(int stmtNo);
	Statement* getFollowBy();
	bool isFollowBy(int stmtNo);
	StatementContainer* getParentContainer();
	bool isParent(int stmtNo);
	bool isParent(string proName);
	int getStmtNo();
	void addModVar(Variable var);
	vector<Variable> getUseVar();
	bool isUse(string varMod);
	void addUseVar(Variable var);
	vector<Variable> getModVar();
	bool isMod(string varMod);
	bool operator==(Statement others);
};
