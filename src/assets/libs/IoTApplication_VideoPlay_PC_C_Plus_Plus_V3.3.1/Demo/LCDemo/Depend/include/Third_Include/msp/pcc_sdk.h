/**
 * Copyright (c) 2014~2015, 浙江大华系统工程有限公司 All rights reserved.
 * \file		pcc_sdk.h
 * \brief		pcc_sdk
 * \author		24997
 * \date		2015年8月26日
 * \note		PCC SDK 接口
 */
#ifndef IBP_PCC_SDK_H
#define IBP_PCC_SDK_H

#ifdef WIN32
#define _WIN32_WINNT 0x0502
#endif

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
#ifdef PCCSDK_LIB_EXPORTS
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
* @defgroup PCC_SDK函数
* @{
*/

/**
* @defgroup PCC_SDK系统
* @{
*/

/**
@brief PCC_SDK初始化
@return 
@remarks
@see 
*/
DLIB_API t_int32 PCC_SC_Init();

/**
@brief PCC_SDK反初始化
@return 
@remarks
@see 
*/
DLIB_API t_int32 PCC_SC_Cleanup();

/** @} */

/**
* @defgroup PCC_SDK连接服务
* @{
*/

/**
@brief 连接ADGU服务
@param [in]  cmusession		CMU登陆句柄
@param [in]  ipinfo		    ADGU服务的ip信息
@param [in]  svrdomid		ADGU服务的域id
@param [in]  serverid		ADGU服务id
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
DLIB_API t_int32 PCC_AC_Connect(t_uint32 cmusession, char* ipinfo, char* svrdomid, t_int32 serverid, char* outxml, t_uint32 maxlen);

/**
@brief 用户认证连接ADGU服务
@param [in]  usersession		用户认证
@param [in]  ipinfo		    ADGU服务的ip信息
@param [in]  svrdomid		ADGU服务的域id
@param [in]  serverid		ADGU服务id
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
DLIB_API t_int32 PCC_AC_ConnectNoCmu(t_uint32 usersession, char* ipinfo, char* svrdomid, t_int32 serverid, char* outxml, t_uint32 maxlen);

/**
@brief 断开ADGU服务
@param [in]  session		连接句柄
@return 
@remarks
@see 
*/
DLIB_API t_int32 PCC_SC_Disconn(t_uint32 session);

/** @} */

/**
* @defgroup PCC_SDK回调函数
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
typedef t_int32 (*fIbpPccMsgCallBack)(t_uint32 session, char *data, t_uint32 bufSize, void* pUser);

/**
@brief 设置消息回调函数
@param [in] session		连接句柄
@param [in] cb			回调函数
@param [in] pUser		用户数据
@return 
@remarks 回调消息示例
@verbatim
打开关闭视频消息
<?xml version='1.0' encoding='utf-8' ?>
<root version="1.0" unit="Unknown" type="Request" cmd="adguPccPlay" sequence="" session="">
	<opt>0</opt>				操作标识 0 打开码流 1 关闭码流 
	<ipinfo>0.0.0.0|0;</ipinfo>	IP地址列表, 格式"ip|port;ip|port;"
	<transproto>1</transproto>	传输协议，0为TCP，1为UDP
	<revered>0</revered>		保留字段，这里存储消息序号
</root>
@endverbatim
@see 
*/
DLIB_API t_int32 PCC_SC_SetPccMsg(t_uint32 session, fIbpPccMsgCallBack cb, void* pUser);

/** @} */

/**
* @defgroup PCC_SDK关于PCC设备交互服务
* @{
*/

/**
@brief 设备注册到服务
@param [in]  session		登陆句柄
@param [in]	 timeout		超时时间
@param [in]	 info			设备信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<device 
		devcode=""			用户设备唯一码
		devname=""			设备名称
		devtype=""			设备类型 6 ipc 27 usb
		phonenum=""			电话号码
	/>
</root>
@endverbatim
@return 
@remarks 此处可以是外部获取到的设备信息(比如手机获取自身信息注册到服务)
@see 
*/
DLIB_API t_int32 PCC_SC_RegPccDev(t_uint32 session, t_int32 timeout, char* info);

/**
@brief 连接并注册到服务
@param [in]	 timeout		超时时间
@param [in]	 info			参数信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>	
	<cmusession />			CMU登陆句柄
	<ipinfo />				ADGU服务的ip信息
	<svrdomid />			ADGU服务的域id
	<serverid />			ADGU服务id
	<device 
		devcode=""			用户设备唯一码
		devname=""			设备名称
		devtype=""			设备类型 6 ipc 27 usb
		phonenum=""			电话号码
	/>
</root>
@endverbatim
@param [out] outxml			返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<handle></handle>		连接成功返回的句柄
</root>
@endverbatim
@param [in]  maxlen			信息最大长度
@return 
@remarks 调用此接口之前不要调用连接ADGU服务接口（内部已连接）
@see 
*/
DLIB_API t_int32 PCC_SC_ConnWithRegPccDev(t_int32 timeout, char* info, char* outxml, t_uint32 maxlen);

/**
@brief 设备视频操作错误码发送到服务
@param [in]  session		登陆句柄
@param [in]	 seq			对应消息序号
@param [in]	 ec				错误码
@return 
@remarks 将回调消息对应的错误码发给服务
@see PCC_SC_StartVideo PCC_SC_CloseVideo
*/
DLIB_API t_int32 PCC_SC_SendPccErrCode(t_uint32 session, t_int32 seq, t_int32 ec);

/**
@brief 设备视频中断信息发送到服务
@param [in]  session		登陆句柄
@param [in]	 timeout		超时时间
@return 
@remarks 
@see 
*/
DLIB_API t_int32 PCC_SC_SendAnnounce(t_uint32 session, t_int32 timeout);

/** @} */

/**
* @defgroup PCC_SDK操作视频
* @{
*/

/**
@brief PCC_SDK开启设备视频
@param [in] ipinfo			ip信息，格式"ip|port;ip|port;"
@param [in]	 timeout		超时时间
@return 
@remarks 回调函数中收到打开视频消息，调用该接口开启码流通道
@see PCC_SC_CloseVideo
*/
DLIB_API t_int32 PCC_SC_StartVideo(char *ipinfo, t_int32 timeout = 5000);

/**
@brief PCC_SDK开启设备视频扩展接口
@param [in] ipinfo				ip信息，格式"ip|port;ip|port;"
@param [in] transportProtocol	传输协议，0为TCP，1为UDP
@param [in]	timeout				超时时间
@return 
@remarks 回调函数中收到打开视频消息，调用该接口开启码流通道
@see PCC_SC_CloseVideo
*/
DLIB_API t_int32 PCC_SC_StartVideoEx(char *ipinfo, t_int32 transportProtocol, t_int32 timeout = 5000);

/**
@brief PCC_SDK关闭设备视频
@return 
@remarks 回调函数中收到关闭视频消息，调用该接口关闭码流通道
@see PCC_SC_StartVideo
*/
DLIB_API t_int32 PCC_SC_CloseVideo();

/**
@brief PCC_SDK外部设备视频发送接口
@param [in] buf				视频数据
@param [in] buflen			数据长度
@param [in] datatype		类型 0是P帧  1是I帧
@param [in] nwidth			宽度
@param [in] nheight			高度
@return 
@remarks 此处接受外部USB摄像头码流输入并发送(比如手机获取自身码流通过该接口发送)
@see 
*/
DLIB_API t_int32 PCC_SC_SendVideoData(char *buf, t_uint32 buflen, t_uint32 datatype, t_int32 nwidth, t_int32 nheight);

/** @} */

/**
* @defgroup PCC_SDK操作本地设备
* @{
*/

/**
@brief PCC_SDK获取用户设备唯一码
@param [out] outxml			返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<devcode></devcode>		
</root>
@endverbatim
@param [in]  maxlen			信息最大长度
@return 
@remarks 
@see 
*/
DLIB_API t_int32 PCC_SC_GetUserDevCode(char *outxml, t_uint32 maxlen);

/**
@brief PCC_SDK获取默认设备信息
@param [out] outxml		获取信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<device 
		devname=""			设备名称
		devtype=""			设备类型 6 ipc 27 usb
		ip=""				设备IP
		port=""				设备端口
		username=""			设备登陆用户名
		pwd=""				设备登陆密码
	/>
</root>
@endverbatim
@param [in]  maxlen		获取信息最大长度
@return 
@remarks 默认设备不一定是可用设备，不可用时需要用户重新选择
@see 
*/
DLIB_API t_int32 PCC_SC_GetDefaultDevInfo(char *outxml, t_uint32 maxlen);

/**
@brief PCC_SDK设置选中的设备为默认设置
@param [in] info		操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<device 
		devname=""			设备名称
		devtype=""			设备类型 6 ipc 27 usb
		ip=""				设备IP
		port=""				设备端口
		username=""			设备登陆用户名
		pwd=""				设备登陆密码
	/>
</root>
@endverbatim
@return 
@remarks 
@see 
*/
DLIB_API t_int32 PCC_SC_SetDefaultDevInfo(char* info);

/**
@brief 局域网设备查找回调函数
@param [in] outxml		消息数据
@param [in] maxlen	    数据长度
@param [in] pUser		用户自定义数据
@return 
@remarks
@see 
*/
typedef t_int32 (*fIbpPccSearchNetDevInfoCallBack)(char *outxml, t_uint32 maxlen, void* pUser);

/**
@brief 开始搜索本地设备（本级USB摄像头、局域网IPC等）
@param [in] devtype		设备类型 0 所有设备全查 6 ipc(局域网设备) 27 usb（USB摄像头设备）
@param [in] cb			回调函数
@param [in] pUser		用户数据
@return 
@remarks 回调消息示例 这里会列出所有搜索到的设备，调用者可以考虑根据设备类型名称和IP版本进行过滤下
@verbatim
回调局域网设备示例
<?xml version='1.0' encoding='utf-8' ?>
<root>
	<device
		devname=""			设备名称
		devtype=""			设备类型 6 ipc 27 usb
		devtypename=""		设备类型名称
		ipversion=""		IP版本
		ip=""				设备IP
		port=""				设备端口
		username=""			设备登陆用户名
		pwd=""				设备登陆密码
	/>
</root>
@endverbatim
@see 
*/
DLIB_API t_int32 PCC_SC_StartSearchNetDevInfo(t_int32 devtype, fIbpPccSearchNetDevInfoCallBack cb, void* pUser);

/**
@brief 停止搜索局域网设备（本级USB摄像头、局域网IPC等）
@param [in] devtype		设备类型 0 所有支持设备 6 ipc 27 usb
@return 
@remarks
@see 
*/
DLIB_API t_int32 PCC_SC_StopSearchNetDevInfo(t_int32 devtype = 0);

/**
@brief PCC_SDK创建选中的设备
@param [in] info		操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<device 
		devname=""			设备名称
		devtype=""			设备类型 6 ipc 27 usb
		ip=""				设备IP
		port=""				设备端口
		username=""			设备登陆用户名
		pwd=""				设备登陆密码
	/>
</root>
@endverbatim
@return 
@remarks 该函数用于创建并初始化当前选中使用的设备,返回失败，表明选中设备不可用或创建失败
@see 
*/
DLIB_API t_int32 PCC_SC_CreateDevice(char* info);

/**
@brief PCC_SDK释放选中的设备
@return 
@remarks 如果选中设备创建成功，需要释放时要调用该函数销毁当前选中使用的设备
@see 
*/
DLIB_API t_int32 PCC_SC_DestroyDevice();

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif


