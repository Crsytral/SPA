#pragma once
#include <vector>
using namespace std;

#include "AssignStatement.h"
#include "Statement.h"
#include "StatementList.h"
#include "WhileStatement.h"
#include "Expression.h"

class AssignStatement;
class Statement;
class StatementList;
class WhileStatement;
class Variable;
class Expression;

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
	AssignStatement* addAssignStatement(int index, Variable* v, Expression* exp);
	WhileStatement* addWhileStatement(int index, Variable* controlVar);
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