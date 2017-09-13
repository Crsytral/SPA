#include "../QPS/QueryEvaluator.h"
#include "../QPS/SyntaticType.h"
#include "../PKB/Expression.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

QueryEvaluator::QueryEvaluator(PKB* pkb, QueryObject q) {
	QueryEvaluator::pkb = pkb;
	queryObj = q;
	rawResult = processQuery();
}

Result QueryEvaluator::processQuery() {
	Result result;
	if (processVariableClause() == true) {
		processSuchThat();
		//processPattern();
	}
	return result;
}

//Process only the variable clauses (Synonym) of the query. Retrieves all relevant statements from PKB based on the type of variable(Eg:Assign/Variable/Statement)
//AfterMerged with PreProcessor, this method handles Select portion of PQL as well.
bool QueryEvaluator::processVariableClause() {
	vector <string> temp;
	Synonyms* symbolTable = queryObj.synonym;
	if (symbolTable->getSize() == NULL || symbolTable->getSize()==0) { //if 0 means no symbol = return nth
		return false;
	}else{
		vector<SyntaticData*> tmp = symbolTable->getQuery();
		vector<SyntaticData*>::iterator i;
		for (i = tmp.begin(); i != tmp.end(); i++)
		{
			if ((**i).getResult() == 1){
				//cout << (**i).getVariableType() << endl;
				// to check for empty or filter out -1 during projector stage
				if ((**i).getVariableType() == syntatic_type::assignment) {
					rawResult.setAsgnData(convertIntVectorToString(pkb->getAllAssignStatements()));
				}
				else if ((**i).getVariableType() == syntatic_type::variable) {
					rawResult.setAsgnData(convertStringVectorToString(pkb->getAllVariables()));
				}
				else if ((**i).getVariableType() == syntatic_type::statement) {
					rawResult.setAsgnData(convertIntVectorToString(pkb->getAllStatements()));
				}
				else if ((**i).getVariableType() == syntatic_type::whileLoop) {
					rawResult.setAsgnData(convertIntVectorToString(pkb->getAllWhileStatements()));
				}
				else if ((**i).getVariableType() == syntatic_type::ifelse) {
					rawResult.setAsgnData(convertIntVectorToString(pkb->getAllIfStatements()));
				}
				else if ((**i).getVariableType() == syntatic_type::procedure) {
					rawResult.setAsgnData(convertStringVectorToString(pkb->getAllProcedures()));
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
	QueryNode* queryNode = queryObj.tree->getQuery();
	//checks if both inputs(L param and R param) are int
	if ((queryNode->getLeftParam()->getType() == syntatic_type::integer) && (queryNode->getRightParam()->getType() == syntatic_type::integer)){
		if (queryNode->getType() == relation::follows) {
			success = pkb->follows(atoi(queryNode->getLeftParam()->getParameter().c_str()), atoi(queryNode->getRightParam()->getParameter().c_str()));
		}
		else if (queryNode->getType() == relation::followsStar) {
			success = pkb->followStar(atoi(queryNode->getLeftParam()->getParameter().c_str()), atoi(queryNode->getRightParam()->getParameter().c_str()));
		}
		else if (queryNode->getType() == relation::parent) {
			success = pkb->parents(atoi(queryNode->getLeftParam()->getParameter().c_str()), atoi(queryNode->getRightParam()->getParameter().c_str()));
		}
		else if (queryNode->getType() == relation::parentStar) {
			success = pkb->parentStar(atoi(queryNode->getLeftParam()->getParameter().c_str()), atoi(queryNode->getRightParam()->getParameter().c_str()));
		}
		else if (queryNode->getType() == relation::modifies) {
			success = pkb->modifies(atoi(queryNode->getLeftParam()->getParameter().c_str()), queryNode->getRightParam()->getParameter());
		}
		else if (queryNode->getType() == relation::uses) {
			success = pkb->uses(atoi(queryNode->getLeftParam()->getParameter().c_str()), queryNode->getRightParam()->getParameter());
		}
		//else if (queryObj.tree->getQuery()->getType() == relation::pattern) {
		//	cout << "pattern processing yet to finish" << endl;
		//}
		else {
			cout << "Yet to be handled (from processSuchThat()) - What case is this?" << endl;
		}
	}
	else if ((queryNode->getLeftParam()->getType() == syntatic_type::integer) && (queryNode->getRightParam()->getType() != syntatic_type::integer)) { //Left Param is Int
		if (queryNode->getType() == relation::follows) {
			int stmtIndex = pkb->follows((int)queryNode->getLeftParam());
			if (stmtIndex != -1){
				success = true;
				rawResult.setQueryResult(stmtIndex + "");
			}else
				success = false;
		}
		else if (queryNode->getType() == relation::followsStar) {
			vector<int> stmts = pkb->followStar((int)queryNode->getLeftParam());
			if (stmts.front() != -1) {
				success = true;
				rawResult.setQueryResult(convertIntVectorToString(stmts));
			}
			else
				success = false;
		}
		else if (queryNode->getType() == relation::parent) {
			vector<int> stmts = pkb->parents((int)queryNode->getLeftParam());
			if (stmts.front() != -1){
				success = true;
				rawResult.setQueryResult(convertIntVectorToString(stmts));
			}
			else
				success = false;
		}
		else if (queryNode->getType() == relation::parentStar) {
			vector<int> stmts = pkb->parentStar((int)queryNode->getLeftParam());
			if (stmts.front() != -1) {
				success = true;
				rawResult.setQueryResult(convertIntVectorToString(stmts));
			}
			else
				success = false;
		}
		else if (queryNode->getType() == relation::modifies) {
			rawResult.setQueryResult(convertStringVectorToString(pkb->modifiedBy((int)queryNode->getLeftParam())));
			success = true;
		}
		else if (queryNode->getType() == relation::uses) {
			rawResult.setQueryResult(convertStringVectorToString(pkb->usedBy((int)queryNode->getLeftParam())));
			success = true;
		}
	}
	else if ((queryNode->getLeftParam()->getType() != syntatic_type::integer) && (queryNode->getRightParam()->getType() == syntatic_type::integer)) { //Right Param is Int
		if (queryNode->getType() == relation::follows) {
			int stmtIndex = pkb->followsBy((int)queryNode->getRightParam());
			if (stmtIndex != -1) {
				success = true;
				rawResult.setQueryResult(stmtIndex + "");
			}
			else
				success = false;
		}
		else if (queryNode->getType() == relation::followsStar) {
			vector<int> stmts = pkb->followStarBy((int)queryNode->getRightParam());
			if (stmts.front() != -1) {
				success = true;
				rawResult.setQueryResult(convertIntVectorToString(stmts));
			}
			else
				success = false;
		}
		else if (queryNode->getType() == relation::parent) {
			int stmts = pkb->parentedBy(atoi(queryNode->getRightParam()->getParameter().c_str()));
			if (stmts != -1) {
				success = true;
				rawResult.setQueryResult(stmts+"");
			}
			else
				success = false;
		}
		else if (queryNode->getType() == relation::parentStar) {
			vector<int> stmts = pkb->parentStarBy(atoi(queryNode->getRightParam()->getParameter().c_str()));
			if (stmts.front() != -1) {
				success = true;
				rawResult.setQueryResult(convertIntVectorToString(stmts));
			}
			else
				success = false;
		}
		else if (queryNode->getType() == relation::modifies) {
			vector<int> stmts = pkb->modifies(queryNode->getRightParam()->getParameter());
			if (stmts.front() != -1) {
				success = true;
				rawResult.setQueryResult(convertIntVectorToString(stmts));
			}
			else
				success = false;
		}
		else if (queryNode->getType() == relation::uses) {
			vector<int> stmts = pkb->uses(queryNode->getRightParam()->getParameter());
			if (stmts.front() != -1) {
				success = true;
				rawResult.setQueryResult(convertIntVectorToString(stmts));
			}
			else
				success = false;
		}

	}else{ //both not int
		if (queryNode->getType() == relation::follows) {
			vector<pair<int, int>> possibleCombinations = pkb->follows();
			if (possibleCombinations.front().first != -1 && possibleCombinations.front().second != -1) {
				success = true;

			}
			else
				success = false;
		}
		else if (queryNode->getType() == relation::followsStar) {
			vector<pair<int, int>> possibleCombinations = pkb->followStar();
			if (possibleCombinations.front().first != -1 && possibleCombinations.front().second != -1) {
				success = true;
				
			}
			else
				success = false;
		}
		else if (queryNode->getType() == relation::parent) {
			vector<pair<int, int>> possibleCombinations = pkb->parents();
			if (possibleCombinations.front().first != -1 && possibleCombinations.front().second != -1) {
				success = true;
				
			}
			else
				success = false;
		}
		else if (queryNode->getType() == relation::parentStar) {
			vector<pair<int, int>> possibleCombinations = pkb->parentStar();
			if (possibleCombinations.front().first != -1 && possibleCombinations.front().second != -1) {
				success = true;
				
			}
			else
				success = false;
		}
		else if (queryNode->getType() == relation::modifies) {
			vector<pair<int, string>> possibleCombinations = pkb->modifies();
			if (possibleCombinations.front().first != -1 && possibleCombinations.front().second != "") {
				success = true;

			}
			else
				success = false;
		}
		else if (queryNode->getType() == relation::uses) {
			vector<pair<int, string>> possibleCombinations = pkb->uses();
			if (possibleCombinations.front().first != -1 && possibleCombinations.front().second != "") {
				success = true;

			}
			else
				success = false;
		}
	}

	if (success == true){
		rawResult.setValid(true);
		processRawResult();
	}
	return true;
}

//Process the Pattern query of the PQL
bool QueryEvaluator::processPattern() {
	bool success = false;
	PatternNode* patternNode = queryObj.tree->getPattern();
	if (patternNode->getLeftParam()->getType() == syntatic_type::assignment) {
		string rightParam = patternNode->getRightParam()->getParameter();
		//check and remove "_" from first index and last index of rightParam
		if (rightParam.at(0) == '_' && rightParam.size()>=2) {
			rightParam = rightParam.substr(1, rightParam.size()-1);
		}
		if (rightParam.back() == '_' && rightParam.size()>=2) {
			rightParam = rightParam.substr(0, rightParam.size() - 2);
		}
		//Turn them into an Expression Var

		//Feed to PKB API
		//vector<int> stmts = PKB.getPattern(Expression leftPattern, Expression rightPattern);
		//if (stmts.front() != -1) {
		//	success = true;
		//	rawResult.setQueryResult(convertIntVectorToString(stmts));
		//}
		//else
			success = false;
	}

	if (success == true){
		rawResult.setValid(true);
	}
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

//Helper methods

//Converts a vector of interger into a string value
string QueryEvaluator::convertIntVectorToString(vector<int> intVector) {
	stringstream ss;
	copy(intVector.begin(), intVector.end(), ostream_iterator<int>(ss, " "));
	string s = ss.str();
	s = s.substr(0, s.length() - 1);  // get rid of the trailing space
	return s;
}

//converts a vector of string into a string value
string QueryEvaluator::convertStringVectorToString(vector<string> stringVector) {
	string s;
	s = accumulate(begin(stringVector), end(stringVector), s);
	return s;
}