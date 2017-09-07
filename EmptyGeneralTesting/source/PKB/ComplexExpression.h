#pragma once
#include <string>
using namespace std;

#include "Variable.h"

/*
This class represents a dummy expression
*/
class ComplexExpression {
private:
	string op;
	ComplexExpression * leftExp;
	ComplexExpression * rightExp;
	Variable * leftVar;
	Variable * rightVar;
	int leftConst;
	int rightConst;
public:
	ComplexExpression();
	ComplexExpression(string ope);
	void addLeftExp(ComplexExpression& exp);
	void addRightExp(ComplexExpression& exp);
	void addLeftVar(Variable& var);
	void addRightVar(Variable& var);
};
