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
    static int DecryptPic(const char *pSrcBufIn,int srcBufLenIn,const char *encryptKey,const char *sDevId,const char *sDevPwd,char *pDestBufOut,int& destBufLenOut);
	static int DecryptPicEx(const char *pSrcBufIn, int srcBufLenIn, const char *encryptKey, const char* accessToken, const char* deviceId, const char *sDevPwd, char *pDestBufOut, int& destBufLenOut);

    static void SetLogInfo(OpenSDK_LogLevel level = All, 
                           const char* fileName = "LCOpenSDK", 
                           int maxSize = 10*1024*1024, 
                           OpenSdk_LogFileMode fileMode = NewFile); //setMobileLogFile,setMobileLogLevel

	static void SetMobileLogFile(const char* fileName = "LCOpenSDK", int maxSize = 10*1024*1024, OpenSdk_LogFileMode fileMode = NewFile);

	static void SetMobileLogLevel(OpenSDK_LogLevel level = All);

	static void setSaveStreamFlag(bool isOpen);

	static const char* getSaveStreamPath();

	static void computeMD5Lower(const char* srcStr, char outStr[128]);

	static void computeMD5Upper(const char* srcStr, char outStr[128]);
	static char *hmac_sha512(const char * key, const char * data, char outData[128]);
	static char *sha512Cry(const char * data);

	/* Cut16(Base64(MD5Lower("HS:"+MD5Lower(KeySeed)))) */
	static void compute1(const char* srcStr, char outStr[128]);

	/* Cut16(Base64(MD5Upper("HS:"+MD5Upper(KeySeed)))) */
	static void compute2(const char* srcStr, char outStr[128]);

	static void getMac(char outMac[128]);

	static void getOsVersion(char version[128]);

	static void loadSubModules();
 
private:
	static bool m_isOpenSaveStreamFlag;
};

#endif /* _LCOPENSDK_UTILS_H_ */
