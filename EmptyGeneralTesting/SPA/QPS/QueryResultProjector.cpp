#include "QueryResultProjector.h"
#include "stdafx.h"
#include <iostream>

QueryResultProjector::QueryResultProjector(Result r) {
	result = r;
}

string QueryResultProjector::sortResult(Result r, int sortOption) {
	if (sortOption == 0) {
		return "This is 0";
	}
	else {
		return "This is 1";
	}
}

void QueryResultProjector::print() {
	cout << result.toString();
}