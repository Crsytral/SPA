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
#include "PatternNode.h"

ParameterNode* leftParam;
ParameterNode* middleParam;
ParameterNode* rightParam;
PatternNode* nextPattern;

PatternNode::PatternNode(ParameterNode* firstParam, ParameterNode* secondParam, ParameterNode* thirdParam) {

	leftParam = firstParam;
	middleParam = secondParam;
	rightParam = thirdParam;
	nextPattern = NULL;

}

PatternNode* PatternNode::getNext() {

	return nextPattern;

}

ParameterNode* PatternNode::getLeftParam() {

	return leftParam;

}

ParameterNode* PatternNode::getMiddleParam() {

	return middleParam;

}

ParameterNode* PatternNode::getRightParam() {

	return rightParam;

}

void PatternNode::setNext(PatternNode* pattern) {

	nextPattern = pattern;

}
