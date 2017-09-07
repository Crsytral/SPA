#pragma once
// PKB_API functions as being imported from ...
// defined with this macro as being exported.

#include <vector>
#include <stack>
using namespace std;

#include "AssignStatement.h"
#include "Procedure.h"
#include "Statement.h"
#include "Variable.h"
#include "ComplexExpression.h"
#include "WhileStatement.h"
#include "StatementContainer.h"

/*
Represents a parsed SIMPLE program
*/
class PKB {
private:
	vector<Procedure> allProcedures;
	vector<Variable> allVariables;
	vector<Statement> allStatements;
	stack<StatementList*> currentStmtContainer;
public:
	PKB();
	void addProcedure(Procedure &proc);
	void addVariable(Variable &var);
	void addStatement(Statement &stmt);
	/*
	Add an assign statement to the PKB.
	It should be guaranteed by the parser that the statement belong to some valid statement list.
	*/
	void addAssignStatement(AssignStatement &stmt);
	/*
	Add WhileStatement stmt to the PKB.
	Parser should guarantee stmt to be not null and have controlVar attribute filled up
	*/
	void addWhileStatement(WhileStatement &stmt);
	/*
	Signal to PKB a closing bracket i.e. remove top of currentStmtContainer
	Return: true if possible, false if stack is empty i.e. extra closing bracket.
	*/
	bool endOfList();
	//the ones below are for query selector
	bool follows(int stmt1, int stmt2);
	int follows(int stmt1);
	int followsBy(int stmt2);
	bool followStar(int stmt1, int stmt2);
	vector<int> followStar(int stmt1);
	vector<int> followStarBy(int stmt2);
	vector<int> follows();
	vector<int> followStar();
	vector<int> parent(int stmtIndex);
	vector<int> parentBy(int stmtIndex);
	vector<int> parents(int stmtIndex);
	vector<int> parentsBy(int stmtIndex);
};