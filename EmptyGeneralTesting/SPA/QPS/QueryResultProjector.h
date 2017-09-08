//header guard at start of header file
#ifndef QUERYRESULTPROJECTOR_H
#define QUERYRESULTPROJECTOR_H	
#include "Result.h"

using namespace std;

class QueryResultProjector {
private:
	Result result;

public:
	QueryResultProjector(Result result);
	string sortResult(Result, int);
	void print();
};

//End guard at bottom of header file
#endif 