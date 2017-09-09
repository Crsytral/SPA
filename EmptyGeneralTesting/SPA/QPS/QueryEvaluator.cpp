#include "QueryEvaluator.h"
#include <vector>
#include <iostream>
#include "SyntaticType.h"

QueryEvaluator::QueryEvaluator(QueryObject q) { //string q to be replaced with QueryObj
	queryObj = q;
	rawResult = processQuery();
}

Result QueryEvaluator::processQuery() {
	Result result;
	if (processVariableClause() == true)
			processSuchThat();

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
	vector <SyntaticData*> symbolTable = queryObj.synonym->getQuery();
	if (symbolTable.size() == 0) { //if 0 means no symbol = return nth
		return false;
	}else{
		for each (SyntaticData *data in symbolTable)
		{
			if (data->getResult() == 1){
				cout << data->getVariableType() << endl;
				if (data->getVariableType() == syntatic_type::assignment) {
					rawResult.setAsgnData(PKB.getAllAssignStatement()); // to replace with relevant PKB API
				}
				else if (data->getVariableType() == syntatic_type::variable) {
					rawResult.setAsgnData(PKB.getAllVariables()); // to replace with relevant PKB API
				}
				else if (data->getVariableType() == syntatic_type::statement) {
					rawResult.setAsgnData(PKB.getAllStatements()); // to replace with relevant PKB API
				}
				else if (data->getVariableType() == syntatic_type::whileLoop) {
					rawResult.setAsgnData(PKB.getAllWhileStatement()); // to replace with relevant PKB API
				}
				else if (data->getVariableType() == syntatic_type::ifelse) {
					rawResult.setAsgnData(PKB.getAllIfStatement()); // to replace with relevant PKB API
				}
				else if (data->getVariableType() == syntatic_type::procedure) {
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
	//checks if its int or var

	if (queryObj.tree->getQuery()->getType() == relation::follows) {
		//to check if param is int or not first before calling
		success = PKB.follows((int)queryObj.tree->getQuery()->getLeftParam(), (int)queryObj.tree->getQuery()->getRightParam());
	}
	else if (queryObj.tree->getQuery()->getType() == relation::followsStar) {
		success = PKB.followStar((int)queryObj.tree->getQuery()->getLeftParam(), (int)queryObj.tree->getQuery()->getRightParam());
	}
	else if (queryObj.tree->getQuery()->getType() == relation::parent) {
		success = PKB.parents((int)queryObj.tree->getQuery()->getLeftParam(), (int)queryObj.tree->getQuery()->getRightParam());
	}
	else if (queryObj.tree->getQuery()->getType() == relation::parentStar) {
		success = PKB.parentStar((int)queryObj.tree->getQuery()->getLeftParam(), (int)queryObj.tree->getQuery()->getRightParam());
	}
	else if (queryObj.tree->getQuery()->getType() == relation::modifies) {
		success = PKB.modifies((int)queryObj.tree->getQuery()->getLeftParam(), queryObj.tree->getQuery()->getRightParam());
	}
	else if (queryObj.tree->getQuery()->getType() == relation::uses) {
		success = PKB.uses((int)queryObj.tree->getQuery()->getLeftParam(), queryObj.tree->getQuery()->getRightParam());
	}
	//else if (queryObj.tree->getQuery()->getType() == relation::pattern) {
	//	cout << "pattern processing yet to finish" << endl;
	//}
	else {
		cout << "Yet to be handled (from processSuchThat()) - What case is this?" << endl;
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

//perheps not need since its covered in processVariableClause()
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

