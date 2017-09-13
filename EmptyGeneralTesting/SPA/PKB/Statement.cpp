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
	return typeid(parentContainer) == typeid(Procedure) && static_cast<Procedure*>(parentContainer)->getName().compare(procName) == 0;
}

int Statement::getStmtNo() {
	return stmtNo;
}

bool Statement::operator==(Statement others) {
	return stmtNo == others.stmtNo;
}

void Statement::addModVar(Variable* var) {
	if (isMod(var->getName())) {
		modVar.push_back(var);
		var->addModifyStmt(this);
		if (parentContainer != nullptr) {
			if (typeid(parentContainer) == typeid(Statement)) {
				static_cast<WhileStatement*>(parentContainer)->addModVar(var);
			}
			else {
				static_cast<Procedure*>(parentContainer)->addModVar(var);
			}
		}
	}
}

vector<Variable*> Statement::getModVar() {
	return modVar;
}

bool Statement::isMod(string varName) {
	for each (Variable* var in modVar)
	{
		if (var->getName().compare(varName) == 0) {
			return true;
		}
	}
	return false;
}

void Statement::addUseVar(Variable* var) {
	if (isUse(var->getName())) {
		useVar.push_back(var);
		var->addUseStmt(this);
		if (parentContainer != nullptr) {
			if (typeid(parentContainer) == typeid(Statement)) {
				static_cast<WhileStatement*>(parentContainer)->addUseVar(var);
			}
			else {
				static_cast<Procedure*>(parentContainer)->addUseVar(var);
			}
		}
	}
}

vector<Variable*> Statement::getUseVar() {
	return useVar;
}

bool Statement::isUse(string varName) {
	for each (Variable* var in useVar)
	{
		if (var->getName().compare(varName) == 0) {
			return true;
		}
	}
	return false;
}