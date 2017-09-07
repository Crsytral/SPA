#pragma once
#define PARAMETERNODE_H

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
#include "SyntaticType.h"

using namespace std;

class ParameterNode {
	syntatic_type SYNTATIC_TYPE;
	std::string parameter;

public:
	ParameterNode(syntatic_type, string);
	syntatic_type getType();
	std::string getParameter();
};
