#include <string>
using namespace std;

#include "Procedure.h"

Procedure::Procedure(const string &name) {
	procName = name;
	StatementList lst;
	stmtLst = &lst;
}

void Procedure::addModVar(Variable var) {
	modVar.push_back(var);
}

vector<Variable> Procedure::getModVar() {
	return modVar;
}

bool Procedure::isMod(string varName) {
	Variable var(varName);
	vector<Variable>::iterator it = find(modVar.begin(), modVar.end(), var);
	return it != modVar.end();
}

void Procedure::addUseVar(Variable var) {
	useVar.push_back(var);
}

vector<Variable> Procedure::getUseVar() {
	return useVar;
}

bool Procedure::isUse(string varName) {
	Variable var(varName);
	vector<Variable>::iterator it = find(useVar.begin(), useVar.end(), var);
	return it != useVar.end();
}

string Procedure::getName() {
	return procName;
}