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
	vector<Variable> useVar;
	vector<Variable> modVar;
public:
	Procedure(string name);
	string getProcName();
	void addModVar(Variable var);
	vector<Variable> getUseVar();
	bool isUse(string varMod);
	void addUseVar(Variable var);
	vector<Variable> getModVar();
	bool isMod(string varMod);
	bool operator==(Statement others);
};