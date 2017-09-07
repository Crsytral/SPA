#include "QueryEvaluator.h"
#include "stdafx.h"
#include <vector>
#include <iostream>

QueryEvaluator::QueryEvaluator(QueryObject q) { //string q to be replaced with QueryObj
	queryObj = q;
	rawResult = processQuery();
}

Result QueryEvaluator::processQuery() {
	Result result;
	if (processVariableClause(result) == true)
			processSuchThat(result);

	//combineResults(r1, r2, r3);
	return result;
}

//Process only the variable clauses of the query. Retrieves all relevant statements from PKB based on the type of variable(Eg:Assign/Variable/Statement)
//AfterMerged with PreProcessor, this method handles Select portion of PQL as well.
bool QueryEvaluator::processVariableClause() {
	//string test = "assign a, variable v; Select v pattern a(v, \"procs * ifs\")";
	vector <string> assignmentType; //to be replaced with API from query preprocessor, get assignmentType(s) of query
	assignmentType.push_back("assign");
	assignmentType.push_back("statement");
	vector <SyntaticData*> symbolTable = queryObj.getSymbolTable();
	if (symbolTable.getSize() == 0) { //if 0 means no symbol = return nth
		return false;
	}else{
		for each (SyntaticData data in symbolTable)
		{
			if (data.getResult() == 1){
				if (data.getVariableType() == "assign") {
					rawResult.setAsgnData(PKB.getAllAssignStatement()); // to replace with relevant PKB API
				}
				else if (data.getVariableType() == "variable") {
					rawResult.setAsgnData(PKB.getAllVariables()); // to replace with relevant PKB API
				}
				else if (data.getVariableType() == "statement") {
					rawResult.setAsgnData(PKB.getAllStatements()); // to replace with relevant PKB API
				}
				else if (data.getVariableType() == "while") {
					rawResult.setAsgnData(PKB.getAllWhileStatement()); // to replace with relevant PKB API
				}
				else if (data.getVariableType() == "if") {
					rawResult.setAsgnData(PKB.getAllIfStatement()); // to replace with relevant PKB API
				}
				else if (data.getVariableType() == "procedure") {
					rawResult.setAsgnData(PKB.getAllProcedures()); // to replace with relevant PKB API
				}
				else {
					//will this case ever be reached?
					return false;
				}
			}
		}
	}
	return true;
}

bool QueryEvaluator::processSuchThat() {
	Result result("This is data 3");
	bool success = false;
	if (queryObj.getQuery().getType() == "follows") {
		//to check if param is int or not first before calling
		success = PKB.follows((int)queryObj.getQuery().getLeftParam(), (int)queryObj.getQuery().getRightParam());
	}
	else if (queryObj.getQuery().getType() == "followsStar") {
		success = PKB.followStar((int)queryObj.getQuery().getLeftParam(), (int)queryObj.getQuery().getRightParam());
	}
	else if (queryObj.getQuery().getType() == "parents") {
		success = PKB.parents((int)queryObj.getQuery().getLeftParam(), (int)queryObj.getQuery().getRightParam());
	}
	else if (queryObj.getQuery().getType() == "parentStar") {
		success = PKB.parentStar((int)queryObj.getQuery().getLeftParam(), (int)queryObj.getQuery().getRightParam());
	}
	else if (queryObj.getQuery().getType() == "modifies") {
		success = PKB.modifies((int)queryObj.getQuery().getLeftParam(), queryObj.getQuery().getRightParam());
	}
	else if (queryObj.getQuery().getType() == "uses") {
		success = PKB.uses((int)queryObj.getQuery().getLeftParam(), queryObj.getQuery().getRightParam());
	}
	else if (queryObj.getQuery().getType() == "pattern") {
		cout << "pattern processing yet to finish" << endl;
	}
	else {
		cout << "Yet to be handled (processSuchThat()) - What case is this?" << endl;
	}

	if (success == true)
		rawResult.setValid(true);
		//processSelect();
	return true;
}

//getters and setters
Result QueryEvaluator::getRawResult() {
	return rawResult;
}

bool QueryEvaluator::processSelect() {
	
	return true;
}
/*
bool QueryEvaluator::processSecondClause(Result result) {
	Result result("This is data 2");
	//calls PKB with the left and right parameter to check base on type
	if (queryObj.getQuery().getType() == "follows") {

	}
	else if (queryObj.getQuery().getType() == "followsStar") {
		
	}
	else if (queryObj.getQuery().getType() == "parent") {

	}
	else if (queryObj.getQuery().getType() == "parentStar") {

	}
	else if (queryObj.getQuery().getType() == "modifies") {

	}
	else if (queryObj.getQuery().getType() == "uses") {

	}
	else {

	}
	
	return	true;
}

Result QueryEvaluator::combineResults(Result r1, Result r2, Result r3) {
	string newData = "Empty Test"; //r1.getQueryResult() + "\n" + r2.getQueryResult() + "\n" + r3.getQueryResult();
	Result newResult(newData);
	return newResult;
}*/

