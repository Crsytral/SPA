#pragma once
#include "StatementContainer.h"
#include "Statement.h"
#include "Variable.h"
#include "StatementList.h"

class WhileStatement : public StatementContainer, public Statement {
public:
	WhileStatement(int index, StatementContainer* parent, Statement* following, Variable* cVar);
};
