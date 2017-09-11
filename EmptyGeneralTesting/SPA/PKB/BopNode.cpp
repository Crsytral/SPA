#include "BopNode.h"
#include "LeafNode.h"

BopNode::BopNode(string c, Node* l, Node* r) {
	content = c;
	left = l;
	right = r;
	empty = false;
}

void BopNode::append(Node* n) {
	if (right == NULL) {
		right = n;
	}
	else {
		if (left == NULL) {
			left = n;
		}
	}
}

Node* BopNode::getLeft() {
	return left;
}

Node* BopNode::getRight() {
	return right;
}

bool BopNode::isFilled() {
	return (left != NULL && right != NULL);
}

bool BopNode::equals(BopNode* other) {
	if (content.compare(other->getContent()) != 0) return false;
	bool flagLeft, flagRight;
	if (typeid(*other->getLeft()) == typeid(LeafNode) && typeid(*left) == typeid(LeafNode)) {
		flagLeft = static_cast<LeafNode*>(other->getLeft())->equals(static_cast<LeafNode*>(left));
	}
	else if (typeid(*other->getLeft()) == typeid(BopNode) && typeid(*left) == typeid(BopNode)) {
		flagLeft = static_cast<BopNode*>(other->getLeft())->equals(static_cast<BopNode*>(left));
	}
	else {
		flagLeft = false;
	}

	if (typeid(*other->getRight()) == typeid(LeafNode) && typeid(*right) == typeid(LeafNode)) {
		flagRight = static_cast<LeafNode*>(other->getRight())->equals(static_cast<LeafNode*>(right));
	}
	else if (typeid(*other->getRight()) == typeid(BopNode) && typeid(*right) == typeid(BopNode)) {
		flagRight = static_cast<BopNode*>(other->getRight())->equals(static_cast<BopNode*>(right));
	}
	else {
		flagRight = false;
	}

	if (flagLeft && flagRight) return true;
	else return false;
}

bool BopNode::contains(Node* other) {
	if (typeid(*other) == typeid(BopNode) && equals(static_cast<BopNode*>(other))) {
		return true;
	}
	bool flagLeft = (typeid(*left) == typeid(BopNode) ? static_cast<BopNode*>(left)->contains(other) : static_cast<LeafNode*>(left)->contains(other));
	bool flagRight = (typeid(*right) == typeid(BopNode) ? static_cast<BopNode*>(right)->contains(other) : static_cast<LeafNode*>(right)->contains(other));
	if (flagLeft || flagRight) return true;
	else return false;
}

