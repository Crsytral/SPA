#pragma once
#include <vector>
using namespace std;

#include "Statement.h"
#include "Variable.h"
#include "Expression.h"

class StatementList {
private:
	Statement* parentStatement;
	//Procedure parentProcedure;
	Statement* curr;

public:
	StatementList(Statement* parent);
	void addStatement(int stmtNo);
	void addAssignmentStatement(int stmtNo, Variable varModified, vector<Variable> varUsed, Expression ex);
	Statement* getParent();
	Statement* getCurr();
};
