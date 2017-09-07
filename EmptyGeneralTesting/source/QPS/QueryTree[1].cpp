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
#include "QueryTree.h"


QueryTree::QueryTree() {

	firstQuery = NULL;
	currQueryNode = NULL;
	firstPattern = NULL;
	currPatternNode = NULL;
	lastAddedQuery = NULL;
	lastAddedPattern = NULL;

}

QueryNode* QueryTree::getQuery() {

	if (currQueryNode != NULL) {

		currQueryNode = currQueryNode->getNext();

		return currQueryNode;
	}

	else {

		currQueryNode = firstQuery;

		return currQueryNode;
	}
}

PatternNode* QueryTree::getPattern() {

	if (currPatternNode != NULL) {

		currPatternNode = currPatternNode->getNext();

		return currPatternNode;

	}

	else {

		currPatternNode = firstPattern;

		return currPatternNode;

	}
}

//Add new query into the QueryTree
void QueryTree::addQuery(QueryNode* query) {

	//If query tree is empty, create the first QueryNode in the tree
	if (firstQuery == NULL) {

		if (firstQuery == NULL) {

			firstQuery = query;
			lastAddedQuery = firstQuery;

		}

		else {

			lastAddedQuery->setNext(query);
			lastAddedQuery = lastAddedQuery->getNext();

		}
	}
}

void QueryTree::addPattern(PatternNode* pattern) {

		//If query tree is empty, create the first PatternNode in the tree
		if(firstPattern == NULL) {

			firstPattern = pattern;
			lastAddedPattern = firstPattern;

		}

		else {

			lastAddedPattern->setNext(pattern);
			lastAddedPattern = lastAddedPattern->getNext();

		}
	}
