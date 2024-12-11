#include "stdafx.h"
#include "Parm.h"
#include "Error.h"

namespace Parm
{
	PARM getparm(int argc, _TCHAR* argv[])
	{
		PARM parm;
		bool bIN = false, bOUT = false, bLOG = false;
		parm.deb = false;

		for (int i = 0; i < argc; i++)
		{
			if (wcslen(argv[i]) > PARM_MAX_SIZE)
				throw ERROR_THROW(104);

			if (wcsstr(argv[i], PARM_IN)) {
				wcscpy_s(parm.in, wcsstr(argv[i], L":") + 1);
				bIN = true;
			}

			if (wcsstr(argv[i], PARM_OUT)) {
				wcscpy_s(parm.out, wcsstr(argv[i], L":") + 1);
				bOUT = true;
			}

			if (wcsstr(argv[i], PARM_LOG)) {
				wcscpy_s(parm.log, wcsstr(argv[i], L":") + 1);
				bLOG = true;
			}

			if (wcsstr(argv[i], PARM_DEB))
				parm.deb = true;

			if (wcsstr(argv[i], PARM_HELP)) {
				cout << endl << "SE_K_KVV-2024_comp.exe \033[32m-in:INFILE [-out:OUTFILE] [-log:LOGFILE] [-debug]\033[0m" << endl << endl;
				cout <<	"\t\033[32m-in:INFILE\033[0m - параметр расположения файла ввода, где \033[32mINFILE\033[0m - путь до файла" << endl;
				cout << "\t\033[32m-out:OUTFILE\033[0m - параметр расположения файла вывода, где \033[32mOUTFILE\033[0m - путь до файла" <<
					"(по умолчанию \033[32mINFILE.out\033[0m)" << endl;
				cout << "\t\033[32m-log:LOGFILE\033[0m - параметр расположения файла логирования, где \033[32mLOGFILE\033[0m - путь до файла" <<
					"(по умолчанию \033[32mINFILE.log\033[0m)" << endl;
				cout << "\t\033[32m-debug\033[0m - ключ вывода полной информации(по умолчанию \033[31mвыкл\033[0m)" << endl;
				exit(0);
			}
		}

		if (!bIN) {
			throw ERROR_THROW(100)
			//wcscpy_s(parm.in, L"in.txt");
		}

		if (!bOUT)
		{
			wcscpy_s(parm.out, parm.in);
			wcscat_s(parm.out, PARM_OUT_DEFAULT_EXT);
		}
		else {
			if (wcsstr(parm.out, parm.in)) {
				throw ERROR_THROW(115)
			}
		}

		if (!bLOG)
		{
			wcscpy_s(parm.log, parm.in);
			wcscat_s(parm.log, PARM_LOG_DEFAULT_EXT);
		}
		else {
			if (wcsstr(parm.log, parm.out) || wcsstr(parm.log, parm.in))
				throw ERROR_THROW(114)
		}
		return parm;
	}
};