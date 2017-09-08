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
#include "QueryNode.h"

/*
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
*/

QueryNode::QueryNode(relation type, ParameterNode* leftNode, ParameterNode* rightNode) {
	relationType = type;
	leftParameter = leftNode;
	rightParameter = rightNode;
	nextQuery = NULL;
}
	

//Returns the type of query for example modifies, follows, calls, parent, etc
relation QueryNode::getType() {

	return relationType;

}

//Returns the next query
QueryNode* QueryNode::getNext() {

	return nextQuery;

}

ParameterNode* QueryNode::getLeftParam() {

	return leftParameter;

}

ParameterNode* QueryNode::getRightParam() {

	return rightParameter;

}

void QueryNode::setNext(QueryNode* query) {

	nextQuery = query;

}

