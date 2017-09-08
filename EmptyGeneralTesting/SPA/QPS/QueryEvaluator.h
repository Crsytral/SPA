//header guard at start of header file
#ifndef QUERYEVALUATOR_H
#define QUERYEVALUATOR_H	

#include <string>
#include "Result.h"
#include "QueryObject.h"
#include "PKB.h"

using namespace std;

class QueryEvaluator {
private:
	QueryObject queryObj; //To be updated with actual "QueryObj" class
	PKB PKB; //To be updated with actual PKB class
	Result rawResult;

	bool processVariableClause();
	bool processSelect();
	//bool processSecondClause(Result result);
	bool processSuchThat();
	//Result combineResults(Result r1, Result r2, Result r3);

public:
	QueryEvaluator(QueryObject query);

	Result processQuery();
	Result getRawResult();
};

//End guard at bottom of header file
#endif 