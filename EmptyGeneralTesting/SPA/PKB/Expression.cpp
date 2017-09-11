/*
Implementation of methods in Expression.h header file
*/
#include <stack>
#include <typeinfo>
using namespace std;

#include "Expression.h"
#include "LeafNode.h"
#include "BopNode.h"

void Expression::buildSyntaxTree(queue<Token> tokens) {
	vector<Token> v;
	while (!tokens.empty()) {
		v.push_back(tokens.front());
		tokens.pop();
	}
	Node* curr;
	int s = v.size();
	stack<BopNode*> st;
	//set last token as root node
	Token last = v[s - 1];
	if (last.isNum() || last.isVar()) {
		LeafNode l(last.getValue());
		syntaxTree = static_cast<Node*>(&l);
		if (last.isVar()) {
			Variable v(last.getValue());
			usedVariables.push_back(&v);
		}
	}
	else {
		BopNode l(last.getValue(), NULL, NULL);
		syntaxTree = static_cast<Node*>(&l);
		st.push(&l);
	}
	//set root node as current node
	curr = syntaxTree;
	//for each element from right to left, excluding last
	for (int i = s - 2; i > -1; i--) {
		//create a node for it
		Token tk = v[i];
		Node* nodeProcessing;
		bool canHaveMoreChildren = false;
		if (tk.isNum() || tk.isVar()) {
			LeafNode l(tk.getValue());
			nodeProcessing = static_cast<Node*>(&l);
			if (tk.isVar()) {
				Variable v(tk.getValue());
				usedVariables.push_back(&v);
			}
		}
		else {
			BopNode l(tk.getValue(), NULL, NULL);
			nodeProcessing = static_cast<Node*>(&l);
			st.push(&l);
		}
		//if current node cannot have more children, search for first parent/grandparent
		//that can have more children and set it as current node
		if (typeid(*curr) == typeid(LeafNode) ||
			(typeid(*curr) == typeid(BopNode) && static_cast<BopNode*>(curr)->isFilled())) {
			while (!st.empty()) {
				if (st.top()->isFilled()) st.pop();
			}
			curr = st.top();
		}
		//append new node to curr
		static_cast<BopNode*>(curr)->append(nodeProcessing);
		curr = nodeProcessing;
	}
}
/*
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
if (top.isNum()) {
left = LeafNode(top.getValue());
}
else if (top.isVar()) {
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
if (top.isNum()) {
right = LeafNode(top.getValue());
}
if (top.isVar()) {
Variable v(top.getValue());
usedVariables.push_back(&v);
right = LeafNode(top.getValue());
}

Token secondTop = s.top();
s.pop();
if (secondTop.isNum()) {
left = LeafNode(top.getValue());
}
if (secondTop.isVar()) {
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
*/


Expression::Expression(queue<Token> tokens) {
	buildSyntaxTree(tokens);
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
	return false;
}

