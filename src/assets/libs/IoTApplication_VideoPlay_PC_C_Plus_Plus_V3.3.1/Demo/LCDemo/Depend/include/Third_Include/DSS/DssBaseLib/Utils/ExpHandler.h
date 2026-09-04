#ifndef EXP_HANDLER_H_INCLUDED
#define EXP_HANDLER_H_INCLUDED

#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
//#include <DbgHelp.h>
#endif

#ifndef DOAX_DEPRECATED
#ifdef _WIN32
// 放在class关键字后面，以及函数或者变量定义的前面
#define DOAX_DEPRECATED	__declspec(deprecated)
#else
#define DOAX_DEPRECATED	__attribute__ ((deprecated))
#endif // #ifdef WIN32
#endif // #ifndef DOAX_DEPRECATED

class DOAX_DEPRECATED CExpHandler
{
public:
	typedef int (*MainProc)(int argc,char* argv[]);

	static int run(MainProc mainProc,int argc,char* argv[],bool sehEnable=true);
	static int run(bool sehEnable=true);
	static int tmpMain(int argc,char* argv[]);
public:
	static int _unknowExceptionCount;
	static int _ignoreExceptionCount;
protected:
	static int runVEH(MainProc mainProc,int argc,char* argv[]);
	static int runSEH(MainProc mainProc,int argc, char* argv[]);
protected:
#if defined(_WIN32) || defined(_WIN64)
	static char*   _buf;
	static HANDLE  _file;
	static HANDLE  _currentProcess;
	static DWORD   _currentProcessId;
	static int	   _fatalExceptionCount;
	static void makeReady();
	static LONG WINAPI VEHHandler(struct _EXCEPTION_POINTERS *ExceptionInfo);
	static LONG WINAPI SEHHandler(struct _EXCEPTION_POINTERS *ExceptionInfo);
	static void createMiniDump(struct _EXCEPTION_POINTERS *ExceptionInfo);
#endif
};

#endif
