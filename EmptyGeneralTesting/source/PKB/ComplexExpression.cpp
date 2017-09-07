#include "ComplexExpression.h"

ComplexExpression::ComplexExpression() {

}

ComplexExpression::ComplexExpression(string ope) {
	op = ope;
	leftExp = 0;
	rightExp = 0;
	leftVar = 0;
	rightVar = 0;
}

void ComplexExpression::addLeftExp(ComplexExpression& exp) {
	leftExp = &exp;
}

void ComplexExpression::addRightExp(ComplexExpression& exp) {
	rightExp = &exp;
}

void ComplexExpression::addLeftVar(Variable& var) {
	leftVar = &var;
}

void ComplexExpression::addRightVar(Variable& var) {
	rightVar = &var;
}
