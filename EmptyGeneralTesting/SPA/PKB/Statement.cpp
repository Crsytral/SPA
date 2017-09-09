#include "Statement.h"

Statement::Statement() {
	stmtNo = NULL;
	parentStatement = nullptr;
	//parentProcedure = nullptr;
	follow = nullptr;
}

Statement::Statement(int index, StatementContainer* p, Statement *following) {
	stmtNo = index;
	parentContainer = p;
	follow = following;
	followBy = nullptr;
}

/*Statement::Statement(int index, Procedure parent, Statement *following) {
stmtNo = index;
parentProcedure = parent;
follow = following;
}*/

void Statement::setFollowedBy(Statement *followedBy) {
	followBy = followedBy;
}

void Statement::setParentStatement(Statement* parent) {
	parentStatement = parent;
}

Statement* Statement::getFollow() {
	return follow;
}
bool Statement::isFollow(int stmtNo) {
	return follow != nullptr && follow->stmtNo == stmtNo;
}
Statement* Statement::getFollowBy() {
	return followBy;
}
bool Statement::isFollowBy(int stmtNo) {
	return followBy != nullptr && followBy->stmtNo == stmtNo;
}
Statement* Statement::getParentStatement() {
	return parentStatement;
}
StatementContainer* Statement::getParentContainer() {
	return parentContainer;
}
//Procedure getParentProcedure();
bool Statement::isParent(int stmtNo) {
	return parentStatement != nullptr && parentStatement->stmtNo == stmtNo;
}
//bool isParent(string proName);
int Statement::getStmtNo() {
	return stmtNo;
}
bool Statement::equals(Statement* others) {
	return stmtNo == others->stmtNo;
}