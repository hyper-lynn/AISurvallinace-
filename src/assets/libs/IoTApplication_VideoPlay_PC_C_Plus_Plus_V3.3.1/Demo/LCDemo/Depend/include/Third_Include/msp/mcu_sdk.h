/**
 * Copyright (c) 2014~2015, 浙江大华系统工程有限公司 All rights reserved.
 * \file		mcu_sdk.h
 * \brief		mcu_sdk
 * \author		13108
 * \date		2015年3月12日
 * \note		MCU SDK 接口
 */
#ifndef _MCU_SDK_H
#define _MCU_SDK_H

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
#ifdef MCUSDK_LIB_EXPORTS
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
* @defgroup MCU_SDK函数
* @{
*/

/**
* @defgroup MCU_SDK系统
* @{
*/

/**
@brief MCU SDK 初始化
@return 
@remarks
@see 
*/
DLIB_API t_int32 MCU_SC_Init();

/**
@brief MCU SDK 反初始化
@return 
@remarks
@see 
*/
DLIB_API t_int32 MCU_SC_Cleanup();

/** @} */

/**
* @defgroup MCU_SDK连接服务
* @{
*/

/**
@brief 连接MCU服务
@param [in]  cmuSession	登陆CMU返回的用户session
@param [in]  ipinfo		    MCU服务的ip信息
@param [in]  svrdomid		MCU服务的域id
@param [in]  serverid		MCU服务id
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
DLIB_API t_int32 MCU_AC_Connect(t_uint32 cmuSession, char* ipinfo, char* svrdomid, t_int32 serverid, char* outxml, t_uint32 maxlen);

/**
@brief 用户认证连接MCU服务
@param [in]  userSession	用户认证
@param [in]  ipinfo		    MCU服务的ip信息
@param [in]  svrdomid		MCU服务的域id
@param [in]  serverid		MCU服务id
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
DLIB_API t_int32 MCU_AC_ConnectNoCmu(t_uint32 userSession, char* ipinfo, char* svrdomid, t_int32 serverid, char* outxml, t_uint32 maxlen);

/**
@brief 断开MCU服务
@param [in]  session		连接句柄
@return 
@remarks
@see 
*/
DLIB_API t_int32 MCU_SC_Disconn(t_uint32 session);

/** @} */

/**
* @defgroup MCU_SDK回调函数
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
typedef t_int32 (*fIbpMCUMsgCallBack)(t_uint32 session, char *data, t_uint32 bufSize, void* pUser);

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
<root version="1.0" unit="MCU" type="onlineNotify" cmd="onlineNotify" sequence="0" length="0">
	<server 
		servername="" 			服务名称
		session="" 				服务句柄
		status="" 				上下线状态
	/>
</root>
@endverbatim
@verbatim
用户登陆会议室消息通知
<?xml version='1.0' encoding='utf-8' ?>
<root version="1.0" unit="MCU" type="Notify" cmd="meetLoginNotify" sequence="0" length="0">
	<userdomid/>				用户域ID
	<userid/>					用户ID
	<username/>					用户名称
	<devcode/>					设备代码
	<telephone/>				号码
	<pwd/>						密码
	<status/>					解禁言状态 0解禁 1禁言
	<flag/>						登陆标识 0登出 1 登入 2剔除
	<roomdomid/>				会议室域ID
	<roomname/>					会议室名称
	<meetid/>					会议室ID
	<sessionid/>				用户session
</root>
@endverbatim
@verbatim
用户解禁言消息通知
<?xml version='1.0' encoding='utf-8' ?>
<root version="1.0" unit="MCU" type="Notify" cmd="meetUserBanNotify" sequence="0" length="0">
	<userdomid/>				用户域ID
	<userid/>					用户ID
	<username/>					用户名称
	<flag/>						解禁言标识 0解禁 1禁言
	<roomdomid/>					会议室域ID
	<roomname/>					会议室名称
	<meetid/>					会议室ID
	<sessionid/>				用户session
</root>
@endverbatim
@verbatim
会议室配置变更消息通知
<?xml version='1.0' encoding='utf-8' ?>
<root version="1.0" unit="MCU" type="Notify" cmd="commonNotify" sequence="0" length="0">
	<notifycode>401</notifycode>			通知代码
	<nofityname>modMeetCfg</nofityname>		通知代码名称
	<operate></operate>						变更类型 0 增加 1 修改 2 删除
	<roomdomid/>							会议室域ID
	<roomname/>								会议室名称
	<roomid></roomid>						会议室ID
</root>
@endverbatim
@verbatim
用户被剔除消息通知
<?xml version='1.0' encoding='utf-8' ?>
<root version="1.0" unit="MCU" type="Notify" cmd="commonNotify" sequence="0" length="0">
	<notifycode>402</notifycode>			通知代码
	<nofityname>kickUser</nofityname>		通知代码名称
	<userdomid/>							用户域ID
	<userid/>					            用户ID
	<username/>								用户名称
	<roomdomid/>							会议室域ID
	<roomname/>								会议室名称
	<roomid/>				                会议室id
	<sessionid/>				            用户session
</root>
@endverbatim
@verbatim
会议结束消息通知
<?xml version='1.0' encoding='utf-8' ?>
<root version="1.0" unit="MCU" type="Notify" cmd="commonNotify" sequence="0" length="0">
	<notifycode>403</notifycode>			通知代码
	<nofityname>meetEnd</nofityname>		通知代码名称
	<roomdomid/>							会议室域ID
	<roomname/>								会议室名称
	<roomid/>				                会议室id
</root>
@endverbatim
@verbatim
会议室文件操作消息通知
<?xml version='1.0' encoding='utf-8' ?>
<root version="1.0" unit="MCU" type="Notify" cmd="commonNotify" sequence="0" length="0">
	<notifycode>404</notifycode>			通知代码
	<nofityname>meetfileOpt</nofityname>	通知代码名称
	<operate></operate>						类型 1:打开文件 2:文件更新
	<roomdomid/>							会议室域ID
	<roomid/>				                会议室id
	<filename/>                             文件名称(注: 可以为空)
	<total/>                                总页数(注: operate==1时有效)
	<current/>                              当前页(注: operate==2时有效,默认值为1)
</root>
@endverbatim
@verbatim
会议室演示文稿当前页码更新通知
<?xml version='1.0' encoding='utf-8' ?>
<root version="1.0" unit="MCU" type="Notify" cmd="commonNotify" sequence="0" length="0">
	<notifycode>405</notifycode>			通知代码
	<nofityname>meetFilePage</nofityname>	通知代码名称
	<roomdomid/>							会议室域ID
	<roomid/>				                会议室id
	<current/>                              当前页
</root>
@endverbatim
@verbatim
会议室锁定解锁消息通知
<?xml version='1.0' encoding='utf-8' ?>
<root version="1.0" unit="MCU" type="Notify" cmd="commonNotify" sequence="0" length="0">
	<notifycode>406</notifycode>			通知代码
	<nofityname>meetLock</nofityname>	    通知代码名称
	<flag/>						            标识    0:解锁 1:锁定
	<roomdomid/>							会议室域ID
	<roomname/>								会议室名称
	<roomid/>				                会议室id
</root>
@endverbatim
@verbatim
邀请参加会议通知
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="MCU" type="Notify" cmd="commonNotify" sequence="44" session="0">
	<notifycode>408</notifycode>
	<notifyname>inviteUser</notifyname>
	<newroomdomdid/>会议室域ID
	<newroomid></newroomid>
	<newroomtype></newroomtype>
	<newroompassword></newroompassword>
	<usernumber></usernumber>
	<userid></userid>
	<userflag></userflag>//1是主讲人 0不是主讲人
	<usersession></usersession>
</root>
@endverbatim
@verbatim
绑定号码通知
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="MCU" type="Notify" cmd="commonNotify" sequence="44" session="0">
	<notifycode>409</notifycode>
	<notifyname>phoneNum<notifyname/>
	<callnumber>33321</callnumber>
	<password>123456</password>
</root>
@endverbatim
@verbatim
VOIP状态通知
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="MCU" type="Notify" cmd="commonNotify" sequence="44" session="0">
	<notifycode>410</notifycode>
	<notifyname>voipExtensionState</notifyname>
	<name></name>
	<number></number>
	<sessionhandle></sessionhandle>
	<sessiontype></sessiontype>
	<state></state>
	<type></type>
</root>
@endverbatim
@verbatim
设备绑定通知
<?xml version='1.0' encoding='utf-8' ?>
<root version="1.0" unit="MCU" type="Notify" cmd="commonNotify" sequence="0" length="0">
    <notifycode>411</notifycode>            通知代码
    <nofityname>bindDevice</nofityname>     通知代码名称
    <devcode></devcode>                		绑定设备的设备编码             
    <domid></domid>                      	 绑定设备的域id
	<userdomid/>							用户域ID
    <userid></userid>						用户id
    <session></session>						用户session  
	<roomdomid/>							会议室域ID
	<roomid></roomid>						会议室id
</root>
@endverbatim
@verbatim
通用错误消息通知
<?xml version='1.0' encoding='utf-8' ?>
<root version="1.0" unit="MCU" type="Notify" cmd="commonNotify" sequence="0" length="0">
    <notifycode>417</notifycode>            通知代码
    <nofityname>mcuErrMsg</nofityname>     通知代码名称
    <errorcode></errorcode>                 	错误码
</root>

<errorcode>1933</errorcode>				用户已经在其他会议中（IBP_Err_MCU_MEMBER_IS_IN_OTHER_MEETING）
<userdomid>11</userdomid>                 	用户域编码
<userid>1</userid>									用户编码

@endverbatim
@see 
*/
DLIB_API t_int32 MCU_SC_SetMCUMsg(t_uint32 session, fIbpMCUMsgCallBack cb, void* pUser);

/** @} */

/**
* @defgroup MCU_SDK会议室配置信息
* @{
*/

/**
@brief 操作会议室配置信息
@param [in]  session		登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 info		操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>		操作类型 0 增加 1 修改 2 删除
	<item 
		meetid=""		会议室ID
		domid=""		会议室域ID
		code=""			会议室代码
		name=""			会议室名称
		theme=""		主题
		pwd=""			会议室密码
		num=""			最大人数
		userid=""		主讲用户ID
		status=""		会议状态
		type=""			会议类型(从第0位开始) 第1位：应急会议或普通会议 第2位：流程会议 第3位：群聊
							typ & 0x02 > 0 应急会议, type & 0x04 > 0 流程会议, type & 0x08 > 0 群聊会议
		fast=""			是否有效
		creatorid=""	会议创建者ID
		time=""			会议创建时间
		starttime=""	开始时间
		endtime=""		结束时间
		updatetime=""	更新时间
		orgid=""		组织ID
		orgdomid=""		组织域ID
		orgcode=""		组织代码
		orgpath=""		组织路径
	/>
</root>
@endverbatim
@return 
@remarks
@see MCU_SC_QueryMeetingCfgInfo
*/
DLIB_API t_int32 MCU_SC_OptMeetingCfgInfo(t_uint32 session, t_int32 timeout, char* info);

/**
@brief 查询会议室配置信息列表
@param [in]  session		登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 info		操作信息(详见MCU_SC_OptMeetingCfgInfo)
@verbatim
按照会议室id查询,不要多填字段，<code/>,<type/>务必为空
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<roomdomid/>		会议室域ID
	<meetid/>			会议室ID,
	<size />			每页大小
	<curpage />			查询第几页
</root>
@endverbatim
@verbatim
按照会议室code查询，<meetid/>
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<roomdomid/>		会议室域ID
	<code />			会议室代码
	<size />			每页大小
	<curpage />			查询第几页
	<type />			会议室类型，用","分隔，比如<type>2,3</type>,为空查全部
</root>
@endverbatim
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
按照会议室类型查询，不要多填字段，<meetid/>,<code/>务必为空
<root>
	<roomdomid/>		会议室域ID
	<type />			会议室类型，用","分隔，比如<type>2,3</type>
	<size />			每页大小
	<curpage />			查询第几页
</root>
@endverbatim
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
查全部，不要多填字段，<meetid/>,<code/>,<type/>务必为空
<root>
	<roomdomid/>		会议室域ID
	<size />			每页大小
	<curpage />			查询第几页
</root>
@endverbatim
@param [out] outxml			返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>
	<item meetid="" domid="" code="" name="" theme="" pwd="" num="" userid="" username="" status="" type="" fast="" creatorid="" creatorname="" time="" starttime="" endtime="" updatetime="" orgid="" orgdomid="" orgcode="" orgname="" orgpath="" />
	<item meetid="" domid="" code="" name="" theme="" pwd="" num="" userid="" username="" status="" type="" fast="" creatorid="" creatorname="" time="" starttime="" endtime="" updatetime="" orgid="" orgdomid="" orgcode="" orgname="" orgpath="" />
</root>
@endverbatim
@param [in]  maxlen			信息最大长度
@return 
@remarks
@see MCU_SC_OptMeetingCfgInfo
*/
DLIB_API t_int32 MCU_SC_QueryMeetingCfgInfo(t_uint32 session, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup MCU_SDK用户操作会议室
* @{
*/

/**
@brief 用户登陆/登出会议室
@param [in]  session		登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 userId		用户ID
@param [in]  roomDomId  会议室域ID
@param [in]	 roomId		会议室ID
@param [in]	 pwd		会议室密码
@param [in]	 flag		登陆标识： 0 登出 1 登陆
@param [out] outxml			返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<flag>0</flag>		主讲人标识 0 不是 1 是
	<userdomid/>
	<userid/>
	<username/>
	<domid/>
	<devcode/>
	<telephone/>
	<pwd/>
	<status/>
	<device devcode="" domid="" />
	<device devcode="" domid="" />
</root>
@endverbatim
@param [in]  maxlen			信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 MCU_SC_LoginMeetingRoom(t_uint32 session, t_int32 timeout, t_int32 userId, char* roomDomId, t_int32 roomId, char *pwd, t_int32 flag, char* outxml, t_uint32 maxlen);

/**
@brief 查询会议室中所有用户信息
@param [in]  session		登陆句柄
@param [in]	 timeout		超时时间
@param [in]	 roomDomId		会议室域ID
@param [in]	 roomId			会议室ID
@param [out] outxml			返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		userdomid=""		用户域ID
		userid=""			用户ID
		username=""			用户名称
		domid=""			设备域ID
		devcode=""			摄像头代码
		telephone=""		号码
		pwd=""				密码
		status=""			用户禁言状态
		sessionid=""		用户session
	/>
	<item userid="" username="" domid="" devcode="" telephone="" pwd="" status="" />
</root>
@endverbatim
@param [in]  maxlen			信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 MCU_SC_QueryMeetingUserInfo(t_uint32 session, t_int32 timeout, char *roomDomId, t_int32 roomId, char *outxml, t_uint32 maxlen);

/**
@brief 用户锁定/解锁会议室
@param [in]  session		登陆句柄
@param [in]	 timeout		超时时间
@param [in]	 userDomId		用户域ID
@param [in]	 userId			主讲用户ID
@param [in]	 roomDomId		会议室域ID
@param [in]	 roomId			会议室ID
@param [in]	 flag			标识 0 解锁 1 加锁
@return 
@remarks
@see 
*/
DLIB_API t_int32 MCU_SC_LockMeetingRoom(t_uint32 session, t_int32 timeout, char *userDomId, t_int32 userId, char *roomDomId, t_int32 roomId, t_int32 flag);

/**
@brief 用户发起语音会话
@param [in]  session		登陆句柄
@param [in]	 timeout		超时时间
@param [in]	 userDomId		用户域ID
@param [in]	 userId			用户ID
@param [in]	 telNum			话机号码
@return 
@remarks
@see 
*/
DLIB_API t_int32 MCU_SC_Call(t_uint32 session, t_int32 timeout, char *userDomId, t_int32 userId, char *telNum);

/**
@brief 用户禁言/取消禁言操作
@param [in]  session		登陆句柄
@param [in]	 timeout		超时时间
@param [in]	 userDomId		用户域ID
@param [in]	 userId			用户ID 
@param [in]	 sessionId		用户session -1全部禁言/全部发言
@param [in]	 roomDomId		会议室域ID
@param [in]	 roomId			会议室ID
@param [in]	 flag			标识 0 解禁 1 禁言
@return 
@remarks
@see 
*/
DLIB_API t_int32 MCU_SC_OptUserMute(t_uint32 session, t_int32 timeout, char *userDomId, t_int32 userId, t_uint32 sessionId, char *roomDomId, t_int32 roomId, t_int32 flag);

/**
@brief 结束会议操作
@param [in]  session		登陆句柄
@param [in]	 timeout		超时时间
@param [in]	 userDomId		用户域ID
@param [in]	 userId			主讲用户ID(-1不验证是不是主讲人)
@param [in]	 roomDomId		会议室域ID
@param [in]	 roomId			会议室ID
@return 
@remarks
@see MCU_SC_OptMeetingCfgInfo
*/
DLIB_API t_int32 MCU_SC_ExitMeeting(t_uint32 session, t_int32 timeout, char *userDomId, t_int32 userId, char *roomDomId, t_int32 roomId);

/**
@brief 查询会议室用户关联视频设备信息列表
@param [in]  session		登陆句柄
@param [in]	 timeout	    超时时间
@param [out] outxml			返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item userdomid="" userid="" chncode="" domid="" />
</root>
@endverbatim
@param [in]  maxlen			信息最大长度
@return 
@remarks
@see
*/
DLIB_API t_int32 MCU_SC_QueryMeetingDeviceInfo(t_uint32 session, t_int32 timeout, char *outxml, t_uint32 maxlen);


/**
@brief 剔除用户协议(老接口，弃用)
@param [in]  session		登陆句柄
@param [in]	 timeout		超时时间
@param [in]	 userDomId		用户域ID
@param [in]	 userId			主讲用户ID
@param [in]	 roomDomId		会议室域ID
@param [in]	 roomId			会议室ID
@param [in]	 kickId			被剔除用户ID
@param [in]	 kickSession 	被剔除用户session

@return 
@remarks
@see 
*/
DLIB_API t_int32 MCU_SC_KickoutUser(t_uint32 session, t_int32 timeout, char *userDomId, t_int32 userId, char *roomDomId, t_int32 roomId, char *kickDomId, t_int32 kickId, t_uint32 kickSession);

/**
@brief 查询会议室文档打开的当前页码
@param [in]  session		登陆句柄
@param [in]	 timeout		超时时间
@param [in]	 roomDomId		会议室域ID
@param [in]	 roomId			会议室ID 
@param [out] outxml			返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<page></page>      没有打开就返回默认值0
</root>
@endverbatim
@param [in]  maxlen			信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 MCU_SC_QueryMeetingFilePage(t_uint32 session, t_int32 timeout, char *roomDomId, t_int32 roomId, char *outxml, t_uint32 maxlen);


/**
@brief 操作会议室文件消息
@param [in]  session		登陆句柄
@param [in]	 timeout		超时时间
@param [in]	 operate    	类型 1:打开文件 2:文件更新
@param [in]	 roomDomId		会议室域ID
@param [in]	 roomid     	会议室id
@param [in]	 filename   	文件名称(注: 可以为空)
@param [in]	 total      	总页数(注: operate==1时有效)
@param [in]	 current    	当前页(注: operate==2时有效,默认值为1)
@return 
@remarks
@see
*/
DLIB_API t_int32 MCU_SC_OptMeetingFile(t_uint32 session, t_int32 timeout, t_int32 opt, char *roomDomId, t_int32 roomId, char *filename, t_int32 total, t_int32 current);

/**
@brief 会议室演示文稿当前页上传消息
@param [in]  session		登陆句柄
@param [in]	 timeout		超时时间
@param [in]	 roomDomId		会议室域ID
@param [in]	 roomid     	会议室id
@param [in]	 current    	当前页
@return 
@remarks
@see
*/
DLIB_API t_int32 MCU_SC_OptMeetingCurrentPage(t_uint32 session, t_int32 timeout, char *roomDomId, t_int32 roomId, t_int32 current);

/**
@brief 邀请用户协议(老接口，弃用)
@param [in]	session			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info			输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item number="" domid="" devcode=""/>
	<item number="" domid="" devcode=""/>
	<roomdomid></roomdomid>
	<roomid></roomid>
</root>
@endverbatim
@param [out] outxml		返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
</root>
@endverbatim
@param [in]  maxlen			信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 MCU_SC_InviteUser(t_uint32 session, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief 邀请进入/踢出会议室
@param [in]	session			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info			输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt></opt><!--0 邀请 2 踢出-->
	<domid></domid><!--会议室domid-->
	<roomid></roomid><!--会议室id-->
	<!--meetingmember
			no 流水号，用于参数错误时确定是第几行，非必填
			domid 成员的域id，必填
			session 成员的session，踢人时有效
			number 成员的号码，和devcode、userid三选一
			devcode 成员的设备编码，和number、userid三选一
			userid 成员的userid，和number、devcode三选一
	-->
	<meetingmember no="" domid="" session="" number="" devcode=""/>
	<meetingmember no="" domid="" session="" number="" devcode=""/>
</root>
@endverbatim
@param [out] outxml		返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<!--如果有错误，则返回错误行-->
	<meetingmember no="" domid="" number="" devcode=""/>
</root>
@endverbatim
@param [in]  maxlen			信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 MCU_SC_OptMeetingMember(t_uint32 session, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);


/**
@brief 挂断电话
@param [in]  session	登陆句柄
@param [in]	 timeout	超时时间
@param [in]	 info		操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<roomdomid></roomdomid>
	<roomid></roomid>
	<callnumber>1001</callnumber>
</root>
@endverbatim
@return 
@remarks
*/
DLIB_API t_int32 MCU_SC_HangUp(t_uint32 session, t_int32 timeout, char* info);

/** @} */

/**
* @defgroup MCU_SDK会议室联系人管理
* @{
*/

/**
@brief 查询联系人
@param [in]	session			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<keywords> 可输入：-1（查全部），电话号码，联系人姓名拼音，联系人姓名首字母，联系人姓名</keywords>
	<curpage></curpage>
	<size></size>
</root>
@endverbatim
@param [out] outxml				返回信息（默认安装联系人姓氏首字母排序）
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>
	<contact id="" userid="" name="" type="" domid="">
		<telephone number=""/>
		<telephone number=""/>
	</contact>
	<contact/>
		...
	</contact>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 MCU_SC_QueryAllContact(t_uint32 session, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief 配置通话记录
@param [in]	session			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt></opt>
	<callrecord id="通话记录编号" 
		userid="通话记录所属用户编号" 
		callingname="主叫名称"
		callingdomid="主叫域编号" 
		callingnumber="主叫号码" 
		calledname="被叫名称，对应原‘name’字段"
		calleddomid="被叫域编号" 
		callednumber="被叫号码，对应原‘number’字段" 
		calltype="0:拨出 1:接听"
		type="1:系统用户联系人 2:固定话机 3:虚拟话机" 
		time="通话记录时间"
		desc=""
	/>
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt></opt>
	<callrecord id=""/>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 MCU_SC_OptCallRecord(t_uint32 session, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief 查询通话记录
@param [in]	session			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<userid></userid>
	<curpage></curgpage>
	<size></size>
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>
	<callrecord id="" userid="" name="" number="" type="1:系统用户联系人 2：固定话机 3：虚拟话机" desc=""/>
	<callrecord id=""/>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 MCU_SC_QueryCallRecord(t_uint32 session, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief 收藏联系人
@param [in]	session			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt></opt>
	<collection id="" userid="" name="" number="" type="1:系统用户联系人 2：固定话机 3：虚拟话机" desc=""/>
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt></opt>
	<collection id=""/>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 MCU_SC_OptContactCollection(t_uint32 session, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief 查询收藏的联系人
@param [in]	session			登陆句柄
@param [in]	timeout			超时时间
@param [in]	 info				输入信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<userid>所属用户id </userid>
	<size>每页大小</size>
	<curpage>第几页，从0开始</curpage>
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>
	<collection id="" userid="" name="" number="" type="1:系统用户联系人 2：固定话机 3：虚拟话机" desc=""/>
	<collection id=""/>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 MCU_SC_QueryContactCollection(t_uint32 session, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif
