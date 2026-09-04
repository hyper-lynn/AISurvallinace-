/**
 * Copyright (c) 2014~2015, 浙江大华系统工程有限公司 All rights reserved.
 * \file		lmu_sdk.h
 * \brief		lmu_sdk
 * \author		24997
 * \date		2014年2月12日
 * \note		LMU SDK 接口
 */
#ifndef IBP_LMU_SDK_H
#define IBP_LMU_SDK_H

#if !defined(t_uint32)
typedef unsigned int t_uint32;
#endif

#if !defined(t_int32)
typedef int t_int32;
#endif

#if !defined(t_int64)
typedef long long t_int64;
#endif

#if !defined(t_float32)
typedef float t_float32;
#endif

#ifdef WIN32
#ifdef IBPLMUSDK_LIB_EXPORTS
#define DLIB_API __declspec(dllexport)
#else
#define DLIB_API __declspec(dllimport)
#endif  //DLIB_EXPORTS
#define CALLBACK __stdcall
#else
#define DLIB_API
#define CALLBACK
#endif   //WIN32

#ifdef __cplusplus
extern "C" 
{
#endif

/**
* @defgroup LMU_SDK函数
* @{
*/

/**
* @defgroup LMU_SDK系统
* @{
*/

/**
@brief LMU_SDK初始化
@return 
@remarks
@see 
*/
DLIB_API t_int32 LMU_SC_Init();

/**
@brief LMU_SDK反初始化
@return 
@remarks
@see 
*/
DLIB_API t_int32 LMU_SC_Cleanup();

/** @} */

/**
* @defgroup LMU_SDK连接服务
* @{
*/

/**
@brief 连接LMU服务
@param [in]  timeout		超时时间
@param [in]  cmusession		CMU登陆句柄
@param [in]  ipinfo		    LMU服务的ip信息
@param [in]  svrdomid		LMU服务的域id
@param [in]  serverid		LMU服务id
@param [out] outxml			返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<handle></handle>		连接成功返回的句柄
</root>
@endverbatim
@param [in]  maxlen			信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 LMU_AC_Connect(t_uint32 cmusession, char* ipinfo, char* svrdomid, t_int32 serverid, char* outxml, t_uint32 maxlen);

/**
@brief 用户认证连接LMU服务
@param [in]  usersession		用户认证
@param [in]  ipinfo		    LMU服务的ip信息
@param [in]  svrdomid		LMU服务的域id
@param [in]  serverid		LMU服务id
@param [out] outxml			返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<handle></handle>		连接成功返回的句柄
</root>
@endverbatim
@param [in]  maxlen			信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 LMU_AC_ConnectNoCmu(t_uint32 usersession, char* ipinfo, char* svrdomid, t_int32 serverid, char* outxml, t_uint32 maxlen);

/**
@brief 断开LMU服务
@param [in]  session		连接句柄
@return 
@remarks
@see 
*/
DLIB_API t_int32 LMU_SC_Disconn(t_uint32 session);

/** @} */

/**
* @defgroup LMU_SDK回调函数
* @{
*/

/**
@brief 消息回调函数
@param [in] session		连接句柄
@param [in] data		消息数据
@param [in] bufSize	    数据长度
@param [in] pUser		用户自定义数据
@return 
@remarks
@see 
*/
typedef t_int32 (*fIbpLmuMsgCallBack)(t_uint32 session, char *data, t_uint32 bufSize, void* pUser);

/**
@brief 设置消息回调函数
@param [in] session		连接句柄
@param [in] cb			回调函数
@param [in] pUser		用户数据
@return 
@remarks 回调消息示例
@verbatim
服务online消息通知
<?xml version='1.0' encoding='utf-8' ?>
<root version="1.0" unit="LMU" type="onlineNotify" cmd="onlineNotify" sequence="0" length="0">
	<server 
		servername="" 			服务名称
		session="" 				服务句柄
		status="" 				上下线状态
	/>
</root>
@endverbatim
@verbatim
短信发送结果通知
<?xml version='1.0' encoding='utf-8' ?>
<root version="1.0" unit="LMU" type="Notify" cmd="commonNotify" sequence="0" length="0">
	<notifycode>903</notifycode>			通知代码
	<nofityname>sendSmsResult</nofityname>	通知代码名称
	<telno></telno>							发送号码
	<rslt></rslt>							发送结果 0 失败 1 成功
</root>
@endverbatim
@see 
*/
DLIB_API t_int32 LMU_SC_SetLmuMsg(t_uint32 session, fIbpLmuMsgCallBack cb, void* pUser);

/** @} */

/**
* @defgroup LMU_SDK短信
* @{
*/

/**
@brief 发送短信
@param [in]  session		登陆句柄
@param [in]	 timeout		超时时间
@param [in]	 telNo			电话号码，格式"189xxxxxxxx;189xxxxxxxx;"
@param [in]  msgInfo		短信信息(utf8)	
@return 
@remarks 
@see 
*/
DLIB_API t_int32 LMU_SC_SendSmsInfo(t_uint32 session, t_int32 timeout, char *telNo, char *msgInfo);

/** @} */

/**
* @defgroup LMU_SDK配置信息
* @{
*/

/**
@brief 服务配置信息
@param [in]  session		登陆句柄
@param [in]	 timeout		超时时间
@param [in]	 serial			串口序号(-1 表示获取, 0~15表示设置)
@param [in]  baudrate		波特率
@param [out] outxml			查询信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<serial>0</serial>			当前使用串口号
	<baudrate>9600</baudrate>	当前使用串口波特率
	<serials>0;1;2;</serials>	可选串口号列表
</root>
@endverbatim
@param [in]	 maxlen			信息最大长度
@return 200成功 其它失败
@remarks 用于配置服务监听短信猫串口参数
@see 
*/
DLIB_API t_int32 LMU_SC_SmsCfgInfo(t_uint32 session, t_int32 timeout, t_int32 serial, t_int32 baudrate, char* outxml, t_uint32 maxlen);

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif


