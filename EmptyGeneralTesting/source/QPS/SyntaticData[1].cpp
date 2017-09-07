#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <unordered_map>
#include <set>
#include <list>

#include "SyntaticType.h"
#include "SyntaticData.h"

using namespace std;

SyntaticData::SyntaticData(string var, syntatic_type varType, bool res = false)
{
	variable = var;
	variableType = varType;
	result = res;
}

void SyntaticData::setVar(string var1)
{
	variable = var1;
}
void SyntaticData::setVarType(syntatic_type varType)
{
	variableType = varType;
}
void SyntaticData::setResult(bool res1)
{
	result = res1;
}

string SyntaticData::getVariable()
{
	return variable;
}
syntatic_type SyntaticData::getVariableType()
{
	return variableType;
}
bool SyntaticData::getResult()
{
	return result;
}
