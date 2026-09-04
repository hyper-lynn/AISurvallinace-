#ifndef __DAHUA_LCHLS_DEFINE_H_
#define __DAHUA_LCHLS_DEFINE_H_
#include<stdio.h>
#include<string.h>
#include <string>

namespace Dahua {
namespace LCHLS {

typedef enum
{
    HLS_DOWNLOAD_FAILED = 0,   /* 下载失败 */
    HLS_DOWNLOAD_BEGIN,       /* 开始下载切片 */
    HLS_DOWNLOAD_END,         /* 下载结束 */
    HLS_SEEK_SUCCESS,         /* seek成功 */
    HLS_SEEK_FAILED,           /* seek 失败 */
    HLS_ABORT_DONE,           /* 用于兼容旧的 */
    HLS_RESUME_DONE,          /* 用于兼容旧的 */
    HLS_DOWNLOAD_TIMEOUT,     /* 下载超时 */
    HLS_DOWNLOAD_INDEX_FAILED, /* 下载索引失败 */
    HLS_SLICE_DONE,             /* 此信号只有下载的时候关注，播放的时候忽略 */
	HLS_PAUSE_DONE,
	HLS_FRAME_EXTRACT_BEGIN = 12,    /* 开始抽帧 */
	HLS_FRAME_EXTRACT_FAILED = 13,
}HLS_CLIENT_MESSAGE;

enum ProtoType
{
    DAHUA_HLS = 0,
    APPLE_HLS = 1,
    DAHUA_LIVE_HLS = 2,
    APPLE_LIVE_HLS = 3,
    EASY_FOR_IP_HLS = 4,
    SAAS_HLS = 5,
};

enum HlsLogLevel
{
    HlsLogLevelSilent,     /// <
    HlsLogLevelErr,        /// <
    HlsLogLevelWarning,    /// <
    HlsLogLevelInfo,       /// <
    HlsLogLevelTrace,      /// <
    HlsLogLevelDebug       /// <
};

typedef void (*LogRedirect) (HlsLogLevel level, const char *log);

typedef struct HlsClientParams
{
    const char *m_m3uUrl;         /* m3u下载地址 */
    const char *m_sliceUrlPrefix; /* 切片下载url前缀 */
    float m_startTime;            /* 视频开始的时间 */
    float m_seekTime;             /* 下载开始播放的时间 */
	float m_endTime;              /* 下载结束播放的时间 */
    int m_timeout;                /* 超时时间，单位: 秒 */
    ProtoType m_protoType;        /* 协议类型 */
    const char *m_sToken;         /*用于统一SAAS HLS播放*/
	
	void *m_userPtr;              /* 用于m_stream_data，m_msg_callback两个回调函数的 userptr */
    void (*m_stream_data)(const char *buf, int len, void *userptr);
    void (*m_msg_callback)(HLS_CLIENT_MESSAGE msg, void *userptr);
    LogRedirect m_logRedirect;

	int m_iFrameExtractInv;     /* 用于设置抽帧时间间隔，比如2秒，4秒，默认0表示不抽帧 */
	float m_fFrameExtractStartTime; /* 视频开始时间 */

	/*easy for ip
    {
        "username":"189699032222",
        "password":"xxxxxxxxx",
        "host":"www.lechange.cn",
        "bucket":"",
        "path":"",
        "url":"http://54.199.243.1:15110",
    }*/

    const char *m_JsonString;
    HlsClientParams()
    {
        memset(this, 0, sizeof(HlsClientParams));
    }
}HLS_CLIENT_PARAMS;


}
}
#endif
