#include "GEN.h"
#define lexT lex.lextable
#define idT lex.idTable
#define out *log.stream

namespace CodeGen
{
	void Head(LT::lexAndIdTable& lex, Out::OUT& log)
	{
		out << ".586\n";
		out << "\t.model flat, stdcall\n";
		out << "\tincludelib libucrt.lib\n";
		out << "\tincludelib kernel32.lib\n";
		out << "\tincludelib ../Debug/standartLib.lib\n";
		out << "\tExitProcess PROTO : DWORD\n\n";
		out << "\tEXTRN rusL: proc\n";
		out << "\tEXTRN OutputInt: proc\n";
		out << "\tEXTRN OutputChar: proc\n";
		out << "\tEXTRN InputInt: proc\n";
		out << "\n.stack 4096\n";
	}
	void Const(LT::lexAndIdTable& lex, Out::OUT& log)
	{
		out << ".const\n";
		for (int i = 0; i < lex.idTable.size; i++)
		{
			if (lex.idTable.table[i].idtype == IT::L)
			{
				out << "\t" << lex.idTable.table[i].id;
				if (lex.idTable.table[i].iddatatype == IT::STR)
				{
					out << " BYTE " << lex.idTable.table[i].value.vstr.str << ", 0\n";
				}
				else
				{
					out << " DWORD " << lex.idTable.table[i].value.vint << std::endl;
				}

			}
		}
	}
	void Data(LT::lexAndIdTable& lex, Out::OUT& log)
	{
		*log.stream << "\n.data\n";
		*log.stream << "\tbuffer BYTE 256 dup(0)\n";
		for (int i = 0; i < lex.lextable.size; i++)
		{
			if (lex.lextable.table[i].lexema == LEX_DECLARE)
			{
				if (lex.idTable.table[lex.lextable.table[i + 2].idxTI].idtype == IT::V)
				{
					*log.stream << "\t" << lex.idTable.table[lex.lextable.table[i + 2].idxTI].id;
					*log.stream << " DWORD ?\n";
				}
			}
		}
	}
	void Code(LT::lexAndIdTable& lex, Out::OUT& log)
	{
		stack<unsigned char*> stk;
		int num_of_points = 0,
			num_of_ret = 0,
			num_of_ends = 0,
			num_of_cycles = 0,
			countParm = 0;
		string strret = string(),
			cycle_code = string(),
			func_name = string();
		bool flag_func = false,
			flag_ret = false,
			flag_body = false,
			flag_if = false,
			flag_then = false,
			flag_else = false,
			flag_measure = false,
			flag_rand = false,
			flag_exp = false,
			flag_proc = false,
			flag_link = false,
			flag_callfunc = false,
			flag_condition = false,
			flag_cycle = false;

		*log.stream << "\n.code\n\n";
		for (int i = 0; i < lex.lextable.size; i++)
		{
			switch (lex.lextable.table[i].lexema)
			{
			case LEX_FUNCTION:
			{
				while (lexT.table[i].lexema != LEX_RIGHTTHESIS)
				{
					if (lexT.table[i].lexema == LEX_ID && idT.table[lexT.table[i].idxTI].idtype == IT::F)
					{
						*log.stream << (func_name = string(idT.table[lexT.table[i].idxTI].id)) << " PROC ";
					}
					else if (lexT.table[i].lexema == LEX_ID && idT.table[lexT.table[i].idxTI].idtype == IT::P)
					{
						out << idT.table[lexT.table[i].idxTI].id << " : ";
						out << "DWORD";
					}
					else if (lexT.table[i].lexema == LEX_COMMA)
					{
						out << ", ";
					}
					i++;
				}
				flag_func = true;
				out << "\n";
				break;
			}
			case LEX_MAIN:
			{
				flag_body = true;
				out << "main PROC\ncall rusL\n";
				break;
			}
			case '=':
			{
				int result_position = i - 1;
				while (lexT.table[i].lexema != LEX_SEMICOLON)
				{
					switch (lexT.table[i].lexema)
					{
					case LEX_ID:
					case LEX_LITERAL:
					{
						if (idT.table[lexT.table[i].idxTI].idtype == IT::F)
						{
							if (idT.table[lexT.table[i].idxTI].idtype == IT::F) {
								countParm = (char)lexT.table[i + 1].lexema - '0';

								for (int j = 1; j <= countParm; j++)
								{
									out << "\tpop edx\n";
								}

								for (int j = 1; j <= countParm; j++)
								{
									out << "\tpush " << stk.top() << "\n";
									stk.pop();
								}

								out << "\tcall " << idT.table[lexT.table[i - countParm - 1].idxTI].id << "\n\tpush eax\n";
								flag_callfunc = false;



							}
							else if (idT.table[lexT.table[i].idxTI].idtype == IT::V) {
								if (idT.table[lexT.table[i].idxTI].iddatatype == IT::INT || idT.table[lexT.table[i].idxTI].iddatatype == IT::BOOL)
								{
									out << "\tpush " << idT.table[lexT.table[i].idxTI].id << "\n";
									stk.push((unsigned char*)idT.table[lexT.table[i].idxTI].id);
									break;
								}
								if (idT.table[lexT.table[i].idxTI].iddatatype == IT::STR)
								{
									char* s;
									if (idT.table[lexT.table[i].idxTI].idtype == IT::L)
									{
										out << "\tpush offset " << idT.table[lexT.table[i].idxTI].id << "\n";
										s = new char[8] { "offset " };
									}
									else
									{
										out << "\tpush " << idT.table[lexT.table[i].idxTI].id << "\n";
										s = new char[1] { "" };
									}
									size_t len1 = strlen((char*)s);
									size_t len2 = strlen((char*)idT.table[lexT.table[i].idxTI].id);
									char* result = (char*)malloc(len1 + len2 + 1);
									memcpy(result, s, len1);
									memcpy(result + len1, (char*)idT.table[lexT.table[i].idxTI].id, len2 + 1);
									stk.push((unsigned char*)result);
									break;
								}
							}
						}
						if (idT.table[lexT.table[i].idxTI].iddatatype == IT::INT)
						{
							out << "\tpush " << idT.table[lexT.table[i].idxTI].id << "\n";
							stk.push((unsigned char*)idT.table[lexT.table[i].idxTI].id);
							break;
						}
						if (idT.table[lexT.table[i].idxTI].iddatatype == IT::STR)
						{
							char* s;
							if (idT.table[lexT.table[i].idxTI].idtype == IT::L)
							{
								out << "\tpush offset " << idT.table[lexT.table[i].idxTI].id << "\n";
								s = new char[8] { "offset " };
							}
							else
							{
								out << "\tpush " << idT.table[lexT.table[i].idxTI].id << "\n";
								s = new char[1] { "" };
							}
							size_t len1 = strlen((char*)s);
							size_t len2 = strlen((char*)idT.table[lexT.table[i].idxTI].id);
							char* result = (char*)malloc(len1 + len2 + 1);
							memcpy(result, s, len1);
							memcpy(result + len1, (char*)idT.table[lexT.table[i].idxTI].id, len2 + 1);
							stk.push((unsigned char*)result);
							break;
						}
					}
					case '*':
						out << "\tpop eax\n\tpop ebx\n";
						out << "\tmul ebx\n\tpush eax\n";
						break;
					case '+':
						out << "\tpop eax\n\tpop ebx\n";
						out << "\tadd eax, ebx\n\tpush eax\n";
						break;
					case '-':
						out << "\tpop ebx\n\tpop eax\n";
						out << "\tsub eax, ebx\n\tpush eax\n";
						break;
					case '/':
						out << "\tpop ebx\n\tpop eax\n";
						out << "\tcdq\n\tidiv ebx\n\tpush eax\n";
						break;
					case '%':
						out << "\tpop ebx\n\tpop eax\n";
						out << "\tcdq\n\tidiv ebx\n\tpush edx\n";
						break;

					}
					i++;
				}
				out << "\tpop " << idT.table[lexT.table[result_position].idxTI].id << "\n";
				break;
			}
			case 'i':
			{
				if (idT.table[lexT.table[i].idxTI].idtype == IT::F) {
					countParm = (char)lexT.table[i + 1].lexema - '0';
					for (int j = 1; j <= countParm; j++)
					{
						if (idT.table[lexT.table[i - j].idxTI].iddatatype == IT::INT)
							out << "\tpush " << idT.table[lexT.table[i - j].idxTI].id << "\n";
						else
						{
							if (idT.table[lexT.table[i - j].idxTI].idtype == IT::L)
								out << "\tpush offset" << idT.table[lexT.table[i - j].idxTI].id << "\n";
							else
								out << "\tpush " << idT.table[lexT.table[i - j].idxTI].id << "\n";
						}
					}
					out << "\tcall " << idT.table[lexT.table[i - countParm - 1].idxTI].id << "\n";
				}
				break;
			}
			case LEX_RETURN:
			{
				out << "\tpush ";
				i++;
				if (idT.table[lexT.table[i + 1].idxTI].idtype == IT::L)
				{
					out << idT.table[lexT.table[i + 1].idxTI].id << "\n";
				}
				else
				{
					out << idT.table[lexT.table[i + 1].idxTI].id << "\n";
				}
				if (flag_func)
				{
					out << "\tjmp local" << num_of_ret << "\n";
					flag_ret = true;
				}
				if (flag_body)
				{
					out << "\t\tjmp theend\n";
					flag_ret = true;
				}
				break;
			}
			case LEX_BRACELET:
			{
				if (flag_body && !flag_if && !flag_func)
				{
					if (flag_ret)
					{
						out << "theend:\n";
						flag_ret = false;
					}
					out << "\tcall ExitProcess\nmain ENDP\nend main";
				}
				if (flag_func && !flag_if)
				{
					if (flag_ret)
					{
						out << "local" << num_of_ret++ << ":\n";
						out << "\tpop eax\n\tret\n";
						flag_ret = false;
					}
					if (flag_proc)
					{
						out << "\tret\n";
						flag_proc = false;
					}
					out << func_name << " ENDP\n\n";
					flag_func = false;
				}
				if (flag_if)
				{
					flag_if = false;
					out << "m" << num_of_points++ << ":\n";
				}
				break;
			}
			case '?':
			{
				flag_if = true;
				break;
			}
			case LEX_LEFTTHESIS:
			{
				if (flag_if)
				{
					if (idT.table[lexT.table[i + 1].idxTI].iddatatype == IT::BOOL && lexT.table[i + 2].lexema == LEX_RIGHTTHESIS)
					{
						out << "\tmov eax, " << idT.table[lexT.table[i + 1].idxTI].id << "\n";
						out << "\tcmp eax, 1\n";
						out << "\tjz m" << num_of_points << "\n";
						out << "\tjnz m" << num_of_points + 1 << "\n";
					}
					out << "\tje m" << num_of_points << "\n";
					int j = i;
				}
				break;
			}
			case LEX_RIGHTTHESIS:
			{
				if (lexT.table[i + 1].lexema == LEX_LEFTBRACE && flag_if)
				{
					out << "m" << num_of_points++ << ":\n";
				}
				break;
			}
			case LEX_PRINT:
			{
				out << "\tpush ecx\n";
				if (idT.table[lexT.table[i + 1].idxTI].iddatatype == IT::INT)
				{
					out << "\tpush " << idT.table[lexT.table[i + 1].idxTI].id << "\n\tcall OutputInt\n";
				}
				else
				{
					if (idT.table[lexT.table[i + 1].idxTI].idtype == IT::L)
						out << "\tpush offset ";
					else
						out << "\tpush ";
					out << idT.table[lexT.table[i + 1].idxTI].id << "\n\tcall OutputChar\n";
				}
				out << "\tpop ecx\n";
				out << "\tpop ecx\n";
				break;
			}
			case LEX_READ:
			{
				out << "\tpush ecx\n";
				out << "call InputInt\n";
				out << "mov " << idT.table[lexT.table[i + 1].idxTI].id << ", eax\n";
				out << "\tpop ecx\n";
				break;
			}
			}

		}
	}

	void Generation(LT::lexAndIdTable& lex, Out::OUT& log)
	{
		for (int i = 0; i < lex.idTable.size; i++) {
			strcat_s(lex.idTable.table[i].id, 20, lex.idTable.table[i].funcID.top());
		}

		out << ";========================= шапка ==============================\n";
		Head(lex, log);

		out << ";=================== сегмент констант =========================\n";
		Const(lex, log);

		out << ";=================== сегмент данных ============================\n";
		Data(lex, log);

		out << ";=================== сегмент кода ==============================\n";
		Code(lex, log);

		out << "\n;=============================================================\n";
	}
}