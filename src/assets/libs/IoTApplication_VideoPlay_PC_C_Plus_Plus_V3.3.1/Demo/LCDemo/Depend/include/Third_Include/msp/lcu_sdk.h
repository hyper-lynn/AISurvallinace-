/**
 * Copyright (c) 2014~2015, 浙江大华系统工程有限公司 All rights reserved.
 * \file		lcu_sdk.h
 * \brief		lcu_sdk
 * \author		13108
 * \date		2016年4月9日
 * \note		LCU SDK 接口
 */
#ifndef _LCU_SDK_H
#define _LCU_SDK_H

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
#ifdef LCUSDK_LIB_EXPORTS
#ifndef DLIB_API
#define DLIB_API __declspec(dllexport)
#endif
#else
#ifndef DLIB_API
#define DLIB_API __declspec(dllimport)
#endif
#endif  //DLIB_EXPORTS
#ifndef CALLBACK
#define CALLBACK __stdcall
#endif
#else
#define DLIB_API
#define CALLBACK
#endif   //WIN32

#ifdef __cplusplus
extern "C" 
{
#endif

/**
* @defgroup LCU_SDK函数
* @{
*/

/**
* @defgroup LCU_SDK系统
* @{
*/

/**
@brief LCU_SDK初始化
@return 
@remarks
@see 
*/
DLIB_API t_int32 LCU_SC_Init();

/**
@brief LCU_SDK反初始化
@return 
@remarks
@see 
*/
DLIB_API t_int32 LCU_SC_Cleanup();

/** @} */

/**
* @defgroup LCU_SDK连接服务
* @{
*/

/**
@brief 连接LCU服务
@param [in]  cmusession		CMU登陆句柄
@param [in]  ipinfo		    LCU服务的ip信息
@param [in]  svrdomid		LCU服务的域id
@param [in]  serverid		LCU服务id
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
DLIB_API t_int32 LCU_AC_Connect(t_uint32 cmusession, char* ipinfo, char* svrdomid, t_int32 serverid, char* outxml, t_uint32 maxlen);

/**
@brief 用户认证连接LCU服务
@param [in]  usersession		用户认证
@param [in]  ipinfo		    LCU服务的ip信息
@param [in]  svrdomid		LCU服务的域id
@param [in]  serverid		LCU服务id
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
DLIB_API t_int32 LCU_AC_ConnectNoCmu(t_uint32 usersession, char* ipinfo, char* svrdomid, t_int32 serverid, char* outxml, t_uint32 maxlen);

/**
@brief 断开LCU服务
@param [in]  session		连接句柄
@return 
@remarks
@see 
*/
DLIB_API t_int32 LCU_SC_Disconn(t_uint32 session);

/** @} */

/**
* @defgroup LCU_SDK回调函数
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
typedef t_int32 (*fIbpLCUMsgCallBack)(t_uint32 session, char *data, t_uint32 bufSize, void* pUser);

/**
@brief 设置消息回调函数
@param [in] session		连接句柄
@param [in] cb			回调函数
@param [in] pUser		用户数据
@return 
@remarks 回调消息示例

@verbatim
LCU服务online消息通知
<?xml version='1.0' encoding='utf-8' ?>
<root version="1.0" unit="LCU" type="onlineNotify" cmd="onlineNotify" sequence="0" length="0">
	<server 
		servername="" 			服务名称
		session="" 				服务句柄
		status="" 				下线状态
	/>
</root>
@endverbatim

@verbatim
收到对方消息的通知
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="SDK" type="Request" cmd="lcuReceiveMsg" sequence="0" session="0">
<fromdomid>对方的domainid</fromdomid>
<fromuserid>对方的用户id</fromuserid>
<todomid>对方的domainid</todomid>
<touserid>对方的用户id</touserid>
<id>对方的用户id</id>
<time>对方的用户id</time>
<status>对方的用户id</status>
<usersession>对方的用户session</usersession>
<msg>发送的消息</msg>
<ctrlinfo>发送的消息</ctrlinfo>
<type>对方的用户id</type>
</root>
@endverbatim

@verbatim
收到对方发送文件消息的通知
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="SDK" type="Request" cmd="lcuReceiveFile" sequence="0" session="0">
<domid>对方的domainid</domid>
<userid>对方的用户id</userid>
<usersession>对方的用户session</usersession>
<filename>发送的文件名</filename>
<guid>发送文件的guid</guid>
</root>
@endverbatim

@verbatim
异步发送文件响应消息通知
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="LCU" type="Response" cmd="lcuSendFile" sequence="0" session="0">
<domid>0</domid>
<filename></filename>
<guid>bcb6519c-19fc-4026-be75-52ab8c7baa41</guid>
</root>
@endverbatim

@verbatim
异步接收文件完成消息通知
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="LCU" type="Notify" cmd="commonNotify" sequence="139" session="0">
	<subtype>FileDownload</subtype>
	<notifycode>501</notifycode>
	<notifyname></notifyname>
	<guid>bcb6519c-19fc-4026-be75-52ab8c7baa41</guid>
	<filename></filename>
	<progress>100</progress>
</root>
@endverbatim
@see 
*/
DLIB_API t_int32 LCU_SC_SetLCUMsg(t_uint32 session, fIbpLCUMsgCallBack cb, void* pUser);


/**
@brief 消息发送同步接口
@param [in] session		   连接句柄
@param [in] timeout		   超时时间
@param [in] msg		       message消息
@param [in] ctrlInfo       参数信息，包含在msg中，只是方便写数据库
@param [in] toDomainId	   对方的域 id
@param [in] toUserId	   对方的用户id
@param [in] toUserSession  对方的session id  (如果toUserSession填0, 则发送给用户id为toUserId的所有登陆用户)
@param [in] tag	           发送消息类型 1 聊天信息；2 消息； 4 任务
@ctrlInfo结构如下
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>			
	<np1></np1>					
	<np2></np2>	
	<np3></np3>					
	<np4></np4>					
	<np5></np5>	
	<str1></str1>					
	<str2></str2>					
	<str3></str3>	
	<str4></str4>					
	<str5></str5>					
	<str6></str6>	
</root>
@return 参见错误码
@remarks
@see 
*/
DLIB_API t_int32 LCU_SC_SendMessge(t_uint32 session, t_int32 timeout, char* msg, char* ctrlInfo, char* toDomainId, t_int32 toUserId, t_uint32 toUserSession, t_int32 tag);

/**
@brief 发送文件同步接口
@param [in] session		   连接句柄
@param [in] timeout		   超时时间
@param [in] toDomainId	   对方的域 id
@param [in] toUserId	   对方的用户id
@param [in] toUserSession  对方的session id
@param [in] info		   文件信息(UTF8编码)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
    <validtime></validtime>	有效期(单位：秒)(文件发送的有效期请默认填写3600*24)
	<filepath></filepath>	文件全路径(包括文件名和后缀)
</root>
@endverbatim
@param [out] guid		文件GUID
@return 参见错误码
@remarks
@see 
*/
DLIB_API t_int32 LCU_SC_SendFile(t_uint32 session, t_int32 timeout, char* toDomainId, t_uint32 toUserId, t_uint32 toUserSession, char* info, char* guid);

/**
@brief 发送文件异步接口
@param [in] session		   连接句柄
@param [in] toDomainId	   对方的域 id
@param [in] toUserId	   对方的用户id
@param [in] toUserSession  对方的session id
@param [in] info		   文件信息(UTF8编码)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
    <validtime></validtime>	有效期(单位：秒)(文件发送的有效期请默认填写3600*24)
	<filepath></filepath>	文件全路径(包括文件名和后缀)
</root>
@endverbatim
@param [out] guid		文件GUID
@return 参见错误码
@remarks
@see 
*/
DLIB_API t_int32 LCU_AC_SendFile(t_uint32 session, char* toDomainId, t_uint32 toUserId, t_uint32 toUserSession, char* info, char* guid);

/**
@brief 接收文件同步接口
@param [in] session		连接句柄
@param [in] timeout		超时时间
@param [in] info		文件信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<domid></domid>					域ID
	<guid></guid>					需要下载的文件GUID
	<filepath></filepath>			下载文件的存放路径	
</root>
@endverbatim
@return 参见错误码
@remarks
@see 
*/
DLIB_API t_int32 LCU_SC_ReceiveFile(t_uint32 session, t_int32 timeout, char* info);

/**
@brief 接收文件异步接口
@param [in] session		连接句柄
@param [in] info		文件信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<domid></domid>					域ID
	<guid></guid>					需要下载的文件GUID
	<filepath></filepath>			下载文件的存放路径	
</root>
@endverbatim
@return 参见错误码
@remarks
@see 
*/
DLIB_API t_int32 LCU_AC_ReceiveFile(t_uint32 session, char* info);


/**
@brief 查询消息同步接口
@param [in] session		连接句柄
@param [in] timeout		超时时间
@param [in] condition	查询的条件
@param [in] outxml	    查询结果
@param [in] maxlen	    查询结果长度
@return 参见错误码
@remarks
@condition结构
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<recordid></recordid>	        消息id	
	<fromdomainid></fromdomainid>  	消息发出方的domainid			
	<fromuserid></fromuserid>	    消息发送方的id
	<todomainid></todomainid>		消息接收方的domainid			
	<touserid></touserid>			消息接收方的id		
	<cmd></cmd>	            消息命令
	<type></type>		    消息类型 1 点对点聊天 2 消息 4 任务 8 应答 16 群聊信息 32 群文件（可以相加组合）
	<status></status>	    消息状态 1 未读 2 正在处理 4 完成				
	<curpage></curpage>	    消息显示分页数
	<size></size>		    消息显示每页消息数量						
	<starttime></starttime>	消息的时间范围在(starttime endtime)
	<endtime></endtime>					
	<np1></np1>					
	<np2></np2>	
	<np3></np3>					
	<np4></np4>					
	<np5></np5>	
	<str1></str1>					
	<str2></str2>					
	<str3></str3>	
	<str4></str4>					
	<str5></str5>					
	<str6></str6>	
</root>

@outxml结构
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>   消息总数
	<item>
		<recordid></recordid>					
		<fromdomainid></fromdomainid>					
		<fromuserid></fromuserid>	
		<todomainid></todomainid>					
		<touserid></touserid>					
		<cmd></cmd>	
		<type></type>					
		<status></status>	
		<msg></msg>       消息内容
		<time></time>     消息发送时间
		<np1></np1>					
		<np2></np2>	
		<np3></np3>					
		<np4></np4>					
		<np5></np5>	
		<str1></str1>					
		<str2></str2>					
		<str3></str3>	
		<str4></str4>					
		<str5></str5>					
		<str6></str6>
	</item>
	<item>
	...
	</item>
</root>
@
@see 
*/
DLIB_API t_int32 LCU_SC_GetQueryInfo(t_uint32 session, t_int32 timeout, const char* condition, char*outxml, t_uint32 maxlen);


/**
@brief 修改任务状态同步接口
@param [in] session		连接句柄
@param [in] timeout		超时时间
@param [in] Id	        查询的数据表id
@param [in] Status	    修改的状态
@return 参见错误码
@remarks
@see 
*/
DLIB_API t_int32 LCU_SC_ChangTaskStatus(t_uint32 session, t_int32 timeout, t_int32 Id, t_int32 status);


/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif
