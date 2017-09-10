#include "Node.h"

Node::Node() {
	empty = true;
}

Node::Node(string c) {
	content = c;
	empty = false;
}

string Node::getContent() {
	return content;
}

bool Node::isEmpty() {
	return empty;
}