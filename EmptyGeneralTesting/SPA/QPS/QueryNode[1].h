#pragma once

#define QUERYNODE_H

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
#include <string.h>
#include "ParameterNode.h"

enum relation {

	calls,
	callsStar,
	uses,
	follows,
	followsStar,
	parent,
	parentStar,
	modifies,
	next,
	nextStar,
	affects,
	affectsStar,
	isError,

};

class QueryNode {
	relation relationType;
	ParameterNode* leftParameter;
	ParameterNode* rightParameter;
	QueryNode* nextQuery;

public:
	QueryNode(relation, ParameterNode*, ParameterNode*);
	relation getType();
	QueryNode* getNext();
	ParameterNode* getLeftParam();
	ParameterNode* getRightParam();

	void setNext(QueryNode*);
};