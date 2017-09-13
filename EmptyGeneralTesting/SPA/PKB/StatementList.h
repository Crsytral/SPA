#pragma once

#include <vector>
using namespace std;

#include "Expression.h"
#include "Statement.h"
#include "StatementContainer.h"
#include "Variable.h"

class StatementList {
private:
	//Statement* stmt0;
	Statement* curr; //Represent the last element of this StatementList
	vector<Statement*> statementList;

public:
	StatementList();
	void addStatement(int stmtNo, StatementContainer* parent);
	Statement* addAssignStatement(int index, StatementContainer* parent,Variable* modVar, vector<Variable*>* usedVars, Expression* exp);
	StatementContainer* addWhileStatement(int index, StatementContainer* parent,Variable* controlVar);
	vector<Statement*> getAllStatement();
	bool isChild(int stmtNo);
};
