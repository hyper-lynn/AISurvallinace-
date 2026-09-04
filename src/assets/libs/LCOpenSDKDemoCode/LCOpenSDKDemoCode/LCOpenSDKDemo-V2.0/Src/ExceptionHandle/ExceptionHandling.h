#pragma once

#ifdef _WIN32
#include <WinSock2.h>
#include <windows.h>
#include <string>
using std::string;

class CExceptionHandling
{
public:
	CExceptionHandling();
	~CExceptionHandling();
	
	int StartMonitor(const char* szFileName); 
	int DoMiniDump(void* pExceptionInfo);
	//谨慎调用改函数，在不确定程序中还存在使用其他异常处理的情况下，不可调用。
	int PreventOtherExceptionHandling(); 

	static CExceptionHandling& GetExceptionHandling();

private:


	int CreateMiniDumpFile();
	void CloseMiniDumpFile();
	int WriteMiniDumpFile(void* pExceptionInfo);
	int DeleteExistDumpFile(const char* pcszDumpPath);

	void ReleaseAddrsSpace();
	void PrintError(const char* sDst);

	
private:
	static CExceptionHandling m_objExceptionHandling;
	HANDLE m_hFileMiniDump;
	string m_sFileName;
	void* m_pAddrsSpace; //地址空间。
};

#define GEH		CExceptionHandling::GetExceptionHandling()	
#define	R_A_S	200 * 1024 * 1024	//保留地址空间。
#else

class CExceptionHandling
{
public:
	CExceptionHandling(){};
	~CExceptionHandling(){};
	int StartMonitor(const char* szFileName){return 0;}; 
	int DoMiniDump(void* pExceptionInfo){return 0;};
	int PreventOtherExceptionHandling(){return 0;}; 
};


#endif
