
#ifndef __FILE_CONSOLE_LOGGER_H__
#define __FILE_CONSOLE_LOGGER_H__
/*
* Copyright (c) 2010, 浙江大华
* All rights reserved.
*
* 文件名称：FileConsoleLogger.h
* 文件标识：
* 摘　　要：提供文件和控制台日志的单件类
*

* 当前版本：1.0
* 原作者　：高圩
* 完成日期：2010年01月28日
* 修订记录：创建
*/
#include "Utils/Singleton.h"
#include "AX_API/AX_Logger.h"

class DOAX_DEPRECATED CFileConsoleLogger
{
	friend class Singleton<CFileConsoleLogger>;
public:
	CLogger* getLogger(void) { return _logger; }

	int setFileLog(LEVEL level, const char* filename);
	int setConsoleLog(LEVEL level);

protected:
	CLogger         *_logger;
	CFileLogHandler *_filelog;
	int             _fileHandleIndex;
	CFileLogHandler *_consolelog;
	int             _consoleIndex;

protected:
	CFileConsoleLogger(void);
	~CFileConsoleLogger(void);
};

typedef Singleton<CFileConsoleLogger> FCLoggerSingleton;
#define FILE_CONSOLE_LOGGER FCLoggerSingleton::instance()->getLogger()->logf

#endif
