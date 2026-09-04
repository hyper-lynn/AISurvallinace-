#ifndef __DAHUA_STREAMAPP_RTMPUTIL_H__
#define __DAHUA_STREAMAPP_RTMPUTIL_H__

#include <string.h>
#include "Infra/IntTypes.h"
#include "Infra/Function.h"

namespace Dahua{
namespace StreamApp{

///\brief rtmp 服务配置
enum rtmp_svr_config_t
{
	RtmpSvrConfigSendBufSize = 0,		///< 设置服务端发送媒体数据的缓冲区大小.opt配置以字节为单位
	RtmpSvrConfigStreamSinkCreateProc,	///< RTMP数据槽创建函数
	RtmpSvrConfigMax = 100,
};

///\brief sdp 初始化SDP 回调函数
///\param [in] bool                  -初始化成功或者失败
///\param [in] const char *   -初始化sdp 信息
///\param [in] void *              -保留参数,暂无作用
typedef Dahua::Infra::TFunction3<void, bool, const char *, void *> InitREventProc;

///\brief rtmp 服务统计信息类型枚举
enum rtmpStatisticType
{
	RtmpSessionStatistic = 0,      ///< 会话信息统计, 对应的信息为rtmpSessionInfo
	RtmpStreamCountStatistic,	   ///< 直播流源引用信息统计, 对应的信息为rtmpStreamCountInfo	
};

///\brief rtmp会话统计信息
struct rtmpSessionInfo
{
	uint32_t liveSessions;          ///< 直播会话数目
	uint32_t vodSessions;           ///< 点播会话数目
	int reserve[8];             	///< 保留字段，暂未使用

	rtmpSessionInfo()
	{
		liveSessions = 0;
		vodSessions  = 0;
		memset(reserve, 0, sizeof(reserve));
	}	
};

///\brief rtmp 直播流源引用统计信息
struct rtmpStreamCountInfo
{
	char    *sourceid;				///< 流源ID , 通常为URL 中IP:PORT/APP/PLAYPATH 的APP/PLAYPATH 部分	
	long     refcount;				///< 流源ID 对应的引用计数

	rtmpStreamCountInfo():sourceid(NULL), refcount(0)
	{}
};

}
}

#endif

