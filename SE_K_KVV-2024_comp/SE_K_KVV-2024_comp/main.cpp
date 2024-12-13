#include "stdafx.h"
#include <iostream>
#include <time.h>

#include <iomanip>

#include "Error.h"	
#include "Parm.h"		
#include "Log.h"		
#include "In.h"			



using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	system("color");
	setlocale(LC_ALL, "RUS");

#ifdef DEBUG
	try {
		cout << "--------- ���� geterror ---------\n\n";
		throw ERROR_THROW(100);
	}
	catch (Error::ERROR e)
	{
		cout << "������ " << e.id << ": " << e.message << endl;
		if (e.id == 111) {
			cout << "C����� " << e.inext.line + 1 << " ������� " << e.inext.col + 1 << "\n\n";
		}
	}


	try {
		cout << "--------- ���� geterrorin ---------\n\n";
		throw ERROR_THROW_IN(111, 7, 7);
	}
	catch (Error::ERROR e)
	{
		cout << "������ " << e.id << ": " << e.message << endl;
		if (e.id == 111) {
			cout << "C����� " << e.inext.line + 1 << " ������� " << e.inext.col + 1 << "\n\n";
		}
	}
	try {
		cout << "--------- ���� getparm ---------\n\n";
		Parm::PARM parm = Parm::getparm(argc, argv);
	}
	catch (Error::ERROR e)
	{
		cout << "������ " << e.id << ": " << e.message << endl;
		if (e.id == 111) {
			cout << "C����� " << e.inext.line + 1 << " ������� " << e.inext.col + 1 << "\n\n";
		}
	}

	
	exit(0);
#endif 



	Log::LOG log = Log::INITLOG;
	Out::OUT out;
	try
	{
		LT::Create(10);
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLine(log, (char*)"����", (char*)" ��� ������ \n", "");
		Log::WriteLine(log, (wchar_t*)L"����", (wchar_t*)L" ��� ������ \n", L"");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		out = Out::getOut(parm.out);
		In::IN in = In::getin(parm.in);
		if (parm.deb) {
			cout << in.text << endl;
		}
		cout << "����� ��������: " << in.size << endl;
		cout << "����� �����: " << in.lines << endl;
		cout << "���������: " << in.ignor << endl;


		Log::WriteIn(log, in); 
		
		LT::LexTable lextable = LT::Create(in.count_words); 
		IT::IdTable idtable = IT::Create(in.count_words);
		FST::GetLexOrID(in, lextable, idtable);
		if (parm.deb) {
			Log::WriteLex(log, lextable, idtable);
		}

		MFST_TRACE_START
			MFST::Mfst mfst(lextable, GRB::getGreibach());
		mfst.start(log, parm.deb);

		mfst.savededucation();

		if (parm.deb) {
			mfst.printrules(log);
		}


		
		

		PLN::findN(lextable, idtable);
		if (parm.deb) {
		std::cout << "28<<: �������� ������ ���������" << std::endl;


			Log::WriteLex(log, lextable, idtable);
		}





		IT::Delete(idtable);
		LT::Delete(lextable);
		In::Delete(in);
		Out::Close(out);
	}

	catch (Error::ERROR e)
	{
		
		if (e.id == 111) {
			cout << e.inext.text << endl; 
			cout << "\033[31m������\033[32m " << e.id << "\033[0m: " << e.message << endl; 
			cout << "C�����: " << "\033[32m" << e.inext.line + 1 << "\033[0m"
				<< ", �������: " << "\033[32m" << e.inext.col + 1 << "\033[0m\n\n"; 
			Out::WriteError(out, e);
		}
		else if ((e.id >= 90 && e.id <= 97) || (e.id == 65)) {
			cout << e.inext.rtext << endl; 
			cout << "\033[31m������\033[32m " << e.id << "\033[0m: " << e.message << endl; 
			cout << "C�����: " << "\033[32m" << e.inext.line + 1 << "\033[0m"
				<< std::endl << "�������:\033[32m \"" << e.inext.text << "\"\033[0m\n\n"; 
		}
		else {
			cout << "\033[31m������:\033[32m " << e.id << "\033[0m: " << e.message << endl; 
		}
		if (log.stream != NULL) {
			Log::WriteError(log, e);
			Log::Close(log);
		}
		system("pause");
		return e.id;
	}
	system("pause");

	
	return 0;
}

