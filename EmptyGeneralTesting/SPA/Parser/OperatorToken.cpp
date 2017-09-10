#include "OperatorToken.h"



OperatorToken::OperatorToken(string v) : Token(v)
{
	type = "O";
}

OperatorToken::~OperatorToken()
{
}
