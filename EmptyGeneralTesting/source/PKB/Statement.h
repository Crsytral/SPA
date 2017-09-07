#pragma once
#include <string>
using namespace std;

//#include "Procedure.h"
/*
Abstract representation of the commonalities of all types of statements
*/
class Statement {

protected:
	int stmtNo;
	Statement* follow;
	Statement* followBy;
	Statement* parentStatement;
	//Procedure parentProcedure;


public:
	Statement();
	Statement(int stmtNo, Statement *parent, Statement *following);
	//Statement(int stmtNo, Procedure parent, Statement *following);
	void setFollowedBy(Statement *followBy);
	Statement* getFollow();
	bool isFollow(int stmtNo);
	Statement* getFollowBy();
	bool isFollowBy(int stmtNo);
	Statement* getParentStatement();
	//Procedure getParentProcedure();
	bool isParent(int stmtNo);
	//bool isParent(string proName);
	int getStmtNo();
	bool equals(Statement* others);
};
