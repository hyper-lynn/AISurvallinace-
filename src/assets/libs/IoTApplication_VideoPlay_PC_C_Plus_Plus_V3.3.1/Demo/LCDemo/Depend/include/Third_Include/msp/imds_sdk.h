/**
 * Copyright (C) 2013 ZHEJIANG  DAHUA  SYSTEM ENGINEERING  CO., LTD 
 * \file		imds_sdk.h
 * \brief		imds_sdk同步操作接口头文件
 * \author		dahuasys
 * \date		2014-01-19
 * \version		1.1.2
 * \note		定义与IMDS服务器操作的 接口
 * \defgroup	IMDS_SDK函数
 * \{
 */
#ifndef IMDS_SDK_H
#define IMDS_SDK_H

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
	#ifdef IMDSSDK_LIB_EXPORTS
	#define DLIB_API __declspec(dllexport)
	#else
	#define DLIB_API __declspec(dllimport)
	#endif //DLIB_EXPORTS
	#define CALLBACK __stdcall
#else
	#define DLIB_API
	#define CALLBACK
#endif	//WIN32

#ifdef __cplusplus
extern "C" 
{
#endif

/**
* \defgroup 同步接口
* \{
*/

/**
* \defgroup 回调函数原型
* \{
*/

/**
 * \brief		SDK消息回调函数定义
 * \param		[in] session		用户会话句柄
 * \param		[in] data			数据缓冲	
 * \param		[in] dataSize		数据长度
 * \param		[in] pUser		用户数据
 * \return		自定义
 * \date		2015-01-19
 * \remarks	接收IMDS服务器相关消息
 * \verbatim
 IMDS服务器上下线状态通知协议
<?xml version='1.0' encoding='utf-8' ?>
<root version="1.0" unit="SDK" type="onlineNotify" cmd="onlineNotify">
        <server servername="IMDS" session="1" status="0"/>
</root>
 IMDS服务器报告注册服务器IP和PORT通知协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="IMDS" type="Request" cmd="reportMasterInfo">
        <modulename>IMDS_SIP</modulename>
        <domid/>
        <ipinfo>10.22.4.55|5060;192.168.1.55|5060;</ipinfo>
        <svrid>0</svrid>
        <sessionid>0</sessionid>
        <accnum>0</accnum>
        <adapnum>0</adapnum>
</root>
调度台管理的话机状态通知协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="IMDS" type="Notify" cmd="DispatchExtensionStateNotify">
	<dispatchNo>1</dispatchNo>
	<currentLabel seq="0" groupId="0" page="1">
		<!--stat:0,1,2,3离线,4已注册（空闲）,5呼叫请求中,6振铃请求中,7振铃,8回铃音,9主叫通话,10被叫通话,11保持,12忙碌,13监听-->
		<!--sessionType:0非法会话,1未知会话,2键权会话,3话机命令会话,4双方会话,5多方会话,6组呼会话,7会议会话,8集呼会话,9调度会话,10紧呼会话11转接会话,12传真会话-->
		<!--speakFlag:0:禁言,1发言请求,2发言-->
		<extension index="0" name="1000" number="1000" sessionType="0" stat="4" speakFlag="0"/>
		<extension index="1" name="1001" number="1001" sessionType="1" stat="7" speakFlag="0"/>
	<currentLabel/>
</root>
调度台键权状态通知协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="IMDS" type="Notify" cmd="DispatchRightKeyStateNotify">
<dispatchNo>1</dispatchNo>
	<sessionHandle>1</sessionHandle>
	<!--rightName 表示当前键权键,0未知,1左键,2右键-->
	<!--rightKeyState 0:弹起 1:按下-->
	<key rightName="1" rightKeyState="0"/>
</root>
调度台功能键状态通知协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="IMDS" type="Notify" cmd="DispatchFuncKeyStateNotify">
	<dispatchNo>1</dispatchNo>
	<sessionHandle>1</sessionHandle>
	<functionKey>
		<!--type: 0未知功能键(默认),1夜服键,2转接键,3保持键,4监听键,5清铃键,6发言键,7闭铃键,8点名键,9轮呼键-->
		<!--stat 0:弹起 1:按下-->
		<funcKey seq="0" type="0" stat="0"/>
		<funcKey seq="1" type="1" stat="0"/>
	</functionKey>
</root>
调度台快捷键状态通知协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="IMDS" type="Notify" cmd="DispatchHotKeyStateNotify">
	<dispatchNo>1</dispatchNo>
	<sessionHandle>1</sessionHandle>
	<hotKey>
	    <!--hotType =0:未知  1:组呼 2:会议 3:集呼-->
		<!--stat 0:弹起 1:按下-->
		<hKey seq="0" hotName="aaa" hotType="1" stat="0"/>
		<hKey seq="1" hotName="bbb" hotType="2" stat="1"/>
	</hotKey>
</root>
调度台配置更新通知协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="IMDS" type="Notify" cmd="DispatchCfgAlterNotify">
        <sessionHandle>0</sessionHandle>
        <dispatchNo>1</dispatchNo>
        <!--cause:0:未知原因,1配置修改,2话机修改,3话机删除,4话机组成员修改,5话机组删除-->
        <cause>1</cause>
</root>
调度台会话更新通知协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="IMDS" type="Notify" cmd="DispatchSessionStateNotify">
        <sessionHandle>0</sessionHandle>
        <dispatchNo>0</dispatchNo>
        <!--prevType:0非法会话,1未知会话,2键权会话,3话机命令会话,4双方会话,5多方会话,6组呼会话,7会议会话,8集呼会话,9调度会话,10紧呼会话11转接会话,12传真会话-->
        <session prevId="1" prevType="1" nextId="1" nextType="1">
                <extensions>
                	<!--lastStatus/status:0,1,2,3离线,4已注册(空闲),5呼叫请求中,6振铃请求中,7振铃,8回铃音,9主叫通话,10被叫通话,11保持,12忙碌,13监听-->
                	<!--type:0会议话机,1虚拟话机,2SIP话机,3ISG话机,4特殊话机,5汇接话机,6命令话机,7外部话机-->
                	<!--identify:0未知,1主叫方,2被叫方,3保持方,4转接方-->
                	<!--speakFlag:0:禁言,1发言请求,2发言-->
                     <extension devCode="IMDS_5000" name="5000" number="5000" lastStatus="3" status="4" type="3" identify="1" speakFlag="0"/>
                </extensions>
        </session>
</root>
调度台共享保持队列通知协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="IMDS" type="Notify" cmd="DispatchHoldlistNotify">
        <sessionHandle>0</sessionHandle>
        <dispatchNo>0</dispatchNo>
        <holdlist>
             <!--seq:分机序号, type:分机类型, operate:操作类型(0:保持队列中增加保持方, 1:保持队列中删除保持方)-->
             <!--callerName:主叫名称, callerNumber:主叫号码, calleeName:被叫名称, calleeNumber:被叫号码-->
             <hold seq="1" type="3" operate="0" callerName="sip" callerNumber="1000" calleeName="sip" calleeNumber="1001"/>
        </holdlist>
</root>
调度台管理的中继键状态通知协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="IMDS" type="Notify" cmd="DispatchExternalStateNotify">
	<dispatchNo>1</dispatchNo>
	<sessionHandle>0</sessionHandle>
	<extentralKey>
		<!--stat:0,1,2,3-->
		<!--sessionType:0非法会话,1未知会话,2键权会话,3话机命令会话,4双方会话,5多方会话,6组呼会话,7会议会话,8集呼会话,9调度会话,10紧呼会话11转接会话,12传真会话-->
		<external seq="0" externalType="1" sessionType="0" stat="4" virtualId="0"/>
	<extentralKey/>
</root>
视频会议预案状态通知协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<dataList>
		<data vId="0" name="aaa" type="1" amount="10" count="0" status="0"/>
		<data vId="1" name="bbb" type="2" amount="10" count="0" status="1"/>
	</dataList>
</root>
视频会议预案成员状态通知协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<type>0</type>
	<dataList>
		<data vId="0" callerName="aaa" callerNumber="1001" inOut="0" status="4" flag="0">
			<member id="0" name="bbb" number="1002" inOut="0" status="5" flag="0"/>
			<member id="1" name="ccc" number="1003" inOut="0" status="5" flag="0"/>
		</data>
	</dataList>
</root>
单个话机状态更新通知视频会议使用协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="IMDS" type="Notify" cmd="ExtensionStateNotify">
	<sessionHandle>1</sessionHandle>
	<extensionName>aaa</extensionName>
	<extensionNumber>1000</extensionNumber>
	<!--extensionType:0会议话机,1虚拟话机,2SIP话机,3ISG话机,4特殊话机,5汇接话机,6命令话机,7外部话机-->
	<extensionType>2</extensionType>
	<!--extensionStat:0,1,2,3离线,4已注册(空闲),5呼叫请求中,6振铃请求中,7振铃,8回铃音,9主叫通话,10被叫通话,11保持,12忙碌,13监听-->
	<extensionStat>2</extensionStat>
	<!--sessionType:0非法会话,1未知会话,2键权会话,3话机命令会话,4双方会话,5多方会话,6组呼会话,7会议会话,8集呼会话,9调度会话,10紧呼会话11转接会话,12传真会话-->
	<sessionType>2</sessionType>
	<!--sessionCaller:当前主叫号码-->
	<sessionCaller>0</sessionCaller>
	<!--speakFlag:0:禁言,1发言请求,2发言-->
	<speakFlag>0</speakFlag>
</root>
单个会话状态更新通知协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="IMDS" type="Notify" cmd="SessionStateNotify">
        <sessionHandle>0</sessionHandle>
        <!--prevType:0非法会话,1未知会话,2键权会话,3话机命令会话,4双方会话,5多方会话,6组呼会话,7会议会话,8集呼会话,9调度会话,10紧呼会话11转接会话,12传真会话-->
        <session prevId="1" prevType="1" nextId="1" nextType="1">
                <extensions>
                	<!--lastStatus/status:0,1,2,3离线,4已注册(空闲),5呼叫请求中,6振铃请求中,7振铃,8回铃音,9主叫通话,10被叫通话,11保持,12忙碌,13监听-->
                	<!--type:0会议话机,1虚拟话机,2SIP话机,3ISG话机,4特殊话机,5汇接话机,6命令话机,7外部话机-->
                	<!--identify:0未知,1主叫方,2被叫方,3保持方,4转接方-->
                	<!--speakFlag:0:禁言,1发言请求,2发言-->
                     <extension devCode="IMDS_5000" name="5000" number="5000" lastStatus="3" status="4" type="3" identify="1" speakFlag="0"/>
                </extensions>
        </session>
</root>
话单上传通知协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="IMDS" type="Notify" cmd="phonebillNotify">
       <result>0</result>
       <phonebill id="0" sessionType="4" pbresult="0" callerNumber="20702" callerName="sip_20702" calleeNumber="20706"
       calleeName="sip_20706" rightHandNumber="20702" leftHandNumber=20706" officeNumber="" starttime="2016-02-23 12:17:36"
       acktime="" endtime="" pbFlag="0" dispatchNo="0"/>
</root>
\endverbatim
 */
typedef t_int32 (*fImdsMsgCallBack)(t_uint32 session, char *data, t_uint32 dataSize, void* pUser);

/** \}
*/

/**
* \defgroup SDK系统
* \{
*/

/**
 * \brief		初始化IMDS SDK
 * \return		IBP错误码
 * \date		2015-01-19
 * \remarks	启动sdk系统
 */
DLIB_API t_int32 IMDS_SC_Init(void);

/**
 * \brief		初始化IMDS SDK,服务或者已经启动applicationBase的程序调用
 * \return		IBP错误码
 * \author	huzhuhua
 * \date		2015-01-19
 * \remarks	启动sdk系统
 */
DLIB_API t_int32 IMDS_SC_InitNoApp(void);

/**
 * \brief		反初始化IMDS SDK
 * \return		错误码
 * \date		2015-01-19
 * \remarks	退出sdk系统
 */
DLIB_API t_int32 IMDS_SC_Cleanup(void);

/** \} */
/**
* \defgroup 打印日志接口
* \{
*/
/**
* \brief		设置日志配置文件路径
* \param		[in] path		配置文件路径
* \return		IBP错误码
* \date		2016-03-09
*/
DLIB_API t_int32 IMDS_SC_SetLogCfgPath(char* path);

/**
 * \brief		客户端记录日志
 * \param		[in] level		日志等级
 * \param 		[in] info		日志信息
 * \return 		IBP错误码
 * \remarks
 * \verbatim
	0	调试日志
	1	信息日志
	2	接口日志
	3	警告日志
	4	错误日志
	5	致命日志
 \endverbatim
*/
DLIB_API t_int32 IMDS_SC_Log(t_uint32 level, char* info);

/** \} */
/**
* \defgroup 登入登出接口
* \{
*/
/**
 * \brief		连接IMDS服务器
 * \param		[in] cmuSession	cmu连接句柄
 * \param		[in] timeout		超时时长(ms)
 * \param		[in]	ipInfo		IMDS服务器ip地址和port地址("10.22.4.55|8800;")
 * \param		[in]	svrDomId		服务器domainID	
 * \param		[in]	svrId		服务器id	
 * \param		[out] outXml		成功连接的句柄	
 * \return		IBP错误码
 * \date		2015-01-19
 * \remarks	在执行初始化sdk后,收到reportMaster消息后调用
 * \verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<imdssession>2</imdssession>
</root>
\endverbatim
 */
DLIB_API t_int32 IMDS_AC_Login(t_uint32 cmuSession, t_int32 timeout, char* ipInfo, char *svrDomId, t_int32 svrId, char* outXml);

/**
 * \brief		断开连接IMDS服务器
 * \param		[in] session			用户会话句柄
 * \return		IMDS_FeedbackCode	错误码
 * \date		2015-01-19
 * \remarks	在执行断开IMDS服务器时或切换IMDS服务器时调用
 */
DLIB_API t_int32 IMDS_AC_Logout(t_uint32 session);

/** \} */
/**
* \defgroup 消息订阅接口
* \{
*/
/**
 * \brief		设置IMDS系统消息
 * \param		[in] session		用户会话句柄
 * \param		[in] cb			回调函数指针
 * \param		[in] pUser		用户数据
 * \return		错误码		IBP错误码
 * \date		2015-01-19
 * \remarks	将回调函数传入系统
 * \see 		fImdsMsgCallBack
 * 
 */
DLIB_API t_int32 IMDS_SC_SetMsg(t_uint32 session, fImdsMsgCallBack cb, void* pUser);

/** \} */

/**
* \defgroup 配置接口
* \{
*/

/**
* \defgroup 基本信息接口
* \{
*/
/**
 * \brief		查询基本配置信息
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \param		[in] length			应答包允许的最大长度
 * \param		[out] outXml			数据指针，参数按照XML格式封装的应答数据包
 * \return		IMDS_FeedbackCode 	IMDS错误码或IBP错误码
 * \date		2015-01-19
 * \remarks	获取基本配置界面信息
 * \verbatim
基本配置界面查询请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
</root>
基本配置界面结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
	<net ip="10.65.0.2" gateway="10.65.0.1" netmask="255.255.0.0" ethernet="eth0" mac=""/>
	<!--表示勾选该项 0表示没有勾选该项-->
	<voiceEncode>
		<encode type="0" choose="0"/>
		<encode type="1" choose="0"/>
		<encode type="2" choose="1"/>
		<encode type="3" choose="1"/>
	</voiceEncode> 
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_BasicCfgQuery(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/**
 * \brief		查询网络参数
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \param		[out] outXml 			数据指针，参数按照XML格式封装的应答数据包
 * \param		[in] length			应答包允许的最大长度
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-19
 * \remarks	获取网络配置参数
 * \verbatim
网络参数查询请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
</root>
网络参数查询结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
	<net ip="10.65.0.2" gateway="10.65.0.1" netmask="255.255.0.0" ethernet="eth0" mac=""/>
</root>
 \endverbatim	
 */
DLIB_API t_int32 IMDS_SC_NetQuery(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/**
 * \brief		配置网络参数
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-19
 * \remarks	设置网络配置参数
 * \verbatim
网络配置请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<net ip="10.65.0.2" gateway="10.65.0.1" netmask="255.255.0.0" ethernet="eth0" mac="" />
</root>
网络配置结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_NetConfig(t_uint32 session, t_int32 timeout, char* inXml);

/**
 * \brief		查询编解码信息
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \param		[out] outXml			数据指针，参数按照XML格式封装的应答数据包
 * \param		[in] length			应答包允许的最大长度
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2014-3-10
 * \remarks	语音编码配置查询
 * \verbatim
语音编码配置查询请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
</root>
语音编码配置查询结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
	<voiceEncode>
		<!--choose:1表示勾选该项 0表示没有勾选该项-->
		<!--encode:0G711U编码,1G711A编码,2G729编码,3G719编码-->
		<encode type="0" choose="0"/>
		<encode type="1" choose="0"/>
		<encode type="2" choose="1"/>
		<encode type="3" choose="1"/>
	</voiceEncode> 
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_VoiceEncodeQuery(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/**
 * \brief		配置编解码信息
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-19
 * \remarks	设置语音编码参数
 * \verbatim
语音编码设置请求	
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<!--choose:1表示勾选该项 0表示没有勾选该项-->
	<!--encode:0G711U编码,1G711A编码,2G729编码,3G719编码-->
	<voiceEncode encode="0" choose="0"/>
	<voiceEncode encode="1" choose="0"/>
	<voiceEncode encode="2" choose="1"/> 
	<voiceEncode encode="3" choose="1"/>
</root>
语音编码参数结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_VoiceEncodeConfig(t_uint32 session, t_int32 timeout, char* inXml);

/**
 * \brief		查询特征键信息
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \param		[in] length			应答包允许的最大长度
 * \param		[out] outXml			数据指针，参数按照XML格式封装的应答数据包
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-19
 * \remarks	获取特征键配置信息
 * \verbatim
查询请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
</root>
查询特征键参数结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
	<item id="0" cmd="11#" describe="转接拨号" />
	<item id="1" cmd="12#" describe="转接执行" />
	<item id="2" cmd="13#" describe="转接回原会话" />
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_SpecialCmdQuery(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/**
 * \brief		配置特征键信息
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-19
 * \remarks	设置特征键参数
 */
DLIB_API t_int32 IMDS_SC_SpecialCmdConfig(t_uint32 session, t_int32 timeout, char* inXml);

/**
 * \brief		查询switch信息
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \param		[out] outXml			数据指针，参数按照XML格式封装的应答数据包
 * \param		[in] length			应答包允许的最大长度
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-19
 * \remarks	查询fs配置时调用
 * \verbatim
查询switch参数请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
</root>
查询switch参数结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
	<fs eslIP="10.22.4.55" eslPort="8086" eventsocketIP="10.22.4.55" eventsocketPort="8021" innerSipPort="5060" outterSipPort="5080"/>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_FSCfgQuery(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/**
 * \brief		配置switch信息 
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装
 * \param		[out] outXml			应答数据指针(预留)，参数按照XML格式封装
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2014-01-19
 * \remarks	修改fs参数时调用
 * \verbatim
switch参数请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<fs eslIP="10.22.4.55" eslPort="8086" eventsocketIP="10.22.4.55" eventsocketPort="8021" innerSipPort="5060" outterSipPort="5080"/>
</root>
switch参数结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_FSCfgSet(t_uint32 session, t_int32 timeout, char* inXml, char* outXml);

/**
 * \brief		查询switch会议号码信息
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \param		[in] length			应答包允许的最大长度
 * \param		[out] outXml			数据指针，参数按照XML格式封装的应答数据包
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2014-5-21
 * \remarks	查询switch会议号码参数
 * \verbatim
查询switch会议号码请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
</root>
查询switch会议号码结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<conference>
		<!--type:1普通音质,2中音质,3高音质,4超高音质-->
		<conf id="0" type="1" number="95xx"/>
		<conf id="1" type="2" number="96xx"/>
		<conf id="2" type="3" number="97xx"/>
		<conf id="3" type="4" number="98xx"/>
	</conference>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_ConferenceQuery(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/**
 * \brief		配置switch会议号码信息
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-19
 * \remarks	设置switch会议室参数
 * \verbatim
switch会议室参数设置请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<conference>
		<!--type:1普通音质,2中音质,3高音质,4超高音质-->
		<conf id="0" type="1" number="99xx"/>
	</conference>
</root>
设置switch会议室结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_ConferenceConfig(t_uint32 session, t_int32 timeout, char* inXml);

/** \} */
/**
* \defgroup 话机信息接口
* \{
*/
/**
 * \brief		查询话机信息
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \param		[out] outXml			数据指针，参数按照XML格式封装的应答数据包
 * \param		[in] length			应答包允许的最大长度
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-19
 * \remarks	查询话机
 * \verbatim
查询话机配置请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<domainId>10</domainId>
	<orgCode>zhejiang</orgCode>
	<page>1</page>
	<numberPerPage>20</numberPerPage>
</root>
查询话机配置结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result> 
	<!--page 当前页码-->
	<page>1</page>
	<!-- totalNum总条目,用于计算页数-->
	<totalNum>20</totalNum>
	<extensions>
		<!--callTransfer(转移类型)0,不转移,1无条件转移,2无应答转移,3遇忙转移,4遇忙+无应答转移-->
		<!--extensionLevel(话机等级)0,不可拨打电话,1可拨打本局电话（默认）,2可拨打市话,3可拨打国内长途,4可拨打国际长途-->
		<!--interposeLevel(强插等级)0:0级,1:1级,2:2级-->
		<!--callHold(呼叫保持)0:不保持,1:保持-->
		<!--recordMode(录音模式)0:不录音,1:录音-->
		<!--DTMFMode(透传模式)0:RFC2833,1:带内 2:Info-->
		<!--dnd(免打扰)0:关闭,1:开启-->
		<!--limitOutIn(限制外线呼入)0:关闭,1:开启-->
		<!--extensionType(话机类型)2:标准sip话机(默认),3ISG话机4特殊SIP话机-->
		<extension deviceCode="201" domainId="1199" deviceType="20000" orgCode="zhejiang" extensionName="aa" extensionNumber="8000"
		alternateNumber="1000" extensionPassword="123456" callTransfer="1" transferNumber="2000" extensionLevel="1" interposeLevel="1" 
		chargeMode="1" advancePayment="200" DTMFMode="0" dialPlan="0" recordMode="0" dialTransform="0" videoChannel="0" callHold="0"
		dnd="0" limitOutIn="0" extensionType="2"/>
	</extensions>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_ExtensionQuery(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/**
 * \brief		配置话机信息
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			请求数据指针，参数按照XML格式封装
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-19
 * \remarks	支持单个话机和批量配置
 * \verbatim
话机配置请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<!--operatetype为操作类型(增0、删1、改2)-->
	<operatetype>0</operatetype>
	<extensions> 
		<extension deviceCode="201" domainId="1199" deviceType="20000" orgCode="zhejiang" extensionName="aa" extensionNumber="8000"
		alternateNumber="1000" extensionPassword="123456" transferNumber="2000" extensionLevel="2" interposeLevel="0" callTransfer="0"
		chargeMode="1" advancePayment="200" DTMFMode="0" dialPlan="0" recordMode="0" dialTransform="0" videoChannel="0" callHold="0"
		dnd="0" limitOutIn="0" extensionType="2"/>
	</extensions>
</root>
话机配置结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_ExtensionConfig(t_uint32 session, t_int32 timeout, char* inXml);

/**
 * \brief		通过号码查询话机信息
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \param		[out] outXml			数据指针，参数按照XML格式封装的应答数据包
 * \param		[in] length			应答包允许的最大长度
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-04-24
 * \remarks	查询话机详细信息
 * \verbatim
查询话机详细信息请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<domainId>10</domainId>
	<number>1000</number>
	<number>1000</number>
</root>
查询话机详细信息请求结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result> 
	<extensions>
		<extension deviceCode="IMDS_1000" domainId="1199" deviceType="20000" orgCode="zhejiang" extensionName="aa" extensionNumber="1000"
		alternateNumber="2000" extensionPassword="123456" transferNumber="2000" extensionLevel="1" interposeLevel="1" callTransfer="1"
		chargeMode="1" advancePayment="200" DTMFMode="0" dialPlan="0" recordMode="0" dialTransform="0" videoChannel="0" callHold="0"
		dnd="0" limitOutIn="0" extensionType="2"/>
	</extensions>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_ExtensionQueryByNumber(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/** \} */
/**
* \defgroup 汇接信息接口
* \{
*/
/**
 * \brief		查询汇接话机信息 
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装
 * \param		[out] outXml			数据指针，参数按照XML格式封装的应答数据包
 * \param		[in] length			应答包允许的最大缓存区长度
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-19
 * \remarks		查询汇接话机(未实现)
 * \deprecated	未实现
 * \verbatim
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_TandemExtensionQuery(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/**
 * \brief		配置汇接话机信息 
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2014-01-19
 * \remarks	增、删、改汇接分机配置时调用(未实现)
 * \verbatim
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_TandemExtensionConfig(t_uint32 session, t_int32 timeout, char* inXml);

/** \} */
/**
* \defgroup 总机信息接口
* \{
*/
/**
 * \brief		查询总机信息
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \param		[in] length			应答包允许的最大长度
 * \param		[out] outXml			数据指针，参数按照XML格式封装的应答数据包
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-19
 * \remarks	获取总机号码配置信息，用于客户端显示
 * \verbatim
查询请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<domainId>10</domainId>
	<orgCode>zhejiang</orgCode>
</root>
查询结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
	<attendantplan>
		<att id="0"domainId="50646"attendantNum="99"attendantIndex=""orgCode="zhejiang"internalMode="0"externalMode="0"/>
		<att id="1"domainId="50646"attendantNum="8"attendantIndex=""orgCode="zhejiang"internalMode="0"externalMode="2"/>
	</attendantplan>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_AttendantQuery(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/**
 * \brief		配置总机信息
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-19
 * \remarks	设置总机号码参数
 * \verbatim
设置总机请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
<usrid>1</usrid>
	<!--operateType为操作类型(增0、删1、改2)-->
	<operateType>0</operateType>
	<!--internalMode externalMode 0对应接续方式为直拨 1人工转接 2语音提示 3未启用-->
	<attendantplan>
		<att id="0"domainId="1" orgCode="zhejiang" attendantNum="8" attendantIndex="0" internalMode="0" externalMode="0"/>
	</attendantplan >
</root>
设置总机号码结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_AttendantConfig(t_uint32 session, t_int32 timeout, char* inXml);

/** \} */
/**
* \defgroup 号码簿接口
* \{
*/
/**
 * \brief		查询号码簿信息
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \param		[in] length			应答包允许的最大长度
 * \param		[out] outXml			数据指针，参数按照XML格式封装的应答数据包
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2014-08-06
 * \remarks	支持查询号码簿
 * \verbatim
号码簿查询
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<domainId>10</domainId>
	<orgCode>zhejiang</orgCode>
</root>
查询号码簿结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
	<domainId>10</domainId>
	<directory>
		<dir domainId="" orgCode="" deviceCode="" name=""number=""/>	
	</directory>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_DirectoryQuery(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/** \} */
/**
* \defgroup 调度信息接口
* \{
*/
/**
 * \brief		查询所有调度台和话机组概要信息
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \param		[out] outXml			数据指针，参数按照XML格式封装的应答数据包
 * \param		[in] length			应答包允许的最大长度
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-19
 * \remarks	调度台管理页面接口(话机组和调度台总参数)
 * \verbatim
调度台管理查询
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
</root>
调度台管理结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
	<extensionGroup> 
		<group id="0" name="a" totalNum="0"/>
		<group id="1" name="b" totalNum="1"/>
	</extensionGroup>
	<dispatchGroup>
		<!--state:0未知,1未使用,2使用中-->
		<dispatch id="0" displayName="xx" state="1"/>
		<dispatch id="1" displayName="xx" state="1"/>
	</dispatchGroup>
</root> 
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_DispatchManageQuery(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/**
 * \brief		查询调度台概要信息
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \param		[out] outXml			数据指针，参数按照XML格式封装的应答数据包
 * \param		[in] length			接收缓冲的最大长度
 * \param		[out] realLen			应答包允许的真实长度
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2016-01-05
 * \remarks	调度台管理接口(所有调度台概要信息)
 * \verbatim
调度台管理查询
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
</root>
调度台管理结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
	<dispatchGroup>
		<!--state:0未知,1未使用,2使用中-->
		<dispatch id="0" displayName="xx" state="1"/>
		<dispatch id="1" displayName="xx" state="1"/>
	</dispatchGroup>
</root> 
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_DispatchManageQueryA(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length, t_uint32 *realLen);

/**
 * \brief		查询话机组概要信息
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \param		[out] outXml			数据指针，参数按照XML格式封装的应答数据包
 * \param		[in] length			接收缓冲的最大长度
 * \param		[out] realLen			应答包允许的真实长度
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2016-01-05
 * \remarks	话机组管理接口(所有话机组概要参数)
 * \verbatim
话机组管理查询
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
</root>
话机组管理结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
	<extensionGroup> 
		<group id="0" name="a" totalNum="0"/>
		<group id="1" name="b" totalNum="1"/>
	</extensionGroup>
</root> 
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_ExtGroupManageQueryA(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length, t_uint32 *realLen);

/**
 * \brief		查询话机组信息
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \param		[out] outXml			数据指针，参数按照XML格式封装的应答数据包
 * \param		[in] length			应答包允许的最大长度
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-19
 * \remarks	查询单个话机组配置时调用
 * \verbatim
话机组参数查询请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<id>1</id>
	<page>1</page>
	<numberPerPage>20</numberPerPage>
</root>
话机组参数查询结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
	<page>1</page>
	<extensionGroup> 
		<id>1</id>
		<name>xxxGroup</name>
		<extension>
			<number seq="4" num="8000" name="aaa" deviceCode="IMDS_8000"/>
			<number seq="5" num="9000" name="bbb" deviceCode="IMDS_9000"/>
		</extension>
	</extensionGroup> 
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_ExtensionGroupQuery(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/**
 * \brief		配置话机组信息
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-19
 * \remarks	增、删、改话机组参数时调用
 * \verbatim
请求协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>  
	<usrid>1</usrid>
	<!--operateType为操作类型(增0、删1、改2)-->
	<operateType>0</operateType>
	<extensionGroup> 
		<id>1</id>
		<name>dispatch</name>
		<extension>
			<!--deviceCode必填项-->
			<number seq="4" num="8000" deviceCode="IMDS_8000"/>
			<number seq="5" num="9000" deviceCode="IMDS_9000"/>
		</extension>
	</extensionGroup> 
</root>
话机组参数配置结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_ExtensionGroupConfig(t_uint32 session, t_int32 timeout, char* inXml);

/**
 * \brief		查询调度台信息
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \param		[out] outXml			数据指针，参数按照XML格式封装的应答数据包
 * \param		[in] length			应答包允许的最大长度
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-19
 * \remarks	查询单个调度台参数时调用
 * \verbatim
查询单个调度台请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<id>1</id>
</root>
查询单个调度台参数结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>	
	<result>200</result>
	<dispatch>
		<id>1<id/>
		<displayName>大华调度台</displayName>
		<lineNumber>9</lineNumber>
		<columnNumber>10</columnNumber>
		<leftPhone name="aa" number="2000" deviceCode="IMDS_2000"/>
		<rightPhone name="" number="" deviceCode=""/>
		<onDutyPhone name="" number="" deviceCode=""/>
		<labelKey>
			<label seq="0" name="aa" groupId="0"/> 
			<label seq="1" name="bb" groupId="1"/> 			
		</labelKey>
		<functionKey>
			<!--type: 0未知功能键,默认参数,1夜服键,2转接键,3保持键,4监听键,5清铃键,6发言键,7闭铃键,8点名键,9轮询键-->
			<func seq="2" type="0"/>   			
		</functionKey>
		<hotKey>
			<!--type =0:未知  1:组呼 2:会议 3:集呼-->
			<hKey seq="" name="aaa" type="2"/>
			<hKey seq="" name="bbb" type="0"/> 
			<hKey seq="" name="" type="0"/>
		</hotKey>
		<externalGroup>
			<externalKey id="1" name="aaa"/>
		</externalGroup>
	</dispatch>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_DispatchQuery(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/**
 * \brief		配置调度台信息
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-19
 * \remarks	单个调度台配置时调用
 * \verbatim
单个调度台配置请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<!--operatetype操作类型(增0、删1、改2)删除操作时只需id节点-->
	<operatetype>0</operatetype>
	<dispatch>
		<id>1<id/>
		<displayName>大华调度台</displayName>
		<lineNumber>9</lineNumber>
		<columnNumber>10</columnNumber>
		<!--deviceCode必填-->
		<leftPhone name="aa" number="2000" deviceCode="IMDS_2000"/>
		!--deviceCode必填-->
		<rightPhone name="" number="" deviceCode=""/>
		!--deviceCode必填-->
		<onDutyPhone name="" number="" deviceCode=""/>
		<labelKey>
			<label seq="2" name=""groupId=""/>			
		</labelKey>
		<functionKey>
			<!--type: 0未知功能键,默认参数,1夜服键,2转接键,3保持键,4监听键,5清铃键,6发言键,7闭铃键,8点名键,9轮询键-->
			<func seq="2" type="0"/>  			
		</functionKey>
		<hotKey>
			<!--type =0:未知  1:组呼 2:会议 3:集呼-->
			<hKey seq="1" name="aaa" type="2"/>
			<hKey seq="2" name="bbb" type="3"/> 
			<hKey seq="3" name="ccc" type="1"/>
		</hotKey>
		<externalGroup>
			<externalKey id="1" name="aaa"/>
		</externalGroup>
	</dispatch>	
</root>
单个调度台配置结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_DispatchConfig(t_uint32 session, t_int32 timeout, char* inXml);

/**
 * \brief		查询外线组概要信息
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml				数据指针，参数按照XML格式封装的请求查询包
 * \param		[out] outXml			数据指针，参数按照XML格式封装的应答数据包
 * \param		[in] length				应答包允许的最大长度
 * \return		IMDS_FeedbackCode		IMDS错误码和IBP错误码
 * \date		2015-07-22
 * \remarks		调度台管理页面接口(中继组总参数)
 * \verbatim
中继组管理查询
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
</root>
中继组管理结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
	<externalGroup> 
		<group id="0" name="a" totalNum="0"/>
		<group id="1" name="b" totalNum="1"/>
	</externalGroup>
</root> 
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_ExternalGroupManageQuery(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/**
 * \brief		查询中继组信息
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml				数据指针，参数按照XML格式封装的请求查询包
 * \param		[out] outXml			数据指针，参数按照XML格式封装的应答数据包
 * \param		[in] length				应答包允许的最大长度
 * \return		IMDS_FeedbackCode		IMDS错误码和IBP错误码
 * \date		2015-07-22
 * \remarks		查询单个中继组配置时调用
 * \verbatim
中继组参数查询请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<id>1</id>
	<page>1</page>
	<numberPerPage>20</numberPerPage>
</root>
中继组参数查询结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
	<page>1</page>
	<externalGroup> 
		<id>1</id>
		<name>xxxGroup</name>
		<external>
			<info seq="4" identifyId="0" name="trunk" type="0"/>
            		<info seq="5" identifyId="0" name="gateway" type="1"/>
		</external>
	</externalGroup> 
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_ExternalGroupQuery(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/**
 * \brief		配置中继组信息
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml				数据指针，参数按照XML格式封装
 * \return		IMDS_FeedbackCode		IMDS错误码和IBP错误码
 * \date		2015-07-22
 * \remarks		增、删、改话机组参数时调用
 * \verbatim
请求协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>  
	<usrid>1</usrid>
	<!--operateType为操作类型(增0、删1、改2)-->
	<operateType>0</operateType>
	<externalGroup> 
		<id>1</id>
		<name>dispatch</name>
		<external>
			<!--identifyId必填项-->
	            <info seq="4" identifyId="0" name="trunk" type="0"/>
	            <info seq="5" identifyId="0" name="gateway" type="1"/>
		</external>
	</externalGroup> 
</root>
中继组参数配置结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_ExternalGroupConfig(t_uint32 session, t_int32 timeout, char* inXml);

/** \} */
/**
* \defgroup 号码变换接口
* \{
*/
/**
 * \brief		查询号码变换信息 
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \param		[in] length			应答包允许的最大长度
 * \param		[out] outXml			数据指针，参数按照XML格式封装的应答数据包
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-19
 * \remarks	获取号码变换配置信息，用于客户端显示
 * \verbatim
号码变换配置请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
</root>
号码变换查询结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<convert id="1" inNumber="xx12xx" outNumber="xx58xx" />  
	<convert id="2" inNumber="35xxxx" outNumber="67xxxx" />  
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_NumberConvertQuery(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/**
 * \brief		配置号码变换信息
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-19
 * \remarks	设置号码变换参数
 * \verbatim
号码变换配置请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<!--operatetype:0添加,1删除,2修改-->
	<opt operatetype="0">
		<convert id="1" inNumber="xx12xx" outNumber="xx58xx" />  
		<convert id="2" inNumber="35xxxx" outNumber="67xxxx" />
	</opt>
</root>
号码变换结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_NumberConvertConfig(t_uint32 session, t_int32 timeout, char* inXml);

/** 
\} 
*/

/**
* \defgroup 路由信息接口
* \{
*/
/**
 * \brief		查询中继参数
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \param		[in] length			应答包允许的最大长度
 * \param		[out] outXml			数据指针，参数按照XML格式封装的应答数据包
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-19
 * \remarks	查询中继参数
 * \verbatim
查询请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
</root>
查询中继参数结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
	<trunkList>
		<trunk tid="1" name="xxxx" identity="trunk004" ip="10.65.0.216" port="5080" limitLine="0" directory="2"
		dialPlanId="0" dialPlanName="aa" callhold="0" cidMode="1" appointNumber="" />
	</trunkList>	
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_TrunkQuery(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/**
 * \brief		 配置中继信息
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \author	huzhuhua
 * \date		2015-01-19
 * \remarks	设置中继参数
 * \verbatim
 请求协议
 <?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<!--operateType为操作类型(增0、删1、改2)-->
	<operateType>0</operateType>
	<trunkList>
		<trunk tid="1" name="xxxx" identity="trunk004" ip="10.65.0.216" port="5080" limitLine="0" directory="2"
		dialPlanId="0" callhold="0" cidMode="1" appointNumber="" />
	</trunkList>
</root>
设置中继参数结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_TrunkConfig(t_uint32 session, t_int32 timeout, char* inXml);

/**
 * \brief		查询网关参数
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装
 * \param		[out] outXml			结果数据指针，参数按照XML格式封装
 * \param		[in] length			应答包允许的最大长度
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-19
 * \remarks	查询网关参数
 * \verbatim
 请求
 <?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
</root>
查询网关参数结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
	<gatewayList>
		<gateway gid="0" name="dhiug88" identify="gateway001" number="88888" passwd="123456" limitLine="10" dialPlan="0" dialPlanName="aa" callhold="0" />
	</gatewayList>	
/root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_GatewayQuery(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/**
 * \brief		IMDS_SC_GatewayConfig
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-19
 * \remarks		配置网关参数
 * \remarks	
 * \verbatim
配置请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<!--operateType为操作类型(增0、删1、改2)-->
	<operateType>0</operateType>
	<gatewayList>
		<gateway gid="0" name="dhiug88" identify="gateway001" number="88888" passwd="123456" limitLine="10" dialPlan="0" callhold="0" />
	</gatewayList>
</root>
配置网关参数结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_GatewayConfig(t_uint32 session, t_int32 timeout, char* inXml);

/**
 * \brief		查询网关FXS/FSO信息
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \param		[in] length			应答包允许的最大长度
 * \param		[out] outXml			数据指针，参数按照XML格式封装的应答数据包
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-19
 * \remarks	获取FXS/FXO配置信息，用于客户端显示
 * \verbatim
请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<!--0表示fxs，1表示fxo -->	
	<fxsoList gid="0" type="0"/>
	</root>
FXS配置查询结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
	<fxsList gid="0"type="0"/>
		<fxs sid="0" number="2000" name="aaa" deviceCode="IMDS_2000"/>
	</fxsList>
</root>
FXO配置查询结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
	<fxoList gid="0"type="0">
		<fxo oid="0"number="2000"name="aaa" />
	</fxoList>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_FxsoQuery(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/**
 * \brief		网关
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-19
 * \remarks	设置FXS/FXO参数
 * \verbatim
设置FXS请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<!--operateType为操作类型(增0、删1、改2)-->
	<operateType>0</operateType>
	<fxsList gid="0">
		<fxs sid="1"name="jack" number="1352222" deviceCode="" />
	</fxsList>
</root>
设置FXO参数
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<!--operateType为操作类型(增0、删1、改2)-->
	<operateType>0</operateType>
	<fxoList gid="0">
		<fxo oid="1" name="lucy" number="1352222"/>
	</fxoList>
</root>
设置FXS/FXO参数结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_FxsoConfig(t_uint32 session, t_int32 timeout, char* inXml);

/**
 * \brief		查询中继/网关cid/did信息 
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \param		[in] length			应答包允许的最大长度
 * \param		[out] outXml			数据指针，参数按照XML格式封装的应答数据包
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-19
 * \remarks	查询中继/网关cid/did参数	
 * \verbatim
查询请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<!--identifyType:0表示中继,1表示网关-->
	<cididList identifyId="0"identifyType="0" />
</root>
查询中继cid/did参数结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
	<cididList identifyId="0" identifyType="0">
		<cidid cdid="0" callerPrefix="02" calleePrefix="" type="0" stripLen="12" addPrefix="12" />
	</cididList>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_CididQuery(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/**
 * \brief		配置中继/网关cid/did信息
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-19
 * \remarks	设置中继/网关cid/did参数
 * \verbatim
配置请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<!-- identifyType:0表示中继,1表示网关 operateType操作类型0添加，1删除(cdid必须要)，2修改(cdid必须要)-->
	<!--operateType为操作类型(增0、删1、改2)-->
	<operateType>0</operateType>
	<cididList identifyId="0" identifyType="1">
		<!--type表示变换类型-->
		<cidid cdid="2" callerPrefix="022" calleePrefix="6" type="1" stripLen="1" addPrefix="135" />
	</cididList>
</root>
设置中继cid/did参数结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_CididConfig(t_uint32 session, t_int32 timeout, char* inXml);

/**
 * \brief		查询中继组和网关组信息
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装
 * \param		[out] outXml			结果数据指针，参数按照XML格式封装
 * \param		[in] length			应答包允许的最大长度
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-19
 * \remarks	查询中继组和网关组参数
 * \verbatim
查询请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
</root>
查询中继和网关参数结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
	<trunkList>
		<trunk tid="1" name="aaaa" identify="trunk001" />  
	</trunkList>
	<gatewayList>
		<gateway gid="1 "name="bbb" identify="gateway001" />
	</trunkList>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_TrunkGatewayQuery(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/**
 * \brief		查询路由信息
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装
 * \param		[out] outXml			结果数据指针，参数按照XML格式封装
 * \param		[in] length			应答包允许的最大长度
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-19
 * \remarks	查询路由参数
 * \verbatim
查询请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<queryType>0</queryType>
</root>
查询路由结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
	<queryType>0</queryType>
	<routeList>
		<route rid="0" name="a" policyType="1" timeInterval="15" retryPolicy="" />
	</routeList>
</root>
查询路由子界面参数
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<queryType>1</queryType>
	<routeId>0</routeId>
</root>
查询路由子界面结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
	<queryType>1</queryType>
	<routeId>0</routeId>
	<tgList>
		<tg id="0" identifyId="0" name="aa" type="1" priority="0" identifyName="routeTosh"/>
	</tgList>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_RouteQuery(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/**
 * \brief		配置路由信息
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-19
 * \remarks	配置路由参数
 * \remarks	
 * \verbatim
配置请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<type>0</type>
	<!--operateType为操作类型(增0、删1、改2)-->
	<operateType>0</operateType>
	<routeList>
		<route rid="0" name="siptodhitg12" policyType="1" timeInterval="15" retryPolicy="1" />
	</routeList>
</root>
配置路由参数子界面协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<type>1</type>
	<routeId>1</routeId>
	<!--operateType为操作类型(增0、删1、改2)-->
	<operateType>0</operateType>
	<tgList>
	<!--type =0表示中继,1表示网关-->
		<tg id="0" identifyId="0" type="0" priority="0" />
		<tg id="1" identifyId="1" type="1" priority="1" />
	</tgList>
</root>
配置路由参数结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_RouteConfig(t_uint32 session, t_int32 timeout, char* inXml);

/** 
\} 
*/
/**
* \defgroup 拨号方案接口
* \{
*/
/**
 * \brief		查询拨号方案信息 
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \param		[in] length			应答包允许的最大长度
 * \param		[out] outXml			数据指针，参数按照XML格式封装的应答数据包
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-09
 * \remarks	获取拨号方案配置信息，用于客户端显示
 * \verbatim
查询拨号方案 
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<queryType>0</queryType>
</root>
查询拨号方案结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
	<queryType>0</queryType>
	<dialPlanList>
		<dialPlan id="0"name="a"/>
	</dialPlanList>
</root>
查询拨号方案内容 子界面
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<queryType>1</queryType>
	<dialPlanId>0</dialPlan>
</root>
查询拨号方案子界面结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
	<queryType>1</queryType>
	<dialPlan>
		<route id="0" matchPrefix="5" policyId="0" policyName="dialtoTrk" dpid="0"/>
	</dialPlan>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_DialPlanQuery(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/**
 * \brief		配置拨号方案信息
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-19
 * \remarks	配置拨号方案参数
 * \verbatim	
配置拨号方案主界面协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<type>0</type>
	<!--operateType为操作类型(增0、删1、改2)-->
	<operateType>0</operateType>
	<dialPlanList>
		<dialPlan dpid="0"name="dialtoiug" />
	</dialPlanList>
</root>
配置拨号方案子界面协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<type>1</type>
	<dialPlanId>1</dialPlanId>
	<!--operateType为操作类型(增0、删1、改2)-->
	<operateType>0</operateType>
	<planContextList>
		<route id="0" matchPrefix="1,2,3" policyId="0" />
		<route id="1" matchPrefix="021,135" policyId="1" />
	</planContextList>
</root>
配置拨号方案结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_DialPlanConfig(t_uint32 session, t_int32 timeout, char* inXml);

/** 
\} 
*/
/**
* \defgroup 视频会议配置
* \{
*/
/**
 * \brief		查询视频会议预案信息
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \param		[in] length			应答包允许的最大长度
 * \param		[out] outXml			数据指针，参数按照XML格式封装的应答数据包
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-15
 * \remarks	获取视频会议室配置信息
 * \deprecated	功能不可用，MCU中实现
 * \verbatim
查询配置视频会议预案界面下所有会议室 
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<domainId>1199</domainId>
	<queryType>0</queryType>
</root>
查询配置视频会议预案界面结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
	<dataList>
		<data vId="0" domainId="1199" orgCode="zhejiang" name="aaaa" topic="xxxxx" type="0" passwd="123456" amount="20" callerDeviceCode="IMDS_1002"/>
	</dataList>
</root>
查询配置视频会议预案界面会议室成员
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<domainId>1199</domainId>
	<queryTtype>1</queryType>
	<vId>0</vId>
</root>
查询配置视频会议预案成员结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
	<vId>0</vId>
	<dataList>	
		<data id="0"name="aaa"number="8000"deviceCode="IMDS_8000" />
		<data id="1"name="bbb"number="8001"deviceCode="IMDS_8000" />
	</dataList>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_VideoConferenceCfgQuery(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/**
 * \brief		配置视频会议室预案信息
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针,参数按照XML格式封装
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-19
 * \remarks	配置视频会议参数
 * \deprecated	功能不可用，MCU中实现
 * \verbatim
配置界面中视频会议配置请求与响应协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<type>0</type>
	<!--operateType为操作类型(增0、删1、改2)-->
	<dataList operateType="0">
		<data vId="0" domainId="1199" orgCode="zhejiang" name="aaaa" topic="xxxxx" type="0" passwd="123456" amount="20" callerDeviceCode="IMDS_1002" />
	</dataList>
</root>
配置界面中视频会议成员请求与响应协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<type>1</type>
	<vId>0</vId>
	<dataList operateType="0">	
		<data id="0" name="aaa" number="8000" deviceCode="IMDS_8000" />
		<data id="1" name="bbb" number="8001" deviceCode="IMDS_8000" />
	</dataList>	
</root>
配置视频会议结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_VideoConferenceCfgConfig(t_uint32 session, t_int32 timeout, char* inXml);

/** 
\} 
*/
/** 
\} 
*/
/**
* \defgroup 业务接口
* \{
*/
/**
* \defgroup 调度操作接口
* \{
*/
/**
 * \brief		登入调度台
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			输入数据指针，参数按照XML格式封装
 * \param		[out] outXml			输出数据指针，参数按照XML格式封装
 * \param		[in] length			输出数据缓冲区长度
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-19
 * \remarks	调度台登入时调用
 * \verbatim
调度台登入请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<dispatchNo>1</dispatchNo>
	<!--dispatchType 0:默认 ,1:19寸调度台-->
	<dispatchType>0</dispatchType>
	<!--numPerPage每页用户数目-->
	<numPerPage>156</numPerPage>
</root>
调度台登入结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
	<dispathNo>1</dispathNo>
	<displayName>大华调度台</displayName>
	<numberPerPage>9</numberPerPage>
	<labelKey>
		<label seq="2" groupId="0" groupName="xxxGroup"/> 
	</labelKey> 			
	<currentLabel seq="0" groupId="1" page="1">
		<!--stat:0,1,2,3离线,4已注册（空闲）,5呼叫请求中,6振铃请求中,7振铃,8回铃音,9主叫通话,10被叫通话,11保持,12忙碌,13监听-->
		<!--sessionType:0非法会话,1未知会话,2键权会话,3话机命令会话,4双方会话,5多方会话,6组呼会话,7会议会话,8集呼会话,9调度会话,10紧呼会话11转接会话,12传真会话-->
		<extension index="0" devCode="001" name="zhangsan" number="1000" sessionType="0" stat="4"/>
		<extension index="1" devCode="002" name="zhangsan" number="1001" sessionType="0" stat="4"/>
		<extension index="2" devCode="003" name="zhangsan" number="1002" sessionType="0" stat="4"/>
		<extension index="3" devCode="004" name="zhangsan" number="1003" sessionType="0" stat="4"/>
	</currentLabel>
	<functionKey>
		<!--type: 0未知功能键,默认参数,1夜服键,2转接键,3保持键,4监听键,5清铃键,6发言键,7闭铃键,8点名键,9轮呼键-->
		<!--stat 0:弹起 1:按下-->
		<funcKey seq="0" type="0" stat="0"/>
		<funcKey seq="1" type="2" stat="1"/> 
		<funcKey/>  			
	</functionKey>
	<hotKey>
		<!--hotType 0:未知  1:组呼 2:会议 3:集呼-->
		<!--stat 0:弹起 1:按下-->
		<hKey seq="1" name="aaa" hotType="2" stat="0"/>
		<hKey seq="2" name="bbb" hotType="0" stat="1"/> 
		<hKey seq="3" name="ccc" hotType="0" stat="0"/>
	</hotKey>
	<externalKey>
		<!--type:0中继1网关-->
		<external seq="0" externalName="aaa" externalType="1" externalStat="1" virtualId="1"/>
	</externalKey>
	<!--keyStat 0:弹起 1:按下-->
	<!--keyName 表示当前键权键，0未知，1左键，2右键-->
	<KeyRight leftName="aa" leftCode="011" leftNumber="2000" rightName="bb" rightCode="022" rightNumber="2001" keyName="0" keyStat="0"/>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_DispatchLogin(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/**
 * \brief		登入调度台新接口
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			输入数据指针，参数按照XML格式封装
 * \param		[out] outXml			输出数据指针，参数按照XML格式封装
 * \param		[in] length			输出数据缓冲区长度
 * \param		[out] realLen			输出数据区实际长度
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-12-21
 * \remarks	调度台登入时调用
 * \verbatim
调度台登入请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<dispatchNo>1</dispatchNo>
	<!--dispatchType 0:默认 ,1:19寸调度台,2:新款android-->
	<dispatchType>2</dispatchType>
	<!--numPerPage每页用户数目-->
	<numPerPage>100</numPerPage>
</root>
调度台登入结果(普通调度台)
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
	<dispathNo>1</dispathNo>
	<displayName>大华调度台</displayName>
	<numberPerPage>150</numberPerPage>
	<labelKey>
		<label seq="2" groupId="0" groupName="xxxGroup"/> 
	</labelKey> 			
	<currentLabel seq="0" groupId="1" page="1">
		<!--stat:0,1,2,3离线,4已注册（空闲）,5呼叫请求中,6振铃请求中,7振铃,8回铃音,9主叫通话,10被叫通话,11保持,12忙碌,13监听-->
		<!--sessionType:0非法会话,1未知会话,2键权会话,3话机命令会话,4双方会话,5多方会话,6组呼会话,7会议会话,8集呼会话,9调度会话,10紧呼会话11转接会话,12传真会话-->
		<extension index="0" devCode="001" name="zhangsan" number="1000" sessionType="0" stat="4"  speakFlag="0"/>
		<extension index="1" devCode="002" name="zhangsan" number="1001" sessionType="0" stat="4"  speakFlag="0"/>
		<extension index="2" devCode="003" name="zhangsan" number="1002" sessionType="0" stat="4"  speakFlag="0"/>
		<extension index="3" devCode="004" name="zhangsan" number="1003" sessionType="0" stat="4"  speakFlag="0"/>
	</currentLabel>
	<functionKey>
		<!--type: 0未知功能键,默认参数,1夜服键,2转接键,3保持键,4监听键,5清铃键,6发言键,7闭铃键,8点名键,9轮呼键-->
		<!--stat 0:弹起 1:按下-->
		<funcKey seq="0" type="0" stat="0"/>
		<funcKey seq="1" type="2" stat="1"/> 
		<funcKey/>  			
	</functionKey>
	<hotKey>
		<!--hotType 0:未知  1:组呼 2:会议 3:集呼-->
		<!--stat 0:弹起 1:按下-->
		<hKey seq="1" name="aaa" hotType="2" stat="0"/>
		<hKey seq="2" name="bbb" hotType="0" stat="1"/> 
		<hKey seq="3" name="ccc" hotType="0" stat="0"/>
	</hotKey>
	<externalKey>
		<!--type:0中继1网关-->
		<external seq="0" externalName="aaa" externalType="1" externalStat="1" virtualId="1"/>
	</externalKey>
	<!--keyStat 0:弹起 1:按下-->
	<!--keyName 表示当前键权键，0未知，1左键，2右键-->
	<KeyRight leftName="aa" leftCode="011" leftNumber="2000" rightName="bb" rightCode="022" rightNumber="2001" keyName="0" keyStat="0"/>
	<!--status:0关闭1开启-->
	<duty status="1" startTime="2016-01-25 12:00:00" endTime="2016-01-25 18:00:00">
		<number>10252</number>
	</duty>	
</root>
调度台登入结果(新的调度台)
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
	<dispathNo>1</dispathNo>
	<displayName>大华调度台</displayName>
	<numberPerPage>1000</numberPerPage>
	<labelKey>
		<!--stat:0,1,2,3离线,4已注册（空闲）,5呼叫请求中,6振铃请求中,7振铃,8回铃音,9主叫通话,10被叫通话,11保持,12忙碌,13监听-->
		<!--sessionType:0非法会话,1未知会话,2键权会话,3话机命令会话,4双方会话,5多方会话,6组呼会话,7会议会话,8集呼会话,9调度会话,10紧呼会话11转接会话,12传真会话-->
                <label seq="0" groupId="1" groupName="aa" page="0">
                        <extension index="0" devCode="IMDS_5001" name="test_5001" number="5001" sessionType="0" stat="0" speakFlag="0"/>
                        <extension index="1" devCode="IMDS_5005" name="test_5005" number="5005" sessionType="0" stat="0" speakFlag="0"/>
                </label>
                <label seq="1" groupId="0" groupName="bb" page="0">
                        <extension index="0" devCode="IMDS_5001" name="test_5001" number="5001" sessionType="0" stat="0" speakFlag="0"/>
                        <extension index="1" devCode="IMDS_5002" name="test_5002" number="5002" sessionType="0" stat="0" speakFlag="0"/>
                </label>
        </labelKey>
	<functionKey>
		<!--type: 0未知功能键,默认参数,1夜服键,2转接键,3保持键,4监听键,5清铃键,6发言键,7闭铃键,8点名键,9轮呼键-->
		<!--stat 0:弹起 1:按下-->
		<funcKey seq="0" type="0" stat="0"/>
		<funcKey seq="1" type="2" stat="1"/> 
		<funcKey/>  			
	</functionKey>
	<hotKey>
		<!--hotType 0:未知  1:组呼 2:会议 3:集呼-->
		<!--stat 0:弹起 1:按下-->
		<hKey seq="1" name="aaa" hotType="2" stat="0"/>
		<hKey seq="2" name="bbb" hotType="0" stat="1"/> 
		<hKey seq="3" name="ccc" hotType="0" stat="0"/>
	</hotKey>
	<externalKey>
		<!--type:0中继1网关-->
		<external seq="0" externalName="aaa" externalType="1" externalStat="1" virtualId="1"/>
	</externalKey>
	<!--keyStat 0:弹起 1:按下-->
	<!--keyName 表示当前键权键，0未知，1左键，2右键-->
	<KeyRight leftName="aa" leftCode="011" leftNumber="2000" rightName="bb" rightCode="022" rightNumber="2001" keyName="0" keyStat="0"/>
	<!--status:0关闭1开启-->
	<duty status="1" startTime="2016-01-25 12:00:00" endTime="2016-01-25 18:00:00">
		<number>10252</number>
	</duty>	
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_DispatchLoginA(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length, t_uint32 *realLen);

/**
 * \brief		登出调度台
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			输入数据指针，参数按照XML格式封装
* \param		[in] length			输出数据缓冲区长度
 * \param		[out] outXml			输入数据指针，参数按照XML格式封装
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-19
 * \remarks		调度台登出时调用
 * \verbatim
调度台登出请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<sessionHandle>5</sessionHandle> 
	<dispatchNo>1<dispatchNo/>
</root>
调度台登出结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_DispatchLogout(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/**
 * \brief		按键权健
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			输入数据指针，参数按照XML格式封装
 * \param		[in] length			输出数据缓冲区长度
 * \param		[out] outXml			输入数据指针，参数按照XML格式封装
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-19
 * \remarks	键权键按下时调用
 * \verbatim
键权键按下请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<dispatchNo>1</dispatchNo>
	<!--rightName 0:未知1:左手柄 2:右手柄-->
	<keyRight rightName="1"/>
</root>
键权键按下结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_DispatchRightKey(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/**
 * \brief		按分机键 
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装
 * \param		[in] length			输出数据缓冲区长度
 * \param		[out] outXml			数据指针，参数按照XML格式封装
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \author	huzhuhua
 * \date		2015-01-19
 * \remarks	用户按下分机键时调用(通知类)
 * \verbatim
分机键按下通知
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<dispatchNo>1</dispatchNo>
	<currentLabel seq="0" groupId="1" page="1">
		<extension index="0" name="zhangsan" number="1000" />
	</currentLabel>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_DispatchExtensionKey(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/**
 * \brief		按标签键
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装
 * \param		[in] length			输出数据缓冲区长度
 * \param		[out] outXml			数据指针，参数按照XML格式封装
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2014-3-7
 * \remarks	用户按下标签键时调用
 * \verbatim
标签键请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<dispatchNo>1</dispatchNo>
	<!--page当前页码,groupId分机组序号-->
	<currentLabel seq="2" groupId="5" page="1" />
</root>
标签键结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
	<dispatchNo>0</dispatchNo>
	<currentLabel seq="0" groupId="1" page="1">
		<extension index="0" name="aa" devCode="001" number="1001" stat="5" sessionType="4" speakFlag="0"/>
		<extension index="1" name="bb" devCode="002" number="1002" stat="5" sessionType="4" speakFlag="0"/>
	</currentLabel>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_DispatchLabelQuery(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/**
 * \brief		按下功能键
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			输入数据指针，参数按照XML格式封装
 * \param		[in] length			输出数据缓冲区长度
 * \param		[out] outXml			输出数据指针，参数按照XML格式封装
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-19
 * \remarks	功能键按下时调用
 * \verbatim
功能键请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<dispatchNo>1</dispatchNo>
	<functionKey>
	<!--stat 0:弹起,1:按下-->
		<funcKey seq="0" type="1" stat="1" />
	</functionKey>
</root>
功能键按下结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_DispatchFuncKey(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/**
 * \brief		按下快捷键
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			输入数据指针，参数按照XML格式封装
 * \param		[in] length			输出数据缓冲区长度
 * \param		[out] outXml			输入数据指针，参数按照XML格式封装
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-01-19
 * \remarks	快捷键按下时调用
 * \verbatim
快捷键请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<dispatchNo>1</dispatchNo>
	<kbType>1</kbType>
	<!--groupType, 0:话机组,1:自定义树呼叫(通过groupId呼叫),2:根据组织结构呼叫(通过domid,orgcode,devtype呼叫)
	<groupType>1</groupType>
	<hotKey>
		<!--hotType:0组呼,1会议,2集呼stat 0:弹起,1:按下-->
		<hKey seq="0" hotName="调度中心会议" hotType="1" stat="0" groupName="调度组" groupId="1" domid="" orgcode="" devtype=""/>
	</hotKey>
</root>
快捷键按下结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_DispatchHotKey(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/**
 * \brief		按下中继键
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			输入数据指针，参数按照XML格式封装
 * \param		[in] length			输出数据缓冲区长度
 * \param		[out] outXml			输入数据指针，参数按照XML格式封装
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2015-06-30
 * \remarks	中继键按下时调用
 * \verbatim
中继键通知
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<dispatchNo>1</dispatchNo>		
	<externalKey>
		<!--type:0中继1网关-->
		<external seq="0" externalType="1" externalStat="5" virtualId="1"/>
	</externalKey>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_DispatchExternalKey(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/**
 * \brief		开启/关闭无人值守功能
 * \param	[in] session			用户会话句柄
 * \param	[in] timeout			超时时间(ms)
 * \param	[in] inXml			输入数据指针，参数按照XML格式封装
 * \param	[in] length			输出数据缓冲区长度
 * \param	[out] outXml			输入数据指针，参数按照XML格式封装
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2016-01-08
 * \remarks	调度无人值守功能时调用
 * \verbatim
 请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<dispatchNo>1</dispatchNo>
	<!--status:0关闭1开启-->
	<onDuty status="0" startTime="2015-12-12 12:20:00" endTime="2015-12-12 15:20:00">
		<number>2000</number>
	</onDuty>
</root>
响应结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_DispatchOnDuty(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/** 
\} 
*/
/**
* \defgroup 视频会议操作
* \{
*/
/**
 * \brief		查询视频预案动态信息 
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \param		[in] length			应答包允许的最大长度
 * \param		[out] outXml			数据指针，参数按照XML格式封装的应答数据包
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2014-10-14
 * \remarks	视频会议操作界面的查询接口 
 * \deprecated	功能不可用，MCU中实现
 * \verbatim
请求协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<domainId>1199</domainId>
	<orgCode>zhejiang</orgCode>
	<queryType>0</queryType>
</root>
响应协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
	<dataList>
		<data vId="0" domainId="1199" orgCode="zhejiang" name="aaaa" topic="xxxxx" type="0" amount="20" count="0"  status="1" callerNumber="1000" callerStatus="4" inOut="0" flag="0" />
			<member id="0"number="8000"name="a"inOut="0"status="4"flag="0"/>
			<member id="0"number="8001"name="a"inOut="0"status="4"flag="0"/>
		</data>
		<data vId="1" domainId="1199" orgCode="zhejiang" name="bbbb" topic="xxxxx" type="0" amount="20" count="0" status="1" callerNumber="1000" callerStatus="4" inOut="0" flag="0" />
			<member id="0" number="8002" name="a" inOut="0" status="4" flag="0"/>
			<member id="0" number="8003" name="a" inOut="0" status="4" flag="0"/>
		</data>
	</dataList>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_VideoConferenceOptQuery(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/**
 * \brief		视频预案操作
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2014-10-21
 * \remarks	视频会议开始/结束操作接口 
 * \deprecated	功能不可用，MCU中实现
 * \verbatim
发起请求协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<callerNumber>1005</callerNumber>
	<vId>0</vId>
	<type>1</type>
</root>
结束请求协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<callerNumber>1005</callerNumber>
	<vId>0</vId>
	<type>2</type>
</root>
响应协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_VideoConferenceOperate(t_uint32 session, t_int32 timeout, char* inXml);

/**
 * \brief		视频会议邀请/剔出操作
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2014-10-21
 * \remarks	支持单个和批量操作
 * \deprecated	功能不可用，MCU中实现
 * \verbatim
邀请请求协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<callerNumber>1005</callerNumber>
	<vId>0</vId>
	<type>1</type>
	<dataList>
		<data id="" number="8000"/>
	</dataList>
</root>
踢出请求协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<callerNumber>1005</callerNumber>
	<vId>0</vId>
	<type>2</type>
	<dataList>
		<data id="" number="8000"/>
	</dataList>
</root>
响应协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_VideoConferenceOperateEx(t_uint32 session, t_int32 timeout, char* inXml);

/**
 * \brief		视频会议室发言/禁言操作
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml				数据指针，参数按照XML格式封装的请求查询包
 * \return		imdsFeedbackCode		IMDS错误码和IBP错误码
 * \date		2014-10-21
 * \remarks	支持单个和批量发言/禁言
 * \deprecated	功能不可用，MCU中实现
 * \verbatim
发言请求协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<callerNumber>1005</callerNumber>
	<vId>0</vId>
	<type>1</type>
	<dataList>
		<data id="" number="8000"/>
	</dataList>
</root>
禁言请求协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<callerNumber>1005</callerNumber>
	<vId>0</vId>
	<type>2</type>
	<dataList>
		<data id="" number="8000" />
	</dataList>
</root>
响应协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_VideoConferenceSpeak(t_uint32 session, t_int32 timeout, char* inXml);

/** 
\}
*/
/**
* \defgroup 新视频会议接口
* \{
*/
/**
 * \brief		视频会议呼叫键权
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \return		imdsFeedbackCode		IMDS错误码和IBP错误码
 * \author		huzhuhua
 * \date		2015-03-11
 * \remarks		首先必须发起的操作
 * \verbatim
视频会议呼叫键权请求协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<callerNumber>1005</callerNumber>
</root>
视频会议呼叫键权响应协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_VideoConferenceCaller(t_uint32 session, t_int32 timeout, char* inXml);

/**
 * \brief		视频会议开始
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \return		imdsFeedbackCode		IMDS错误码和IBP错误码
 * \date		2015-03-11
 * \remarks		开始视频会议
 * \verbatim
视频会议开始请求协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<callerNumber>1005</callerNumber>
	<--!grade:0 表示普通会议-->
	<grade>0</grade>
	<--!type:0 表示会议类型-->
	<type>0</type>
</root>
视频会议开始响应协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_VideoConferenceStart(t_uint32 session, t_int32 timeout, char* inXml);

/**
 * \brief		视频会议结束
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \return		imdsFeedbackCode		IMDS错误码和IBP错误码
 * \date		2015-03-11
 * \remarks		结束视频会议
 * \verbatim
视频会议结束请求协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<callerNumber>1005</callerNumber>
</root>
视频会议结束响应协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_VideoConferenceEnd(t_uint32 session, t_int32 timeout, char* inXml);

/**
 * \brief		视频会议添加人员
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \return		imdsFeedbackCode		IMDS错误码和IBP错误码
 * \date		2015-03-11
 * \remarks		结束视频会议
 * \verbatim
视频会议添加人员请求协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<callerNumber>1005</callerNumber>
	<dataList>
		<data number="8000" />
	</dataList>
</root>
视频会议添加人员响应协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_VideoConferenceAdd(t_uint32 session, t_int32 timeout, char* inXml);

/**
 * \brief		视频会议踢出人员
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \return		imdsFeedbackCode		IMDS错误码和IBP错误码
 * \date		2015-03-11
 * \remarks		结束视频会议
 * \deprived	版本升级无法使用
 * \verbatim
视频会议踢出人员请求协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<callerNumber>1005</callerNumber>
	<dataList>
		<data number="8000" />
	</dataList>
</root>
视频会议踢出人员响应协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_VideoConferenceRemove(t_uint32 session, t_int32 timeout, char* inXml);

/** 
\} 
*/

/**
* \defgroup 话机对讲接口
* \{
*/
/**
 * \brief		话机对讲开始/结束
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \return		IMDS_FeedbackCode		IMDS错误码和IBP错误码
 * \date		2014-10-24
 * \remarks	用于两个话机对话
 * \verbatim
对讲请求协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<type>1</type>
	<dataList>
		<data srcNumber="8000" destNumber="8001"/>
	</dataList>
</root>
对讲请求结束协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<type>2</type>
	<dataList>
		<data srcNumber="8000" destNumber="8001"/>
	</dataList>
</root>
响应协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_Talk(t_uint32 session, t_int32 timeout, char* inXml);

/** 
\} 
*/

/**
* \defgroup 话单接口
* \{
*/
/**
 * \brief		IMDS_SC_PhonebillQuery 
 * \param		[in] session			用户会话句柄，由客户端传入
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \param		[in] length			应答包允许的最大长度
 * \param		[out] outXml			数据指针，参数按照XML格式封装的应答数据包
 * \return		imdsFeedbackCode.h	IMDS错误码和IBP错误码
 * \date		2015-01-27
 * \remarks	查询话单	
 * \verbatim
查询请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<page>1</page>
    	<numberPerPage>20</numberPerPage>
	<phonebill startId="" sessionType="" pbResult="" callerNumber="" calleeNumber="" officeNumber="" starttime="" endtime="" pbFlag ="" />
</root>
查询结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
	<page>1</page>
    	<totalNum>20</totalNum>
    	<numberPerPage>20</numberPerPage>
	<phonebill id="" sessionType="" pbresult="" callerNumber="" calleeNumber="" officeNumber="" starttime="2015-01-26 13:30:30" acktime="2015-01-26 13:30:30" endtime="2015-01-26 13:30:30" pbFlag =""/>
	<phonebill id="" sessionType="" pbresult="" callerNumber="" calleeNumber="" officeNumber="" starttime="2015-01-26 13:30:30" acktime="2015-01-26 13:30:30" endtime="2015-01-26 13:30:30" pbFlag =""/>
	<phonebill id="" sessionType="" pbresult="" callerNumber="" calleeNumber="" officeNumber="" starttime="2015-01-26 13:30:30" acktime="2015-01-26 13:30:30" endtime="2015-01-26 13:30:30" pbFlag =""/>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_PhonebillQuery(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/**
 * \brief		IMDS_SC_PhonebillDelete 
 * \param		[in] session			用户会话句柄，由客户端传入
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \return		imdsFeedbackCode.h	IMDS错误码和IBP错误码
 * \date		2015-02-06
 * \remarks 	删除话单	
 * \verbatim
查询请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<phonebill startId="" count="" sessionType="" pbResult="" callerNumber="" calleeNumber="" officeNumber="" starttime="" endtime="" pbFlag ="" />
</root>
查询结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_PhonebillDelete(t_uint32 session, t_int32 timeout, char* inXml);

/**
 * \brief		IMDS_SC_PhonebillSubscribe 
 * \param		[in] session			用户会话句柄，由客户端传入
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \return		imdsFeedbackCode.h	IMDS错误码和IBP错误码
 * \date		2015-02-06
 * \remarks	订阅话单	
 * \verbatim
话单订阅请求
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<phonebill clientFlag =""/>
</root>
订阅结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_PhonebillSubscribe(t_uint32 session, t_int32 timeout, char* inXml);

/**
 * \brief		IMDS_SC_ExtensionOnOffSet 
 * \param		[in] session			用户会话句柄，由客户端传入
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装
 * \return		imdsFeedbackCode.h	IMDS错误码和IBP错误码
 * \date		2015-01-27
 * \remarks	分机禁用/启用设置(供计费模块控制)
 * \verbatim
请求协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<!--switch:0禁用，1启用-->
	<extensionOnOff extensionNumber="" switch="0"/>
	<extensionOnOff extensionNumber="" switch="1"/>
	<extensionOnOff extensionNumber="" switch="0"/>
</root>
参数结果
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_ExtensionOnOffSet(t_uint32 session, t_int32 timeout, char* inXml);

/** 
\} 
*/

/**
* \defgroup 话机报警接口
* \{
*/
/**
 * \brief		语音报警开始/结束
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml				数据指针，参数按照XML格式封装的请求查询包
 * \return		IMDS_FeedbackCode		IMDS错误码和IBP错误码
 * \date		2014-10-24
 * \remarks	用于报警产生时，需要呼叫指定话机并播放报警音，支持单个或多个同时播放
 * \verbatim
语音报警请求协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<!--flag:0开始,1结束或取消-->
	<flag>0</flag>
	<!--TextToAll:该字段填充后统一播放该段语音,忽略data中的text-->
	<!--中文请填入utf8格式数据-->
	<TextToAll>报警请撤离</TextToAll>
	<!--TTS语音播放次数-->
	<playtimes>10</playtimes>
	<!--TTS语音播放间隔时间，单位秒-->
	<interval>10</interval>
	<!--TTS报警呼叫无应答重新发起呼叫次数-->
	<noAnswerRecallTimes>10</noAnswerRecallTimes>
	<!--TTS报警呼叫无应答重新发起呼叫间隔，单位秒-->
	<noAnswerRecallInterval>10</noAnswerRecallInterval>
	<dataList>
	<!--type:0火警,1水警,2瓦斯,3其他-->
		<!--中文请填入utf8格式数据-->
		<data number="8000" text="火警" type="0"/>
		<data number="8001" text="水警" type="1"/>
	</dataList>
</root>
响应协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_AlarmVoice(t_uint32 session, t_int32 timeout, char* inXml);

/** 
\} 
*/

/**
* \defgroup 手动录音接口
* \{
*/
/**
 * \brief		开始录音/结束录音
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \return		IMDS_FeedbackCode		IMDS错误码和IBP错误码
 * \date		2016-02-24
 * \remarks	用于手动录音
 * \remarks	p1-p6是录音附加参数，p1,p2,p3类型为非负整数，p4,p5,p6类型为字符串
 * \verbatim
开始录音请求协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<dataList>
		<data callerNumber="8000" type="1" p1="" p2="" p3="" p4="" p5="" p6=""/>
	</dataList>
</root>
结束录音请求协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<dataList>
		<data callerNumber="8000" type="2"/>
	</dataList>
</root>
响应协议
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_Record(t_uint32 session, t_int32 timeout, char* inXml);

/** 
\} 
*/

/**
* \defgroup 通话接口
* \{
*/
/**
 * \brief		一般呼叫
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \return		IMDS_FeedbackCode		IMDS错误码和IBP错误码
 * \date		2016-02-22
 * \remarks	用于呼叫空闲话机,支持一对一和一对多个呼叫(必须发起方摘机后才会呼叫目标话机)
 * \remarks	 一般用于多方会话(发起方可以自动继承的会话)
 * \verbatim
发起请求内容
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<!--flag:0开始,1结束或取消-->
	<flag>0</flag>
	<orgNumber>8000</orgNumber>
	<dataList>
		<data destNumber="8001"/>
		<data destNumber="8002"/>
	</dataList>
</root>
响应协议内容
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_MakeCall(t_uint32 session, t_int32 timeout, char* inXml);

/**
 * \brief		强插呼叫
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \return		IMDS_FeedbackCode		IMDS错误码和IBP错误码
 * \date		2016-02-22
 * \remarks	用于呼叫话机或者强插呼叫话机,支持一对一和一对多个呼叫(必须发起方摘机后才会呼叫目标话机)
 * \verbatim
发起请求内容
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<!--flag:0开始,1结束或取消-->
	<flag>0</flag>
	<orgNumber>8000</orgNumber>
	<!--若结束时,想全部停止,无需填写一下节点-->
	<dataList>
		<data destNumber="8001"/>
		<data destNumber="8002"/>
	</dataList>
</root>
响应协议内容
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_MakeForceCall(t_uint32 session, t_int32 timeout, char* inXml);

/**
 * \brief		发起组呼呼叫
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \return		IMDS_FeedbackCode		IMDS错误码和IBP错误码
 * \date		2016-02-22
 * \remarks	用于呼叫一组话机形成通话,一对多个呼叫(必须发起方摘机后才会呼叫目标话机)
 * \remarks	 用于发起一组组呼会话呼叫(所有人都能发言)(含强插功能,但是发起方如果挂机所有人都退出通话)
 * \verbatim
发起请求内容
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<!--flag:0开始,1结束或取消-->
	<flag>0</flag>
	<orgNumber>8000</orgNumber>
	<dataList>
		<data destNumber="8001"/>
		<data destNumber="8003"/>
	</dataList>
</root>
响应协议内容
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_MakeTeamCall(t_uint32 session, t_int32 timeout, char* inXml);

/**
 * \brief		发起广播呼叫
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \return		IMDS_FeedbackCode		IMDS错误码和IBP错误码
 * \date		2016-02-22
 * \remarks	用于呼叫一组话机形成通话,一对多个呼叫(必须发起方摘机后才会呼叫目标空闲状态话机)
 * \remarks	 用于发起一组广播会话呼叫(除了发起方,所有人都只能听)(发起方如果挂机所有人都退出通话)
 * \verbatim
发起请求内容
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<!--flag:0开始,1结束或取消-->
	<flag>0</flag>
	<orgNumber>8000</orgNumber>
	<!--若结束时,想全部停止,无需填写一下节点-->
	<dataList>
		<data destNumber="8001"/>
		<data destNumber="8002"/>
		<data destNumber="8003"/>
	</dataList>
</root>
响应协议内容
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_MakeBroadCastCall(t_uint32 session, t_int32 timeout, char* inXml);

/**
 * \brief		发起会议呼叫
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \return		IMDS_FeedbackCode		IMDS错误码和IBP错误码
 * \date		2016-02-22
 * \remarks	用于呼叫一组话机形成通话,一对多个呼叫(必须发起方摘机后才会呼叫目标空闲状态话机)
 * \remarks	 用于发起一组会议会话呼叫(除了发起方,所有人都只能听,后续可控制发言权限)(发起方如果挂机所有人都退出通话)
 * \verbatim
发起请求内容
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<!--flag:0开始,1结束或取消-->
	<flag>0</flag>
	<orgNumber>8000</orgNumber>
	<!--若结束时,想全部停止,无需填写一下节点-->
	<dataList>
		<data destNumber="8001"/>
		<data destNumber="8002"/>
		<data destNumber="8003"/>
	</dataList>
</root>
响应协议内容
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_MakeMeetingCall(t_uint32 session, t_int32 timeout, char* inXml);

/**
 * \brief		会议成员发言控制
 * \param		[in] session			用户会话句柄
 * \param		[in] timeout			超时时间(ms)
 * \param		[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \return		IMDS_FeedbackCode		IMDS错误码和IBP错误码
 * \date		2016-02-25
 * \remarks	可以指定成员用于会议发言和禁言控制
 * \remarks	如果想会议所有人发言/禁言,只需在xml中传入发起方即可
 * \verbatim
发起请求内容
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<!--flag:0开始发言,1结束发言-->
	<flag>0</flag>
	<orgNumber>8000</orgNumber>
	<!--若结束时,想全部停止,无需填写一下节点-->
	<dataList>
		<data destNumber="8001"/>
		<data destNumber="8002"/>
		<data destNumber="8003"/>
	</dataList>
</root>
响应协议内容
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_MakeMeetingControl(t_uint32 session, t_int32 timeout, char* inXml);

/**
 * \brief		话机状态及所在会话ID查询
 * \param	[in] session			用户会话句柄
 * \param	[in] timeout			超时时间(ms)
 * \param	[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \param	[in] length			应答包允许的最大长度
 * \param	[out] outXml			数据指针，参数按照XML格式封装的应答数据包
 * \return	IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date	2016-04-21
 * \remarks	查询话机状态话机状态及所在会话ID
 * \remarks	支持一次查询多个话机(如果返回状态为0xff，表示该话机不存在)
 * \verbatim
发起请求内容
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<usrid>1</usrid>
	<dataList>
		<data number="8001"/>
		<data number="8002"/>
		<data number="8003"/>
	</dataList>
</root>
响应协议内容
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
	<dataList>
		<data number="8001", extensionState="", sessionId=""/>
		<data number="8001", extensionState="", sessionId=""/>
		<data number="8001", extensionState="", sessionId=""/>
	</dataList>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_ExtensionStateQuery(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/**
 * \brief		传真发送
 * \param	[in] session			用户会话句柄
 * \param	[in] timeout			超时时间(ms)
 * \param	[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2016-07-15
 * \remarks	支持向多个目的端发送同一份传真
 * \remarks	支持发送多个传真文件
 * \verbatim
发起请求内容
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<!--域ID --->
	<domainId></domainId>
	<!-传真目标方 --->
	<destNumber>
		<number>xxxxx</ number>
		<number>xxxxx</ number>
	</destNumber>
	<!--传真文件ID 列表-->
	< dataList >
		<tifId>xxxxx</ tifId>
		<tifId>xxxxx</ tifId>
	</ dataList >
</root>
响应协议内容
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_FaxSend(t_uint32 session, t_int32 timeout, char* inXml);

/**
 * \brief		传真查询
 * \param	[in] session			用户会话句柄
 * \param	[in] timeout			超时时间(ms)
 * \param	[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \param	[in] length			应答包允许的最大长度
 * \param	[out] outXml			数据指针，参数按照XML格式封装的应答数据包
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2016-04-21
 * \remarks	支持分页查询
 * \verbatim
发起请求内容
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<!--域ID --->
	<domainid></domainid>
	<!-传真目标方 --->
	<destNumber></destNumber>
	<!-当前页 -->
	<page>1</page>
	<numberPerPage>20</numberPerPage>
	<!--传真目标方 -->
	<destNumber></destNumber>
	< flag >xxxxx</ flag >
	< type >xxxxx</ type >
</root>
响应协议内容
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
	<page>xxxxx</ page >
	<totalNum>xxxxx</ totalNum >
	< numberPerPage >xxxx</ numberPerPage >
	<!--传真文件信息 -->
	< dataList >
		<data id="1", orgNumber="", orgName="", destNumber="", tifName="", tifNameId="", flag="", type="", procTime="", finTime=""/>
		<data id="2", orgNumber="", orgName="", destNumber="", tifName="", tifNameId="", flag="", type="", procTime="", finTime=""/>
		<data id="3", orgNumber="", orgName="", destNumber="", tifName="", tifNameId="", flag="", type="", procTime="", finTime=""/>
	</ dataList >
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_FaxQuery(t_uint32 session, t_int32 timeout, char* inXml, char* outXml, t_uint32 length);

/**
 * \brief		传真记录删除
 * \param	[in] session			用户会话句柄
 * \param	[in] timeout			超时时间(ms)
 * \param	[in] inXml			数据指针，参数按照XML格式封装的请求查询包
 * \return		IMDS_FeedbackCode	IMDS错误码和IBP错误码
 * \date		2016-07-15
 * \remarks	通过传真文件ID删除传真记录
 * \verbatim
发起请求内容
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<!--域ID --->
	<domainid></domainid>
	<dataList>
	<!--传真文件ID -->
	<tifId>1</ tifId >
	</ dataList >
</root>
响应协议内容
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<result>200</result>
</root>
 \endverbatim
 */
DLIB_API t_int32 IMDS_SC_FaxDelete(t_uint32 session, t_int32 timeout, char* inXml);

/** 
\} 
*/
/**
\} 
*/
/**
\} 
*/
/**
\} 
*/

#ifdef __cplusplus
}
#endif

#endif

