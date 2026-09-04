
#ifndef LogTime_h__
#define LogTime_h__

#include "../globaldef.h"
#include "platform.h"
#include <string>

// Log Level
enum Log_Level{
    Log_Error   = 0,
    Log_Info    = 1,
    Log_Debug   = 2,
};

/*
    统计某一个函数的费时多少
*/
class INTERFACE_API_CLASS CLogTime
{
public:
    CLogTime( const char*, Log_Level level = Log_Debug );
    ~CLogTime(void);

    void SetLog( const char*, ... );
    void ShowLog();

private:
    const char* m_szName;
    bool        m_showLog;
    DWORD       m_time;
    std::string m_strContent;
    Log_Level   m_level;
};

// show / hide log
INTERFACE_API void SetLogFlag(bool bShow);
// set log level
INTERFACE_API void SetLogLevel(Log_Level level);
// to show content log
INTERFACE_API void DHLog(Log_Level, const char*, ...);

#endif // LogTime_h__

