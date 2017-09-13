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
	std::string procName;
	std::vector<Variable> useVar;
	std::vector<Variable> modVar;
public:
	Procedure(const string &name);
	void addModVar(Variable var);
	vector<Variable> getUseVar();
	bool isUse(string varMod);
	void addUseVar(Variable var);
	vector<Variable> getModVar();
	bool isMod(string varMod);
	bool operator==(Statement others);
	string getName();
};