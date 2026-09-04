
#ifndef _LCOPENSDK_PARAM_H_
#define _LCOPENSDK_PARAM_H_
#include <string>
#include "lcopensdk_global.h"

/**
* 流媒体模式
*/
typedef enum
{
	STREAM_MAIN = 0,        //主码流
	STREAM_MINOR_1,     //辅码流1
	STREAM_MINOR_2,     //辅码流2
	STREAM_MINOR_3,     //辅码流3
}DEFINITION_MODE;

/**
* 云录像类型
*/
typedef enum
{
	RECORD_TYPE_ALL = 0,      /* 全部 */
	RECORD_TYPE_ALARM = 1000, /* 报警 */
	RECORD_TYPE_TIMING = 2000  /* 定时 */ 
}RECORD_TYPE;

/**
* 参数模型基类
*/
class LCOPENSDK_EXPORT LCOpenSDK_Param {
public:
	LCOpenSDK_Param();
	~LCOpenSDK_Param();
public:	
	const char* accessToken; /* 管理员Token或用户Token */ 
    const char* deviceID;    /* 设备序列号 */
	const char* pid;     /* 设备pid */
	int         channel;     /* 通道号 */
	const char* psk;         /* 秘钥(如果不是用户自定义秘钥，则为设备序列号) */
	const char* playToken;   /* 播放token(此值可为空，但是传空会增加拉流耗时) */
};

/**
* 预览参数模型
*/
class LCOPENSDK_EXPORT LCOpenSDK_ParamReal:public LCOpenSDK_Param {
public:
	LCOpenSDK_ParamReal();
	~LCOpenSDK_ParamReal();
public:	
	DEFINITION_MODE defiMode;          /* 流媒体模式HD/SD */ 
	bool            assistStreamEnable;/* 是否开启辅助帧(当设备支持时才有效) */ 
	bool            isTls;             /* 是否TLS加密使能 */   
	int             imageSize;         /* 多档分辨率切换传递 */   
};

/**
* 本地录像文件按文件名播放
*/
class LCOPENSDK_EXPORT LCOpenSDK_ParamDeviceRecordFileName:public LCOpenSDK_Param {
public:
	LCOpenSDK_ParamDeviceRecordFileName();
	~LCOpenSDK_ParamDeviceRecordFileName();
public:	
	const char* fileName;   /* 设备本地录像文件名 */ 
	double      offsetTime; /* 偏移时间 */ 
	bool        isTls;      /* 是否TLS加密使能 */
};

/**
* 本地录像文件按时间播放
*/
class LCOPENSDK_EXPORT LCOpenSDK_ParamDeviceRecordUTCTime:public LCOpenSDK_Param {
public:
	LCOpenSDK_ParamDeviceRecordUTCTime();
	~LCOpenSDK_ParamDeviceRecordUTCTime();
public:	
	DEFINITION_MODE defiMode;   /* 流媒体模式HD/SD */ 
	long            beginTime;  /* 开始时间 */ 
	long            endTime;    /* 结束时间 */ 
	bool            isTls;      /* 是否TLS加密使能 */  
	double			offsetTime; /* 偏移时间 */ 
};

/**
* 云录像播放
*/
class LCOPENSDK_EXPORT LCOpenSDK_ParamCloudRecord:public LCOpenSDK_Param {
public:
	LCOpenSDK_ParamCloudRecord();
	~LCOpenSDK_ParamCloudRecord();
public:	
	const char* recordRegionID; /* 录像ID */ 
	double      offsetTime;     /* 偏移时间 */ 
	RECORD_TYPE recordType;     /* 录像类型 */
	int         timeout;        /* 超时时间 */    
};

/**
* 语音对讲
*/
class LCOPENSDK_EXPORT LCOpenSDK_ParamTalk:public LCOpenSDK_Param {
public:
	LCOpenSDK_ParamTalk();
	~LCOpenSDK_ParamTalk();
public:	
	bool            isTls;      /* 是否使用TLS加密处理 */
};

/**
* 长链接云台控制
*/
class LCOPENSDK_EXPORT LCOpenSDK_ParamControlPTZ:public LCOpenSDK_Param {
public:
	LCOpenSDK_ParamControlPTZ();
	~LCOpenSDK_ParamControlPTZ();
public:	
	const char*           operation;      /*操作行为  0-上，1-下，2-左，3-右，4-左上，5-左下，6-右上，7-右下，8-放大，9-缩小，10-停止*/ 
	long                  duration;      /* 移动持续时间，单位毫秒 */
};



#endif