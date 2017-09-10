#pragma once
#include "Node.h"

class LeafNode : public Node {
public:
	LeafNode(string c);
	bool equals(LeafNode* other);
	bool contains(Node* other);
};