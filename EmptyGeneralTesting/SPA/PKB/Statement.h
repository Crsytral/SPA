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
	StatementContainer* parentContainer;

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
	bool isParent(string proName);
	int getStmtNo();
	bool operator==(Statement others);
};
