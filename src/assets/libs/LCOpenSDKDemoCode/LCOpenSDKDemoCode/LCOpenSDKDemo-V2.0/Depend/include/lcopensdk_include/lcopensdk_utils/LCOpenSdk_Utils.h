#ifndef _LCOPENSDK_UTILS_H_
#define _LCOPENSDK_UTILS_H_

#include "lcopensdk_global.h"

class LCOPENSDK_EXPORT LCOpenSdk_Utils
{
public:

    enum OpenSDK_LogLevel
    {
        Fatal,                  /* 致命错误 */
        Err,                    /* 错误 */
        Warning,                /* 可能导致出错 */
        Info,                   /* 告知用户当前运行状态 */
        Debug,                  /* 详细调试信息 */
        All,                    /* 所有日志 */
    };

    enum OpenSdk_LogFileMode
    {
        NewFile,                /* 新文件追加模式 */
        RollFile,               /* 双文件滚动模式 */
        Unvalid,                /* 非法写日志文件 */
    };

    LCOpenSdk_Utils();
    ~LCOpenSdk_Utils();
    static int DecryptPic(const char *pSrcBufIn,int srcBufLenIn,const char *encryptKey,char *pDestBufOut,int& destBufLenOut);
	static int DecryptPicEx(const char *pSrcBufIn, int srcBufLenIn, const char *encryptKey, const char* accessToken, const char* deviceId, char *pDestBufOut, int& destBufLenOut);

	/*****************************************************************************
	* @函数功能: 设备密码加密
	* @参数 1  : devicePwd（需要加密的明文）
	* @参数 2  : deviceID
	* @参数 3  : appSecret
	* @参数 4  : encryptDevPwd（加密的密码）
	* @返 回 值:  true/false
	*****************************************************************************/
	static bool EncryptDevPwd(const char* devicePwd,const char* deviceID,const char* appSecret,char* encryptDevPwd);

    static void SetLogInfo(OpenSDK_LogLevel level = All, 
                           const char* fileName = "LCOpenSDK", 
                           int maxSize = 10*1024*1024, 
                           OpenSdk_LogFileMode fileMode = NewFile);
 
};

#endif /* _LCOPENSDK_UTILS_H_ */
