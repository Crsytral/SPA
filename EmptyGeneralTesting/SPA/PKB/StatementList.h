#pragma once

#include <vector>
using namespace std;

#include "Expression.h"
#include "Statement.h"
#include "StatementContainer.h"
#include "Variable.h"

class StatementList {
private:
	StatementContainer* parentContainer;
	Statement* curr; //Represent the last element of this StatementList
	vector<Statement> statementList;

public:
	StatementList();
	StatementList(StatementContainer* p);
	void addStatement(int stmtNo);
	Statement* addAssignStatement(int index, Variable* modVar, vector<Variable*>* usedVars, Expression* exp);
	StatementContainer* addWhileStatement(int index, Variable* controlVar);
	StatementContainer* getParentContainer();
	void setParentContainer(StatementContainer* container);
	vector<Statement*> getAllStatement();
	bool isChild(int stmtNo);
};
