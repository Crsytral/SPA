#pragma once
#include "Token.h"
class VarToken :
	public Token
{
public:
	VarToken(string v);
	~VarToken();
};

