/*
Implementation of methods in Expression.h header file
*/
#include <stack>
#include <typeinfo>
using namespace std;

#include "Expression.h"
#include "LeafNode.h"
#include "BopNode.h"

Node* Expression::buildSyntaxTree(queue<Token> tokens) {
	stack<Token> s;
	Node bufferNode = Node();
	Node leafNode = Node();
	while (!tokens.empty()) {
		Token tokenToBeProcessed = tokens.front();
		tokens.pop();
		//push all operand tokens into stack
		if (tokenToBeProcessed.isOperand()) {
			s.push(tokenToBeProcessed);
		}
		//whenever encounter an operator, process 2 tokens from the stack
		if (tokenToBeProcessed.isOperator()) {
			Node right;
			Node left;
			if (!bufferNode.isEmpty()) {
				right = bufferNode;
				Token top = s.top();
				s.pop();
				if (top.isNumToken()) {
					left = LeafNode(top.getValue());
				}
				else if (top.isVarToken()) {
					Variable v(top.getValue());
					usedVariables.push_back(&v);
					left = LeafNode(top.getValue());
				}
				bufferNode = BopNode(tokenToBeProcessed.getValue(),
					&left,
					&right);
				continue;

			}
			else {
				while (!s.empty()) {
					Token top = s.top();
					s.pop();
					if (top.isNumToken()) {
						right = LeafNode(top.getValue());
					}
					if (top.isVarToken()) {
						Variable v(top.getValue());
						usedVariables.push_back(&v);
						right = LeafNode(top.getValue());
					}

					Token secondTop = s.top();
					s.pop();
					if (secondTop.isNumToken()) {
						left = LeafNode(top.getValue());
					}
					if (secondTop.isVarToken()) {
						Variable v(secondTop.getValue());
						usedVariables.push_back(&v);
						left = LeafNode(secondTop.getValue());
					}
					bufferNode = BopNode(tokenToBeProcessed.getValue(),
						&left,
						&right);
					continue;
				}
			}
		}
	}
	return &bufferNode;
}

Expression::Expression(queue<Token> tokens) {
	Node* root = buildSyntaxTree(tokens);
	syntaxTree = root;
}

Node* Expression::getSyntaxTree() {
	return syntaxTree;
}

vector<Variable*> Expression::getUsedVariable() {
	return usedVariables;
}

bool Expression::equals(Expression* other) {
	Node* rootOther = other->getSyntaxTree();
	if (typeid(*rootOther) == typeid(LeafNode) && typeid(*syntaxTree) == typeid(LeafNode)) {
		return static_cast<LeafNode*>(rootOther)->equals(static_cast<LeafNode*>(syntaxTree));
	}
	else if (typeid(*rootOther) == typeid(BopNode) && typeid(*syntaxTree) == typeid(BopNode)) {
		return static_cast<BopNode*>(rootOther)->equals(static_cast<BopNode*>(syntaxTree));
	}
	else {
		return false;
	}
}
bool Expression::contains(Expression* other) {
	Node* rootOther = other->getSyntaxTree();
	if (typeid(*syntaxTree) == typeid(LeafNode)) {
		return static_cast<LeafNode*>(syntaxTree)->contains(rootOther);
	}
	else if (typeid(*syntaxTree) == typeid(BopNode)) {
		return static_cast<BopNode*>(syntaxTree)->contains(rootOther);
	}
}

