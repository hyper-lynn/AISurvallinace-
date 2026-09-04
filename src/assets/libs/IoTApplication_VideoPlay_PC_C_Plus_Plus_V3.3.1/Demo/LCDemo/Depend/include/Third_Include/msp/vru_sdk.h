/**
 * Copyright (c) 2014, 浙江大华系统工程有限公司 All rights reserved.
 * \file		vru_sdk.h
 * \brief		vru_sdk
 * \author		17400
 * \date		2014年12月19日
 * \note		VRU SDK 接口
 */
#ifndef _IBP_VRU_SDK_I_H_
#define _IBP_VRU_SDK_I_H_

#if !defined(t_uint32)
typedef unsigned int t_uint32;
#endif

#if !defined(t_int32)
typedef int t_int32;
#endif

#if !defined(t_float32)
typedef float t_float32;
#endif

#ifdef WIN32
#ifdef IBPVRUSDK_LIB_EXPORTS
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
* @defgroup VRU_SDK函数
* @{
*/

/**
* @defgroup VRU_SDK系统
* @{
*/

/**
@brief VRU_SDK初始化
@return 
@remarks
@see VRU_C_Init
*/
DLIB_API t_int32 VRU_SC_Init();

/**
@brief VRU_SDK初始化,服务或者已经启动applicationBase的程序调用
@return 
@remarks
@see VRU_C_Init
*/
DLIB_API t_int32 VRU_SC_InitNoApp();

/**
@brief VRU_SDK反初始化
@return 
@remarks
@see VRU_C_Cleanup
*/
DLIB_API t_int32 VRU_SC_Cleanup();

/** @} */

/**
* @defgroup VRU_SDK码流回调函数
* @{
*/

/**
@brief 码流回调接口
@param [out] realHandle 句柄
@param [out] buffer	码流
@param [out] dwBufSize 长度
@param [out] pUser 用户信息
@return 
@see 
*/
typedef t_int32 (*fVru_C_RealDataCallBack)(t_uint32 realHandle, char *buffer, t_uint32 dwBufSize, void *pUser);


/**
@brief 设置码流回调函数
@param [in] realHandle 视频句柄号
@param [in] cb 回调函数
@param [in] pUser 用户数据
@return 
@remarks
@see 
*/
DLIB_API t_int32 VRU_SC_SetRealDataCallBack(t_uint32 realHandle, fVru_C_RealDataCallBack cb, void *pUser);

/**
@brief 码流缓存回调函数
@param [out] realHandle	句柄
@param [out] buffer	码流
@param [out] dwBufSize 长度
@param [out] cacheLen 内部缓存长度
@param [out] pUser 用户信息
@see 
*/
typedef t_int32 (*fVru_C_RealDataCallBackByCache)(t_uint32 realHandle, char *buffer, t_uint32 dwBufSize, t_uint32 cacheLen, void *pUser);

/**
@brief 设置码流缓存回调函数,开启内部缓存
@param [in] realHandle 视频句柄号
@param [in] cb 回调函数
@param [in] pUser 用户数据
@return  
@remarks
@see 
*/
DLIB_API t_int32 VRU_SC_SetRealDataCallBackByCache(t_uint32 realHandle, fVru_C_RealDataCallBackByCache cb, void *pUser);

/** @} */

/**
* @defgroup VRU_SDK回调函数
* @{
*/

/**
@brief 异步消息回调函数
@param [out] vruSession 消息句柄
@param [out] buffer		回调内容
@param [out] buffLen	数据长度
@param [out] pUser		用户数据
@return  
@remarks
@see 
*/
typedef t_int32 (*fVru_C_CallBack)(t_uint32 vruSession, char *buffer, t_uint32 buffLen, void *pUser);

/**
@brief 设置异步消息回调函数
@param [out] vruSession 消息句柄
@param [in] cb 回调函数
@param [in] pUser 用户数据
@return  
@remarks
@see
@verbatim
服务online消息通知
<?xml version='1.0' encoding='utf-8' ?>
<root version="1.0" unit="SDK" type="onlineNotify" cmd="onlineNotify" sequence="0" length="0">
<server
	servername="VRU"	服务名称
	session="1"			服务句柄
	status="1"			上下线状态
/>
</root>
@endverbatim

rtsp announce消息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="SDK" type="request" cmd="announce" sequence="0" length="0"/>

<state>200</state>			状态：200表示在线，其他详见错误码
<realhandle>5</realhandle>	视频句柄
</root>
@endverbatim
*/
DLIB_API t_int32 VRU_SC_SetCallBack(t_uint32 vruSession, fVru_C_CallBack cb, void *pUser);

/** @} */

/**
* @defgroup VRU_SDK异步连接
* @{
*/

/**
@brief 异步连接vru
@param [in] cmuLoginHandle	cmu的登录句柄
@param [in] ipInfo			服务ip信息，格式"ip|port;ip|port;"
@param [in] svrDomId		服务域id
@param [in] svrId			服务id
@param [in] maxLen			xmlOutput长度
@param [out] xmlOutput		xml输出
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<vrusession>2</vrusession>
</root>
@endverbatim
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VRU_AC_Connect(t_uint32 cmuLoginHandle, char *ipInfo, char *svrDomId, t_int32 svrId, char *xmlOutput, t_uint32 maxLen);

/**
@brief 用户认证异步连接vru
@param [in] usersession		用户认证
@param [in] ipInfo			服务ip信息，格式"ip|port;ip|port;"
@param [in] svrDomId		服务域id
@param [in] svrId			服务id
@param [in] maxLen			xmlOutput长度
@param [out] xmlOutput		xml输出
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<vrusession>2</vrusession>
</root>
@endverbatim
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VRU_AC_ConnectNoCmu(t_uint32 usersession, char *ipInfo, char *svrDomId, t_int32 svrId, char *xmlOutput, t_uint32 maxLen);

/**
@brief 异步断开连接
@param [in] vruSession		服务句柄
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VRU_AC_Disconnect(t_uint32 vruSession);

/** @} */

/**
* @defgroup VRU_SDK异步录像
* @{
*/

/**
@brief 异步录像查询
@param [in] vruSession		服务句柄
@param [in] xmlInput		录像查询信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<moduletype><moduletype>:1 voip; 0 ibp
<VOIP callernumber="123" calleenumber="456" sessiontype=""/>
<IBP domid="123" chncode="chad" />
<svrid></svrid>				服务器ID
<ipinfo></ipinfo>			IP、端口信息
<sourcetype></sourcetype>	1:中心录像，2:前端录像
<recordtype></recordtype>	录像类型 0:未知录像类型, 1:手动录像, (1<<1):定时录像, (1<<2):全天候录像, (1<<3):告警录像, 1<<4):视频丢失, (1<<5):视频遮挡, (1<<6):移动侦测, 0xFFFFFFFF:所有文件
<vruid></vruid>				录像存储服务ID
<diskid></diskid>			录像存储磁盘ID
<filehandle></filehandle>	录像存储文件句柄
<starttime></starttime>		开始时间
<endtime></endtime>			结束时间
<streamtype></streamtype>   0:视频; 1:语音
<curpage></curpage>			当前页(起始0)
<size></size>				页显示数
</root>
@endverbatim
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VRU_AC_QueryRecordFile(t_uint32 vruSession, char *xmlInput);

/** @} */

/**
* @defgroup VRU_SDK异步实时视频
* @{
*/

/**
@brief 异步获取视频 集成rtsp流程
@param [in] vruSession					服务句柄
@param [in] xmlInput							视频请求信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<domid></domid>							设备域id
<chncode></chncode>						通道代码
<playtype></playtype>					1:按文件回放,  2:按时间回放
<transproto></transproto>				0:TCP, 1:UDP
<streamtype></streamtype>				0:视频, 1:语音
<streampacktype></streampacktype>		码流包类型 //-1 其他 0 用对于的制造商sdk来解码 1 rpt h264 裸码流 2 rpt h264 nal打包 3 pg  pss流 
<sourcetype></sourcetype>				1:中心录像，2:前端录像
<filename></filename>					录像文件名
<vruid></vruid>							录像存储服务ID
<diskid></diskid>						录像存储磁盘ID
<filehandle></filehandle>				录像存储文件句柄
<starttime></starttime>					开始时间
<endtime></endtime>						结束时间
</root>
@endverbatim
@param [in] maxLen						xmlOutput长度
@param [out] xmlOutput					xml输出
@verbatim
<root version="1.0" unit="Unknown" type="Response" cmd="startRVideo" sequence="16" session="0">
<token>1</token>
<playvideotype>0</playvideotype>
<svrid>4</svrid>
<ipinfo>10.36.65.112|8513;</ipinfo>		服务端rtsp ip、port信息
<transproto>1</transproto>
<substream>0</substream>
<rtspurl>rtsp://10.36.65.112:8513/realplay/1?token=1</rtspurl>
<sessionid>0</sessionid>
<errmsg/>
<errcode>200</errcode>
<streamportfrom>0</streamportfrom>
<streampacktype>0</streampacktype>
<version>0</version>
<realhandle>3</realhandle>
</root>
@endverbatim
@return									200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VRU_AC_StartVideo_I(t_uint32 vruSession, char *xmlInput, char *xmlOutput, t_uint32 maxLen);

/**
@brief 异步获取视频
@param [in] vruSession		服务句柄
@param [in] xmlInput		请求内容
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<domid></domid>							设备域id
<chncode></chncode>						通道代码
<talktype></talktype>					0:通道对讲，1:设备对讲
<playtype></playtype>					1:按文件回放,  2:按时间回放
<transproto></transproto>				0:TCP, 1:UDP
<streamtype></streamtype>				0:视频, 1:语音
<streampacktype></streampacktype>
<blocalrecv>1</blocalrecv>				非0:码流直接发送给sdk,0:发送给其他机器
<sourcetype></sourcetype>				1:中心录像，2:前端录像
<filename></filename>					录像文件名
<vruid></vruid>							录像存储服务ID
<diskid></diskid>						录像存储磁盘ID
<filehandle></filehandle>				录像存储文件句柄
<starttime></starttime>					开始时间
<endtime></endtime>						结束时间
</root>
@endverbatim
@param [in] maxLen						xmlOutput长度
@param [out] xmlOutput					xml输出 格式同VRU_AC_StartVideo_I
@return									200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VRU_AC_StartVideo(t_uint32 vruSession, char *xmlInput, char *xmlOutput, t_uint32 maxLen);

/**
@brief 异步获取视频 VOIP使用
@param [in] vruSession		服务句柄
@param [in] xmlInput		请求内容
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<streamid></streamid>
<transproto></transproto>				0:TCP, 1:UDP
<streamtype></streamtype>				0:视频, 1:语音
<streampacktype></streampacktype>
<blocalrecv>1</blocalrecv>				非0:码流直接发送给sdk,0:发送给其他机器
<filename></filename>					录像文件名
<vruid></vruid>							录像存储服务ID
<diskid></diskid>						录像存储磁盘ID
<filehandle></filehandle>				录像存储文件句柄
<starttime></starttime>					开始时间
<endtime></endtime>						结束时间
</root>
@endverbatim
@param [in] maxLen						xmlOutput长度
@param [out] xmlOutput					xml输出 格式同VRU_AC_StartVideo_I
@return									200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VRU_AC_StartVideo_Voip(t_uint32 vruSession, char *xmlInput, char *xmlOutput, t_uint32 maxLen);

/** @} */

/**
* @defgroup VRU_SDK异步RTSP流程
* @{
*/

/**
@brief 异步Rtsp连接
@param [in] realHandle		服务句柄
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VRU_AC_RtspConnect(t_uint32 realHandle);

/**
@brief 异步rtsp Describe
@param [in] realHandle		播放句柄
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VRU_AC_VideoDescribe(t_uint32 realHandle);

/**
@brief 异步rtsp Setup
@param [in] realHandle		播放句柄
@param [in] clientIpInfo	请求端ip信息，格式"ip|port;ip|port;"
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VRU_AC_VideoSetup(t_uint32 realhandle, char *clientIpInfo);

/**
@brief 异步rtsp Play
@param [in] realHandle		播放句柄
@param [in] rang			请求端ip信息，格式"ip|port;ip|port;"
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VRU_AC_VideoPlay(t_uint32 realHandle);

/**
@brief 异步录像拖动
@param [in] realHandle		播放句柄
@param [in] timeout			超时时间
@param [in] range			定位位置,按时间拖动格式:clock=19000101T000000Z-，按文件大小拖动格式:byte=12333-
@param [in] scale			播放速度 
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VRU_AC_SeekPlay(t_uint32 realHandle, char *range, t_float32 scale);

/**
@brief 异步录像暂停
@param [in] realHandle		播放句柄
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VRU_AC_VideoPause(t_uint32 realHandle);

/**
@brief 视频停止
@param [in] realHandle		播放句柄
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VRU_AC_Stop(t_uint32 realHandle);

/** @} */

/*
@brief 异步录像存储计划操作
@param [in] vruSession 登录成功后返回的值
@param [in] timeout			超时时间
@param [in] xmlInput信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<opt 
operatetype="0" //操作类型 0 增加 1 修改 2 删除
domainid="1" //域ID
userid="1"//用户ID
>
<storeplan 
planid="" //计划ID
timetemplateid="" //时间模板ID
planname="" //计划名称
domid="" //域ID
chncode="" //通道代码
voiceenable="" //是否有声音
status="" //状态
updatetime=""//更新时间
recordtype=""//录像类型 同 VRU_AC_QueryRecordFile
alarmtime=""//报像录像时间（s）
streamtype=""//0:视频; 1:语音
/>
</opt>
</root>
@endverbatim
@return  错误码查看 IBP_Error.h
@remarks
@see 
*/
DLIB_API t_int32 VRU_AC_OptStorePlan(t_uint32 vruSession, char* xmlInput);

/*
@brief 异步录像存储
@param [in] vruSession 登录成功后返回的值
@param [in] xmlInput信息
@verbatim
<?xml version="1.0" encoding="utf-8" standalone="no" ?> 
<root>
<opt operatetype="0" moduletype="1"> operatetype:0 开始，1:停止; moduletype:1 voip;0 ibp
<VOIP callernumber="123" calleenumber="456" sessiontype="">
<callername>call1</callername> 
<calleename>call2</calleename> 
<samplerate>2</samplerate> 
<samplenumber>22</samplenumber> 
<channeltype>1</channeltype> 
<audiotype></audiotype>
</VOIP>
<IBP domid="123" chncode="chad" streamtype = "" recordtype="1" /> streamtype 0:video,1: audio; recordtype录像类型同 VRU_AC_QueryRecordFile
</opt>
</root>
@endverbatim
@return  错误码查看 IBP_Error.h
@remarks
@see 
*/
DLIB_API t_int32 VRU_AC_VideoStore(t_uint32 vruSession, char *xmlInput);


/**
* @defgroup VRU_SDK同步连接
* @{
*/

/**
@brief 同步连接vru
@param [in] cmuLoginHandle	cmu验证session
@param [in] timeout			超时时间
@param [in] ipInfo			vru服务ip信息
@param [in] svrDomId		服务域id
@param [in] svrId			服务id
@param [in] maxLen			xmlOutput长度
@param [out] xmlOutput		xml输出
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<vrusession>2</vrusession>
</root>
@endverbatim
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VRU_SC_Connect(t_uint32 cmuLoginHandle, t_int32 timeout, char *ipInfo, char *svrDomId, t_int32 svrId, char *xmlOutput, t_uint32 maxLen);

/**
@brief 同步断开连接
@param [in] vruSession		服务句柄
@param [in] timeout			超时时间
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VRU_SC_Disconnect(t_uint32 vruSession, t_int32 timeout);

/** @} */

/**
* @defgroup VRU_SDK同步录像
* @{
*/

/**
@brief 同步录像查询
@param [in] vruSession		服务句柄
@param [in] timeout			超时时间
@param [in] xmlInput		录像查询信息，格式同VRU_AC_QueryRecordFile
@param [in] maxLen			对应的最大长度
@param [out] xmlOutput		查询结果输出
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<info>
<count>2</count>
<item sourcetype="2" recordtype="1" starttime="20141229T160000Z" endtime="20141229T170000Z" filename="0|0|77036|682394|0|5|20141229T160000Z|20141229T170000Z" length="682394" title="" planid="0" vruid="0" diskid="0" filehandle="0" devcode="" rtspurl="" caller="ibpdvr70-1" callee="90653" sesstype="0" extend="" streamid="10"/>
<item sourcetype="2" recordtype="1" starttime="20141229T170000Z" endtime="20141229T175534Z" filename="0|0|77631|603136|0|15|20141229T170000Z|20141229T175534Z" length="603136" title="" planid="0" vruid="0" diskid="0" filehandle="0" devcode="" rtspurl="" caller="ibpdvr70-1" callee="90653" sesstype="0" extend="" streamid="10"/>
</info>
@endverbatim
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VRU_SC_QueryRecordFile(t_uint32 vruSession, t_int32 timeout, char *xmlInput, char *xmlOutput, t_uint32 maxLen);

/** @} */

/**
* @defgroup VRU_SDK同步视频语音
* @{
*/

/**
@brief 同步获取视频（包括实时,录像,语音等），集成rtsp流程
@param [in] vruSession		服务句柄
@param [in] timeout			超时时间
@param [in] xmlInput		视频请求信息，格式同VRU_AC_StartVideo_I
@param [in] maxLen			xmlOutput长度
@param [out] xmlOutput		xml输出
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<realhandle>3</realhandle>
</root>
@endverbatim
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VRU_SC_StartVideo_I(t_uint32 vruSession, t_int32 timeout, char *xmlInput, char *xmlOutput, t_uint32 maxLen);

/**
@brief 同步发送对讲数据
@param [in] realHandle		播放句柄
@param [in] buffer			数据
@param [in] bufferLen		数据长度
@return						200 成功,其他详见错误码 
@remarks
@see 
*/
DLIB_API t_int32 VRU_SC_SendTalkData(t_uint32 realHandle, char* buffer, t_uint32 bufferLen);

/**
@brief 同步获取视频
@param [in] vruSession		服务句柄
@param [in] timeout			超时时间
@param [in] xmlInput		请求内容，格式同VRU_AC_StartVideo
@param [in] maxLen			xmlOutput长度
@param [out] xmlOutput		xml输出
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<realhandle>3</realhandle>
</root>
@endverbatim
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VRU_SC_StartVideo(t_uint32 vruSession, t_int32 timeout, char *xmlInput, char *xmlOutput, t_uint32 maxLen);

/**
@brief 同步获取视频
@param [in] vruSession		服务句柄
@param [in] timeout			超时时间
@param [in] xmlInput		请求内容，格式同VRU_AC_StartVideo
@param [in] maxLen			xmlOutput长度
@param [out] xmlOutput		xml输出
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<realhandle>3</realhandle>
</root>
@endverbatim
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VRU_SC_StartVideo_Voip(t_uint32 vruSession, t_int32 timeout, char *xmlInput, char *xmlOutput, t_uint32 maxLen);

/** @} */

/**
* @defgroup VRU_SDK同步RTSP流程
* @{
*/

/**
@brief 同步Rtsp连接
@param [in] realHandle		服务句柄
@param [in] timeout			超时时间
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VRU_SC_RtspConnect(t_uint32 realHandle, t_int32 timeout);

/**
@brief 同步rtsp Describe
@param [in] realHandle		播放句柄
@param [in] timeout			超时时间
@return						200 成功,其他详见错误码文档  
@remarks
@see 
*/
DLIB_API t_int32 VRU_SC_VideoDescribe(t_uint32 realHandle, t_int32 timeout);

/**
@brief 同步rtsp Setup
@param [in] realHandle		播放句柄
@param [in] timeout			超时时间
@param [in] clientIpInfo	请求端ip信息，格式"ip|port;ip|port;"
@param [in] maxLen			xmlOutput长度
@param [out] xmlOutput		xml输出
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<serverIp>10.36.65.112</serverIp>
<serverPort>20000</serverPort>
</root>
@endverbatim
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VRU_SC_VideoSetup(t_uint32 realHandle, t_int32 timeout, char *clientIpInfo, char *xmlOutput, t_uint32 maxLen);

/**
@brief 同步rtsp Play
@param [in] realHandle		播放句柄
@param [in] timeout			超时时间
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VRU_SC_VideoPlay(t_uint32 realHandle, t_int32 timeout);

/**
@brief 同步录像拖动
@param [in] realHandle		播放句柄
@param [in] timeout			超时时间
@param [in] range			定位位置,按时间拖动格式:clock=19000101T000000Z-，按文件大小拖动格式:byte=12333-
@param [in] scale			播放速度 
@return						200 成功,其他详见错误码文档   
@remarks
@see 
*/
DLIB_API t_int32 VRU_SC_SeekPlay(t_uint32 realHandle, t_int32 timeout, char *range, t_float32 scale);

/**
@brief 同步录像暂停
@param [in] realHandle		播放句柄
@param [in] timeout			超时时间
@return						200 成功,其他详见错误码文档 
@remarks
@see 
*/
DLIB_API t_int32 VRU_SC_VideoPause(t_uint32 realHandle, t_int32 timeout);

/**
@brief 同步视频关闭
@param [in] realHandle		播放句柄
@param [in] timeout			超时时间
@return						200 成功,其他详见错误码文档  
@remarks
@see 
*/
DLIB_API t_int32 VRU_SC_Stop(t_uint32 realhandle, t_int32 timeout);

/**
@brief 同步码流切换        
@param [in] timeout			超时时间
@param [in] chnCode			通道code
@param [in] domainId		设备域id
@param [in] streamType		码流类型：0主码流， 1辅码流
@return						200 成功,其他详见错误码文档  
@remarks					仅供广东电网使用
@see 
*/
DLIB_API t_int32 VRU_SC_StreamChange(t_uint32 vruSession, t_int32 timeout, char *chnCode, char *domainId, t_int32 streamType);


/*
@brief 异步录像存储计划操作
@param [in] vruSession 登录成功后返回的值
@param [in] timeout			超时时间
@param [in] xmlInput信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<opt 
operatetype="0" //操作类型 0 增加 1 修改 2 删除
domid="1" //域ID
userid="1"//用户ID
>
<storeplan 
planid="" //计划ID
timetemplateid="" //时间模板ID
planname="" //计划名称
domid="" //域ID
chncode="" //通道代码
voiceenable="" //是否有声音
status="" //状态
updatetime=""//更新时间
recordtype=""//录像类型 同 VRU_AC_QueryRecordFile
alarmtime=""//报像录像时间（s）
streamtype=""//0:视频; 1:语音
/>
</opt>
</root>
@endverbatim
@return  错误码查看 IBP_Error.h
@remarks
@see 
*/
DLIB_API t_int32 VRU_SC_OptStorePlan(t_uint32 vruSession, t_int32 timeout,  char* xmlInput);

/*
@brief 同步录像存储
@param [in] vruSession 登录成功后返回的值
@param [in] timeout			超时时间
@param [in] xmlInput信息
@verbatim
<?xml version="1.0" encoding="utf-8" standalone="no" ?> 
<root>
<opt operatetype="0" moduletype="1"> operatetype:0 开始，1:停止;moduletype:1 voip;0 ibp
<VOIP callernumber="123" calleenumber="456" sessiontype="">
<callername>call1</callername> 
<calleename>call2</calleename> 
<samplerate>2</samplerate> 
<samplenumber>22</samplenumber> 
<channeltype>1</channeltype> 
</VOIP>
<IBP domid="123" chncode="chad" streamtype = "" recordtype="1" /> streamtype 0:video,1: audio; recordtype录像类型同 VRU_AC_QueryRecordFile
</opt>
</root>
@endverbatim
@param [in] maxLen			xmlOutput长度
@param [out] xmlOutput信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<ipInfo></ipInfo>//voip用
</root>
@endverbatim
@return  错误码查看 IBP_Error.h
@remarks
@see 
*/
DLIB_API t_int32 VRU_SC_VideoStore(t_uint32 vruSession, t_int32 timeout, char *xmlInput, char *xmlOutput, t_uint32 maxLen);

/*
@brief 时间模板操作
@param [in] vruSession 登录成功后返回的值
@param [in] timeout			超时时间
@param [in] xmlInput信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<opt 
	operatetype="0" //操作类型 0 增加 1 修改 2 删除
>
	<timetemplate 
		id=""; //模板id
		title="";//模板名
		type="";//模板类型 1:按天; 2:按周; 3:按月
		config="";//模板配置，以xml形式，格式如下
	/>
</opt>
</root>
@endverbatim

@模板配置格式
@verbatim
//按天进行
<Config>
<Day>
<Time>10:10:10-15:15:15</Time>
<Time>16:10:10-17:15:15</Time>
</Day>
</Config>

//按周进行
<Config>
<Week>
<Day Num="1"> //周一
<Time>10:10:10-15:15:15</Time>
<Time>16:10:10-17:15:15</Time>
</Day>
<Day Num="5">//周五
<Time>10:10:10-15:15:15</Time>
<Time>16:10:10-17:15:15</Time>
</Day>
</Week>
</Config>

//按月进行
<Config>
<Month>
<Day Num="1">//一号
<Time>10:10:10-15:15:15</Time>
<Time>16:10:10-17:15:15</Time>
</Day>
<Day Num="5">//五号
<Time>10:10:10-15:15:15</Time>
<Time>16:10:10-17:15:15</Time>
</Day>
<Day Num="28">//二十八号
<Time>10:10:10-15:15:15</Time>
<Time>16:10:10-17:15:15</Time>
</Day>
</Month>
</Config>
@endverbatim

@param [in] maxLen			xmlOutput长度
@param [out] xmlOutput信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<templateid></templateid>
</root>
@endverbatim
@return  错误码查看 IBP_Error.h
@remarks
@see 
*/
DLIB_API t_int32 VRU_SC_OptTimeTemplate(t_uint32 vruSession, t_int32 timeout, char *xmlInput, char *xmlOutput, t_uint32 maxLen);

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif


#endif
