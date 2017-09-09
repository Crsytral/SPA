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
#include <ctype.h>
#include <regex>
#include <fstream>
#include "QueryParser.h"
#include "SyntaticType.h"
#include "QueryObject.h"
#include "QueryTree.h"

using namespace std;

QueryTree* newTree;
Synonyms* newSynonyms;

bool noSynFound;
bool errorRelation;
bool errorFound;

bool buildResult = false;
bool isSuch = false;
bool buildSuchThat = false;
bool buildPattern = false;

string concatQuery;

regex varRegex("(([a-zA-Z])+(([a-zA-Z])|#|(\\d)+)*|_|\"([a-zA-Z])+(([a-zA-Z])|#|(\\d)+)*\")");

//Regex for expressions like X*Y+Z in parameters
regex varExpressions("\"(([a-zA-Z])+(([a-zA-Z])|(\\d)+)*|\\d+)((\\+|\\-|\\*)(([a-zA-Z])+(([a-zA-Z])|(\\d)+)*|\\d+))*\"|_");

/*
enum relation {
	modifies,
	uses,
	follows,
	followsStar,
	parent,
	parentStar,
	calls,
	callsStar,
	next,
	nextStar,
	affects,
	affectsStar,
	isError,
};
*/

QueryParser::QueryParser() {

}

/*
//Check the parameter of queries with pattern clause
bool parametersCheck(syntatic_type currentSyn, string firstPara, string secondPara, string thirdPara) {

	bool validity = false;
	
	//This function serves to check test cases like Select a pattern a ( _ , _“x*y+z”_)
	if (regex_match(firstPara, varRegex)) {

		if (regex_match(firstPara, varRegex)) {



		}

	}
	
}
*/

//Check the parameter of queries with such that clause
bool parametersCheck(relation relationClause, string firstParam, string secondParam) {

	bool validity = false;

	regex entRef("(([a-zA-Z])+(([a-zA-Z])|#|(\\d)+)*|_|(\\d)+|\"([a-zA-Z])+(([a-zA-Z])|#|(\\d)+)*\")");
	regex stmtRef("(([a-zA-Z])+(([a-zA-Z])|#|(\\d)+)*|_|(\\d)+)");
	regex lineRef("(([a-zA-Z])+(([a-zA-Z])|#|(\\d)+)*|_|(\\d)+)");
	regex varRef("(([a-zA-Z])+(([a-zA-Z])|#|(\\d)+)*|_|\"([a-zA-Z])+(([a-zA-Z])|#|(\\d)+)*\")");


	if (relationClause == relation::modifies)
	{
		if (regex_match(firstParam, entRef) && regex_match(secondParam, entRef))
		{
			validity = true;
		}
	}
	else if (relationClause == relation::uses)
	{
		if (regex_match(firstParam, entRef) && regex_match(secondParam, varRef))
		{
			validity = true;
		}
	}
	else if (relationClause == relation::calls)
	{
		if (regex_match(firstParam, entRef) && regex_match(secondParam, entRef))
		{
			validity = true;
		}
	}
	else if (relationClause == relation::callsStar)
	{
		if (regex_match(firstParam, entRef) && regex_match(secondParam, entRef))
		{
			validity = true;
		}
	}
	else if (relationClause == relation::parent)
	{
		if (regex_match(firstParam, stmtRef) && regex_match(secondParam, stmtRef))
		{
			validity = true;
		}
	}
	else if (relationClause == relation::parentStar)
	{
		if (regex_match(firstParam, stmtRef) && regex_match(secondParam, stmtRef))
		{
			validity = true;
		}
	}
	else if (relationClause == relation::follows)
	{
		if (regex_match(firstParam, stmtRef) && regex_match(secondParam, stmtRef))
		{
			validity = true;
		}
	}
	else if (relationClause == relation::followsStar)
	{
		if (regex_match(firstParam, stmtRef) && regex_match(secondParam, stmtRef))
		{
			validity = true;
		}
	}
	else if (relationClause == relation::next)
	{
		if (regex_match(firstParam, lineRef) && regex_match(secondParam, lineRef))
		{
			validity = true;
		}
	}
	else if (relationClause == relation::nextStar)
	{
		if (regex_match(firstParam, lineRef) && regex_match(secondParam, lineRef))
		{
			validity = true;
		}
	}
	else if (relationClause == relation::affects)
	{
		if (regex_match(firstParam, stmtRef) && regex_match(secondParam, stmtRef))
		{
			validity = true;
		}
	}
	else if (relationClause == relation::affectsStar)
	{
		if (regex_match(firstParam, stmtRef) && regex_match(secondParam, stmtRef))
		{
			validity = true;
		}
	}
	return validity;

}

void removeCharsFromString(string &str, char* charsToRemove) {

	//int charSize = strlen(charsToRemove);
	for (unsigned int i = 0; i < strlen(charsToRemove); ++i) {

		str.erase(remove(str.begin(), str.end(), charsToRemove[i]), str.end());
	}
}

//Check the synonym of the query if its a variable or an expression
syntatic_type checkSyntaticType(string input) {

	regex underScoreOnly("_");
	regex doubleQuotes("\"[^\"]+\"");
	regex underScoreBothSides("_\"[^\"]+\"_");
	regex integer("\\d+");

	syntatic_type resultingSyn = syntatic_type::synTypeError;

	if (regex_match(input, doubleQuotes) || regex_match(input, underScoreBothSides))
	{
		resultingSyn = syntatic_type::expression;
	}
	else if (regex_match(input, underScoreOnly))
	{
		resultingSyn = syntatic_type::expression;
	}
	else if (regex_match(input, integer))
	{
		resultingSyn = syntatic_type::integer;
	}
	else
	{
		if (newSynonyms->checkExists(input))
		{
			resultingSyn = newSynonyms->getSyntType(input);
		}
	}
	return resultingSyn;

}

//Get the entity relationsip inside a such as clause
relation getType(char* rsType){

	if (strcmp(rsType, "Uses") == 0)
	{
		return relation::uses;
	}
	else if (strcmp(rsType, "Modifies") == 0)
	{
		return relation::modifies;
	}
	else if (strcmp(rsType, "Calls") == 0)
	{
		return relation::calls;
	}
	else if (strcmp(rsType, "Calls*") == 0)
	{
		return relation::callsStar;
	}
	else if (strcmp(rsType, "Parent") == 0)
	{
		return relation::parent;
	}
	else if (strcmp(rsType, "Parent*") == 0)
	{
		return relation::parentStar;
	}
	else if (strcmp(rsType, "Follows") == 0)
	{
		return relation::follows;
	}
	else if (strcmp(rsType, "Follows*") == 0)
	{
		return relation::followsStar;
	}
	else if (strcmp(rsType, "Next") == 0)
	{
		return relation::next;
	}
	else if (strcmp(rsType, "Next*") == 0)
	{
		return relation::nextStar;
	}
	else if (strcmp(rsType, "Affects") == 0)
	{
		return relation::affects;
	}
	else if (strcmp(rsType, "Affects*") == 0)
	{
		return relation::affectsStar;
	}

	else errorFound = true;
	return isError;
}

void identifyResult(char* curTok){

	if (!newSynonyms->checkExists(curTok))
	{
		noSynFound = true;		
	} 
	else
	{
		newSynonyms->setResult(newSynonyms->getIndex(curTok));
	}

}

void buildQueryNode(char* curTok, string concatQuery) {

	//regex qurPattern("([^\\(]+\\(([^\\)]+|[^\,]+)\,([^\\)]+|[^\,]+)\\))");
	regex qurPattern("([^\\(]+\\(([^\\)]+|[^\,]+)\,([^\\)]+|[^\,]+)\\))");
	concatQuery.append(curTok);

	if (regex_match(concatQuery, qurPattern))
	{
		string relationEntity = "";
		relation relationClause;
		string firstParameter = "";
		string secondParameter = "";
		bool gottenRelation = false;
		bool firstParameterDone = false;

		//int size = concatQuery.size();

		for (std::string::size_type i = 0; i < concatQuery.size(); ++i) {

			if (concatQuery[i] == '(')
			{
				vector<char> writable(relationEntity.begin(), relationEntity.end());
				writable.push_back('\0');
				relationClause = getType(&writable[0]);

				gottenRelation = true;
			}

			else if (concatQuery[i] == ')')
			{
				concatQuery = "";
			}

			else if (gottenRelation && concatQuery[i] != ',')
			{
				if (firstParameterDone)
				{
					secondParameter += concatQuery[i];
				}

				else 
				{ 
					
					firstParameter += concatQuery[i];
				}

			}

			else if (concatQuery[i] == ',')
			{
				firstParameterDone = true;
			}

			else if (!gottenRelation)
			{
				relationEntity += concatQuery[i];
			}

		}

		if (parametersCheck(relationClause, firstParameter, secondParameter))
		{
			syntatic_type firstSynType = checkSyntaticType(firstParameter);
			syntatic_type secondSynType = checkSyntaticType(secondParameter);

			if (firstSynType != syntatic_type::synTypeError && secondSynType != syntatic_type::synTypeError)
			{
				removeCharsFromString(secondParameter, "\"");
				removeCharsFromString(firstParameter, "\"");
				ParameterNode* firstParamNode = new ParameterNode(firstSynType, firstParameter);
				ParameterNode* secondParamNode = new ParameterNode(secondSynType, secondParameter);
				QueryNode* newQuery = new QueryNode(relationClause, firstParamNode, secondParamNode);
				newTree->addQuery(newQuery);
			}
		}
	}
	

}


void checkPatternOrQuery(char* inputTok) {


	if (strcmp(inputTok, "Select") == 0)
	{
		buildResult = true;
		isSuch = false;
		buildSuchThat = false;
		buildPattern = false;

	}

	else if (strcmp(inputTok, "such") == 0)
	{
		isSuch = true;
		buildSuchThat = false;
		buildPattern = false;
		buildResult = false;
	}

	else if (isSuch == true && strcmp(inputTok, "that") == 0)
	{
		buildSuchThat = true;
		buildPattern = false;
		buildResult = false;
		isSuch = false;

		concatQuery = "";
	}

	else if (strcmp(inputTok, "pattern") == 0)
	{
		buildPattern = true;
	}

	else
	{
		if (buildResult = true)
		{
			identifyResult(inputTok);
		}

		else if (buildSuchThat = true)
		{
			buildQueryNode(inputTok, concatQuery);
		}
	}


	
}

syntatic_type getEntityType(char* input, bool checkEntityType) {


	syntatic_type result;

	if (strcmp(input, "while") == 0)
	{
		result = syntatic_type::whileLoop;
	}
	else if (strcmp(input, "assign") == 0)
	{
		result = syntatic_type::assignment;
	}
	else if (strcmp(input, "procedure") == 0)
	{
		result = syntatic_type::procedure;
	}
	else if (strcmp(input, "stmtLst") == 0)
	{
		result = syntatic_type::statementList;
	}
	else if (strcmp(input, "stmt") == 0)
	{
		result = syntatic_type::statement;
	}
	else if (strcmp(input, "call") == 0)
	{
		result = syntatic_type::call;
	}
	else if (strcmp(input, "if") == 0)
	{
		result = syntatic_type::ifelse;
	}
	else if (strcmp(input, "variable") == 0)
	{
		result = syntatic_type::variable;
	}
	else if (strcmp(input, "constant") == 0)
	{
		result = syntatic_type::constant;
	}
	else if (strcmp(input, "prog_line") == 0)
	{
		result = syntatic_type::progline;
	}

	checkEntityType = true;

	return result;

}

void tokenCheck(char *tok) {

	regex entity(" *(procedure|stmtLst|stmt|assign|call|while|if|variable|constant|prog_line) +([a-zA-Z])+(\\d|#)*( *, *[a-zA-Z]+(\\d|#)*)*");
	regex select(" *Select *.*");

	if (regex_match(tok, entity))
	{
		char *pch;
		char *end_tok;
		pch = strtok_s(tok, " ,", &end_tok);
		bool checkEntityType = false;
		syntatic_type newSyntaticType = syntatic_type::synError;

		while (pch != NULL) {

			if (!checkEntityType)
			{

				newSyntaticType = getEntityType(pch, checkEntityType);

			}

			else {
				newSynonyms->createVar(pch, newSyntaticType);
			}

			pch = strtok_s(NULL, " ,", &end_tok);


		}
	}

	else if(regex_match(tok, select)){

		char *pch;
		char *end_tok;
		pch = strtok_s(tok, " ", &end_tok);

		while (pch != NULL) {

			checkPatternOrQuery(pch);
			pch = strtok_s(NULL, " ", &end_tok);
		}

	}

	else errorFound = true;

}

//This function will take in a user input and turn it into a query object
QueryObject QueryParser::getQueryObj(std::string i) {

	QueryObject query;

	const char* semiColon = ";";

	int str_size = i.size();
	char *token;
	char *end;
	char *temp = new char[str_size + 1];
	newTree = new QueryTree();
    newSynonyms = new Synonyms();

	//points the temp pointer to the input string elements
	memcpy(temp, i.c_str(), str_size);

	token = strtok_s(temp, semiColon, &end);

	while (token != NULL) {

		tokenCheck(token);
		token = strtok_s(NULL, semiColon, &end);

	}

	//QueryObj will be null if there is error

	if (errorFound) {

		query.synonym = NULL;
		query.tree = NULL;

		return query;

	}

	//If there is no error, then create new QueryObj
	else {
		query.synonym = newSynonyms;
		query.tree = newTree;

		return query;
	}


}

int main(void){

	return 0;

}
