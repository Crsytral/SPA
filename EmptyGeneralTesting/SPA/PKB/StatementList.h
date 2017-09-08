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
	//Procedure parentProcedure;
	Statement* curr; //Represent the last element of this StatementList

public:
	StatementList(StatementContainer* p);
	void addStatement(int stmtNo);
	/*
	Build an AssignStatement object from the provided parameters and link it in this StatementList.
	To be implemented by Shermine
	*/
	Statement* addAssignStatement(int index, Variable* v, vector<Variable*>* usedVars, Expression* exp);
	/*
	Build a WhileStatement object from the provided parameters and link it in this StatementList.
	Return a pointer to this WhileStatement object to be added onto PKB stack.
	To be implemented by Shermine
	*/
	StatementContainer* addWhileStatement(int index, Variable* controlVar);
	StatementContainer* getParentContainer();
	Statement* getCurr();
};
