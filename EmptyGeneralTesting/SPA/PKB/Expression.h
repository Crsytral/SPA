#pragma once
/*
To be implemented by Lu Yu
*/
#include <string>
#include <vector>
#include <queue>
using namespace std;

#include "Variable.h"
#include "../Parser/Token.h"
#include "Node.h"
class Variable;

class Expression {
private:
	Node* syntaxTree;
	vector<Variable*> usedVariables;
	void buildSyntaxTree(queue<Token> tokens);
public:
	Expression(queue<Token> tokens);
	Node* getSyntaxTree();
	vector<Variable*> getUsedVariable();
	bool equals(Expression* other);
	bool contains(Expression* other);
};