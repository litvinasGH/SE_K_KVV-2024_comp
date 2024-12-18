#include "SEM.h"

void SemAnl(LT::LexTable lextable, IT::IdTable idtable) 
{
	for (int i = 0; i < lextable.size; i++) {
		if (lextable.table[i].lexema == 'i') {
			int e = i;
			if (idtable.table[lextable.table[i].idxTI].idtype == IT::F 
				&& idtable.table[lextable.table[i].idxTI].idxfirstLE != i) {
				std::queue<IT::Entry> parms;
				for (int j = lextable.table[i].idxTI + 1; j < idtable.size; j++) {
					if (idtable.table[j].idtype == IT::P) {
						parms.push(idtable.table[j]);
					}
					else {
						break;
					}
				}
				for (i += 2; lextable.table[i].lexema != ')'; i++) {
					if ((lextable.table[i].lexema == 'i' || lextable.table[i].lexema == 'l')) {
						if (parms.front().iddatatype != idtable.table[lextable.table[i].idxTI].iddatatype) {
							throw ERROR_THROW_SEM(140, lextable.table[e].sn)
						}
						else
							parms.pop();

						if (parms.empty() && lextable.table[i = 1].lexema != ')') {
							throw ERROR_THROW_SEM(140, lextable.table[e].sn)
						}
					}
				}
				if (!parms.empty()) {
					throw ERROR_THROW_SEM(140, lextable.table[e].sn)
				}
			}
			else if (idtable.table[lextable.table[i].idxTI].idtype == IT::V) {
				IT::IDDATATYPE dt = idtable.table[lextable.table[i].idxTI].iddatatype;
				for (int j = i + 1; lextable.table[j].lexema != ';'; j++) {
					if (lextable.table[j].lexema == '=') {
						for (j++; lextable.table[j].lexema != ';'; j++) {
							if ((lextable.table[j].lexema == 'i' || lextable.table[j].lexema == 'l')
								&& idtable.table[lextable.table[j].idxTI].iddatatype != dt) {
								throw ERROR_THROW_SEM(141, lextable.table[e].sn)
							}
						}
						break;
					}
				}
			}
		}
		else if (lextable.table[i].lexema == '?') {
			int e = i;
			for (i++; lextable.table[i].lexema != ';'; i++) {
				if (lextable.table[i].lexema == '(') {
					for (i += 1; lextable.table[i].lexema != ')'; i++) {
						if ((lextable.table[i].lexema == 'i' || lextable.table[i].lexema == 'l')
							&& idtable.table[lextable.table[i].idxTI].iddatatype != IT::BOOL) {
							throw ERROR_THROW_SEM(141, lextable.table[e].sn)
						}
					}
					break;
				}
			}
		}
	}
}