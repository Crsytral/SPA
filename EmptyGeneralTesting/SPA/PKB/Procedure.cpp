#include <string>
using namespace std;

#include "Procedure.h"

Procedure::Procedure(string name) {
	procName = name;
}

void Procedure::addModVar(Variable* var) {
	if (isMod(var->getName())) {
		modVar.push_back(var);
	}
}

vector<Variable*> Procedure::getModVar() {
	return modVar;
}

bool Procedure::isMod(string varName) {
	for each (Variable* var in modVar)
	{
		if (var->getName().compare(varName) == 0) {
			return true;
		}
	}
	return false;
}

void Procedure::addUseVar(Variable* var) {
	if (isUse(var->getName())) {
		useVar.push_back(var);
	}
}

vector<Variable*> Procedure::getUseVar() {
	return useVar;
}

bool Procedure::isUse(string varName) {
	for each (Variable* var in useVar)
	{
		if (var->getName().compare(varName) == 0) {
			return true;
		}
	}
	return false;
}

string Procedure::getName() {
	return procName;

}