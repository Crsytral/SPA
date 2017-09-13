//header guard
#ifndef QUERYEVALUATOR_H
#define QUERYEVALUATOR_H	

#include <string>
#include "../QPS/QueryObject.h"
#include "../QPS/Result.h"
#include "../PKB/PKB.h"

using namespace std;

class QueryEvaluator {
private:
	QueryObject queryObj;
	PKB* pkb;
	Result rawResult;

	Result processQuery();
	bool processVariableClause();
	bool processRawResult();
	bool processSuchThat();
	bool processPattern();
	string convertIntVectorToString(vector<int> intVector);
	string convertStringVectorToString(vector<string> stringVector);
	//bool processSecondClause(Result result);
	//Result combineResults(Result r1, Result r2, Result r3);

public:
	QueryEvaluator(PKB* pkb, QueryObject query);

	Result getRawResult();
};

//End guard
#endif 