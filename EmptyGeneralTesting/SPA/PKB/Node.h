#pragma once
#include <string>
using namespace std;

/*
Represent an abstract Node in the expression tree.
*/
class Node {
protected:
	string content;
	bool empty = true;
public:
	Node();
	Node(string c);
	string getContent();
	bool isEmpty();
};