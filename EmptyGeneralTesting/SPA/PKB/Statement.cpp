#include "Statement.h"
#include "WhileStatement.h"
#include "Procedure.h"

Statement::Statement() {
	stmtNo = NULL;
	parentContainer= nullptr;
	follow = nullptr;
}

Statement::Statement(int index, StatementContainer* p, Statement *following) {
	stmtNo = index;
	parentContainer = p;
	follow = following;
	followBy = nullptr;
}

void Statement::setFollowedBy(Statement *followedBy) {
	followBy = followedBy;
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
StatementContainer* Statement::getParentContainer() {
	return parentContainer;
}
//Procedure getParentProcedure();
bool Statement::isParent(int stmtNo) {
	return typeid(parentContainer) == typeid(Statement) && static_cast<WhileStatement*>(parentContainer)->stmtNo == stmtNo;
}

bool Statement::isParent(string procName) {
	return typeid(parentContainer) == typeid(Procedure) && static_cast<Procedure*>(parentContainer)->getProcName() == procName;
}

int Statement::getStmtNo() {
	return stmtNo;
}
bool Statement::operator==(Statement others) {
	return stmtNo == others.stmtNo;
}