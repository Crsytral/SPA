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
	vector<Statement*> modifyStmtLst;
	vector<Statement*> useStmtLst;
public:
	Variable(string name);
	/*
	Return a string representing this variable's name.
	*/
	string getName();
	/*
	Check if the provided variable is the same as this variable
	by comparing their names.
	*/
	bool equals(Variable& v);
	/*
	Add a statement into the list of statements that modify this variable.
	Statement needs to have a statement number already assigned.
	*/
	void addModifyStmt(Statement* stmt);
	/*
	Add a statement into the list of statements that use this variable.
	Statement needs to have a statement number already assigned.
	*/
	void addUseStmt(Statement* stmt);
	bool operator==(Variable other);
};