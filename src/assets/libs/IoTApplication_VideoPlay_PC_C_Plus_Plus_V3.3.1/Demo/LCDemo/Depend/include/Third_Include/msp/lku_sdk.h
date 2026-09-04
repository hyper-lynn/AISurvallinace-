/**
 * Copyright (c) 2014~2015, 浙江大华系统工程有限公司 All rights reserved.
 * \file		lku_sdk.h
 * \brief		lku_sdk
 * \author		24997
 * \date		2014年2月12日
 * \note		LKU SDK 接口
 */
#ifndef IBP_LKU_SDK_H
#define IBP_LKU_SDK_H

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
#ifdef IBPLKUSDK_LIB_EXPORTS
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
* @defgroup LKU_SDK函数
* @{
*/

/**
* @defgroup LKU_SDK系统
* @{
*/

/**
@brief LKU_SDK初始化
@return 
@remarks
@see 
*/
DLIB_API t_int32 LKU_SC_Init();

/**
@brief LKU_SDK反初始化
@return 
@remarks
@see 
*/
DLIB_API t_int32 LKU_SC_Cleanup();

/** @} */

/**
* @defgroup LKU_SDK连接服务
* @{
*/

/**
@brief 连接LKU服务
@param [in]  cmusession		CMU登陆句柄
@param [in]  ipinfo		    LKU服务的ip信息
@param [in]  svrdomid		LKU服务的域id
@param [in]  serverid		LKU服务id
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
DLIB_API t_int32 LKU_AC_Connect(t_uint32 cmusession, char* ipinfo, char* svrdomid, t_int32 serverid, char* outxml, t_uint32 maxlen);

/**
@brief 用户认证连接LKU服务
@param [in]  usersession		用户认证
@param [in]  ipinfo		    LKU服务的ip信息
@param [in]  svrdomid		LKU服务的域id
@param [in]  serverid		LKU服务id
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
DLIB_API t_int32 LKU_AC_ConnectNoCmu(t_uint32 usersession, char* ipinfo, char* svrdomid, t_int32 serverid, char* outxml, t_uint32 maxlen);

/**
@brief 断开LKU服务
@param [in]  session		连接句柄
@return 
@remarks
@see 
*/
DLIB_API t_int32 LKU_SC_Disconn(t_uint32 session);

/** @} */

/**
* @defgroup LKU_SDK回调函数
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
typedef t_int32 (*fIbpLkuMsgCallBack)(t_uint32 session, char *data, t_uint32 bufSize, void* pUser);

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
<root version="1.0" unit="LKU" type="onlineNotify" cmd="onlineNotify" sequence="0" length="0">
	<server 
		servername="" 			服务名称
		session="" 				服务句柄
		status="" 				上下线状态
	/>
</root>
@endverbatim
@verbatim
动作执行结果通知
<?xml version='1.0' encoding='utf-8' ?>
<root version="1.0" unit="LKU" type="Notify" cmd="linkActNotify" sequence="0" length="0">
	<defcode />					流程定义ID
	<instcode />				流程实例ID
	<actcode />					流程节点ID
	<actinstcode />				流程节点实例ID
	<execcode />				流程执行动作ID
	<planid />					联动预案ID

	<srcid />					告警源ID
	<srcdomid />				告警源设备域ID
	<srcdevcode />				告警源设备代码
	<flag />					告警源设备配置标识 0 默认必须配置源设备 1 不需要配置
	<alarmtype />				告警类型
	<alarmsubtype />			告警子类型
	<status />					告警状态 1 产生 2 消失
	
	<dstid />					动作ID
	<typeid />					动作类型ID
	<dstdomid />				动作设备域ID
	<dstdevcode />				动作设备代码
	<params />					动作设备执行参数
	
	<rlstid />					结果数据ID
	<rlstdata />				结果参数数据
	<rettype />					结果返回类型 0 预案开始 1 预案结束 2 动作成功 3 动作失败 4 动作不等待结果 5 动作超时 6 动作结束 7 动作中断，预案结束 8 动作由客户端执行
	<retinfo />					结果展示信息
</root>
@endverbatim
@verbatim
联动预案变更通知
<?xml version='1.0' encoding='utf-8' ?>
<root version="1.0" unit="LKU" type="Notify" cmd="modLinkCfgNotify" sequence="0" length="0">
	<opt/>						变更类型 0 增加 1 修改 2 删除
	<planid/>					联动预案ID
	<planid/>					联动预案ID
</root>
@endverbatim
@see 
*/
DLIB_API t_int32 LKU_SC_SetLkuMsg(t_uint32 session, fIbpLkuMsgCallBack cb, void* pUser);

/** @} */

/**
* @defgroup LKU_SDK联动预案管理
* @{
*/

/**
@brief 操作多联动预案
@param [in]  session			登陆句柄
@param [in]	 timeout			超时时间
@param [in]	 info				操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>				操作类型 0 增加 1 修改 2 删除
	<plan 
		planid=""				预案ID（修改、删除有效）
		planname=""				预案名称
		planfrom=""				预案来源（见预案来源字典表）
		isopen=""				是否启用 0 不启用 1 启用（默认）
		opentime=""				启用时间段（格式：）
		exectype=""				执行类型 0 默认 1 自动执行 2 手动执行
		desc=""					描述
	>
		<alarmsrc				注：特殊情况下可以没有告警源，由其它消息关联planid触发动作
			domid=""			设备域ID
			devcode=""			设备代码
			flag=""				告警源设备配置标识 0 默认必须配置源设备 1 不需要配置
			type=""				告警类型
			subtype=""			告警子类型（没有或者不是子类型产生告警，填0）
			isopen=""			是否启用 0 不启用 1 启用（默认）
			opentime=""			启用时间段（格式：）
			desc=""				描述
		/>
		<alarmsrc domid="" devcode="" flag="" type="" subtype="" isopen="" opentime="" desc="" />
		<dstaction				动作按序号串行执行（升序）
			typeid=""			动作类型ID
			domid=""			动作设备域ID
			devcode=""			动作设备代码
			param=""			动作执行参数XML
			isopen=""			是否启用 0 不启用 1 启用（默认）
			opentime=""			启动时间段（格式：）
			sequence=""			执行动作序号，从0开始(从动作不参与排序，默认为0)
			second=""			等待指定时间后执行该动作（秒）
			type=""				动作返回结果 0 默认无返回结果 1 一个返回结果 2 多个返回结果（等待结束结果后结束）
			exectype=""			执行类型 0 服务执行 1 客户端执行
			canerr=""			动作失败处理 0 默认动作序列继续执行 1 动作序列返回
			acttimeout=""		动作执行超时时间（秒）0 默认超时 >0 等待超时时间 （没有特殊情况填0）
			masterflag=""		主动作标识 0 默认主 1 从
		/>
		<dstaction typeid="" domid="" devcode="" param="" isopen="" opentime="" sequence="" second="" type="" exectype="" canerr="" acttimeout="" masterflag="" />
	</plan>
	<plan planid="" planname="" planfrom="" isopen="" opentime="" exectype="" desc="" >
		<alarmsrc domid="" devcode="" flag="" type="" subtype="" isopen="" opentime="" desc="" />
		<alarmsrc domid="" devcode="" flag="" type="" subtype="" isopen="" opentime="" desc="" />
		<dstaction typeid="" domid="" devcode="" param="" isopen="" opentime="" sequence="" second="" type="" exectype="" canerr="" acttimeout="" masterflag="" />
		<dstaction typeid="" domid="" devcode="" param="" isopen="" opentime="" sequence="" second="" type="" exectype="" canerr="" acttimeout="" masterflag="" />
	</plan>
</root>
@endverbatim
@return 
@remarks
@see LKU_SC_OptPlan
*/
DLIB_API t_int32 LKU_SC_OptLinkPlan(t_uint32 session, t_int32 timeout, char* info);

/**
@brief 操作单预案
@param [in]  session			登陆句柄
@param [in]	 timeout			超时时间
@param [in]	 info				操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>				操作类型 0 增加 1 修改 2 删除
	<plan 
		planid=""				预案ID（修改、删除有效）
		planname=""				预案名称
		planfrom=""				预案来源（见预案来源字典表, 0 保留为所有来源）
		isopen=""				是否启用 0 不启用 1 启用（默认）
		opentime=""				启用时间段（格式：）
		exectype=""				执行类型 0 默认 1 自动执行 2 手动执行
		desc=""					描述
	>
		<alarmsrc				注：特殊情况下可以没有告警源，由其它消息关联planid触发动作
			domid=""			设备域ID
			devcode=""			设备代码
			flag=""				告警源设备配置标识 0 默认必须配置源设备 1 不需要配置
			type=""				告警类型
			subtype=""			告警子类型（没有或者不是子类型产生告警，填0）
			isopen=""			是否启用 0 不启用 1 启用（默认）
			opentime=""			启用时间段（格式：）
			desc=""				描述
		/>
		<alarmsrc domid="" devcode="" flag="" type="" subtype="" isopen="" opentime="" desc="" />
		<dstaction				动作按序号串行执行（升序）
			typeid=""			动作类型ID
			domid=""			动作设备域ID
			devcode=""			动作设备代码
			param=""			动作执行参数XML
			isopen=""			是否启用 0 不启用 1 启用（默认）
			opentime=""			启动时间段（格式：）
			sequence=""			执行动作序号，从0开始(从动作不参与排序，默认为0)
			second=""			等待指定时间后执行该动作（秒）
			type=""				动作返回结果 0 默认无返回结果 1 一个返回结果 2 多个返回结果（等待结束结果后结束）
			exectype=""			执行类型 0 服务执行 1 客户端执行
			canerr=""			动作失败处理 0 默认动作序列继续执行 1 动作序列返回
			acttimeout=""		动作执行超时时间（秒）0 默认超时 >0 等待超时时间 （没有特殊情况填0）
			masterflag=""		主动作标识 0 默认主 1 从（由主动作启动的动作）
		/>
		<dstaction typeid="" domid="" devcode="" param="" isopen="" opentime="" sequence="" second="" type="" exectype="" canerr="" acttimeout="" masterflag="" />
	</plan>
</root>
@endverbatim
@param [out] outxml
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<planid></planid>			预案ID
</root>
@endverbatim
@param [in]	 maxlen				信息最大长度
@return 
@remarks
@see LKU_SC_OptLinkPlan
*/
DLIB_API t_int32 LKU_SC_OptPlan(t_uint32 session, t_int32 timeout, char* info, char* outxml, t_uint32 maxlen);

/**
@brief 按条件查询联动预案信息（可分页）
@param [in]  session		登陆句柄
@param [in]	 timeout		超时时间
@param [in]	 info			条件信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<planfrom />			预案来源(为0 所有来源)
	<srcdomid />			告警源设备域ID（为"" 不判断）
	<srcdevcode />			告警源设备代码（为"" 不判断）
	<alarmtype />			告警类型（为0 不判断）
	<alarmsubtype />		告警子类型（没有或者不是子类型产生告警，填0）
	<dstdomid />			动作设备域ID（为"" 不判断）
	<dstdevcode />			动作设备代码（为"" 不判断）
	<isopen />				预案是否启用（-1 不判断 0 不启用 1 启用）
	<size />				每页大小 
	<curpage />				查询第几页 （从0开始）
</root>
@endverbatim
@param [out] outxml			查询信息(详见LKU_SC_OptLinkPlan注释)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>			总数
	<plan planid="" planname="" planfrom="" isopen="" opentime="" exectype="" desc="" />
	<plan planid="" planname="" planfrom="" isopen="" opentime="" exectype="" desc="" />
</root>
@endverbatim
@param [in]	 maxlen			信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 LKU_SC_QueryLinkPlan(t_uint32 session, t_int32 timeout, char *info, char* outxml, t_uint32 maxlen);

/**
@brief 根据预案ID查询联动预案详细信息
@param [in]  session		登陆句柄
@param [in]	 timeout		超时时间
@param [in]	 planid			方案ID
@param [out] outxml			查询信息(详见LKU_SC_OptLinkPlan注释)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<plan planid="" planname="" planfrom="" isopen="" opentime="" exectype="" desc="" >
		<alarmsrc domid="" devcode="" flag="" type="" subtype="" isopen="" opentime="" desc="" />
		<alarmsrc domid="" devcode="" flag="" type="" subtype="" isopen="" opentime="" desc="" />
		<dstaction typeid="" domid="" devcode="" param="" isopen="" opentime="" sequence="" second="" type="" exectype="" canerr="" acttimeout="" masterflag="" />
		<dstaction typeid="" domid="" devcode="" param="" isopen="" opentime="" sequence="" second="" type="" exectype="" canerr="" acttimeout="" masterflag="" />
	</plan>
</root>
@endverbatim
@param [in]	 maxlen			信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 LKU_SC_QueryLinkPlanDetail(t_uint32 session, t_int32 timeout, t_int32 planid, char* outxml, t_uint32 maxlen);

/**
@brief 按条件查询联动预案详细信息（分页）
@param [in]  session		登陆句柄
@param [in]	 timeout		超时时间
@param [in]	 info			条件信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<planfrom />			预案来源(为0 所有来源)
	<srcdomid />			告警源设备域ID（为"" 不判断）
	<srcdevcode />			告警源设备代码（为"" 不判断）
	<alarmtype />			告警类型（为0 不判断）
	<alarmsubtype />		告警子类型（没有或者不是子类型产生告警，填0）
	<dstdomid />			动作设备域ID（为"" 不判断）
	<dstdevcode />			动作设备代码（为"" 不判断）
	<isopen />				预案是否启用（-1 不判断 0 不启用 1 启用）
	<size />				每页大小 
	<curpage />				查询第几页 （从0开始）
</root>
@endverbatim
@param [out] outxml			查询信息(详见LKU_SC_OptLinkPlan注释)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<total></total>			总数
	<plan planid="" planname="" planfrom="" isopen="" opentime="" exectype="" desc="" >
		<alarmsrc domid="" devcode="" flag="" type="" subtype="" isopen="" opentime="" desc="" />
		<alarmsrc domid="" devcode="" flag="" type="" subtype="" isopen="" opentime="" desc="" />
		<dstaction typeid="" domid="" devcode="" param="" isopen="" opentime="" sequence="" second="" type="" exectype="" canerr="" acttimeout="" masterflag="" />
		<dstaction typeid="" domid="" devcode="" param="" isopen="" opentime="" sequence="" second="" type="" exectype="" canerr="" acttimeout="" masterflag="" />
	</plan>
	<plan planid="" planname="" planfrom="" isopen="" opentime="" exectype="" desc="" >
		<alarmsrc domid="" devcode="" flag="" type="" subtype="" isopen="" opentime="" desc="" />
		<alarmsrc domid="" devcode="" flag="" type="" subtype="" isopen="" opentime="" desc="" />
		<dstaction typeid="" domid="" devcode="" param="" isopen="" opentime="" sequence="" second="" type="" exectype="" canerr="" acttimeout="" masterflag="" />
		<dstaction typeid="" domid="" devcode="" param="" isopen="" opentime="" sequence="" second="" type="" exectype="" canerr="" acttimeout="" masterflag="" />
	</plan>
</root>
@endverbatim
@param [in]	 maxlen			信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 LKU_SC_QueryLinkPlanDetailByInfo(t_uint32 session, t_int32 timeout, char *info, char* outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup LKU_SDK联动字典表
* @{
*/

/**
@brief 查询联动动作类型
@param [in]  session		登陆句柄
@param [in]	 timeout		超时时间
@param [out] outxml			查询信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		typeid=""			动作类型ID
		param=""			参数模板
		index=""			性能指标
		desc=""				描述
		fast=""				是否有效
		updatetime=""		更新时间
	/>
	<item typeid="" param="" index="" desc="" fast="" updatetime="" />
</root>
@endverbatim
@param [in]	 maxlen			信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 LKU_SC_QueryLinkActionType(t_uint32 session, t_int32 timeout, char* outxml, t_uint32 maxlen);

/**
@brief 查询预案来源类型
@param [in]  session		登陆句柄
@param [in]	 timeout		超时时间
@param [out] outxml			查询信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		typeid=""			来源类型ID
		desc=""				描述
		fast=""				是否有效
		updatetime=""		更新时间
	/>
	<item typeid="" desc="" fast="" updatetime="" />
</root>
@endverbatim
@param [in]	 maxlen			信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 LKU_SC_QueryPlanFromType(t_uint32 session, t_int32 timeout, char* outxml, t_uint32 maxlen);

/**
@brief 查询预案日志数据类型
@param [in]  session		登陆句柄
@param [in]	 timeout		超时时间
@param [out] outxml			查询信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item 
		typeid=""			日志数据类型ID
		param=""			参数模板
		desc=""				描述
		fast=""				是否有效
		updatetime=""		更新时间
	/>
	<item typeid="" param="" desc="" fast="" updatetime="" />
</root>
@endverbatim
@param [in]	 maxlen			信息最大长度
@return 
@remarks
@see 
*/
DLIB_API t_int32 LKU_SC_QueryLogDataType(t_uint32 session, t_int32 timeout, char* outxml, t_uint32 maxlen);

/** @} */

/**
* @defgroup LKU_SDK联动应急预案
* @{
*/

/**
@brief 外部触发应急预案
@param [in]  session		登陆句柄
@param [in]	 timeout		超时时间
@param [in]	 planid			预案ID
@return 
@remarks 外部告警引发应急预案
@see LKU_SC_TouchEmergPlan
*/
DLIB_API t_int32 LKU_SC_StartUpEmergPlan(t_uint32 session, t_int32 timeout, t_int32 planid);

/**
@brief 触发应急预案
@param [in]  session		登陆句柄
@param [in]	 timeout		超时时间
@param [in]	 planid			预案ID
@param [in]	 touchtype		触发类型 0 外部触发 1 手动触发 2 节点触发
@param [in]	 info			附加信息（没有为 ""）
@verbatim
外部触发附加信息为""
@endverbatim
@verbatim
手动触发附加信息XML:
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<device domid="" devcode="" devname="" devtype="" manufid="" />
	<device domid="" devcode="" devname="" devtype="" manufid="" />
</root>
@endverbatim
@verbatim
节点触发附加信息XML:
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<defcode />				流程定义ID
	<instcode />			流程实例ID
	<actcode />				流程节点ID
	<actinstcode />			流程节点实例ID
	<execcode />			流程执行ID
	<flag>0</flag>			标识 0 默认通用 1 发短信 2 通过LCU发布任务或消息
	<extradata info="" />	自定义额外数据
</root>
自定义额外数据info值：
0：通用
1：发短信
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<domid />				发送人域ID
	<userid></userid>		发送人用户ID
	<username />			发送人昵称
	<telno />				接受号码表,为""表示使用预设配置发送(示例：189xxxxxxxx;189xxxxxxxx;)
	<smsmsg />				短信息
</root>
2：发布任务或消息
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<info 
		domid=""			对方用户域ID
		userid="0"			对方用户ID
		username=""			对方用户昵称
		usersession="0"		对方sessionid,不知道填0
		tag="0"				消息类型 1 聊天的消息 2 发布的消息 4 发布的任务
		tagname=""			消息类型名称  与tag对应
		msg=""				消息内容
		ctrlinfo=""			附加信息
	/>
</root>
目前将2 发送消息 msg字段内容暂定为XML：（特例处理）
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<root>
	<imgsize>1</imgsize>					图片数量
	<coordinatesize>1</coordinatesize>		地理位置数量
	<videosize>1</videosize>				视频数量
	<message></message>						消息内容
	<todomid />								接收方域ID
	<touserid></touserid>					接受方用户ID
	<towho></towho>							接受方用户名
	<type>1</type>							消息类型
	<fromdomid />							发送方域ID
	<fromuserid></fromuserid>				发送方用户ID
	<who></who>								发送方用户名
	<coordiantes>							地理位置信息
		<coordiante 
			description=""					描述
			latitude=""						纬度
			longitude=""					经度
		/>
	</coordiantes>
	<images>								图片信息
		<image 
			domid=""						域ID
			ext="jpg"						扩展名
			filename="pic.jpg"				文件名称
			guid="GFGDSII6d67g5d8ssdfg"		GUID
		/>
	</images>
	<videos>								视频信息
		<video 
			domid=""						域ID
			ext="dav"						扩展名
			filename="video.dav"			文件名称
			guid="asdfasdffdgGDSD"			GUID
		/>
	</videos>
</root>
对应的附加信息XML定义为：
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<str1>标题</str1>						消息或任务的标题
</root>
@endverbatim
@return 
@remarks 兼容LKU_SC_StartUpEmergPlan接口
@see LKU_SC_StartUpEmergPlan
*/
DLIB_API t_int32 LKU_SC_TouchEmergPlan(t_uint32 session, t_int32 timeout, t_int32 planid, t_int32 touchtype, char *info);

/** @} */

/**
* @defgroup LKU_SDK联动日志
* @{
*/

/**
@brief 操作联动日志
@param [in]  session			登陆句柄
@param [in]	 timeout			超时时间
@param [in]	 info				操作信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<opt>0</opt>				操作类型 0 增加(目前只支持增加)
	<item 
		defcode=""				流程定义ID
		instcode=""				流程实例ID
		actcode=""				流程节点ID
		actinstcode=""			流程节点实例ID
		execcode=""				流程执行动作ID
		planid=""				预案ID
		srcid=""				触发源ID
		actid=""				动作ID
		typeid=""				日志数据ID（用于查找日志描述模板）
		rlstdata=""				日志数据（数据参数值XML）
		rettype=""				操作结果 0 预案开始 1 预案结束 2 动作成功 3 动作失败 4 动作不等待结果返回 5 动作超时 6 动作结束 7 动作中断预案结束 8 客户端执行
		desc=""					不填（用于保存自动生成的日志描述信息）
	/>
</root>
@endverbatim
@return 
@remarks
@see LKU_SC_QueryLinkLog
*/
DLIB_API t_int32 LKU_SC_OptLinkLog(t_uint32 session, t_int32 timeout, char* info);

/**
@brief 查询联动日志
@param [in]  session		登陆句柄
@param [in]	 timeout		超时时间
@param [in]	 info			条件信息(为""查询所有)
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<defcode />				流程定义ID(为""不判断)
	<instcode />			流程实例ID(为""不判断)
	<actcode />				流程节点ID(为""不判断)
	<actinstcode />			流程节点实例ID(为""不判断)
	<execcode />			流程执行ID(为""不判断)
	<planid>-1</planid>		预案ID(为-1不判断)
</root>
@endverbatim
@param [out] outxml			查询信息
@verbatim
<?xml version='1.0' encoding='utf-8' standalone='no' ?>
<root>
	<item id="" defcode="" instcode="" actcode="" actinstcode="" execcode="" planid="" srcid="" actid="" typeid="" rlstdata="" rettype="" desc="" fast="" updatetime="" />
	<item id="" defcode="" instcode=", actcode="" actinstcode="" execcode="" planid="" srcid="" actid="" typeid="" rlstdata="" rettype="" desc="" fast="" updatetime="" />
</root>
@endverbatim
@param [in]	 maxlen			信息最大长度
@return 
@remarks
@see LKU_SC_OptLinkLog
*/
DLIB_API t_int32 LKU_SC_QueryLinkLog(t_uint32 session, t_int32 timeout, char* info, char* outxml, t_uint32 maxlen);

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif


