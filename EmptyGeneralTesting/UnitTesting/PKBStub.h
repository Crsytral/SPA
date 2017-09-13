#pragma once
#include <vector>
using namespace std;

#include "../PKB/Procedure.h"
#include "../PKB/Variable.h"
#include "../PKB/Statement.h"
#include "../PKB/AssignStatement.h"
#include "../PKB/WhileStatement.h"
#include "../PKB/StatementContainer.h"

class PKBStub {
private:
	int currIndex = 4;
	vector<Procedure*> allProcedures;
	vector<Variable*> allVariables;
	vector<Statement*> allStatements;
	bool isValidStmtNo(int s);
	bool followStar(Statement* s1, Statement* s2);
	bool parentStar(WhileStatement* s1, StatementContainer* s2);
public:
	PKBStub();
	vector<string> getAllProcedures();
	/*
	Return a vector of all indices of all statements in the program
	Return a vector with 1 element -1 if there is no statement.
	*/
	vector<int> getAllStatements();
	/*
	Return a vector of all indices of all assignment statements in the program
	Return a vector with 1 element -1 if there is no assignment statement.
	*/
	vector<int> getAllAssignStatements();
	/*
	Return a vector of all indices of all while statements in the program
	Return a vector with 1 element -1 if there is no while statement.
	*/
	vector<int> getAllWhileStatements();
	/*
	Return a vector of all indices of all if statements in the program
	Return a vector with 1 element -1 if there is no if statement.
	*/
	vector<int> getAllIfStatements();
	/*
	Return a vector of names of all variables in the program.
	Return a vector with 1 element "" if there is no variable.
	*/
	vector<string> getAllVariables();
	//follows relation
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
	vector<int> parents(int stmt1);
	int parentedBy(int stmt2);
	bool parentStar(int stmt1, int stmt2);
	vector<int> parentStar(int stmt1);
	vector<int> parentStarBy(int stmt2);
	vector<pair<int, int>> parents();
	vector<pair<int, int>> parentStar();
};