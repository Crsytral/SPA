#pragma once
#include <vector>
using namespace std;

#include "Statement.h"
#include "Expression.h"
#include "Variable.h"
#include "StatementList.h"

class StatementList;

/*
An abstract interface representing any object that has at least 1 statement list
To be implemented by the following class: Procedure, IfStatement, WhileStatement
*/
class StatementContainer {
protected:
	StatementList * stmtLst;
	StatementContainer * pContainer;
public:
	StatementContainer();
	/*
	Return a vector of all statements that are nested under this statement container.
	Return an empty vector if there is no statement nested under this statement container.
	*/
	vector<Statement*> getAllStatements();
	/*
	Parameter: Statement stmt
	Outcome: stmt is added to the StatementList of this StatementContainer object.
	StatementList of this object should also be added to the StatementList of stmt.
	Set parent of stmt to this Statement Container for if & while statements.
	*/
	Statement* addAssignStatement(int index, Variable* v, Expression* exp);
	StatementContainer* addWhileStatement(int index, Variable* controlVar);
	/*
	Update varUsed list of this object and its parentContainer (if exist) after a statement is added to the stmtLst.
	To be implemented by Shermine
	*/
	void setParentContainer(StatementContainer * p);
	/*
	Get the parent StatementContainer of this object.
	*/
	StatementContainer* getParentContainer();
};