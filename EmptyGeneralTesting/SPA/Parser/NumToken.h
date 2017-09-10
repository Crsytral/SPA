#pragma once
#include "Token.h"
class NumToken :
	public Token
{
public:
	NumToken(string v);
	~NumToken();
};

