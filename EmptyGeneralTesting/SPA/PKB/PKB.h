#pragma once

#include <vector>
#include <stack>
#include <utility>
using namespace std;

#include "AssignStatement.h"
#include "Procedure.h"
#include "Statement.h"
#include "Variable.h"
#include "WhileStatement.h"
#include "StatementContainer.h"

/*
Represents a parsed SIMPLE program
*/
class PKB {
private:
	int currIndex = 0;
	vector<Procedure*> allProcedures;
	vector<Variable*> allVariables;
	vector<Statement*> allStatements;
	stack<StatementContainer*> currentStmtContainer;
	bool isValidStmtNo(int s);
	bool followStar(Statement* s1, Statement* s2);
public:
	PKB();
	void addProcedure(string procName);
	void addVariable(Variable* var);
	/*
	Add an assign statement to the PKB.
	It should be guaranteed by the parser that the statement belong to some valid statement list.
	*/
	void addAssignStatement(Variable* v, Expression* exp);
	/*
	Add WhileStatement stmt to the PKB.
	Parser should guarantee stmt to be not null and have controlVar attribute filled up
	*/
	void addWhileStatement(Variable* controlVar);
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
	vector<pair<int, int>> follows();
	vector<pair<int, int>> followStar();
	//parent relation
	bool parents(int stmt1, int stmt2);
	int parents(int stmt1);
	int parentedBy(int stmt2);
	bool parentStar(int stmt1, int stmt2);
	vector<int> parentStar(int stmt1);
	vector<int> parentStarBy(int stmt2);
	vector<pair<int, int>> parents();
	vector<pair<int, int>> parentStar();
};