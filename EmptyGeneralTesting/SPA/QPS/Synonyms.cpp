#include "Synonyms.h"
#include <string>
#include <vector>
#include "SyntaticData.h"
#include "SyntaticType.h"

using namespace std;

Synonyms::Synonyms()
{
	vector<SyntaticData*> symbolTable;
}

Synonyms::Synonyms(string variable, syntatic_type variableType)
{
	symbolTable.push_back(new SyntaticData(variable, variableType, false));
}

void Synonyms::createVar(string variable, syntatic_type variableType)
{
	symbolTable.push_back(new SyntaticData(variable, variableType, false));
}

//set the result of the specified index to true
void Synonyms::setResult(int target)
{
	symbolTable.at(target)->setResult(true);
}

vector<SyntaticData*> Synonyms::getQuery()
{
	return symbolTable;
}

//returns the size of the symbolTable
int Synonyms::getSize()
{   
	int size = symbolTable.max_size();
	return size;
}

int Synonyms::getIndex(string var)
{   
	/*
	//initialize iterator
    vector<SyntaticData*>::iterator i;
	int index;

	for (i = symbolTable.begin(); i != symbolTable.end(); i++)
	{
		if ((**i).getVariable() == var)
	    index = distance(symbolTable.begin(), i);
		return index;
	}
	return index;

	*/

	for (std::vector<SyntaticData*>::iterator i = symbolTable.begin(); i != symbolTable.end(); i++)
	{
		if ((**i).getVariable() == var)
			return std::distance(symbolTable.begin(), i);
	}
	return -1;
}

//Check whether a certain synonym exist in the symbolTable
bool Synonyms::checkExists(string var)
{
	bool existOrNot = false;
	vector<SyntaticData*>::iterator i;

	for (i = symbolTable.begin(); i != symbolTable.end(); i++)
	{
		if ((**i).getVariable() == var)
		{
			existOrNot = true;
		}

	}
	return existOrNot;
}

//returns the syntactic type of the vaiable
syntatic_type Synonyms::getSyntType(string variable)
{
	syntatic_type synType = synError;
	vector<SyntaticData*>::iterator i;

	for (i = symbolTable.begin(); i != symbolTable.end(); i++)
	{
		if ((**i).getVariable() == variable)
		{
			SyntaticData *temp;
			temp = *i;
			synType = temp->getVariableType();
		}

	}
	return synType;


}
