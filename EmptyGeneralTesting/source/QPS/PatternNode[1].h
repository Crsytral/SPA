#pragma once

#define PATTERNNODE_H

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

#include "ParameterNode.h"

class PatternNode {
	ParameterNode* leftParam;
	ParameterNode* middleParam;
	ParameterNode* rightParam;
	PatternNode* nextPattern;

public:
	PatternNode(ParameterNode*, ParameterNode*, ParameterNode*);
	PatternNode* getNext();
	ParameterNode* getLeftParam();
	ParameterNode* getMiddleParam();
	ParameterNode* getRightParam();

	void setNext(PatternNode*);
};