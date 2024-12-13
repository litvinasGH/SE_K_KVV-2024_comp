#pragma once
#include "stdafx.h"
#include "In.h"

namespace Out {

	struct OUT
	{
		wchar_t outFile[PARM_MAX_SIZE];
		std::ofstream* stream;
	};

	static const OUT INITOUT{ L"", NULL };					
	OUT getOut(wchar_t outFile[]);							
	void WriteOut(OUT out, In::IN in);						
	void Close(OUT out);									
	void WriteError(OUT out, Error::ERROR e);
}