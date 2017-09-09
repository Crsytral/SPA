#pragma once

#define QUERYPARSER_H
#include "QueryObject.h"

class QueryParser {

public:
	QueryParser();
	QueryObject QueryParser::getQueryObj(std::string);
};

