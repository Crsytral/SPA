#pragma once
#include "StatementContainer.h"
#include "Statement.h"
#include "Variable.h"

class StatementContainer;
class Statement;

class WhileStatement : public StatementContainer, public Statement {
public:
	WhileStatement(Variable* cVar);
};
