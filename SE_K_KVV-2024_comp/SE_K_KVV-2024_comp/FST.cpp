#include "FST.h"
#include <iostream>
#include <stdarg.h>
#include "stdafx.h"


#include <iomanip>



namespace FST
{
	RELATION::RELATION(char c, short ns)
	{
		symbol = c;
		nnode = ns;
	};


	NODE::NODE() {
		n_relation = 0;
		RELATION* relations = nullptr;
	}
	NODE::NODE(short n, RELATION rel, ...)
	{
		n_relation = n;
		RELATION* p = &rel;
		relations = new RELATION[n];
		for (int i = 0; i < n; i++)
		{
			relations[i] = p[i];
		}
	}

	FST::FST(const char* s, short ns, NODE n, ...) {
		string = s;
		nstates = ns;
		nodes = new NODE[ns];

		va_list args;
		va_start(args, n);
		nodes[0] = n;

		for (int k = 1; k < ns; k++) {
			nodes[k] = va_arg(args, NODE);
		}

		va_end(args);
		rstates = new short[nstates];
		memset(rstates, 0xff, sizeof(short) * nstates);
		rstates[0] = 0;
		position = -1;
	}


	bool execute(FST& fst)
	{
		short* rstates = new short[fst.nstates];
		memset(rstates, 0xff, sizeof(short) * fst.nstates);

		short lstring = strlen(fst.string);

		bool rc = true;

		for (short i = 0; i < lstring && rc; i++)
		{
			fst.position++;
			rc = [](FST& fst, short*& rstates) -> bool {
				bool rc = false;

				std::swap(rstates, fst.rstates);

				for (short i = 0; i < fst.nstates; i++)
				{
					if (rstates[i] == fst.position)
					{

						for (short j = 0; j < fst.nodes[i].n_relation; j++)
						{

							if (fst.nodes[i].relations[j].symbol == fst.string[fst.position])
							{

								fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
								rc = true;
							}
						}
					}
				}
				return rc;
				}(fst, rstates);;
		}

		delete[] rstates;


		return (rc ? (fst.rstates[fst.nstates - 1] == lstring) : rc);
	}

	
	int parseInteger(char* str) {
		// Проверяем, начинается ли строка с "0x", "0b" или "0"
		if (str[1] != '\0' && str[0] == '0') {
			if (str[1] == 'x' || str[1] == 'X') {
				// Шестнадцатеричное число
				return std::stoi(str + 2, (size_t*)nullptr, 16);
			}
			else if (str[1] == 'b' || str[1] == 'B') {
				// Двоичное число
				return std::stoi(str + 2, (size_t*)nullptr, 2);
			}
			else {
				// Восьмеричное число
				return std::stoi(str, (size_t*)nullptr, 8);
			}
		}
		// Десятичное число
		return std::stoi(str);
	}
	char GetLex(char* word) {

		FST Ilex(
			(char*)word,
			8,
			NODE(1, RELATION('i', 1)),
			NODE(1, RELATION('n', 2)),
			NODE(1, RELATION('t', 3)),
			NODE(1, RELATION('e', 4)),
			NODE(1, RELATION('g', 5)),
			NODE(1, RELATION('e', 6)),
			NODE(1, RELATION('r', 7)),
			NODE()
		);
		FST Slex(
			(char*)word,
			5,
			NODE(1, RELATION('c', 1)),
			NODE(1, RELATION('h', 2)),
			NODE(1, RELATION('a', 3)),
			NODE(1, RELATION('r', 4)),
			NODE()
		);
		FST Blex(
			(char*)word,
			5,
			NODE(1, RELATION('b', 1)),
			NODE(1, RELATION('o', 2)),
			NODE(1, RELATION('o', 3)),
			NODE(1, RELATION('l', 4)),
			NODE()
		);
		if (execute(Ilex) || execute(Slex) || execute(Blex))
			return LEX_INTEGER;
		FST Flex(
			(char*)word,
			9,
			NODE(1, RELATION('f', 1)),
			NODE(1, RELATION('u', 2)),
			NODE(1, RELATION('n', 3)),
			NODE(1, RELATION('c', 4)),
			NODE(1, RELATION('t', 5)),
			NODE(1, RELATION('i', 6)),
			NODE(1, RELATION('o', 7)),
			NODE(1, RELATION('n', 8)),
			NODE());
		if (execute(Flex))
			return LEX_FUNCTION;
		FST Dlex(
			(char*)word,
			8,
			NODE(1, RELATION('d', 1)),
			NODE(1, RELATION('e', 2)),
			NODE(1, RELATION('c', 3)),
			NODE(1, RELATION('l', 4)),
			NODE(1, RELATION('a', 5)),
			NODE(1, RELATION('r', 6)),
			NODE(1, RELATION('e', 7)),
			NODE()
		);
		if (execute(Dlex))
			return LEX_DECLARE;
		FST Plex(
			(char*)word,
			6,
			NODE(1, RELATION('w', 1)),
			NODE(1, RELATION('r', 2)),
			NODE(1, RELATION('i', 3)),
			NODE(1, RELATION('t', 4)),
			NODE(1, RELATION('e', 5)),
			NODE()
		);
		if (execute(Plex))
			return LEX_PRINT;
		FST RElex(
			(char*)word,
			5,
			NODE(1, RELATION('r', 1)),
			NODE(1, RELATION('e', 2)),
			NODE(1, RELATION('a', 3)),
			NODE(1, RELATION('d', 4)),
			NODE()
		);
		if (execute(RElex))
			return LEX_READ;
		FST Mlex(
			(char*)word,
			5,
			NODE(1, RELATION('m', 1)),
			NODE(1, RELATION('a', 2)),
			NODE(1, RELATION('i', 3)),
			NODE(1, RELATION('n', 4)),
			NODE()
		);
		if (execute(Mlex))
			return LEX_MAIN;

		FST Rlex(
			(char*)word,
			7,
			NODE(1, RELATION('r', 1)),
			NODE(1, RELATION('e', 2)),
			NODE(1, RELATION('t', 3)),
			NODE(1, RELATION('u', 4)),
			NODE(1, RELATION('r', 5)),
			NODE(1, RELATION('n', 6)),
			NODE()
		);
		if (execute(Rlex))
			return LEX_RETURN;
		FST IFlex(
			(char*)word,
			3,
			NODE(1, RELATION('i', 1)),
			NODE(1, RELATION('f', 2)),
			NODE()
		);
		if (execute(IFlex))
			return LEX_IF;

		return 0;

	}
	
	int GetID(char* word, int str, char* ret, int symb) {

		if (GetLex(word) != 0) {
			ret[symb] = '\0';
			throw ERROR_THROW_LEX(99, str, (unsigned char*)word, (unsigned char*)ret)
		}

		FST Tlex(
			(char*)word,
			5,
			NODE(1, RELATION('t', 1)),
			NODE(2, RELATION('r', 2)),
			NODE(3, RELATION('u', 3)),
			NODE(4, RELATION('e', 4)),
			NODE()
		);
		FST Flex(
			(char*)word,
			6,
			NODE(1, RELATION('f', 1)),
			NODE(2, RELATION('a', 2)),
			NODE(3, RELATION('l', 3)),
			NODE(4, RELATION('s', 4)),
			NODE(5, RELATION('e', 5)),
			NODE()
		);
		if (execute(Tlex) || execute(Flex))
			return 'b';

		FST strLit(
			word,
			4,
			NODE(1, RELATION('\'', 1)),
			NODE(258,
				RELATION('A', 1), RELATION('A', 2), RELATION('B', 1), RELATION('B', 2),
				RELATION('C', 1), RELATION('C', 2), RELATION('D', 1), RELATION('D', 2),
				RELATION('E', 1), RELATION('E', 2), RELATION('F', 1), RELATION('F', 2),
				RELATION('G', 1), RELATION('G', 2), RELATION('H', 1), RELATION('H', 2),
				RELATION('I', 1), RELATION('I', 2), RELATION('J', 1), RELATION('J', 2),
				RELATION('K', 1), RELATION('K', 2), RELATION('L', 1), RELATION('L', 2),
				RELATION('M', 1), RELATION('M', 2), RELATION('N', 1), RELATION('N', 2),
				RELATION('O', 1), RELATION('O', 2), RELATION('P', 1), RELATION('P', 2),
				RELATION('Q', 1), RELATION('Q', 2), RELATION('R', 1), RELATION('R', 2),
				RELATION('S', 1), RELATION('S', 2), RELATION('T', 1), RELATION('T', 2),
				RELATION('U', 1), RELATION('U', 2), RELATION('V', 1), RELATION('V', 2),
				RELATION('W', 1), RELATION('W', 2), RELATION('X', 1), RELATION('X', 2),
				RELATION('Y', 1), RELATION('Y', 2), RELATION('Z', 1), RELATION('Z', 2),
				RELATION('a', 1), RELATION('a', 2), RELATION('b', 1), RELATION('b', 2),
				RELATION('c', 1), RELATION('c', 2), RELATION('d', 1), RELATION('d', 2),
				RELATION('e', 1), RELATION('e', 2), RELATION('f', 1), RELATION('f', 2),
				RELATION('g', 1), RELATION('g', 2), RELATION('h', 1), RELATION('h', 2),
				RELATION('i', 1), RELATION('i', 2), RELATION('j', 1), RELATION('j', 2),
				RELATION('k', 1), RELATION('k', 2), RELATION('l', 1), RELATION('l', 2),
				RELATION('m', 1), RELATION('m', 2), RELATION('n', 1), RELATION('n', 2),
				RELATION('o', 1), RELATION('o', 2), RELATION('p', 1), RELATION('p', 2),
				RELATION('q', 1), RELATION('q', 2), RELATION('r', 1), RELATION('r', 2),
				RELATION('s', 1), RELATION('s', 2), RELATION('t', 1), RELATION('t', 2),
				RELATION('u', 1), RELATION('u', 2), RELATION('v', 1), RELATION('v', 2),
				RELATION('w', 1), RELATION('w', 2), RELATION('x', 1), RELATION('x', 2),
				RELATION('y', 1), RELATION('y', 2), RELATION('z', 1), RELATION('z', 2),
				RELATION('А', 1), RELATION('А', 2), RELATION('Б', 1), RELATION('Б', 2),
				RELATION('В', 1), RELATION('В', 2), RELATION('Г', 1), RELATION('Г', 2),
				RELATION('Д', 1), RELATION('Д', 2), RELATION('Е', 1), RELATION('Е', 2),
				RELATION('Ё', 1), RELATION('Ё', 2), RELATION('Ж', 1), RELATION('Ж', 2),
				RELATION('З', 1), RELATION('З', 2), RELATION('И', 1), RELATION('И', 2),
				RELATION('Й', 1), RELATION('Й', 2), RELATION('К', 1), RELATION('К', 2),
				RELATION('Л', 1), RELATION('Л', 2), RELATION('М', 1), RELATION('М', 2),
				RELATION('Н', 1), RELATION('Н', 2), RELATION('О', 1), RELATION('О', 2),
				RELATION('П', 1), RELATION('П', 2), RELATION('Р', 1), RELATION('Р', 2),
				RELATION('С', 1), RELATION('С', 2), RELATION('Т', 1), RELATION('Т', 2),
				RELATION('У', 1), RELATION('У', 2), RELATION('Ф', 1), RELATION('Ф', 2),
				RELATION('Х', 1), RELATION('Х', 2), RELATION('Ц', 1), RELATION('Ц', 2),
				RELATION('Ч', 1), RELATION('Ч', 2), RELATION('Ш', 1), RELATION('Ш', 2),
				RELATION('Щ', 1), RELATION('Щ', 2), RELATION('Ъ', 1), RELATION('Ъ', 2),
				RELATION('Ы', 1), RELATION('Ы', 2), RELATION('Ь', 1), RELATION('Ь', 2),
				RELATION('Э', 1), RELATION('Э', 2), RELATION('Ю', 1), RELATION('Ю', 2),
				RELATION('Я', 1), RELATION('Я', 2), RELATION('а', 1), RELATION('а', 2),
				RELATION('б', 1), RELATION('б', 2), RELATION('в', 1), RELATION('в', 2),
				RELATION('г', 1), RELATION('г', 2), RELATION('д', 1), RELATION('д', 2),
				RELATION('е', 1), RELATION('е', 2), RELATION('ё', 1), RELATION('ё', 2),
				RELATION('ж', 1), RELATION('ж', 2), RELATION('з', 1), RELATION('з', 2),
				RELATION('и', 1), RELATION('и', 2), RELATION('й', 1), RELATION('й', 2),
				RELATION('к', 1), RELATION('к', 2), RELATION('л', 1), RELATION('л', 2),
				RELATION('м', 1), RELATION('м', 2), RELATION('н', 1), RELATION('н', 2),
				RELATION('о', 1), RELATION('о', 2), RELATION('п', 1), RELATION('п', 2),
				RELATION('р', 1), RELATION('р', 2), RELATION('с', 1), RELATION('с', 2),
				RELATION('т', 1), RELATION('т', 2), RELATION('у', 1), RELATION('у', 2),
				RELATION('ф', 1), RELATION('ф', 2), RELATION('х', 1), RELATION('х', 2),
				RELATION('ц', 1), RELATION('ц', 2), RELATION('ч', 1), RELATION('ч', 2),
				RELATION('ш', 1), RELATION('ш', 2), RELATION('щ', 1), RELATION('щ', 2),
				RELATION('ъ', 1), RELATION('ъ', 2), RELATION('ы', 1), RELATION('ы', 2),
				RELATION('ь', 1), RELATION('ь', 2), RELATION('э', 1), RELATION('э', 2),
				RELATION('ю', 1), RELATION('ю', 2), RELATION('я', 1), RELATION('я', 2),
				RELATION('0', 1), RELATION('0', 2), RELATION('1', 1), RELATION('1', 2),
				RELATION('2', 1), RELATION('2', 2), RELATION('3', 1), RELATION('3', 2),
				RELATION('4', 1), RELATION('4', 2), RELATION('5', 1), RELATION('5', 2),
				RELATION('6', 1), RELATION('6', 2), RELATION('7', 1), RELATION('7', 2),
				RELATION('8', 1), RELATION('8', 2), RELATION('9', 1), RELATION('9', 2),
				RELATION(' ', 1), RELATION(' ', 2)),
			NODE(1, RELATION('\'', 3)),
			NODE()
		);
		if (execute(strLit)) {
			return 's';
		}
		FST intLit(
			word,
			7, 
			NODE(20,
				RELATION('0', 1), RELATION('0', 6), // Если встречается "0", переход в состояние 1
				RELATION('1', 5), RELATION('2', 5), RELATION('3', 5), RELATION('4', 5),
				RELATION('5', 5), RELATION('6', 5), RELATION('7', 5), RELATION('8', 5), RELATION('9', 5),
				RELATION('1', 6), RELATION('2', 6), RELATION('3', 6), RELATION('4', 6),
				RELATION('5', 6), RELATION('6', 6), RELATION('7', 6), RELATION('8', 6), RELATION('9', 6)
			),
			// Состояние 1: После "0"
			NODE(13,
				RELATION('x', 3), RELATION('X', 3), // Если "x", то переходим к шестнадцатеричному формату
				RELATION('b', 4), RELATION('B', 4), // Если "b", то переходим к двоичному формату
				RELATION('0', 1), RELATION('0', 2), RELATION('1', 2), RELATION('2', 2), RELATION('3', 2), RELATION('4', 2),
				RELATION('5', 2), RELATION('6', 2), RELATION('7', 2) // Восьмеричные цифры
			),
			NODE(16,
				RELATION('0', 2), RELATION('1', 2), RELATION('2', 2), RELATION('3', 2), RELATION('4', 2),
				RELATION('5', 2), RELATION('6', 2), RELATION('7', 2),
				RELATION('0', 6), RELATION('1', 6), RELATION('2', 6), RELATION('3', 6), RELATION('4', 6),
				RELATION('5', 6), RELATION('6', 6), RELATION('7', 6) // Восьмеричные цифры
			),
			// Состояние 2: После "0x"
			NODE(44,
				// Для "0x": допустимы только шестнадцатеричные символы
				RELATION('0', 3), RELATION('1', 3), RELATION('2', 3), RELATION('3', 3), RELATION('4', 3), RELATION('5', 3),
				RELATION('6', 3), RELATION('7', 3), RELATION('8', 3), RELATION('9', 3),
				RELATION('a', 3), RELATION('b', 3), RELATION('c', 3), RELATION('d', 3),
				RELATION('e', 3), RELATION('f', 3), RELATION('A', 3), RELATION('B', 3),
				RELATION('C', 3), RELATION('D', 3), RELATION('E', 3), RELATION('F', 3),
				
				RELATION('0', 6), RELATION('1', 6), RELATION('2', 6), RELATION('3', 6), RELATION('4', 6), RELATION('5', 6),
				RELATION('6', 6), RELATION('7', 6), RELATION('8', 6), RELATION('9', 6),
				RELATION('a', 6), RELATION('b', 6), RELATION('c', 6), RELATION('d', 6),
				RELATION('e', 6), RELATION('f', 6), RELATION('A', 6), RELATION('B', 6),
				RELATION('C', 6), RELATION('D', 6), RELATION('E', 6), RELATION('F', 6)
			),
			NODE(4,
				RELATION('0', 4), RELATION('1', 4), 
				RELATION('0', 6), RELATION('1', 6)
			),
			NODE(20,
				RELATION('0', 5), RELATION('1', 5), RELATION('2', 5), RELATION('3', 5), RELATION('4', 5),
				RELATION('5', 5), RELATION('6', 5), RELATION('7', 5), RELATION('8', 5), RELATION('9', 5),
				RELATION('0', 6), RELATION('1', 6), RELATION('2', 6), RELATION('3', 6), RELATION('4', 6),
				RELATION('5', 6), RELATION('6', 6), RELATION('7', 6), RELATION('8', 6), RELATION('9', 6)
			),

			NODE() 
		);
		if (execute(intLit)) {

			return 'i';
		}

		FST iLex(
			word,
			3,
			NODE(156,
				RELATION('A', 0), RELATION('A', 1), RELATION('A', 2),
				RELATION('B', 0), RELATION('B', 1), RELATION('B', 2),
				RELATION('C', 0), RELATION('C', 1), RELATION('C', 2),
				RELATION('D', 0), RELATION('D', 1), RELATION('D', 2),
				RELATION('E', 0), RELATION('E', 1), RELATION('E', 2),
				RELATION('F', 0), RELATION('F', 1), RELATION('F', 2),
				RELATION('G', 0), RELATION('G', 1), RELATION('G', 2),
				RELATION('H', 0), RELATION('H', 1), RELATION('H', 2),
				RELATION('I', 0), RELATION('I', 1), RELATION('I', 2),
				RELATION('J', 0), RELATION('J', 1), RELATION('J', 2),
				RELATION('K', 0), RELATION('K', 1), RELATION('K', 2),
				RELATION('L', 0), RELATION('L', 1), RELATION('L', 2),
				RELATION('M', 0), RELATION('M', 1), RELATION('M', 2),
				RELATION('N', 0), RELATION('N', 1), RELATION('N', 2),
				RELATION('O', 0), RELATION('O', 1), RELATION('O', 2),
				RELATION('P', 0), RELATION('P', 1), RELATION('P', 2),
				RELATION('Q', 0), RELATION('Q', 1), RELATION('Q', 2),
				RELATION('R', 0), RELATION('R', 1), RELATION('R', 2),
				RELATION('S', 0), RELATION('S', 1), RELATION('S', 2),
				RELATION('T', 0), RELATION('T', 1), RELATION('T', 2),
				RELATION('U', 0), RELATION('U', 1), RELATION('U', 2),
				RELATION('V', 0), RELATION('V', 1), RELATION('V', 2),
				RELATION('W', 0), RELATION('W', 1), RELATION('W', 2),
				RELATION('X', 0), RELATION('X', 1), RELATION('X', 2),
				RELATION('Y', 0), RELATION('Y', 1), RELATION('Y', 2),
				RELATION('Z', 0), RELATION('Z', 1), RELATION('Z', 2),
				RELATION('a', 0), RELATION('a', 1), RELATION('a', 2),
				RELATION('b', 0), RELATION('b', 1), RELATION('b', 2),
				RELATION('c', 0), RELATION('c', 1), RELATION('c', 2),
				RELATION('d', 0), RELATION('d', 1), RELATION('d', 2),
				RELATION('e', 0), RELATION('e', 1), RELATION('e', 2),
				RELATION('f', 0), RELATION('f', 1), RELATION('f', 2),
				RELATION('g', 0), RELATION('g', 1), RELATION('g', 2),
				RELATION('h', 0), RELATION('h', 1), RELATION('h', 2),
				RELATION('i', 0), RELATION('i', 1), RELATION('i', 2),
				RELATION('j', 0), RELATION('j', 1), RELATION('j', 2),
				RELATION('k', 0), RELATION('k', 1), RELATION('k', 2),
				RELATION('l', 0), RELATION('l', 1), RELATION('l', 2),
				RELATION('m', 0), RELATION('m', 1), RELATION('m', 2),
				RELATION('n', 0), RELATION('n', 1), RELATION('n', 2),
				RELATION('o', 0), RELATION('o', 1), RELATION('o', 2),
				RELATION('p', 0), RELATION('p', 1), RELATION('p', 2),
				RELATION('q', 0), RELATION('q', 1), RELATION('q', 2),
				RELATION('r', 0), RELATION('r', 1), RELATION('r', 2),
				RELATION('s', 0), RELATION('s', 1), RELATION('s', 2),
				RELATION('t', 0), RELATION('t', 1), RELATION('t', 2),
				RELATION('u', 0), RELATION('u', 1), RELATION('u', 2),
				RELATION('v', 0), RELATION('v', 1), RELATION('v', 2),
				RELATION('w', 0), RELATION('w', 1), RELATION('w', 2),
				RELATION('x', 0), RELATION('x', 1), RELATION('x', 2),
				RELATION('y', 0), RELATION('y', 1), RELATION('y', 2),
				RELATION('z', 0), RELATION('z', 1), RELATION('z', 2),
				RELATION('_', 0), RELATION('_', 1)
			),
			NODE(126,
				RELATION('0', 1), RELATION('0', 2),
				RELATION('1', 1), RELATION('1', 2),
				RELATION('2', 1), RELATION('2', 2),
				RELATION('3', 1), RELATION('3', 2),
				RELATION('4', 1), RELATION('4', 2),
				RELATION('5', 1), RELATION('5', 2),
				RELATION('6', 1), RELATION('6', 2),
				RELATION('7', 1), RELATION('7', 2),
				RELATION('8', 1), RELATION('8', 2),
				RELATION('9', 1), RELATION('9', 2),
				RELATION('_', 1), RELATION('_', 2),
				RELATION('A', 1), RELATION('A', 2),
				RELATION('B', 1), RELATION('B', 2),
				RELATION('C', 1), RELATION('C', 2),
				RELATION('D', 1), RELATION('D', 2),
				RELATION('E', 1), RELATION('E', 2),
				RELATION('F', 1), RELATION('F', 2),
				RELATION('G', 1), RELATION('G', 2),
				RELATION('H', 1), RELATION('H', 2),
				RELATION('I', 1), RELATION('I', 2),
				RELATION('J', 1), RELATION('J', 2),
				RELATION('K', 1), RELATION('K', 2),
				RELATION('L', 1), RELATION('L', 2),
				RELATION('M', 1), RELATION('M', 2),
				RELATION('N', 1), RELATION('N', 2),
				RELATION('O', 1), RELATION('O', 2),
				RELATION('P', 1), RELATION('P', 2),
				RELATION('Q', 1), RELATION('Q', 2),
				RELATION('R', 1), RELATION('R', 2),
				RELATION('S', 1), RELATION('S', 2),
				RELATION('T', 1), RELATION('T', 2),
				RELATION('U', 1), RELATION('U', 2),
				RELATION('V', 1), RELATION('V', 2),
				RELATION('W', 1), RELATION('W', 2),
				RELATION('X', 1), RELATION('X', 2),
				RELATION('Y', 1), RELATION('Y', 2),
				RELATION('Z', 1), RELATION('Z', 2),
				RELATION('a', 1), RELATION('a', 2),
				RELATION('b', 1), RELATION('b', 2),
				RELATION('c', 1), RELATION('c', 2),
				RELATION('d', 1), RELATION('d', 2),
				RELATION('e', 1), RELATION('e', 2),
				RELATION('f', 1), RELATION('f', 2),
				RELATION('g', 1), RELATION('g', 2),
				RELATION('h', 1), RELATION('h', 2),
				RELATION('i', 1), RELATION('i', 2),
				RELATION('j', 1), RELATION('j', 2),
				RELATION('k', 1), RELATION('k', 2),
				RELATION('l', 1), RELATION('l', 2),
				RELATION('m', 1), RELATION('m', 2),
				RELATION('n', 1), RELATION('n', 2),
				RELATION('o', 1), RELATION('o', 2),
				RELATION('p', 1), RELATION('p', 2),
				RELATION('q', 1), RELATION('q', 2),
				RELATION('r', 1), RELATION('r', 2),
				RELATION('s', 1), RELATION('s', 2),
				RELATION('t', 1), RELATION('t', 2),
				RELATION('u', 1), RELATION('u', 2),
				RELATION('v', 1), RELATION('v', 2),
				RELATION('w', 1), RELATION('w', 2),
				RELATION('x', 1), RELATION('x', 2),
				RELATION('y', 1), RELATION('y', 2),
				RELATION('z', 1), RELATION('z', 2)),
			NODE()
		);

		if (execute(iLex)) {
			return 'I';
		}


		return 0;
	}

	
	char check_int(char* word) {
		FST Ilex(
			(char*)word,
			8,
			NODE(1, RELATION('i', 1)),
			NODE(1, RELATION('n', 2)),
			NODE(1, RELATION('t', 3)),
			NODE(1, RELATION('e', 4)),
			NODE(1, RELATION('g', 5)),
			NODE(1, RELATION('e', 6)),
			NODE(1, RELATION('r', 7)),
			NODE()
		);
		FST Clex(
			(char*)word,
			5,
			NODE(1, RELATION('c', 1)),
			NODE(1, RELATION('h', 2)),
			NODE(1, RELATION('a', 3)),
			NODE(1, RELATION('r', 4)),
			NODE()
		);

		FST Blex(
			(char*)word,
			5,
			NODE(1, RELATION('b', 1)),
			NODE(1, RELATION('o', 2)),
			NODE(1, RELATION('o', 3)),
			NODE(1, RELATION('l', 4)),
			NODE()
		);
		if (execute(Ilex))
			return LEX_INTEGER;
		if (execute(Clex))
			return 'c';
		if (execute(Ilex))
			return 'b';
	}



	bool compareStacks(std::stack<char*> s1, std::stack<char*> s2) {
		if (s1.size() != s2.size()) {
			return false;
		}

		while (!s1.empty()) {
			if (strcmp(s1.top(), s2.top()) != 0) {
				return false;
			}
			s1.pop();
			s2.pop();
		}

		return true; 
	}

	bool test(IT::IdTable idtable, char* word ,std::stack<char*> func) {
		for (int k = idtable.size - 1; k >= 0; k--) {
			if (!strcmp(IT::GetEntry(idtable, k).id, word) && compareStacks(IT::GetEntry(idtable, k).funcID, func))
			{
				return true;
			}
		}
		return false;

	}

	void GetLexOrID(In::IN in, LT::LexTable& lextable, IT::IdTable& idtable) {
		char* ret = new char[LT_MAXSIZE];
		int symbols = 0;
		const char constlex[] = ";,{}()=|&!^]";
		int str = 1;
		int id = 0;
		int lastid = 0;
		ret[symbols++] = (str / 10) + '0';
		ret[symbols++] = (str % 10) + '0';
		ret[symbols++] = ' ';
		str = 0;
		stack<char*> funcID;
		funcID.push((char*)"0GLOBAL");
		IT::Add(idtable, { -1, (char*)"strEq", IT::BOOL, IT::F, funcID });
		funcID.push((char*)"strEq");
		IT::Add(idtable, { -1, (char*)"a", IT::STR, IT::P, funcID });
		IT::Add(idtable, { -1, (char*)"b", IT::STR, IT::P, funcID });
		funcID.pop();
		IT::Add(idtable, { -1, (char*)"findWord", IT::STR, IT::F, funcID });
		funcID.push((char*)"findWord");
		IT::Add(idtable, { -1, (char*)"a", IT::STR, IT::P, funcID });
		IT::Add(idtable, { -1, (char*)"n", IT::INT, IT::P, funcID });
		funcID.pop();
		bool param = false, func = false;
		for (int i = 0; i < in.count_words - 1; i++) {
			if (in.words[i][0] == (unsigned char)' ' || in.words[i][0] == (unsigned char)'\0') {
				continue;
			}
			if (in.words[i][0] == '\n') {
				ret[symbols++] = '\n';
				str++;
				ret[symbols++] = (str / 10) + '0';
				ret[symbols++] = (str % 10) + '0';
				ret[symbols++] = ' ';
				continue;
			}
			if (lextable.size + 1 > lextable.maxsize) {
				ret[symbols] = '\0';
				throw ERROR_THROW(60);
			}
			if (in.words[i][0] == '[') {
				if (idtable.table[idtable.size - 1].idxfirstLE = lextable.size - 1) {
					idtable.table[idtable.size - 1].isArray = true;
				}
				else if (!idtable.table[lextable.table[lextable.size - 1].idxTI].isArray) {
					throw ERROR_THROW_LEX(68, str, (unsigned char*)idtable.table[lextable.table[lextable.size - 1].idxTI].id, (unsigned char*)ret);
				}
				LT::Add(lextable, { '[', str, NULL});
				continue;
			}
			bool flag = false;
			for (int j = 0; j < 12; j++) {
				if (in.words[i][0] == constlex[j]) {
					ret[symbols++] = in.words[i][0];
					LT::Add(lextable, { (char)in.words[i][0], str, NULL });
					flag = true;
					break;
				}
			}

			if (flag) {
				switch (in.words[i][0])
				{
				case '(':
					param = true;
					break;
				case ')':
					param = false;
					break;
				case '{':
					func = true;
					break;
				case '}':
					func = false;
					funcID.pop();
					break;
				}
				continue;
			}
			
			IT::IDDATATYPE datatypeIT;
			int leng = 0;
			switch (GetLex((char*)in.words[i]))
			{
			case LEX_INTEGER:
				ret[symbols++] = 't';
				datatypeIT = check_int((char*)in.words[i]) == LEX_INTEGER ? IT::INT : check_int((char*)in.words[i]) == 'c' ? IT::STR : IT::BOOL;
				LT::Add(lextable, { 't', str, NULL, datatypeIT });
				do {
					i++;
					if (in.words[i][0] == '\n') {
						ret[symbols++] = '\n';
						str++;
						ret[symbols++] = (str / 10) + '0';
						ret[symbols++] = (str % 10) + '0';
						ret[symbols++] = ' ';
					}
				} while (in.words[i][0] == (unsigned char)' ' || in.words[i][0] == (unsigned char)'\0' || in.words[i][0] == '\n');
				
				if (GetLex((char*)in.words[i]) == LEX_FUNCTION)
				{
					LT::Add(lextable, { 'f', str, NULL });
					ret[symbols++] = 'f';
					do {
						i++;
						if (in.words[i][0] == '\n') {
							ret[symbols++] = '\n';
							str++;
							ret[symbols++] = (str / 10) + '0';
							ret[symbols++] = (str % 10) + '0';
							ret[symbols++] = ' ';
						}
					} while (in.words[i][0] == (unsigned char)' ' || in.words[i][0] == (unsigned char)'\0' || in.words[i][0] == '\n');
					if (GetID((char*)in.words[i], str, ret, symbols) == 'I') {
						while (in.words[i][leng++] != '\0');
						if (leng > ID_MAXSIZE) {
							ret[symbols] = '\0';
							throw ERROR_THROW_LEX(65, str, in.words[i], (unsigned char*)ret);
						}
						if (idtable.size + 1 > idtable.maxsize) {
							ret[symbols] = '\0';
							throw ERROR_THROW(66);
						}
						if (test(idtable, (char*)in.words[i], funcID)) {
							ret[symbols] = '\0';
							throw ERROR_THROW_LEX(95, str, in.words[i], (unsigned char*)ret);
						}
						LT::Add(lextable, { 'i', str, idtable.size });
						IT::Add(idtable, { lextable.size - 1,(char*)in.words[i], datatypeIT, IT::F, funcID});
						funcID.push((char*)in.words[i]);
						ret[symbols++] = 'i';
					}
					else {
						ret[symbols] = '\0';

						throw ERROR_THROW_LEX(93, str, in.words[i], (unsigned char*)ret);
					}
				}
				else if (GetID((char*)in.words[i], str, ret, symbols) == 'I') {
					while (in.words[i][leng++] != '\0');
					if (leng > ID_MAXSIZE) {
						ret[symbols] = '\0';
						throw ERROR_THROW_LEX(65, str, in.words[i], (unsigned char*)ret);
					}
					if (idtable.size + 1 > idtable.maxsize) {
						ret[symbols] = '\0';
						throw ERROR_THROW(66);
					}
					/*if (test(idtable, (char*)in.words[i], funcID)) {
						ret[symbols] = '\0';
						throw ERROR_THROW_LEX(96, str, in.words[i], (unsigned char*)ret);
					}*/

					LT::Add(lextable, { 'i', str, idtable.size });
					IT::Add(idtable, { lextable.size - 1,(char*)in.words[i], datatypeIT, IT::P, funcID});
					ret[symbols++] = 'i';
				}
				else {
					ret[symbols] = '\0';

					throw ERROR_THROW_LEX(93, str, in.words[i], (unsigned char*)ret);
				}
				continue;
				break;
			case LEX_DECLARE:
				LT::Add(lextable, { 'd', str, NULL });
				ret[symbols++] = 'd';
				do {
					i++;
					if (in.words[i][0] == '\n') {
						ret[symbols++] = '\n';
						str++;
						ret[symbols++] = (str / 10) + '0';
						ret[symbols++] = (str % 10) + '0';
						ret[symbols++] = ' ';
					}
				} while (in.words[i][0] == (unsigned char)' ' || in.words[i][0] == (unsigned char)'\0' || in.words[i][0] == '\n');


				if (GetLex((char*)in.words[i]) == LEX_INTEGER) {
					ret[symbols++] = 't';
					datatypeIT = check_int((char*)in.words[i]) == LEX_INTEGER ? IT::INT : check_int((char*)in.words[i]) == 'c' ? IT::STR : IT::BOOL;
					LT::Add(lextable, { 't', str, NULL, datatypeIT });
					do {
						i++;
						if (in.words[i][0] == '\n') {
							ret[symbols++] = '\n';
							str++;
							ret[symbols++] = (str / 10) + '0';
							ret[symbols++] = (str % 10) + '0';
							ret[symbols++] = ' ';
						}
					} while (in.words[i][0] == (unsigned char)' ' || in.words[i][0] == (unsigned char)'\0' || in.words[i][0] == '\n');

					if (GetLex((char*)in.words[i]) == LEX_FUNCTION)
					{
						LT::Add(lextable, { 'f', str, NULL });
						ret[symbols++] = 'f';
						do {
							i++;
							if (in.words[i][0] == '\n') {
								ret[symbols++] = '\n';
								str++;
								ret[symbols++] = (str / 10) + '0';
								ret[symbols++] = (str % 10) + '0';
								ret[symbols++] = ' ';
							}
						} while (in.words[i][0] == (unsigned char)' ' || in.words[i][0] == (unsigned char)'\0' || in.words[i][0] == '\n');
						if (GetID((char*)in.words[i], str, ret, symbols) == 'I') {
							while (in.words[i][leng++] != '\0');
							if (leng > ID_MAXSIZE) {
								ret[symbols] = '\0';
								throw ERROR_THROW_LEX(65, str, in.words[i], (unsigned char*)ret);
							}
							if (idtable.size + 1 > idtable.maxsize) {
								ret[symbols] = '\0';
								throw ERROR_THROW(66);
							}
							if (test(idtable, (char*)in.words[i], funcID)) {
								ret[symbols] = '\0';
								throw ERROR_THROW_LEX(95, str, in.words[i], (unsigned char*)ret);
							}
							LT::Add(lextable, { 'i', str, idtable.size });
							IT::Add(idtable, { lextable.size - 1,(char*)in.words[i], datatypeIT, IT::F, funcID});
							ret[symbols++] = 'i';
						}
						else {
							ret[symbols] = '\0';


							throw ERROR_THROW_LEX(93, str, in.words[i], (unsigned char*)ret);
						}
					}
					else if (GetID((char*)in.words[i], str, ret, symbols) == 'I') {
						while (in.words[i][leng++] != '\0');
						if (leng > ID_MAXSIZE) {
							ret[symbols] = '\0';
							throw ERROR_THROW_LEX(65, str, in.words[i], (unsigned char*)ret);
						}
						if (idtable.size + 1 > idtable.maxsize) {
							ret[symbols] = '\0';
							throw ERROR_THROW(66);
						}
						if (test(idtable, (char*)in.words[i], funcID)) {
							ret[symbols] = '\0';
							throw ERROR_THROW_LEX(96, str, in.words[i], (unsigned char*)ret);
						}
						LT::Add(lextable, { 'i', str, idtable.size });
						IT::Add(idtable, { lextable.size - 1,(char*)in.words[i], datatypeIT, IT::V, funcID});
						ret[symbols++] = 'i';
					}
					else {
						ret[symbols] = '\0';


						throw ERROR_THROW_LEX(93, str, in.words[i], (unsigned char*)ret);
					}

				}
				
				continue;
				break;

			case LEX_RETURN:
				LT::Add(lextable, { 'r', str, NULL });
				ret[symbols++] = 'r';
				continue;
				break;

			case LEX_PRINT:
				LT::Add(lextable, { 'p', str, NULL });
				ret[symbols++] = 'p';
				continue;
				break;
			case LEX_READ:
				LT::Add(lextable, { LEX_READ, str, NULL });
				ret[symbols++] = LEX_READ;
				continue;
				break;
			case LEX_IF:
				LT::Add(lextable, { LEX_IF, str, NULL });
				ret[symbols++] = LEX_IF;
				continue;
				break;
			case LEX_MAIN:
				for (int i = 0; i < lextable.size; i++) {
					if (LT::GetEntry(lextable, i).lexema == 'm') {
						ret[symbols] = '\0';
						throw ERROR_THROW_LEX(94, str, in.words[i], (unsigned char*)ret);
					}
				}
				funcID.push((char*)"MAIN");
				LT::Add(lextable, { 'm', str, NULL });
				ret[symbols++] = 'm';
				continue;
				break;


			default:
				break;
			}

			IT::IDDATATYPE datatype;
			IT::IDTYPE type;
			IT::Entry entry;
			stack<char*> global;
			global.push((char*)"0GLOBAL");
			int j = 0;
			int l = -1;
			char* tmp_literal_name = new char[20];
			char* LiteralSTR = (char*)"STR";
			char* LiteralINT = (char*)"INT";
			char* LiteralBOOL = (char*)"BOOl";
			int g = 0;
			int tmp_lit_number = id;
			char tmp_number[10];
			int h = 0;


			switch (GetID((char*)in.words[i], str, ret, symbols))
			{
			case 's':
				l = idtable.size;
				for (int k = idtable.size - 1; k >= 0; k--) {
					if (IT::GetEntry(idtable, k).iddatatype == IT::STR && IT::GetEntry(idtable, k).idtype == IT::L && 
						!strcmp(IT::GetEntry(idtable, k).value.vstr.str, (char*)in.words[i]))
					{
						l = k;
						break;
					}
				}
				LT::Add(lextable, { 'l', str, l });


				if (l == idtable.size) {
					datatype = IT::STR;
					type = IT::L; 
					
					while (LiteralSTR[g] != '\0') {
						tmp_literal_name[g] = LiteralSTR[g];
						g++;
					}
					if (tmp_lit_number == 0) {
						tmp_literal_name[g++] = '0';
					}

					else {
						while (tmp_lit_number > 0) {
							tmp_number[h++] = tmp_lit_number % 10 + '0';
							tmp_lit_number /= 10;
						}
						tmp_number[h] = '\0';
						h--;
						while (h >= 0) {

							tmp_literal_name[g++] = tmp_number[h--];
						}
					}

					tmp_literal_name[g] = '\0';
					id++;
					while (in.words[i][j++] != '\0');
					if (j - 3 > IT_STR_MAXSIZE) {
						ret[symbols] = '\0';
						throw ERROR_THROW_LEX(91, str, in.words[i], (unsigned char*)ret);
					}
					entry = { lextable.size - 1, tmp_literal_name , datatype, type, global};
					entry.value.vstr = { j - 3, ((char*)in.words[i])};
					IT::Add(idtable, entry);
				}
				ret[symbols++] = 'l';
				
				
				continue;
				break;
			case 'i':
				l = idtable.size;
				for (int k = idtable.size - 1; k >= 0; k--) {
					if (IT::GetEntry(idtable, k).iddatatype == IT::STR && IT::GetEntry(idtable, k).idtype == IT::L &&
						IT::GetEntry(idtable, k).value.vint == parseInteger((char*)in.words[i])) {
						l = k;
						break;
					}
				}
				LT::Add(lextable, { 'l', str, l });
				if (l == idtable.size) {
					datatype = IT::INT;
					type = IT::L;
					while (LiteralINT[g] != '\0') {
						tmp_literal_name[g] = LiteralINT[g];
						g++;
					}
					if (tmp_lit_number == 0) {
						tmp_literal_name[g++] = '0';
					}

					else {
						while (tmp_lit_number > 0) {
							tmp_number[h++] = tmp_lit_number % 10 + '0';
							tmp_lit_number /= 10;
						}
						tmp_number[h] = '\0';
						h--;
						while (h >= 0) {

							tmp_literal_name[g++] = tmp_number[h--];
						}
					}

					tmp_literal_name[g] = '\0';
					id++;
					IT::Add(idtable, { lextable.size - 1, tmp_literal_name , datatype, type, global,parseInteger((char*)in.words[i])});
				}
				ret[symbols++] = 'l';
				
				continue;
				break;

			case 'b':
				l = idtable.size;
				for (int k = idtable.size - 1; k >= 0; k--) {
					if (IT::GetEntry(idtable, k).iddatatype == IT::BOOL && IT::GetEntry(idtable, k).idtype == IT::L &&
						!strcmp(IT::GetEntry(idtable, k).value.vbool ? "true" : "false", (char*)in.words[i])) {
						l = k;
						break;
					}
				}
				LT::Add(lextable, { 'l', str, l });
				if (l == idtable.size) {
					datatype = IT::BOOL;
					type = IT::L;
					while (LiteralBOOL[g] != '\0') {
						tmp_literal_name[g] = LiteralBOOL[g];
						g++;
					}
					if (tmp_lit_number == 0) {
						tmp_literal_name[g++] = '0';
					}

					else {
						while (tmp_lit_number > 0) {
							tmp_number[h++] = tmp_lit_number % 10 + '0';
							tmp_lit_number /= 10;
						}
						tmp_number[h] = '\0';
						h--;
						while (h >= 0) {

							tmp_literal_name[g++] = tmp_number[h--];
						}
					}

					tmp_literal_name[g] = '\0';
					id++;
					IT::Add(idtable, { lextable.size - 1, tmp_literal_name , datatype, type, global, strcmp((char*)in.words[i], (char*)"true")? 0:1 });
				}
				ret[symbols++] = 'l';

				continue;

				break;
			case 'I':
				for (int k = idtable.size - 1; k >= 0; k--) {
					if (!strcmp(IT::GetEntry(idtable, k).id,(char*)in.words[i])) {
						l = k;
						break;
					}
				}
				if (l != -1) {
					LT::Add(lextable, { 'i', str, l });
				}
				else
				{
					ret[symbols] = '\0';
					throw ERROR_THROW_LEX(97, str, in.words[i], (unsigned char*)ret);
				}
				ret[symbols++] = 'i';
				
				continue;
				break;
			}

			ret[symbols] = '\0';

			throw ERROR_THROW_LEX(90, str, in.words[i], (unsigned char*)ret);
		}
		bool fl = true;
		for (int i = 0; i < lextable.size; i++) {
			if (LT::GetEntry(lextable, i).lexema == 'm') {
				fl = false;
			}
		}
		if (fl)
			throw ERROR_THROW(98);
		delete[] ret;

	}
}
