﻿#pragma once
#include "GRB.h"

#define GRB_ERROR_SERIES 130
#define NS(n) GRB::Rule::Chain::N(n)
#define TS(n) GRB::Rule::Chain::T(n)
#define ISNS(n)	GRB::Rule::Chain::isN(n)

namespace GRB
{
	Greibach greiibach(NS('S'), TS('$'),				
		6,											
		Rule(NS('S'), GRB_ERROR_SERIES + 0,
			12,
			Rule::Chain(8, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S')),
			Rule::Chain(7,  TS('m'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}')),
			Rule::Chain(7,  TS('m'), TS('{'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S')),
			Rule::Chain(6,  TS('m'), TS('{'), TS('r'), NS('E'), TS(';'), TS('}')),
			Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S')),
			Rule::Chain(12, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}')),
			Rule::Chain(12, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S')),
			Rule::Chain(11, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), TS('r'), NS('E'), TS(';'), TS('}')),
			Rule::Chain(12, TS('t'), TS('f'), TS('i'), TS('('), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S')),
			Rule::Chain(11, TS('t'), TS('f'), TS('i'), TS('('), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}')),
			Rule::Chain(11, TS('t'), TS('f'), TS('i'), TS('('), TS(')'), TS('{'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S')),
			Rule::Chain(10, TS('t'), TS('f'), TS('i'), TS('('), TS(')'), TS('{'), TS('r'), NS('E'), TS(';'), TS('}'))
		),
		Rule(NS('N'), GRB_ERROR_SERIES + 1,			
			16,		
			Rule::Chain(4, TS('d'), TS('t'), TS('i'), TS(';')),
			Rule::Chain(7, TS('d'), TS('t'), TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(3, TS('r'), NS('E'), TS(';')),
			Rule::Chain(5, TS('d'), TS('t'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(7, TS('d'), TS('t'), TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(4, TS('r'), NS('E'), TS(';'), NS('N')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(5, TS('i'), TS('='), NS('M'), TS(';'), NS('N')),
			Rule::Chain(4, TS('i'), TS('='), NS('M'), TS(';')),
			Rule::Chain(3, TS('p'), NS('E'), TS(';')),
			Rule::Chain(4, TS('p'), NS('E'), TS(';'), NS('N')),
			Rule::Chain(3, TS('n'), NS('i'), TS(';')),
			Rule::Chain(4, TS('n'), NS('i'), TS(';'), NS('N')),

			Rule::Chain(7, TS('?'), TS('('), NS('E'), TS(')'), TS('{'), NS('N'), TS('}')),
			Rule::Chain(8, TS('?'), TS('('), NS('E'), TS(')'), TS('{'), NS('N'), TS('}'), NS('N'))
		),
		Rule(NS('E'), GRB_ERROR_SERIES + 2,			
			9,		
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
			Rule::Chain(3, TS('i'), TS('('), TS(')')),
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M'))

		),
		Rule(NS('W'), GRB_ERROR_SERIES + 3,			
			4,		
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W'))

		),
		Rule(NS('F'), GRB_ERROR_SERIES + 4,			
			2,		
			Rule::Chain(2, TS('t'), TS('i')),
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F'))

		),
		Rule(NS('M'), GRB_ERROR_SERIES + 2,			
			8,		
			Rule::Chain(2, TS('|'), NS('E')),
			Rule::Chain(3, TS('|'), NS('E'), NS('M')),
			Rule::Chain(2, TS('&'), NS('E')),
			Rule::Chain(3, TS('&'), NS('E'), NS('M')),
			Rule::Chain(2, TS('!'), NS('E')),
			Rule::Chain(3, TS('!'), NS('E'), NS('M')),
			Rule::Chain(2, TS('^'), NS('E')),
			Rule::Chain(3, TS('^'), NS('E'), NS('M'))
		)
	);
}

