#include "AssignStatement.h"

AssignStatement::AssignStatement(Variable varModified, vector<Variable> varUsed, Expression ex) {
	modifiedVar = varModified;
	usedVar = varUsed;
	exp = ex;
}