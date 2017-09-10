#pragma once
#include "Token.h"
class OperatorToken :
	public Token
{
public:
	OperatorToken(string v);
	~OperatorToken();
};
