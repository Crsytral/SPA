#pragma once

#define QUERYTREE_H

#include "QueryNode.h"
#include "PatternNode.h"

class QueryTree {
	QueryNode* firstQuery;
	PatternNode* firstPattern;
	QueryNode* currQueryNode;
	PatternNode* currPatternNode;
	QueryNode* lastAddedQuery;
	PatternNode* lastAddedPattern;

public:
	QueryTree();
	QueryNode* getQuery();
	PatternNode* getPattern();

	void addQuery(QueryNode*);
	void addPattern(PatternNode*);
};

