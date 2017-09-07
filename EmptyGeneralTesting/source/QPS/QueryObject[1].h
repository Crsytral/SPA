#pragma once

#include "QueryTree.h"
#include "Synonyms.h"

struct QueryObject {
	QueryTree* tree;
	Synonyms* synonym;
};