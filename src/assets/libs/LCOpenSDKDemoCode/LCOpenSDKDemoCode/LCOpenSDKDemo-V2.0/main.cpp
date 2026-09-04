#include "Src/View/LCOpenSDKDemo.h"
#include "Src/ExceptionHandle/ExceptionHandling.h"
#include <QApplication>
#include <QTranslator>

#include "Windows.h"
#include <direct.h>
#include <string>
#include "DbgHelp.h"
using namespace std;


#if _MSC_VER>=1900
#include "stdio.h" 
_ACRTIMP_ALT FILE* __cdecl __acrt_iob_func(unsigned);
#ifdef __cplusplus 
extern "C"
#endif 
FILE* __cdecl __iob_func(unsigned i) {
	return __acrt_iob_func(i);
}
#endif /* _MSC_VER>=1900 */

bool g_isReleasedForOverseas = false;



std::string current_working_directory()
{
	char buff[250];
	_getcwd(buff, 250);
	std::string current_working_directory(buff);
	return current_working_directory;
}


LONG WINAPI ExpFilter(struct _EXCEPTION_POINTERS *pExpInfo)
{
	string sAppDirectory = ::current_working_directory();
	string sDumpDirectory;
	SYSTEMTIME tm;
	GetLocalTime(&tm);

	string sDumpFile = "LCOpenSDKCrash.dmp";
	HANDLE hFile = CreateFileA(sDumpFile.c_str(),
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (INVALID_HANDLE_VALUE != hFile)
	{
		MINIDUMP_EXCEPTION_INFORMATION einfo;
		einfo.ThreadId = GetCurrentThreadId();
		einfo.ExceptionPointers = pExpInfo;
		einfo.ClientPointers = FALSE;

		MiniDumpWriteDump(
			GetCurrentProcess(),
			GetCurrentProcessId(),
			hFile,
			MiniDumpNormal,
			&einfo,
			NULL,
			NULL);

		CloseHandle(hFile);
	}

	return EXCEPTION_EXECUTE_HANDLER;
}


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTranslator* trans = new QTranslator;
	g_isReleasedForOverseas = !(trans->load("ch.qm"));
	a.installTranslator(trans);
	LCOpenSDKDemo w;
	w.show();

	::SetUnhandledExceptionFilter(ExpFilter);
	return a.exec();
}
