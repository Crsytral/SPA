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
	vector<Variable*> varUsed;
	vector<Variable*> varModified;
	StatementList * stmtLst;
	StatementContainer * parentContainer;
public:
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
	void updateVarUsed(vector<Variable*>* vars);
	/*
	Update varModified list after a statement is added to the stmtLst. To be implemented by Shermine
	*/
	void updateVarModified(Variable* v);
	/*
	Set StatementContainer p as the parentContainer of this object to facilitate updateVarUsed and
	updateVarModified operations.
	*/
	void setParentContainer(StatementContainer * p);
};