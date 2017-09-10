#pragma once
#include <string>
#include <vector>
using namespace std;

#include "Expression.h"
#include "StatementContainer.h"
#include "Variable.h"
#include "WhileStatement.h"

class Procedure: public StatementContainer {
private:
	string procName;
public:
	Procedure(string name);
	string getName();
};