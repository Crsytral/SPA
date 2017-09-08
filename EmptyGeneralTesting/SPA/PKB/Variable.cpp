#include "Variable.h"

Variable::Variable() {

}

Variable::Variable(string name) {
	varName = name;
}

string Variable::getName() { return varName; }

bool Variable::equals(Variable& v) {
	if (varName.compare(v.getName()) == 0) return true;
	else return false;
}

void Variable::addModifyStmt(Statement* stmt) {
	modifyStmtLst->push_back(stmt);
}

void Variable::addUseStmt(Statement* stmt) {
	useStmtLst->push_back(stmt);
}