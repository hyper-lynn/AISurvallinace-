/**
 * Copyright (c) 2014~2015, 浙江大华系统工程有限公司 All rights reserved.
 * \file		fs_sdk.h
 * \brief		fs_sdk
 * \author		19833
 * \date		2015年3月23日
 * \note		FS SDK 接口
 */
#ifndef _FS_SDK_H
#define _FS_SDK_H

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
#ifdef FSSDK_LIB_EXPORTS
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
* @defgroup FS_SDK函数
* @{
*/

/**
* @defgroup FS_SDK系统
* @{
*/

/**
@brief FS_SDK初始化
@return 
@remarks
@see 
*/
DLIB_API t_int32 FS_SC_Init();

/**
@brief FS_SDK反初始化
@return 
@remarks
@see 
*/
DLIB_API t_int32 FS_SC_Cleanup();

/** @} */

/**
* @defgroup FS_SDK连接服务
* @{
*/

/**
@brief 连接FS服务
@param [in]  cmuSession		登陆CMU返回的用户session
@param [in]  ipinfo		    FS服务的ip信息
@param [in]  svrdomid		FS服务的域id
@param [in]  serverid		FS服务id
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
DLIB_API t_int32 FS_AC_Connect(t_uint32 cmuSession, char* ipinfo, char* svrdomid, t_int32 serverid, char* outxml, t_uint32 maxlen);

/**
@brief 用户认证连接FS服务
@param [in]  userSession	用户认证
@param [in]  ipinfo		    FS服务的ip信息
@param [in]  svrdomid		FS服务的域id
@param [in]  serverid		FS服务id
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
DLIB_API t_int32 FS_AC_ConnectNoCmu(t_uint32 userSession, char* ipinfo, char* svrdomid, t_int32 serverid, char* outxml, t_uint32 maxlen);

/**
@brief 断开FS服务
@param [in]  session		连接句柄
@return 
@remarks
@see 
*/
DLIB_API t_int32 FS_SC_Disconn(t_uint32 session);

/** @} */

/**
* @defgroup FS_SDK回调函数
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
typedef t_int32 (*fIbpFSMsgCallBack)(t_uint32 session, char *data, t_uint32 bufSize, void* pUser);

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
<root version="1.0" unit="FS" type="onlineNotify" cmd="onlineNotify" sequence="0" length="0">
	<server 
		servername="" 			服务名称
		session="" 					服务句柄
		status="" 					上下线状态
	/>
</root>
@endverbatim

@verbatim
文件开始上传回复
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="Unknown" type="Response" cmd="optFileLoad" sequence="119" session="1">
	<operate>0</operate>
	<guid>3dee7bc4-56c6-4314-9ed6-c79934b72573</guid>
	<filesize>0</filesize>
	<filename/>
	<errmsg/>
	<errcode>200</errcode>
</root>
@endverbatim

@verbatim
文件开始下载回复
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="Unknown" type="Response" cmd="optFileLoad" sequence="186" session="1">
	<operate>1</operate>
	<guid>df6cf787-ca4d-456f-be25-f32548769b4e</guid>
	<filesize>10776916</filesize>
	<filename>CHM_Editor_XP85.rar</filename>
	<errmsg/>
	<errcode>200</errcode>
</root>
@endverbatim

@verbatim
文件上传完成消息通知
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="FS" type="Notify" cmd="commonNotify" sequence="139" session="0">
	<subtype>FileUpload</subtype>
	<notifycode>501</notifycode>
	<notifyname></notifyname>
	<guid>bcb6519c-19fc-4026-be75-52ab8c7baa41</guid>
	<progress>100</progress>
</root>
@endverbatim

@verbatim
文件下载完成消息通知
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="FS" type="Notify" cmd="commonNotify" sequence="139" session="0">
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
DLIB_API t_int32 FS_SC_SetFSMsg(t_uint32 session, fIbpFSMsgCallBack cb, void* pUser);

/** @} */

/**
* @defgroup FS_SDK文件操作
* @{
*/


/**
@brief 查询文件
@param [in] session		连接句柄
@param [in] timeout		超时时间
@param [in] info				条件信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<domainid></domainid>								域ID
	<filename></filename>							文件名称
	<modulename></modulename>			模块名称
	<mainid></mainid>								文件主标识ID
	<subid></subid>									文件辅标识ID
	<size></size>											每页大小
	<curpage></curpage>							查询第几页
</root>
@endverbatim
@param [out] outxml		返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>             总数
	<item domainid="" filename="" creatortime="" outoftime="" modulename="" mainid="" subid="" guid="" uploaderdomainid="" uploader="" desc=""/>
	<item domainid="" filename="" creatortime="" outoftime="" modulename="" mainid="" subid="" guid="" uploaderdomainid="" uploader="" desc=""/>
	<item domainid="" filename="" creatortime="" outoftime="" modulename="" mainid="" subid="" guid="" uploaderdomainid="" uploader="" desc=""/>
</root>
@endverbatim
@param [in]  maxlen		信息最大长度
@return 参见错误码
@remarks 四个查询条件是相与的关系，其中文件名称是模糊查询，只要包含该名称即符合条件
@see 
*/
DLIB_API t_int32 FS_SC_QueryFile(t_uint32 session,t_int32  timeout,char* info, char* outxml,t_uint32  maxlen);

/**
@brief 上传文件同步接口
@param [in] session		连接句柄
@param [in] timeout		超时时间
@param [in] info				文件信息(UTF8编码)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<domainid></domainid>								域ID
	<filepath></filepath>							文件全路径(包括文件名和后缀)
	<modulename></modulename>		模块名称
	<mainid></mainid>							文件主标识ID
	<subid></subid>								文件主标识ID
	<validtime></validtime>					有效期(单位：秒)
	<uploader></uploader>					上传人
	<desc></desc>               					文件描述
</root>
@endverbatim
@param [out] guid		文件GUID
@return 参见错误码
@remarks
@see 
*/
DLIB_API t_int32 FS_SC_UploadFile(t_uint32 session,t_int32  timeout,char* info, char* guid);

/**
@brief 上传文件异步接口
@param [in] session		连接句柄
@param [in] info				文件信息(UTF8编码)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<domainid></domainid>								域ID
	<filepath></filepath>							文件全路径(包括文件名和后缀)
	<modulename></modulename>		模块名称
	<mainid></mainid>							文件主标识ID
	<subid></subid>								文件主标识ID
	<validtime></validtime>					有效期(单位：秒)
	<uploader></uploader>					上传人
	<desc></desc>               					文件描述
</root>
@endverbatim
@param [out] guid		文件GUID
@return 参见错误码
@remarks
@see 
*/
DLIB_API t_int32 FS_AC_UploadFile(t_uint32 session, char* info, char* guid);

/**
@brief 下载文件同步接口
@param [in] session		连接句柄
@param [in] timeout		超时时间
@param [in] info				文件信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<domainid></domainid>								域ID
	<guid></guid>					需要下载的文件GUID
	<filepath></filepath>			下载文件的存放路径	
</root>
@endverbatim
@return 参见错误码
@remarks
@see 
*/
DLIB_API t_int32 FS_SC_DownloadFile(t_uint32 session,t_int32  timeout,char* info);

/**
@brief 下载文件异步接口
@param [in] session		连接句柄
@param [in] info				文件信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<domainid></domainid>								域ID
	<guid></guid>					需要下载的文件GUID
	<filepath></filepath>			下载文件的存放路径	
</root>
@endverbatim
@return 参见错误码
@remarks
@see 
*/
DLIB_API t_int32 FS_AC_DownloadFile(t_uint32 session, char* info);
/**
@brief 下载文件异步接口
@param [in] session		连接句柄
@param [in] info				文件信息
@param [out] Name				文件名
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<domainid></domainid>								域ID
	<guid></guid>					需要下载的文件GUID
	<filepath></filepath>			下载文件的存放路径	
</root>
@endverbatim
@return 参见错误码
@remarks
@see 
*/

DLIB_API t_int32 FS_SC_DownloadFileOutName(t_uint32 session,t_int32  timeout,char* info,char*name);

/**
@brief 下载文件并获得文件数据流
@param [in] session		连接句柄
@param [in] timeout		超时时间
@param [in] info				文件信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<domainid></domainid>								域ID
	<guid></guid>					需要下载的文件GUID
</root>
@endverbatim
@param [out] buf		文件内容
@param [in]  maxlen		信息最大长度
@return 参见错误码
@remarks
@see 
*/
DLIB_API t_int32 FS_SC_DownloadFileAsStream(t_uint32 session,t_int32  timeout,char* info, char* buf,t_uint32  maxlen);

/**
@brief 删除文件
@param [in] session		连接句柄
@param [in] timeout		超时时间
@param [in] guid			文件GUID
@param [in] domainId		域ID
@return 参见错误码
@remarks
@see 
*/
DLIB_API t_int32 FS_SC_DeleteFile(t_uint32 session,t_int32  timeout,char* guid,char*domainId);

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif
