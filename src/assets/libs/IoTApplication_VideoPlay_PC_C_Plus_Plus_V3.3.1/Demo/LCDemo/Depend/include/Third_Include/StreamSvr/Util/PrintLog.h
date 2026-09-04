#ifndef __INCLUDE_DAHUA_STREAMSVR_PRINTLOG_H__
#define __INCLUDE_DAHUA_STREAMSVR_PRINTLOG_H__

#include <stdarg.h>
#include "Infra/Mutex.h"
#include "StreamSvr/Defs.h"
#include "Infra/Thread.h"
///\ <1> 用户使用的宏
///\ 日志等级设定，等级越高，输出内容越少

///\ DEBUG ： 调试信息，以及正常情况的非关键路径，或者频繁出现的地方，正常情况下不打印，供调试使用，数量也要控制
#define DLOG_LEVEL_DEBUG		2

///\ INFO ： 正常情况，开始时可以多些，随稳定性提高逐步减少，最后只保留关键点，例如session创建和销毁
#define DLOG_LEVEL_INFO		4
#define DLOG_LEVEL_WARN		5
///\ ERR ： 严重问题，不应该出现的，需要引起注意，需要处理的
#define DLOG_LEVEL_ERR		6

///\ CIRCUIT : 记录业务的请求以及响应，不受打印等级限制,并且该等级使用流媒体库日志输出 
#define DLOG_LEVEL_CIRCUIT	0

///\ 日志设置
#define DLOG_SET_FILE( filename, size)	( Dahua::StreamSvr::CPrintLog::instance()->setFile( filename, size ) )
#define DLOG_SET_SIZE( size)			( Dahua::StreamSvr::CPrintLog::instance()->setLogSize( size ) )
#define DLOG_SET_CONSLOG( enable )	( Dahua::StreamSvr::CPrintLog::instance()->setConsoleLog( enable ) )
#define DLOG_SET_SYSLOG( enable )		( Dahua::StreamSvr::CPrintLog::instance()->setSyslog( enable ) )
#define DLOG_SET_LEVEL( level )			( Dahua::StreamSvr::CPrintLog::instance()->setLevel( level ) )
#define DLOG_SET_INFRALOG( enable )		( Dahua::StreamSvr::CPrintLog::instance()->enableInfraPrint( enable ) )

///\ 可以单独设置某个特定模块的level，最大支持64个，通常用于需要对某些特定模块进行详细日志分析
#define DLOG_SET_MODULE_LEVEL( module_name, level ) ( Dahua::StreamSvr::CPrintLog::instance()->setModuleLevel( module_name, level ) )

///\ 注册日志回调
#define DLOG_ATTACH_LOG_PROC( proc )				( Dahua::StreamSvr::CPrintLog::instance()->attachLogproc( proc ) )

///\ 注销日志回调
#define DLOG_DETACH_LOG_PROC( proc )				( Dahua::StreamSvr::CPrintLog::instance()->detachLogproc( proc ) )

///\ 具体模块可以定义自己的模块名称，需要时可以特定过滤，CPP文件中先定义DLOG_MODULE宏，再 #include "PrintLog.h"
#ifndef DLOG_MODULE
#define DLOG_MODULE ""
#endif

///\ 模块名称
#ifndef DLOG_MODNAME
#define DLOG_MODNAME ""
#endif

///\ 模块版本信息
#ifndef DLOG_VERSION
#define DLOG_VERSION ""
#endif

///\ 是否正式发布版本
#ifndef DLOG_LIB_REALSE
#define DLOG_LIB_REALSE false
#endif

///\ 具体输出日志的宏
#define DLOG_ERR( fmt, ... )		( Dahua::StreamSvr::CPrintLog::instance()->log( __FILE__, __LINE__, __FUNCTION__, DLOG_MODNAME, DLOG_VERSION, DLOG_LIB_REALSE, DLOG_LEVEL_ERR, fmt, ##__VA_ARGS__ ) )
#define DLOG_WARN( fmt, ... )		( Dahua::StreamSvr::CPrintLog::instance()->log( __FILE__, __LINE__, __FUNCTION__, DLOG_MODNAME, DLOG_VERSION, DLOG_LIB_REALSE, DLOG_LEVEL_WARN, fmt, ##__VA_ARGS__ ) )
#define DLOG_INFO( fmt, ... )	( Dahua::StreamSvr::CPrintLog::instance()->log( __FILE__, __LINE__, __FUNCTION__, DLOG_MODNAME, DLOG_VERSION, DLOG_LIB_REALSE, DLOG_LEVEL_INFO, fmt, ##__VA_ARGS__ ) )
#define DLOG_DEBUG( fmt, ... )	( Dahua::StreamSvr::CPrintLog::instance()->log( __FILE__, __LINE__, __FUNCTION__, DLOG_MODNAME, DLOG_VERSION, DLOG_LIB_REALSE, DLOG_LEVEL_DEBUG, fmt, ##__VA_ARGS__ ) )
#define DLOG_CIRCUIT( fmt, ... )	( Dahua::StreamSvr::CPrintLog::instance()->log( __FILE__, __LINE__, __FUNCTION__, DLOG_MODNAME, DLOG_VERSION, DLOG_LIB_REALSE, DLOG_LEVEL_CIRCUIT, fmt, ##__VA_ARGS__ ) )

#define DLOG_ASSERT(ASSERT_CASE, fmt, ...) \
{\
	if (!(ASSERT_CASE)) \
	{\
		( Dahua::StreamSvr::CPrintLog::instance()->log( __FILE__, __LINE__, __FUNCTION__, DLOG_MODNAME, DLOG_VERSION, DLOG_LIB_REALSE, DLOG_LEVEL_ERR, fmt, ##__VA_ARGS__ ) ); \
		assert(0); \
	}\
}


//////// 可以输出this 和 当前线程id的日志宏
#define DLOG_ERR_THIS( fmt, ...) ( Dahua::StreamSvr::CPrintLog::instance()->log(\
										__FILE__, __LINE__, __FUNCTION__, DLOG_MODNAME, DLOG_VERSION, DLOG_LIB_REALSE, DLOG_LEVEL_ERR, "[%p], " fmt, this, ##__VA_ARGS__ ) )
										
#define DLOG_WARN_THIS( fmt, ...) ( Dahua::StreamSvr::CPrintLog::instance()->log(\
										__FILE__, __LINE__, __FUNCTION__, DLOG_MODNAME, DLOG_VERSION, DLOG_LIB_REALSE, DLOG_LEVEL_WARN, "[%p], " fmt, this, ##__VA_ARGS__ ) )

#define DLOG_INFO_THIS( fmt, ...) ( Dahua::StreamSvr::CPrintLog::instance()->log(\
										__FILE__, __LINE__, __FUNCTION__, DLOG_MODNAME, DLOG_VERSION, DLOG_LIB_REALSE, DLOG_LEVEL_INFO, "[%p], " fmt, this, ##__VA_ARGS__ ) )
										
#define DLOG_DEBUG_THIS( fmt, ...) ( Dahua::StreamSvr::CPrintLog::instance()->log(\
										__FILE__, __LINE__, __FUNCTION__, DLOG_MODNAME, DLOG_VERSION, DLOG_LIB_REALSE, DLOG_LEVEL_DEBUG, "[%p], " fmt, this, ##__VA_ARGS__ ) )

#define DLOG_ASSERT_THIS(ASSERT_CASE, fmt, ...) \
{\
	if (!(ASSERT_CASE)) \
	{\
		( Dahua::StreamSvr::CPrintLog::instance()->log(\
										__FILE__, __LINE__, __FUNCTION__, DLOG_MODNAME, DLOG_VERSION, DLOG_LIB_REALSE, DLOG_LEVEL_ERR, "[%p], " fmt, this, ##__VA_ARGS__ ) ); \
		assert(0); \
	}\
}

#define ASSERT_LOG(ASSERT_CASE, ASSERT_LOG) \
{\
	if (!(ASSERT_CASE)) \
	{\
		(ASSERT_LOG); \
		assert(0); \
	}\
}

// 调试点结构体
struct STREAM_DBG_POINT 
{
    char    file[64];		//调试文件
	char	proc[64];       //调试函数
};

STREAMSVR_API extern struct STREAM_DBG_POINT gStreamDebugPoint;

// 跟踪打印宏 DEBUG_INFO, 用于可开关的调试打印
#define  DEBUG_INFO(fmt, ...)   \
     if (('\0' != gStreamDebugPoint.file[0]) || ('\0' != gStreamDebugPoint.proc[0]))  \
     {\
        if (('\0' == gStreamDebugPoint.proc[0]) && (NULL != strstr(__FILE__, gStreamDebugPoint.file)))\
        {\
            (Dahua::StreamSvr::CPrintLog::instance()->log(\
										__FILE__, __LINE__, __FUNCTION__, DLOG_MODNAME, DLOG_VERSION, DLOG_LIB_REALSE, DLOG_LEVEL_CIRCUIT, "[%p], " fmt, this, ##__VA_ARGS__ ) ); \
        }\
        else if ((0 == strcmp(gStreamDebugPoint.proc, __FUNCTION__)) && (NULL != strstr(__FILE__, gStreamDebugPoint.file))) \
        {\
            (Dahua::StreamSvr::CPrintLog::instance()->log(\
										__FILE__, __LINE__, __FUNCTION__, DLOG_MODNAME, DLOG_VERSION, DLOG_LIB_REALSE, DLOG_LEVEL_CIRCUIT, "[%p], " fmt, this, ##__VA_ARGS__ ) ); \
        }\
     }  


namespace Dahua{
namespace StreamSvr{
class CPrintLogImpl;

///\brief 日志回调函数
///\param [in]  日志信息
///\return 0 成功, -1失败
typedef Infra::TFunction1<int, char const*> LogProc;	

class STREAMSVR_API CPrintLog
{
public:
	///\brief 默认构造函数
	CPrintLog();
	
	///\brief 析构函数
	~CPrintLog();
	
	///\brief 获取CPrintLog实例
	static CPrintLog * instance();
	
	///\brief 设置日志文件路径和文件大小
	///\param [in] szFileName -- 日志文件路径
	///\param [in] szFileSize -- 0--不限制日志文件大小  >0 --日志文件大小上限
	///\return 0 -- 成功   -1 -- 失败
	int setFile( const char* szFileName, int szFileSize );
	
	///\brief 开启日志文件大小限制
	///\param [in] szFileSize -- 0--关闭日志文件大小限制  >0 --日志文件大小上限(KB)
	///\return 0 -- 成功   -1 -- 失败
	int setLogSize( int szLogSize );
	
	///\brief 开启控制台打印输出
	///\param [in] enable -- true--开启控制台输出  false -- 关闭控制台打印输出
	///\return 0 -- 成功   -1 -- 失败
	int setConsoleLog( bool enable );

	///\brief 开启系统打印输出
	///\param [in] enable -- true--开启系统台输出  false -- 关闭系统打印输出
	///\return 0 -- 成功   -1 -- 失败
	int setSyslog( bool enable );
	
	///\brief 设置普通打印等级
	///\param [in] level -- 等级大于level的则输出，等级小于的则不输出
	///\return 0 -- 成功   -1 -- 失败
	int setLevel( int level );

	///\brief 设置模块打印等级
	///\param [in] module -- 模块名称，由DLOG_MODULE宏定义中设置进来，module数量满时不能设置，module == NULL表示清空所有设置
	///\param [in] level -- 模块打印等级，模块中大于这个等级的则给与打印 -1表示删除
	///\return 0 -- 成功   -1 -- 失败
	int setModuleLevel( const char * module, int level );
	
	///\brief 用于打印信息
	///\param [in] file -- 打印所在文件的名称
	///\param [in] line -- 打印所在的行号
	///\param [in] func -- 打印的函数
	///\param [in] module -- 输出打印的模块
	///\param [in] version -- 输出打印的模块版本信息
	///\param [in] release -- 输出打印的模块是否正式版本
	///\param [in] level -- 输出打印的等级，DLOG_LEVEL_ERROR、DLOG_LEVEL_INFO、DLOG_LEVEL_DEBUG等
	///\return 0 -- 成功   -1 -- 失败
	int log(const char *file, int line, const char *func, const char * module, const char *version, bool release, int level, const char *fmt, ... );

	///\brief 用于打印信息, 注意由外部调用va_end 进行ap 相关内存的释放
	///\param [in] file -- 打印所在文件的名称
	///\param [in] line -- 打印所在的行号
	///\param [in] func -- 打印的函数
	///\param [in] module -- 输出打印的模块
	///\param [in] version -- 输出打印的模块版本信息
	///\param [in] release -- 输出打印的模块是否正式版本
	///\param [in] level -- 输出打印的等级，DLOG_LEVEL_ERROR、DLOG_LEVEL_INFO、DLOG_LEVEL_DEBUG等
	///\return 0 -- 成功   -1 -- 失败
	int logV(const char *file, int line, const char *func, const char * module, const char *version, bool release, int level, const char *fmt, va_list ap);

	///\brief 注册日志回调函数
	///\param [in] proc -- 回调函数
	///\return 0 -- 成功   -1 -- 失败
	int attachLogproc(LogProc proc);

	///\brief 注销日志回调函数
	///\param [in] proc --回调函数
	///\return 0 -- 成功   -1 -- 失败
	int detachLogproc(LogProc proc);

	///\brief 使能Infra 库打印, 关闭后, 使用流媒体库实现的日志功能
	///\param [in] enable --使能状态
	///\return 0 -- 成功   -1 -- 失败
	int enableInfraPrint(bool enable);
private:
	CPrintLogImpl *m_impl;
};

}//StreamSvr
}//Dahua

#endif //__INCLUDE_DAHUA_STREAMSVR_PRINTLOG_H__
