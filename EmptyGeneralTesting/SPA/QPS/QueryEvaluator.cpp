#include "QueryEvaluator.h"
#include <vector>
#include <iterator>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "SyntaticType.h"

QueryEvaluator::QueryEvaluator(QueryObject q) { //string q to be replaced with QueryObj
	queryObj = q;
	rawResult = processQuery();
}

Result QueryEvaluator::processQuery() {
	Result result;
	if (processVariableClause() == true) {
		processSuchThat();
		processPattern();
	}
	//combineResults(r1, r2, r3);
	return result;
}

//Process only the variable clauses (Synonym) of the query. Retrieves all relevant statements from PKB based on the type of variable(Eg:Assign/Variable/Statement)
//AfterMerged with PreProcessor, this method handles Select portion of PQL as well.
bool QueryEvaluator::processVariableClause() {
	vector <string> temp;
	vector <SyntaticData*> symbolTable = queryObj.synonym->getQuery();
	if (symbolTable.size() == 0) { //if 0 means no symbol = return nth
		return false;
	}else{
		for each (SyntaticData *data in symbolTable)
		{
			if (data->getResult() == 1){
				cout << data->getVariableType() << endl;
				// to check for empty or filter out -1 during projector stage
				if (data->getVariableType() == syntatic_type::assignment) {
					rawResult.setAsgnData(convertIntVectorToString(PKB.getAllAssignStatement()));
				}
				else if (data->getVariableType() == syntatic_type::variable) {
					rawResult.setAsgnData(convertIntVectorToString(PKB.getAllVariables()));
				}
				else if (data->getVariableType() == syntatic_type::statement) {
					rawResult.setAsgnData(convertIntVectorToString(PKB.getAllStatements()));
				}
				else if (data->getVariableType() == syntatic_type::whileLoop) {
					rawResult.setAsgnData(convertIntVectorToString(PKB.getAllWhileStatement()));
				}
				else if (data->getVariableType() == syntatic_type::ifelse) {
					rawResult.setAsgnData(convertIntVectorToString(PKB.getAllIfStatement()));
				}
				else if (data->getVariableType() == syntatic_type::procedure) {
					rawResult.setAsgnData(PKB.getAllProcedures());
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
	bool success = false;
	//checks if both inputs(L param and R param) are int
	if ((queryObj.tree->getQuery()->getLeftParam()->getType() == syntatic_type::integer) && (queryObj.tree->getQuery()->getRightParam()->getType() == syntatic_type::integer)){
		if (queryObj.tree->getQuery()->getType() == relation::follows) {
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
	}
	else if ((queryObj.tree->getQuery()->getLeftParam()->getType() == syntatic_type::integer) && (queryObj.tree->getQuery()->getRightParam()->getType() != syntatic_type::integer)) { //Left Param is Int
		if (queryObj.tree->getQuery()->getType() == relation::follows) {
			int stmtIndex = PKB.follows((int)queryObj.tree->getQuery()->getLeftParam());
			if (stmtIndex != -1){
				success = true;
				rawResult.setQueryResult(stmtIndex + "");
			}else
				success = false;
		}
		else if (queryObj.tree->getQuery()->getType() == relation::followsStar) {
			vector<int> stmts = PKB.followStar((int)queryObj.tree->getQuery()->getLeftParam());
			if (stmts.front() != -1) {
				success = true;
				rawResult.setQueryResult(convertIntVectorToString(stmts));
			}
			else
				success = false;
		}
		else if (queryObj.tree->getQuery()->getType() == relation::parent) {
			vector<int> stmts = PKB.parents((int)queryObj.tree->getQuery()->getLeftParam());
			if (stmts.front() != -1){
				success = true;
				rawResult.setQueryResult(convertIntVectorToString(stmts));
			}
			else
				success = false;
		}
		else if (queryObj.tree->getQuery()->getType() == relation::parentStar) {
			vector<int> stmts = PKB.parentStar((int)queryObj.tree->getQuery()->getLeftParam());
			if (stmts.front() != -1) {
				success = true;
				rawResult.setQueryResult(convertIntVectorToString(stmts));
			}
			else
				success = false;
		}
		else if (queryObj.tree->getQuery()->getType() == relation::modifies) {
			rawResult.setQueryResult(PKB.modifiedBy((int)queryObj.tree->getQuery()->getLeftParam()));
			success = true;
		}
		else if (queryObj.tree->getQuery()->getType() == relation::uses) {
			rawResult.setQueryResult(PKB.usedBy((int)queryObj.tree->getQuery()->getLeftParam()));
			success = true;
		}
	}
	else if ((queryObj.tree->getQuery()->getLeftParam()->getType() != syntatic_type::integer) && (queryObj.tree->getQuery()->getRightParam()->getType() == syntatic_type::integer)) { //Right Param is Int
		if (queryObj.tree->getQuery()->getType() == relation::follows) {
			int stmtIndex = PKB.followsBy((int)queryObj.tree->getQuery()->getRightParam());
			if (stmtIndex != -1) {
				success = true;
				rawResult.setQueryResult(stmtIndex + "");
			}
			else
				success = false;
		}
		else if (queryObj.tree->getQuery()->getType() == relation::followsStar) {
			vector<int> stmts = PKB.followStarBy((int)queryObj.tree->getQuery()->getRightParam());
			if (stmts.front() != -1) {
				success = true;
				rawResult.setQueryResult(convertIntVectorToString(stmts));
			}
			else
				success = false;
		}
		else if (queryObj.tree->getQuery()->getType() == relation::parent) {
			vector<int> stmts = PKB.parentedBy((int)queryObj.tree->getQuery()->getRightParam());
			if (stmts.front() != -1) {
				success = true;
				rawResult.setQueryResult(convertIntVectorToString(stmts));
			}
			else
				success = false;
		}
		else if (queryObj.tree->getQuery()->getType() == relation::parentStar) {
			vector<int> stmts = PKB.parentStarBy((int)queryObj.tree->getQuery()->getRightParam());
			if (stmts.front() != -1) {
				success = true;
				rawResult.setQueryResult(convertIntVectorToString(stmts));
			}
			else
				success = false;
		}
		else if (queryObj.tree->getQuery()->getType() == relation::modifies) {
			vector<int> stmts = PKB.modifies(queryObj.tree->getQuery()->getRightParam());
			if (stmts.front() != -1) {
				success = true;
				rawResult.setQueryResult(convertIntVectorToString(stmts));
			}
			else
				success = false;
		}
		else if (queryObj.tree->getQuery()->getType() == relation::uses) {
			vector<int> stmts = PKB.uses(queryObj.tree->getQuery()->getRightParam());
			if (stmts.front() != -1) {
				success = true;
				rawResult.setQueryResult(convertIntVectorToString(stmts));
			}
			else
				success = false;
		}

	}else{ //both not int
		if (queryObj.tree->getQuery()->getType() == relation::follows) {
			vector<pair<int, int>> possibleCombinations = PKB.follows();
			if (possibleCombinations.front().first != -1 && possibleCombinations.front().second != -1) {
				success = true;

			}
			else
				success = false;
		}
		else if (queryObj.tree->getQuery()->getType() == relation::followsStar) {
			vector<pair<int, int>> possibleCombinations = PKB.followStar();
			if (possibleCombinations.front().first != -1 && possibleCombinations.front().second != -1) {
				success = true;
				
			}
			else
				success = false;
		}
		else if (queryObj.tree->getQuery()->getType() == relation::parent) {
			vector<pair<int, int>> possibleCombinations = PKB.parents();
			if (possibleCombinations.front().first != -1 && possibleCombinations.front().second != -1) {
				success = true;
				
			}
			else
				success = false;
		}
		else if (queryObj.tree->getQuery()->getType() == relation::parentStar) {
			vector<pair<int, int>> possibleCombinations = PKB.parentStar();
			if (possibleCombinations.front().first != -1 && possibleCombinations.front().second != -1) {
				success = true;
				
			}
			else
				success = false;
		}
		else if (queryObj.tree->getQuery()->getType() == relation::modifies) {
			vector<pair<int, string>> possibleCombinations = PKB.modifies();
			if (possibleCombinations.front().first != -1 && possibleCombinations.front().second != "") {
				success = true;

			}
			else
				success = false;
		}
		else if (queryObj.tree->getQuery()->getType() == relation::uses) {
			vector<pair<int, string>> possibleCombinations = PKB.uses();
			if (possibleCombinations.front().first != -1 && possibleCombinations.front().second != "") {
				success = true;

			}
			else
				success = false;
		}
	}

	if (success == true)
		rawResult.setValid(true);
		processRawResult();
	return true;
}

bool QueryEvaluator::processPattern() {
	bool success = false;

	return true;
}

Result QueryEvaluator::getRawResult() {
	return rawResult;
}

//Used to further clean/filter the rawResults before passing to the QueryResultProjector
//Or can be moved to QueryResultProjector
bool QueryEvaluator::processRawResult() {
	//to combine asgnData & queryResult (filter out duplicates and -1 etc...?) 
	return true;
}

string QueryEvaluator::convertIntVectorToString(vector<int> intVector) {
	stringstream ss;
	copy(intVector.begin(), intVector.end(), ostream_iterator<int>(ss, " "));
	string s = ss.str();
	s = s.substr(0, s.length() - 1);  // get rid of the trailing space
	return s;
}