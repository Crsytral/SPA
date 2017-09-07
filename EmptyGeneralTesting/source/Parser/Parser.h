#pragma once
#include <string>
#include <vector>
#include "Token.h"


class Parser
{
private:
	string text;
	int line;
	int position;
	Token currentToken;
	char currentChar;

	char buffer[50];
	int bufferPosition;
	void advance();

public:
	Parser(string text);
	Token lex();
};