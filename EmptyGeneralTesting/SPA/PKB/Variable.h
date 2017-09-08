#pragma once
#include <string>
#include <vector>
using namespace std;

#include "Statement.h"

/*
A simplified Variable class implement to try out Unit Testing.
Full implementation to be completed later.
*/
class Variable {
private:
	string varName;
	vector<Statement*>* modifyStmtLst;
	vector<Statement*>* useStmtLst;
public:
	Variable();
	Variable(string name);
	string getName();
	bool equals(Variable& v);
	void addModifyStmt(Statement* stmt);
	void addUseStmt(Statement* stmt);
};