#include "Variable.h"

Variable::Variable(string name) {
	varName = name;
}

string Variable::getName() { return varName; }

bool Variable::equals(Variable& v) {
	if (varName.compare(v.getName()) == 0) return true;
	else return false;
}

void Variable::addModifyStmt(Statement* stmt) {
	//check if stmt is already inside
	bool alrAdded = false;
	for (Statement* s : modifyStmtLst) {
		if (s->getStmtNo() == stmt->getStmtNo()) {
			alrAdded = true;
			break;
		}
	}
	//add to list if not already added
	if (!alrAdded) {
		modifyStmtLst.push_back(stmt);
	}
}

void Variable::addUseStmt(Statement* stmt) {
	//check if stmt is already inside
	bool alrAdded = false;
	for (Statement* s : useStmtLst) {
		if (s->getStmtNo() == stmt->getStmtNo()) {
			alrAdded = true;
			break;
		}
	}
	//add to list if not already added
	if (!alrAdded) {
		useStmtLst.push_back(stmt);
	}
bool Variable::operator==(Variable other) {
	return varName.compare(other.varName) == 0;
}