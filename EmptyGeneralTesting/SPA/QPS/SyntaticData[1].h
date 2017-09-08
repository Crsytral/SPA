#pragma once

#ifndef SYNTATICDATA_H
#define SYNTATICDATA_H

using namespace std;

#include <string>
#include "SyntaticType.h"

class SyntaticData {

private:
	std::string variable;
	syntatic_type variableType;
	bool result;

public:
	SyntaticData(string x, syntatic_type y, bool res);
	
	void setVar(string x);

	void setVarType(syntatic_type y);

	void setResult(bool r);

	string getVariable();

	syntatic_type getVariableType();

	bool getResult();

};

#endif
