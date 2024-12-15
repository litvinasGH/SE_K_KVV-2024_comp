#pragma once
#include "stdafx.h"

namespace CodeGen
{
	void Head(LT::lexAndIdTable& lex, Out::OUT& log);
	void Const(LT::lexAndIdTable& lex, Out::OUT& log);
	void Data(LT::lexAndIdTable& lex, Out::OUT& log);
	void Code(LT::lexAndIdTable& lex, Out::OUT& log);
	void Generation(LT::lexAndIdTable& lex, Out::OUT& log);
}
