#include <typeinfo>
using namespace std;
#include "LeafNode.h"

LeafNode::LeafNode(string c) {
	content = c;
	empty = false;
}

bool LeafNode::equals(LeafNode* other) {
	if (content.compare(other->getContent()) == 0) return true;
	else return false;
}

bool LeafNode::contains(Node* other) {
	if (typeid(*other) == typeid(LeafNode)) {
		return equals(static_cast<LeafNode*>(other));
	}
	return false;
}