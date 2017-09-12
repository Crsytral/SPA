#include "WhileStatement.h"

WhileStatement::WhileStatement(int index, StatementContainer* parent, Statement* following, Variable* cVar) {
	Statement(index, parent, following);
	addUseVar(cVar);
	stmtLst = new StatementList(this);
}
