#pragma once
#include <string>
using namespace std;

class StatementContainer;

/*
Abstract representation of the commonalities of all types of statements
*/
class Statement {

protected:
	int stmtNo;
	Statement* follow;
	Statement* followBy;
	Statement* parentStatement;
	//I think this can be used to replace parentStatement
	StatementContainer* parentContainer;
	//Procedure parentProcedure;

public:
	Statement();
	Statement(int stmtNo, StatementContainer* p, Statement *following);
	//Statement(int stmtNo, Procedure parent, Statement *following);
	void setFollowedBy(Statement* followBy);
	void setParentStatement(Statement* parent);
	Statement* getFollow();
	bool isFollow(int stmtNo);
	Statement* getFollowBy();
	bool isFollowBy(int stmtNo);
	Statement* getParentStatement();
	//Procedure getParentProcedure();
	StatementContainer* getParentContainer();
	bool isParent(int stmtNo);
	//bool isParent(string proName);
	int getStmtNo();
	bool equals(Statement* others);
};
