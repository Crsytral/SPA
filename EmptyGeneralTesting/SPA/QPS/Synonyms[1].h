#pragma once

#ifndef SYMBOL_H
#define SYMBOL_H

#include "vector"
#include "SyntaticData.h"
#include "SyntaticType.h"

using namespace std;

class Synonyms {
private:
	std::vector<SyntaticData*> symbolTable;

public:
	Synonyms();
	Synonyms(string var, syntatic_type varType);
	void createVar(string var, syntatic_type varType);
	void setResult(int index);
	vector<SyntaticData*> getQuery();
	int getSize();
	int getIndex(string var);
	bool checkExists(string var);
	syntatic_type getSyntType(string var);
};

#endif