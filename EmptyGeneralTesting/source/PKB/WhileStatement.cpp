#include "WhileStatement.h"

WhileStatement::WhileStatement(Variable* cVar) {
	StatementList lst(this);
	stmtLst = &lst;
	varUsed.push_back(cVar);
}
