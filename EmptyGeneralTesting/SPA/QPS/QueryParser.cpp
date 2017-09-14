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

string concatQuery = "";
string concatPattern = "";

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


//Check the parameter of queries with pattern clause
bool parametersCheck(syntatic_type inputSyn, string firstPara, string secondPara, string thirdPara) {

	bool validity = false;
	regex expressionRegex("\"(([a-zA-Z])+(([a-zA-Z])|(\\d)+)*|\\d+)((\\+|\\-|\\*)(([a-zA-Z])+(([a-zA-Z])|(\\d)+)*|\\d+))*\"|_");
	regex singleUnderscore("_");
	regex doubleUnderscore("_\"(([a-zA-Z])+(([a-zA-Z])|(\\d)+)*|\\d+)((\\+|\\-|\\*)(([a-zA-Z])+(([a-zA-Z])|(\\d)+)*|\\d+))*\"_");
	
	//This function serves to check test cases like Select a pattern a ( _ , _“x*y+z”_)
	if (inputSyn == syntatic_type::assignment)
	{
		if (regex_match(firstPara, varRegex)) {

			//cout << firstPara;
			if (regex_match(secondPara, singleUnderscore) || regex_match(secondPara, expressionRegex) || regex_match(secondPara, doubleUnderscore) )
			{
				validity = true;
			}

			else
			{
				cout << secondPara;
				printf("Invalid regex detected");
			}

		}

		else
		{
			cout << firstPara;
			printf("invalid parameter detected");
		}
	}

	else if (inputSyn == syntatic_type::ifelse)
	{
		if (regex_match(firstPara, varRegex) && regex_match(secondPara, singleUnderscore) && regex_match(thirdPara, singleUnderscore))
		{
			if (regex_match(firstPara, varRegex) && regex_match(secondPara, singleUnderscore) && regex_match(thirdPara, singleUnderscore))
			{
				validity = true;
			}
		}
	}

	else if (inputSyn == syntatic_type::whileLoop)
	{
		if (regex_match(firstPara, varRegex) && regex_match(secondPara, singleUnderscore))
		{
			validity = true;
		}
	}

	return validity;


}


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
	regex alphabets("/^[a-z]+$/i");


	syntatic_type resultingSyn = syntatic_type::synTypeError;

	if (regex_match(input, doubleQuotes) || regex_match(input, underScoreBothSides))
	{
		resultingSyn = syntatic_type::expression;
	}
	else if (regex_match(input, underScoreOnly))
	{
		resultingSyn = syntatic_type::expression;
	}
	else if (regex_match(input, alphabets))
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
	else if (strcmp(rsType, "Parent") == 0)
	{   
		//printf("checkParent");
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
		int index = newSynonyms->getIndex(curTok);
		//printf("%d", index);
		//char a = getchar();
		newSynonyms->setResult(newSynonyms->getIndex(curTok));
	}

}

void buildQueryNode(char* curTok) {

	//printf("getQuery");
	//std::cout << curTok << '\n';
	regex qurPattern("([^\\(]+\\(([^\\)]+|[^\,]+)\,([^\\)]+|[^\,]+)\\))");
	concatQuery.append(curTok);
	//std::cout << concatQuery;
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
				//printf("getQuery");
				vector<char> writable(relationEntity.begin(), relationEntity.end());
				writable.push_back('\0');
				relationClause = getType(&writable[0]);

				gottenRelation = true;
			}

			else if (concatQuery[i] == ')')
			{   
				//concatQuery = "";
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
				//string test = firstParamNode->getParameter();
				//string test1 = secondParamNode->getParameter();
				//cout << test1;
				newTree->addQuery(newQuery);
				//string test2 = newTree->getQuery()->getLeftParam()->getParameter();
				//cout << test2;
				
				/*
				if (newTree->getQuery()->getType() == relation::parent)
				{
					printf("yay");
				}
				*/
				
				
			}
		}
	}
	

}

void buildPatternNode(char* curTok) {
	
	//printf("pattern");
	//char a = getchar();

	concatPattern.append(curTok);

	//printf("test");

	regex expectedPattern("([^\\(]+\\(([^\\)]+|[^\,]+)(\,([^\\)]+|[^\,]+)\\))+)");
	/*
	bool firstParameterDone = false;
	bool secondParameterDone = false;
	bool foundPatternSyn = false;
	bool synonymExist;
	bool isIfElse;

	string firstParameter = "";
	string secondParameter = "";
	string thirdParameter = "";
	syntatic_type  patternSynType;

	string patternSyn = "";
	*/

	if (regex_match(concatPattern, expectedPattern))
	{
		bool firstParameterDone = false;
		bool secondParameterDone = false;
		bool foundPatternSyn = false;
		bool synonymExist;
		bool isIfElse = false;

		string firstParameter = "";
		string secondParameter = "";
		string thirdParameter = "";
		string patternSyn = "";

		syntatic_type  patternSynType;


		for (std::string::size_type i = 0; i < concatPattern.size(); ++i) {

			if (concatPattern[i] == '(')
			{
				if (newSynonyms->checkExists(patternSyn))
				{
					synonymExist = true;
				}

				else;

				if (synonymExist = false)
				{
					errorFound = true;
					break;
				}

				else
				{
					patternSynType = newSynonyms->getSyntType(patternSyn);

					//check if its syntactic type is valid
					if (patternSynType != syntatic_type::assignment && patternSynType != syntatic_type::whileLoop && patternSynType != syntatic_type::ifelse)
					{
						errorFound = true;
						printf("Error with pattern syntactic type");
						break;
					}

					else;

					if (patternSynType == syntatic_type::ifelse)
					{
						isIfElse = true;
					}

				}
				foundPatternSyn = true;
			}

			else if (concatPattern[i] == ')')
			{
				concatPattern = "";
			}

			else if (foundPatternSyn && concatPattern[i] != ',')
			{
				if (!isIfElse)
				{
					if (firstParameterDone)
					{
						secondParameter += concatPattern[i];
					}

					else
					{
						firstParameter += concatPattern[i];
					}
				}

				else
				{
					if (firstParameterDone)
					{
						secondParameter += concatPattern[i];
					}

					else if (secondParameterDone)
					{
						thirdParameter += concatPattern[i];
					}

					else
					{
						firstParameter += concatPattern[i];
					}

				}

			}

			else if (concatPattern[i] == ',')
			{
				if (!firstParameterDone)
				{
					firstParameterDone = true;
				}

				else
				{
					secondParameterDone = true;
				}
			}

			else if (foundPatternSyn != true)
			{
				patternSyn += concatPattern[i];
			}
		}


		if (parametersCheck(patternSynType, firstParameter, secondParameter, thirdParameter))
		{
			printf("entered parameterCheck\n");
			ParameterNode* leftParameterNode = new ParameterNode(patternSynType, patternSyn);
			syntatic_type middleParameterSynType = checkSyntaticType(firstParameter);
			syntatic_type rightParameterSynType = checkSyntaticType(secondParameter);
			removeCharsFromString(secondParameter, "\"");
			removeCharsFromString(firstParameter, "\"");
			ParameterNode* middleParameterNode = new ParameterNode(middleParameterSynType, firstParameter);
			printf("second parameterCheck");
			char a = getchar();
			ParameterNode* rightParameterNode = new ParameterNode(rightParameterSynType, secondParameter);
			PatternNode* newPattern = new PatternNode(leftParameterNode, middleParameterNode, rightParameterNode);
			newTree->addPattern(newPattern);
			//string test2 = newTree->getPattern()->getMiddleParam()->getParameter();
			//cout << test2;
			/*
			if (newTree->getPattern()->getRightParam()->getType() == syntatic_type::expression)
			{
				printf("correct syn");
			}

			else
			{
				printf("wrong syn");
			}

			
			if (newTree->getPattern()->getMiddleParam()->getType() == syntatic_type::integer)
			{
				printf("correct syn");
			}

			else
			{
				printf("wrong syn");
			}
			*/


		}
	}

}

void checkPatternOrQuery(char* inputTok) {


	if (strcmp(inputTok, "Select") == 0)
	{   
		//printf("test select");
		buildResult = true;
		isSuch = false;
		buildSuchThat = false;
		buildPattern = false;

	}

	else if (strcmp(inputTok, "such") == 0)
	{   
		//printf("test such");
		isSuch = true;
		buildSuchThat = false;
		buildPattern = false;
		buildResult = false;
	}

	else if (isSuch == true && strcmp(inputTok, "that") == 0)
	{   
		//printf("test that\n");
		buildSuchThat = true;
		buildPattern = false;
		buildResult = false;
		isSuch = false;

		//concatQuery = "";

		
	}

	else if (strcmp(inputTok, "pattern") == 0)
	{
		buildPattern = true;
	}

	else
	{   
		//std::cout << inputTok << '\n';
	
		if (buildResult)
		{   
			//printf("hello");
			identifyResult(inputTok);
		}

		else;
		
	    if (buildSuchThat)
		{   
			//printf("check");
			buildQueryNode(inputTok);
		}

		else;

		if (buildPattern)
		{   
			//printf("buildPattern");
			//std::cout << inputTok << '\n';
			//char a = getchar();
			buildPatternNode(inputTok);
		}

		else;
	}
	
}

syntatic_type getEntityType(char* input) {

	syntatic_type result;

	if (strcmp(input, "while") == 0)
	{
		result = syntatic_type::whileLoop;
		//checkEntityType = true;
	}
	else if (strcmp(input, "assign") == 0)
	{
		result = syntatic_type::assignment;
		//checkEntityType = true;
	}
	else if (strcmp(input, "procedure") == 0)
	{
		result = syntatic_type::procedure;
		//checkEntityType = true;
	}

	else if (strcmp(input, "statement") == 0)
	{
		result = syntatic_type::statement;
		//checkEntityType = true;
	}
	else if (strcmp(input, "call") == 0)
	{
		result = syntatic_type::call;
		//checkEntityType = true;
	}
	else if (strcmp(input, "if") == 0)
	{
		result = syntatic_type::ifelse;
		//checkEntityType = true;
	}
	else if (strcmp(input, "variable") == 0)
	{
		result = syntatic_type::variable;
		//checkEntityType = true;
	}
	else if (strcmp(input, "constant") == 0)
	{
		result = syntatic_type::constant;
		//checkEntityType = true;
	}
	else if (strcmp(input, "prog_line") == 0)
	{
		result = syntatic_type::progline;
		//checkEntityType = true;
	}
	

	return result;

}

void tokenCheck(char *tok) {

	regex entity(" *(procedure|stmtLst|statement|assign|call|while|if|variable|constant|prog_line) +([a-zA-Z])+(\\d|#)*( *, *[a-zA-Z]+(\\d|#)*)*");
	regex select(" *Select *.*");

	//std::cout << tok << '\n';

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

				newSyntaticType = getEntityType(pch);
				checkEntityType = true;
				//printf("1");
				//std::cout << tok << '\n';

			}

			else {
				newSynonyms->createVar(pch, newSyntaticType);
				//std::cout << pch << '\n';
			}

			pch = strtok_s(NULL, " ,", &end_tok);


		}
	}

	else if(regex_match(tok, select)){

		//std::cout << tok << '\n';
		//char a = getchar();
		char *pch;
		char *end_tok;
		pch = strtok_s(tok, " ", &end_tok);
		while (pch != NULL) {
			//std::cout << pch << '\n';
			//char a = getchar();
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
	temp[str_size] = 0;
	newTree = new QueryTree();
    newSynonyms = new Synonyms();

	//printf("%d", str_size);

	//points the temp pointer to the input string elements
	memcpy(temp, i.c_str(), str_size);
	//std::cout << temp << '\n';

	token = strtok_s(temp,semiColon, &end);
	
	while (token != NULL) {

		tokenCheck(token);
		token = strtok_s(NULL,semiColon, &end);

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

/*

int main(void){
	
	QueryParser* qp;
	qp = new QueryParser();

	//string input = "assign a; variable v; Select a pattern a ("3",_)";

	//printf("%s, input");

	QueryObject test = qp -> getQueryObj("assign a; statement s; variable v; Select s such that Parent (2, s)");
	//QueryObject test = qp->getQueryObj("assign a; variable v; Select a pattern a (\"v\", _)");
	/*
	int size = test.synonym->getSize();

	if (size == 3)
	{
		printf("true");
	}

	else

		printf("fail");

	*/

	//char a = getchar();

	//return 0;
}
*/




