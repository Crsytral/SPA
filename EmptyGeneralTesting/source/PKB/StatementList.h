#pragma once
#include <set>
using namespace std;

#include "Statement.h"

class StatementList {
private:
	Statement* parentStatement;
	//Procedure parentProcedure;
	Statement* curr;

public:
	StatementList(Statement* parent);
	void addStatement(int stmtNo);
	Statement* getParent();
	Statement* getCurr();
};
