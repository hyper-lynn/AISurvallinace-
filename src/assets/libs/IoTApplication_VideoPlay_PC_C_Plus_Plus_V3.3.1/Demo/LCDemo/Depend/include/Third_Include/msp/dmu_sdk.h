/**
 * Copyright (c) 2014, 浙江大华系统工程有限公司 All rights reserved.
 * \file		dmu_sdk.h
 * \brief		dmu_sdk
 * \author		24997
 * \date		2014年12月19日
 * \note		DMU SDK 接口
 */
#ifndef IBP_DMU_SDK_H
#define IBP_DMU_SDK_H

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
#ifdef IBPDMUSDK_LIB_EXPORTS
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
* @defgroup DMU_SDK函数
* @{
*/

/**
* @defgroup DMU_SDK系统
* @{
*/

/**
@brief DMU_SDK初始化
@return 
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_Init();


/**
@brief DMU_SDK初始化,服务或者已经启动applicationBase的程序调用
@return 
@remarks
@see DMU_SC_InitNoApp
*/
DLIB_API t_int32 DMU_SC_InitNoApp();

/**
@brief DMU_SDK反初始化
@return 
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_Cleanup();

/** @} */

/**
* @defgroup DMU_SDK连接服务
* @{
*/

/**
@brief 连接DMU服务
@param [in]  timeout		超时时间
@param [in]  cmusession		CMU登陆句柄
@param [in]  ipinfo		    DMU服务的ip信息
@param [in]  svrdomid		DMU服务的域id
@param [in]  serverid		DMU服务id
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
DLIB_API t_int32 DMU_AC_Connect(t_uint32 cmusession, char* ipinfo, char* svrdomid, t_int32 serverid, char* outxml, t_uint32 maxlen);

/**
@brief 用户认证连接DMU服务
@param [in]  timeout		超时时间
@param [in]  usersession	用户认证
@param [in]  ipinfo		    DMU服务的ip信息
@param [in]  svrdomid		DMU服务的域id
@param [in]  serverid		DMU服务id
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
DLIB_API t_int32 DMU_AC_ConnectNoCmu(t_uint32 usersession, char* ipinfo, char* svrdomid, t_int32 serverid, char* outxml, t_uint32 maxlen);

/**
@brief 断开DMU服务
@param [in]  session		连接句柄
@return 
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_Disconn(t_uint32 session);

/** @} */

/**
* @defgroup DMU_SDK回调函数
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
typedef t_int32 (*fIbpDmuMsgCallBack)(t_uint32 session, char *data, t_uint32 bufSize, void* pUser);

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
<root version="1.0" unit="DMU" type="onlineNotify" cmd="onlineNotify" sequence="0" length="0">
	<server 
		servername="" 			服务名称
		session="" 				服务句柄
		status="" 				上下线状态
	/>
</root>
@endverbatim
@verbatim
报告master更新通知
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="DMU" type="Notify" cmd="reportMasterUpdate" sequence="" session="0">
	<domid></domid>				域ID
	<modulename></modulename>	模块名称
</root>
@endverbatim
@verbatim
告警数据通知
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="DMU" type="Notify" cmd="alarmData" sequence="">
	<item
		domid=""				域ID
		devcode=""				设备代码
		devname=""				设备名称
		subdevcode=""			子设备代码
		name=""					子设备名称
		chncode=""				资源或通道代码
		chnname=""				资源或通道名称
		chnidx=""				资源或通道索引
		type=""					告警类型
		subtype=""				告警子类型
		status=""				状态
		level=""				告警等级 0 无 1 严重 2 重要 3 一般 4 次要 5普通
		alarmtime=""			告警上报时间
		msgtxt=""				消息内容
		val=""					值
		unit=""					单位
		orgpath=""				组织设备路径
		title=""				组织设备路径名
		longitude=""            经度(单位是百万分之度，范围0-360度)
		latitude=""             纬度(单位是百万分之度，范围0-180度)
		phonedomid=""			话机域
		phonecode=""			话机编码
		phonenum=""				话机号码
		phonepass=""			话机密码
	/>
</root>
@endverbatim
@verbatim
实时数据通知
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="DMU" type="Notify" cmd="realData" sequence="">
	<item
		domid=""				域ID
		devcode=""				设备代码
		subdevcode=""			子设备代码
		chncode=""				通道代码
		chnidx=""				通道索引
		val=""					值
		unit=""					单位
		desc=""					描述
		time=""					时间
		isalarm=""				是否告警
		type=""					告警类型
		level=""				告警等级
		orgpath=""			
		title=""
		phonedomid=""			话机域
		phonecode=""			话机编码
		phonenum=""				话机号码
		phonepass=""			话机密码

		intparam1=""			gps定位星数
		intparam2=""			gps天线状态(true 好，false 坏)
		intparam3=""			gps定位状态(true 定位，false 不定位)
		strparam1=""
		strparam2=""
		strparam3=""
	>
		<expand					    pgs扩展信息
			longitude=""			经度(单位是百万分之度，范围0-360度)
			latitude=""				纬度(单位是百万分之度，范围0-180度)
			height=""				高度(米)
			angle=""				方向角(正北方向为原点，顺时针为正)
			speed=""				速度(单位是海里，speed/1000*1.852公里/小时)
		/>
	</item>
</root>
@endverbatim
@verbatim
修改预置点通知
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="DMU" type="Notify" cmd="modifyPrepointNotify" sequence="">
	<domid></domid>				域ID
	<devcode></devcode>			设备代码
	<index></index>				预置点号
	<name></name>				名称
	<operate></operate>			操作类型
	<userid></userid>			用户ID
	<username></username>		用户名称
	<level>1</level>			用户级别
	<updatetime></updatetime>	操作时间
</root>
@endverbatim
@verbatim
修改OSD通知
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="DMU" type="Notify" cmd="modifyOSDNotify" sequence="">
	<opt 
		domid="" 				域ID
		devcode="" 				设备代码
		userid="" 				用户ID
		operate="" 				操作类型
		count=""				操作数量
	>
		<info 
			type="" 			修改类型 1 修改OSD标签 2 修改OSD时间
			pointx="" 			原点X坐标
			pointy="" 			原点Y坐标
			width="" 			宽度
			length="" 			高度
			rgb="" 				RGB值
			alpha="" 			ALPHA值
			title=""			标签内容
		/>
	</opt>
</root>
@endverbatim
@verbatim
云台抢占通知
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="DMU" type="Notify" cmd="ptzArrange" sequence="">
	<domid></domid>				域ID
	<chncode></chncode>			通道代码
	<userid></userid>			用户ID
	<username>0</username>		用户名 
	<level></level>				用户级别
	<department></department>	部门
	<locktime></locktime>		锁定时间
</root>
@endverbatim
@verbatim
查询局域网设备结果通知
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="DMU" type="Notify" cmd="searchDevRetNotify" sequence="">
	<devcode>abc</devcode>
	<type>1</type>
	<ip></ip>
	<port>1</port>
	<mac></mac>
</root>
@endverbatim
@see 
*/
DLIB_API t_int32 DMU_SC_SetDmuMsg(t_uint32 session, fIbpDmuMsgCallBack cb, void* pUser);

/**
@brief 设置回调告警数据缓存配置
@param [in] session		连接句柄
@param [in] num			告警条数(默认设置100条)
@return
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_SetAlarmDataCfg(t_uint32 session, t_int32 num);

/**
@brief 查询最新回调告警数据
@param [in] session		连接句柄
@param [out] outxml		返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		domid=""			域ID
		devcode=""			设备代码
		devname=""			设备名称
		subdevcode=""		子设备代码
		name=""				子设备名称
		chncode=""			资源或通道代码
		chnname=""			资源或通道名称
		chnidx=""			资源或通道索引
		type=""				告警类型
		subtype=""			告警子类型
		status=""			状态
		level=""			告警等级
		alarmtime=""		告警上报时间
		msgtxt=""			消息内容
		val=""				值
		unit=""				单位
		orgpath=""			组织设备路径
		title=""			组织设备路径名
	/>
</root>
@endverbatim
@param [in]  maxlen		信息最大长度
@return
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_QueryNewAlarmData(t_uint32 session, char *outxml, t_uint32 maxlen);

/**
@brief 设置回调非设备上下线的告警消息
@param [in] session		连接句柄
@param [in] flag		回调标识 0 默认不回调 1 回调
@return
@remarks 如果想实时回调告警消息，请调用此接口
@see 
*/
DLIB_API t_int32 DMU_SC_OpenCbAlarmData(t_uint32 session, t_int32 flag);

/** @} */

/**
* @defgroup DMU_SDK告警订阅
* @{
*/

/**
@brief 设置订阅全部告警或实时数据标识
@param [in] session				连接句柄
@param [in] subscribeflag		告警全部订阅标识 0 默认否 1 是
@param [in] distributeflag		分发设备授权标识 0 否 1 默认是
@return
@remarks 1、默认时，无须调用此接口 2、有需要，连接成功后立即调用
@see 
*/
DLIB_API t_int32 DMU_SC_SetSubAllAlarm(t_uint32 session, t_int32 subscribeflag = 0, t_int32 distributeflag = 1);

/**
@brief 操作告警或实时数据订阅
@param [in] session		连接句柄
@param [in] timeout		超时时间
@param [in] info		操作xml
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt
		type=""			子类型 0 告警订阅 1 实时数据订阅 2pgs信息
		level=""		所有告警等级 -1 表示订阅告警 1~5表订阅等级统一修改位该等级
	>
		<item 
			operate=""	操作类型
			flag=""		0：订阅具体的设备；1：订阅组织
			devcode=""	设备代码(为组织时，填写路径)
			domid=""	设备域ID
			type=""		告警类型 -1 所有类型
			level=""	告警等级 5 高于等于该等级的告警都可以收到
		/>
	</opt>
</root>
@endverbatim
@return
@remarks 订阅组织就是订阅组织及其下所有设备
@see 
*/
DLIB_API t_int32 DMU_SC_OptSubscribe(t_uint32 session, t_int32 timeout, char *info);

/**
@brief 查询告警或实时数据订阅
@param [in] session		连接句柄
@param [in] timeout		超时时间
@param [in] subtype		子类型 0 告警订阅 1 实时数据订阅
@param [out] outxml		返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		devcode=""		设备代码
		domid=""		设备域ID
		type=""			告警类型
		level=""		告警等级
	/>
</root>
@endverbatim
@param [in]  maxlen		信息最大长度
@return
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_QuerySubscribe(t_uint32 session, t_int32 timeout, t_int32 subtype, char *outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup DMU_SDK视频OSD信息
* @{
*/

/**
@brief 操作OSD信息
@param [in] session		连接句柄
@param [in] timeout		超时时间
@param [in] info		操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt 
		domid=""		域ID
		devcode=""		设备代码
		operate=""		操作类型
		count=""		OSD数量
	>
		<item 
			type=""		OSD索引类型 1 名称OSD 2 时间OSD
			pointx=""	原点X坐标
			pointy=""	原点Y坐标
			width=""	宽度
			length=""	长度
			rgb=""		RGB值
			alapha=""	ALAPHA值
			title=""	标签
		/>
	</opt>
</root>
@endverbatim
@return
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_OptOsdInfo(t_uint32 session, t_int32 timeout, char* info);

/**
@brief 获取OSD信息
@param [in]  session		连接句柄
@param [in]  timeout		超时时间
@param [in]  domainid		设备域id
@param [in]  chncode		通道编码
@param [in]  idx			信息索引 0 全部 1 名称OSD 2 时间OSD
@param [out] outxml			返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item type="" pointx="" pointy="" width="" length="" rgb="" alapha="" title="" />
</root>
@endverbatim
@param [in]  maxlen			信息最大长度
@return
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_QueryOsdInfo(t_uint32 session, t_int32 timeout, char* domainid, char* chncode, t_int32 idx, char* outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup DMU_SDK预置点
* @{
*/

/**
@brief 操作预置点
@param [in] session			连接句柄
@param [in] timeout			超时时间
@param [in] info			操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<srcdomid></srcdomid>	源发起域ID
	<domid></domid>			设备域ID
	<devcode></devcode>		通道设备代码
	<chnidx></chnidx>		通道序号(不填)
	<index></index>			预置点ID
	<name></name>			预置点名称
	<flag></flag>			是否为默认预置点，1 默认预置点，0 非默认预置点
	<interval></interval>	flag为1时，设备回归默认预置点时间间隔
	<operate></operate>		操作类型 0 添加，1修改，2删除
</root>
@endverbatim
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_OptPrepoint(t_uint32 session, t_int32 timeout, char *info);

/**
@brief 获取预置点
@param [in] session			连接句柄
@param [in] timeout			超时时间
@param [in] domainid		设备域id
@param [in] chncode			通道编码
@param [out] outxml			返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<count></count>			数量
	<item 
		index=""			预置点编号
		name=""				预置点名称
		flag=""				标志，1 默认预置点，0 非默认预置点
		revered=""			保留
	/>
</root>
@endverbatim
@param [in]  maxlen			信息最大长度
@return
@remarks
@see 
*/
DLIB_API t_int32 DMU_SC_QueryPrepoint(t_uint32 session, t_int32 timeout, char* domainid, char* chncode, char *outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup DMU_SDK云台控制
* @{
*/

/**
@brief 云台控制
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] info				操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<domid></domid>				域ID
	<chncode></chncode>			通道代码
	<stop></stop>				停止位，1表示停止，0表示开启
	<cmd></cmd>					控制命令
	<intparam1></intparam1>		参数1
	<intparam2></intparam2>		参数2
	<intparam3></intparam3>		参数3
	<intparam4></intparam4>		参数4
	<intparam5></intparam5>		参数5
	<intparam6></intparam6>		参数6
	<intparam7></intparam7>		参数7
	<intparam8></intparam8>		参数8
	<strparam1></strparam1>		字符串参数1
	<strparam2></strparam2>		字符串参数2
</root>
@endverbatim
@param [out] outxml				错误码信息
@param [in]  maxlen				信息最大长度
@return
@remarks 
@verbatim
控制命令定义
	0 ePTZCmd_Unknown,			未知
	1 ePTZCmd_Up,               向上 
	2 ePTZCmd_Down,             向下
	3 ePTZCmd_Left,		        向左
	4 ePTZCmd_Right,		    向右
	5 ePTZCmd_LeftUp,           左上 
	6 ePTZCmd_RightUp,          右上 
	7 ePTZCmd_LeftDown,         左下 
	8 ePTZCmd_RightDown,        右下 
	9 ePTZCmd_GotoPreset,       转到预置点 
	10 ePTZCmd_SetPreset,       设置预置点
	11 ePTZCmd_ClearPreset,     清除预置点
	12 ePTZCmd_QuickOrient,     三维快速定位 
	13 ePTZCmd_Zoom_Tele,       焦距拉进 
	14 ePTZCmd_Zoom_Wide,       焦距拉远 
	15 ePTZCmd_Focus_Near,      焦点调进 
	16 ePTZCmd_Focus_Far,       焦点调远 
	17 ePTZCmd_Iris_Auto,       光圈自动调整 
	18 ePTZCmd_Iris_Large,      光圈增大 
	19 ePTZCmd_Iris_Small,      光圈缩小
	20 ePTZCmd_Aux_On,          擦拭启动
	21 ePTZCmd_Aux_Off,         擦拭停止
	22 ePTZCmd_Light_On ,       灯光开启 
	23 ePTZCmd_Light_Off,       灯光关闭
	24 ePTZCmd_StartTour,       开始自动巡航
	25 ePTZCmd_StopTour,        停止自动巡航 
	26 ePTZCmd_AutoPan_On,      水平巡航启动 
	27 ePTZCmd_AutoPan_Off      水平巡航停止 
	39 ePTZCmd_IOControl		IO状态控制(报警输出控制)
	40 ePTZCmd_LockPtz			云台加解锁控制(stop:1 解锁 0 锁定)
针对不同命令参数说明（未说明参数不填或者默认）
1、3D定位命令
	intparam1					顶点X坐标
	intparam2					底点X坐标
	intparam3					顶点Y坐标
	intparam4					底点Y坐标
2、预置点命令
	intparam2					预置点索引
3、其它命令
	intparam1					垂直速度
	intparam2					水平速度
@endverbatim
@see 
*/
DLIB_API t_int32 DMU_SC_PTZControl(t_uint32 session, t_int32 timeout, char *info, char* outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup DMU_SDK查询告警数据
* @{
*/

/**
@brief 查询历史告警信息
@param [in]  session			连接句柄
@param [in]  timeout			超时时间
@param [in]	 info				条件信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<srcdomid />		发起域ID
	<starttime />		开始时间
	<endtime />			结束时间
	<type />			告警类型 -1 查询全部 其它查询指定
	<domid />			设备域ID
	<devcode />			通道设备代码，比如"'chn0','chn1','chn2'"
	<chnidx />			通道序号
	<domdevcode />		设备域ID+设备代码，比如"'chn0','chn1','chn2'@domid1; 'chn0','chn1','chn2'@domid2"
	<size />			每页大小
	<curpage />			查询第几页
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>				总数
	<item 
		id=""					告警记录ID
		domid=""				域ID
		devcode=""				设备代码
		devname=""				设备名称
		chnidx=""				通道索引
		devtype=""				设备类型
		type=""					告警类型
		status=""				状态
		level=""				告警等级
		alarmtime=""			告警时间
		length=""				数据长度
		msgtxt=""				消息文本
		confirmor=""			确认人
		confirmtime=""			确认时间
		comfirmmsg=""			确认消息
		comfirmstatus=""		确认状态
	/>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QueryHistoryAlarmInfo(t_uint32 session, t_int32 timeout, char *info, char *outxml, t_uint32 maxlen);

/**
@brief 操作告警确认信息
@param [in]  session			连接句柄
@param [in]  timeout			超时时间
@param [in]	 info				操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<confirmtime></confirmtime>	告警消息日期
	<item 
		id=""					告警记录ID
		confirmmsg=""			确认信息
		confirmstatus=""		确认状态 0 未确认 1 已确认
	/>
</root>
@endverbatim
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_OptAlarmConfirm(t_uint32 session, t_int32 timeout, char *info);

/**
@brief 查询历史实时数据信息
@param [in]  session			连接句柄
@param [in]  timeout			超时时间
@param [in]  inxml				条件信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<srcdomid />		发起域ID
	<starttime />		开始时间
	<endtime />			结束时间
	<domid />			设备域ID
	<devcode />			通道设备代码，比如"'chn0';'chn1';'chn2'"
	<size />			每页大小
	<curpage />			查询第几页
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>				总数
	<item 
		domid=""				域ID
		devcode=""				设备代码
		devname=""				设备名称
		devtype=""				设备类型
		time=""					上报时间
		val=""					实时数据值
		unit=""					实时数据单位
	/>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QueryHistoryRealData(t_uint32 session, t_int32 timeout, char* inxml, char* outxml, t_uint32 maxlen);


/**
@brief 查询历史实时数据的平均值
@param [in]  session			连接句柄
@param [in]  timeout			超时时间
@param [in]  inxml				条件信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<starttime />		开始时间
	<endtime />			结束时间
	<domid />			设备域ID
	<devcode />			设备编码
	<interval />		间隔的时间，单位秒
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		domid=""				域ID
		devcode=""				设备代码
		devname=""				设备名称
		devtype=""				设备类型
		starttime=""			时间段开始时间
		endtime=""			    时间段结束时间
		val=""					时间段的平均值
		unit=""					实时数据单位
	/>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QueryHistoryRealData_AVG(t_uint32 session, t_int32 timeout, char* inxml, char* outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup DMU_SDK告警等级
* @{
*/

/**
@brief 操作告警优先级
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] info				操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt 
		operate=""				操作类型
	>
		<item 
			devcode=""			设备代码
			domid=""			域ID
			type=""				告警类型
			level=""			告警等级
			updatetime=""		更新时间
		/>
	</opt>
</root>
@endverbatim
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_OptAlarmPriority( t_uint32 session, t_int32 timeout, char *info);

/**
@brief 查询告警优先级
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] alarmcategory		告警大类型 0表示非大类条件
@param [in] info				非大类条件
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		devcode=""				设备代码
		domid=""				域ID
		type=""					告警类型
		level=""				告警等级(不填)
		udatetime=""			更新时间(不填)
	/>
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		devcode=""				设备代码
		domid=""				域ID
		type=""					告警类型
		level=""				告警等级
		udatetime=""			更新时间
	/>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QueryAlarmPriority( t_uint32 session, t_int32 timeout, t_int32 alarmcategory, char* info, char *outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup DMU_SDK保存策略
* @{
*/

/**
@brief 操作告警或实时数据保存策略
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] info				操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt 
		operate=""				操作类型 0 增加 1 修改 2 删除
	>
		<item 
			domId=""			设备域
			devcode=""			设备代码（为空表示所有设备）
			type=""				告警类型 具体类型 比如 1 （一种告警类型一个item）
			interval=""			间隔时间（间隔内重复告警不处理）
			autodisappear=""	告警自动消失时间（-1表示不自动消失，否则模拟自动消失）
			stop=""				发起告警停止 暂时无用
			enable==""			是否启用
			msgtxt=""			告警描述
		/>
	</opt>
</root>
@endverbatim
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_OptSaveStrategy( t_uint32 session, t_int32 timeout, char* info);

/**
@brief 查询告警或实时数据保存策略
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] info				条件信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<category></category>		组别                          
	<size />					每页大小
	<curpage />					查询第几页
</root>
@endverbatim
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>				总数
	<item domId="" devcode="" type="" interval="" autodisappear="" stop="" enable=="" msgtxt="" />
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return
@remarks
@see DMU_SC_OptSaveStrategy
*/
DLIB_API t_int32 DMU_SC_QuerySaveStrategy( t_uint32 session, t_int32 timeout, char* info, char *outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup DMU_SDK动力环境
* @{
*/

/**
@brief 动环控制
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] domid				域ID
@param [in] scsid				动环ID
@param [in] scsdevid			动环设备ID
@param [in] scslabel			类别 0 资产 1 资源
@param [in] scsopt				操作 如 1 开灯 0 关灯
@param [in] scspram				操作参数，用户自定义

1、对于简单的控制，比如灯的开关，使用字段scsopt就够了，0关，1开
2、对于复杂的控制，比如空调，需要一个额外参数scspram，scspram的格式是 param1|param2
	param1确定是哪一种控制，包括开关控制，模式设置，风速设置，温度设置，scsopt是这种控制的取值，
	比如param1为风速设置，scsopt取值为高速，param1为温度设置，scsopt取值26度
	param2是发码或者学习，开始调试的时候，先要让空调学习一下，以后的控制使用发码。

@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_ScsControl(t_uint32 session, t_int32 timeout, char *domid, char *scsid, char *scsdevid, t_int32 scslabel, t_int32 scsopt, char *scspram);

/**
@brief 查询动环信息
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] domid				域ID
@param [in] scsid				动环ID
@param [in] scsdevid			动环设备ID
@param [in] scslabel			类别 0 资产 1 资源
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<id/>						SCS资产或资源ID
	<res/>0						获取成功 1 获取失败
	<time/>						时间
	<devtype/>					资产资源类型
	<val/>						值
	<desc/>						描述
	<errmsg/>
	<errcode/>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return  错误码查看 IBP_Error.h
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QueryScsInfo(t_uint32 session, t_int32 timeout, char *domid, char *scsid, char *scsdevid, t_int32 scslabel, char *outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup DMU_SDK设备状态
* @{
*/

/**
@brief 查询设备状态
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] inxml				查询的设备
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="CLIENT">
<device domid="2000" devcode="123" status="0"/>
...
</root>
@endverbatim
@param [out] outxml				返回的设备状态
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root version="1.0" unit="CLIENT">
<device domid="2000" devcode="123" status="1"/> 1:在线 2:离线
...
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QueryDevStatus(t_uint32 session, t_int32 timeout,char* inxml, char* outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup DMU_SDK红外热图
* @{
*/

/**
@brief 获取红外设备的能力
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] domid				域ID
@param [in] chnCode				通道ID
@param [in] type				能力标识（哪一种能力）
0: NET_DEV_CAP_SEQPOWER     // 电源时序器能力 
1: NET_ENCODE_CFG_CAPS      // 设备编码配置对应能力 
2: NET_VIDEOIN_FISHEYE_CAPS // 鱼眼能力 
3: NET_THERMO_GRAPHY_CAPS	// 热成像能力 
4: NET_RADIOMETRY_CAPS	    // 热成像测温能力 
@param [out] outxml				返回信息
@verbatim
<?xml version='1.0' encoding='utf-8' ?>
<root>
<size>3435973836</size>
<modes>14</modes>
<colorization>30</colorization>
<roimodes>495</roimodes>
<brightness max="100.000000" min="0.000000" isstep="1" step="1.000000" isdefault="0" default="0.000000" reserved=""/>
<sharpness max="100.000000" min="0.000000" isstep="1" step="5.000000" isdefault="0" default="0.000000" reserved=""/>
<ezoom max="16.000000" min="0.000000" isstep="1" step="1.000000" isdefault="0" default="0.000000" reserved=""/>
<thermographygamma max="8.000000" min="-8.000000" isstep="1" step="1.000000" isdefault="0" default="0.000000" reserved=""/>
<smartoptimizer max="100.000000" min="0.000000" isstep="1" step="5.000000" isdefault="0" default="0.000000" reserved=""/>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return  错误码查看 IBP_Error.h
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_GetThermoDevCaps(t_uint32 session, t_int32 timeout,char* domId,char* chnCode,int type,char* outxml, t_uint32 maxlen);


/**
@brief 获取红外设备的信息
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] domid				域ID
@param [in] chnCode				通道ID
@param [in] type				查询哪一种信息
9: NET_QUERY_DEV_THERMO_GRAPHY_PRESET		// 查询热成像预设信息		
10: NET_QUERY_DEV_THERMO_GRAPHY_OPTREGION	// 查询热成像优化区域信息	
11: NET_QUERY_DEV_THERMO_GRAPHY_EXTSYSINFO	// 查询热成像外部系统信息	
12: NET_QUERY_DEV_RADIOMETRY_POINT_TEMPER	// 查询测温点的参数值		
13:NET_QUERY_DEV_RADIOMETRY_TEMPER 			// 查询测温项温度的参数值
@param [in] inxml				对于测温点和测温区的查询，还需要其他的参数
测温点
<root>
<x>200</x>
<y>120</y>
</root>
测温项
<root>
<presetid>1</presetid>
<ruleid>2</ruleid>
<metertype>3</metertype>
<itemname>4</itemname>
</root>
@param [out] outxml				返回信息
测温返回结果
<?xml version='1.0' encoding='utf-8' ?>
<root>
<size></size>
<radiometryinfo>
<metertype></metertype>
<temperaver></temperaver>
<tempermax></tempermax>
<tempermin></tempermin>
<tempermid></tempermid>
<temperstd></temperstd>
<reserved></reserved>
</radiometryinfo>
</root>
@param [in]  maxlen				信息最大长度
@return  错误码查看 IBP_Error.h
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QueryThermoDevInfo(t_uint32 session, t_int32 timeout,char* domId,char* chnCode,int type,char* inxml,char* outxml, t_uint32 maxlen);


/**
@brief 获取红外设备的信息
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] domid				域ID
@param [in] chnCode				通道ID
@param [in] type				控制类型
0: NET_CTRL_DEV_THERMO_GRAPHY_ENSHUTTER, // 热成像开关
1: NET_CTRL_DEV_RADIOMETRY_SETOSDMARK,	 // 设置测温项的osd为高亮
@param [in] inxml				需要其他的参数
热成像开关
<root>
<enable>1</enable>
</root>
 设置测温项的osd为高亮
<root>
<presetid>1</presetid>
<ruleid>2</ruleid>
<metertype>3</metertype>
<itemname>4</itemname>
</root>
@param [out] outxml				返回信息


@param [in]  maxlen				信息最大长度
@return  错误码查看 IBP_Error.h
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_ControlThermoDevEx(t_uint32 session, t_int32 timeout,char* domId,char* chnCode,int type,char* inxml);


/**
@brief 获取红外设备的配置
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] domid				域ID
@param [in] chnCode				通道ID
@param [in] type				配置标识（哪一种配置）
0: CFG_CMD_THERMO_GRAPHY	// 热成像配置
1: CFG_CMD_THERMOMETRY_RULE	// 热成像规则配置
2: CFG_CMD_TEMP_STATISTICS	// 温度统计配置
3: CFG_CMD_THERMOMETRY		// 热成像测温配置
@param [out] outxml				返回信息

@param [in]  maxlen				信息最大长度
@return  错误码查看 IBP_Error.h
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_GetThermoDevConfig(t_uint32 session, t_int32 timeout,char* domId,char* chnCode,int type,char* outxml, t_uint32 maxlen);

/**
@brief 获取红外设备的配置
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] domid				通道的域
@param [in] chnCode				通道编码
@param [in] type				配置标识（哪一种配置）
0: CFG_CMD_THERMO_GRAPHY	// 热成像配置
1: CFG_CMD_THERMOMETRY_RULE	// 热成像规则配置
2: CFG_CMD_TEMP_STATISTICS	// 温度统计配置
3: CFG_CMD_THERMOMETRY		// 热成像测温配置
@param [in] isSaveDB			是否保存到数据库
@param [in] inxml				返回信息

@return  错误码查看 IBP_Error.h
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_SetThermoDevConfig(t_uint32 session, t_int32 timeout,
	char* domId,char* chnCode,int type,int isSaveDB,char* inxml);


/**
@brief 根据一次设备或者通道的预置位，查询测温对象
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] qryFlg				查询标识
1: 根据eleDom+eleCode,查询
2: 根据chnDom+chnCode,查询
3: 根据eleDom+eleCode+chnDom+chnCode+prepointId,查询
@param [in] eleDom				一次设备的域
@param [in] eleCode				一次设备的编码
@param [in] chnDom				通道的域
@param [in] chnCode				通道的编码
@param [in] prepointId			通道的预置位
@param [out] outxml				返回信息
@param [in]  maxlen				信息最大长度
@return  错误码查看 IBP_Error.h
@remarks 如果eleDom和eleCode为空字符串，按照通道和预置位查询
@see
*/
DLIB_API t_int32 DMU_SC_GetIrArea_ByElecDev_ChnPrepoint(t_uint32 session, t_int32 timeout,int qryFlag,char* eleDom,char* eleCode,
	char* chnDom,char* chnCode,int prepointId,char* outxml, t_uint32 maxlen);


/**
@brief 抓取红外热图
@param [in]  session			连接句柄
@param [in]  timeout			超时时间
@param [in]	 chnDom				通道的域
@param [in]	 chnCode			通道的编码
@param [out] outxml				返回信息
@param [in]  maxlen				信息最大长度
@return  错误码查看 IBP_Error.h
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_FetchThermoGraphy(t_uint32 session, t_int32 timeout,char* chnDom,char* chnCode,char* outxml,t_uint32 maxlen);

/** @} */


/**
* @defgroup DMU_SDK解码器通道信息
* @{
*/

/**
@brief 查询解码器通道信息
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] inxml				查询的解码器
@verbatim
<root>
	<ip>1</ip>
	<port>1</port>
	<username>1</username>
	<password>1</password>
</root>
@endverbatim
@param [out] outxml				返回的解码器通道信息
@verbatim
<root>
	<chn seq=xxx maxsplit=xxx />
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QueryDecorderChnInfo(t_uint32 session, t_int32 timeout,char* inxml, char* outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup DMU_SDK开始局域网设备搜索
* @{
*/

/**
@brief 查询局域网内设备
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] inxml				查询的IP范围(一个网段)
@verbatim
<root>
	<startip>1</startip>
	<endip>1</endip>
	<searchtime>1</searchtime>
</root>
@endverbatim
@param [in] cb					回调函数
@param [in] pUser				用户自定义数据
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_StartSearchLanDev(t_uint32 session, t_int32 timeout,char* inxml);

/** @} */


/**
* @defgroup DMU_SDK停止局域网设备搜索
* @{
*/

/**
@brief 查询局域网内设备
@param [in] session				连接句柄
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_StopSearchLanDev(t_uint32 session);

/** @} */


/**
* @defgroup DMU_SDK查询设备信息
* @{
*/

/**
@brief 查询局域网内设备
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] inxml				查询的解码器
@verbatim
<root>
	<device devtype="" loginname="" loginpwd="" ipaddr="" portdev="" />
</root>
@endverbatim
@param [out] outxml				返回的设备信息
@verbatim
<root>
	<device devcode="id" maxchn="16" manufid="1">
		<channel title="通道1" devtype="22" manufid="1"/>	现有通道信息
		<channel title="通道2" devtype="22" manufid="1"/>	现有通道信息
	</device>
</root>
@endverbatim
@param [in]  maxlen				信息最大长度
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_QueryLanDevInfo(t_uint32 session, t_int32 timeout,char* inxml, char* outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup DMU_SDK设备告警
* @{
*/
/**
@brief 客户端向dmu发送客户端告警
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] inxml				查询的解码器
@verbatim
见DMU_SC_SetDmuMsg中的告警数据通知
@endverbatim
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_SendClientAlarm(t_uint32 session, t_int32 timeout,char* inxml);
/** @} */

/**
* @defgroup DMU_SDK实时数据
* @{
*/
/**
@brief 客户端向dmu发送客户端实时数据
@param [in] session				连接句柄
@param [in] timeout				超时时间
@param [in] inxml				gps信息
@verbatim
见DMU_SC_SetDmuMsg中的实时数据通知
@endverbatim
@return
@remarks
@see
*/
DLIB_API t_int32 DMU_SC_SendClientRealData(t_uint32 session, t_int32 timeout,char* inxml);



/** @} */

#ifdef __cplusplus
}
#endif

#endif


