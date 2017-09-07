#include "AssignStatement.h"

AssignStatement::AssignStatement(int stmtNo, int index, Statement *parent, Statement *following, Variable varModified, vector<Variable> varUsed, Expression ex) {
	Statement(stmtNo, parent, following);
	modifiedVar = varModified;
	usedVar = varUsed;
	exp = ex;
}