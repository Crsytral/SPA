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


ParameterNode::ParameterNode(syntatic_type type, string p) {
	SYNTATIC_TYPE = type;
	parameter = p;
}

syntatic_type ParameterNode::getType() {
	return SYNTATIC_TYPE;
}

string ParameterNode::getParameter() {
	return parameter;
}