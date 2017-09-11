#pragma once
#include "Node.h"

class BopNode : public Node {
private:
	Node* left;
	Node* right;
public:
	BopNode(string c, Node* l, Node* r);
	void append(Node* n);
	Node* getLeft();
	Node* getRight();
	bool equals(BopNode* other);
	bool contains(Node* other);
	bool isFilled();
};