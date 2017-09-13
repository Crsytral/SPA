#pragma once

#include <vector>
#include <stack>
#include <utility>
using namespace std;

#include "../PKB/AssignStatement.h"
#include "../PKB/Procedure.h"
#include "../PKB/Statement.h"
#include "../PKB/Variable.h"
#include "../PKB/WhileStatement.h"
#include "../PKB/StatementContainer.h"

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
	bool parentStar(WhileStatement* s1, StatementContainer* s2);
public:
	PKB();
	/*
	Create an emtpy Procedure object with the specified procName,
	add it to allProcedures list and push it on top of the currentStmtContainer stack.
	procName has to be guaranteed to be valid by Parser.
	*/
	void addProcedure(const string& procName);
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
	//getAll APIs
	/*
	Return a vector of names of all procedures in the program
	*/
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
	//uses relation
	bool uses(int stmtIndex, string varName);
	vector<int> uses(string varName);
	vector<string> usedBy(int stmtIndex);
	vector<pair<int, string>> uses();
	//modifies relation
	bool modifies(int stmtIndex, string varName);
	vector<int> modifies(string varName);
	vector<string> modifiedBy(int stmtIndex);
	vector<pair<int, string>> modifies();
};