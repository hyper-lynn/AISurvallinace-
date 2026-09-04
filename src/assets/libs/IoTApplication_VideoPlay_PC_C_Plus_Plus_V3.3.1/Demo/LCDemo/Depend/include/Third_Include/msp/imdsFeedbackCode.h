/**
 * Copyright (C) 2013 ZHEJIANG  DAHUA  SYSTEM ENGINEERING  CO., LTD 
 * \file		imdsFeedbackCode.h
 * \brief		imds服务端反馈码头文件
 * \defgroup 	IMDS错误码
 * \author		qianwei
 * \date		2014-7-28
 * \note		
 */
#ifndef _IMDS_FEEDBACK_CODE_H_
#define _IMDS_FEEDBACK_CODE_H_
#include "ibp_error_enum.h"

/**
* \ingroup IMDS错误码
*/
typedef enum 
{
		VOIP_START = 20200,                         						/**<IMDS错误码开始*/
		VOIP_DB_ERROR,											/**<数据库操作错误*/
		VOIP_DB_CONNECT_FAIL,									/**<数据库连接错误*/
		VOIP_OPERATETYPE_ERR,									/**<操作类型出错*/
		VOIP_VECTOR_EMPTY_ERR,								/**<配置队列为空*/
		VOIP_OVERWEIGHT_MAX_ERR,								/**<超过系统最大数目*/
		VOIP_EXTENSION_UNREGISTER_ERR,						/**<话机未注册或离线*/
		VOIP_EXTENSION_LIMIT_CALL_ERR,						/**<话机禁止呼叫*/
		VOIP_ORIGINAL_ERR,										/**<话机发起呼叫失败*/
		VOIP_EXTENSION_UNHOOK_ERR,							/**<话机未处于摘机呼叫状态*/
		VOIP_MEETING_RESOURCE_ERR,							/**<会议资源不足*/
		VOIP_EXTENSION_BUSY_ERR,								/**<话机忙碌*/
		
		VOIP_EXTENSION_CNT_OVERRIDE_ERR = 20300,				/**<超过系统支持的分机最大数量*/
		VOIP_EXTENSION_NUM_LENGTH_ERR,						/**<超过分机号码长度*/
		VOIP_EXTENSION_DEVICECODE_EXIST_ERR,				/**<该操作对应分机节点号已经存在*/
		VOIP_EXTENSION_EXIST_ERR,								/**<该操作对应分机主号已存在*/
		VOIP_EXTENSION_ALTERNATE_EXIST_ERR,					/**<该操作对应分机备号已经存在*/
		VOIP_EXTENSION_REQUIRE_ERR,							/**<申请分机失败*/
		VOIP_EXTENSION_OPERATE_PART_ERR,					/**<部分分机操作失败*/
		VOIP_EXTENSION_ADD_EMPTY_ERR,						/**<添加分机为空*/
		VOIP_EXTENSION_ADD_ALTERNATE_ERR,					/**<添加分机备号失败*/
		VOIP_EXTENSION_ADD_ERR,								/**<添加分机失败*/
		VOIP_EXTENSION_MODIFY_EMPTY_ERR,					/**<修改分机为空*/
		VOIP_EXTENSION_MODIFY_PHONE_NOFOUND_ERR,			/**<内存中找不到修改的分机号码*/
		VOIP_EXTENSION_MODIFY_DEVICECODE_NOEXIST_ERR,		/**<被修改的节点号对应分机不存在*/
		VOIP_EXTENSION_DELETE_PHONE_MEMORY_ERR,			/**<内存中删除分机失败*/
		VOIP_EXTENSION_QUERY_ORGCODE_EMPTY_ERR,			/**<分机查询组织结构为空*/
		VOIP_EXTENSION_QUERY_PAGE_OVERRIDE_ERR,			/**<分机查询页数过长*/
		VOIP_EXTENSION_QUERY_PAGE_INVALID_ERR,				/**<分机查询页数非法*/
		VOIP_EXTENSION_QUERY_NUMPERPAGE_INVALID_ERR,		/**<分机查询每页分机数非法*/
		VOIP_EXTENSION_QUERY_EMPTY_ERR,						/**<分机查询为空*/
		VOIP_EXTENSION_QUERY_OVERRIDE_ERR,					/**<分机查询分机个数超过总数*/
		VOIP_EXTENSION_MODIFY_INUSE_ERR,					/**<分机正在使用中禁止修改*/
		VOIP_EXTENSION_DELETE_INUSE_ERR,					/**<分机正在使用中禁止删除*/
		VOIP_EXTENSION_TYPE_ERR,								/**<分机类型不正确*/

		VOIP_EXTENSION_GROUP_SEQ_OVERRIDE_ERR=20400,		/**<分机组序号过大*/
		VOIP_EXTENSION_GROUP_SEQ_EXIST_ERR,					/**<该序号分机组已存在*/
		VOIP_EXTENSION_GROUP_ID_OVERRIDE_ERR,				/**<查询分机组ID过大*/	
		VOIP_EXTENSION_GROUP_SEQ_NOEXIST_ERR,				/**<分机组序号不存在	*/
		VOIP_EXTENSION_GROUP_QUERY_NOEXISTINDB_ERR,		/**<查询分机组序号数据库中不存在*/
		VOIP_EXTENSION_GROUP_NUMBER_ERR,					/**<分机组对应的号码错误或不存在*/
		VOIP_EXTENSION_GROUP_NAME_ERR,						/**<分机组对应的名称重复*/
		VOIP_EXTENSION_GROUP_RECORD_ERR,					/**<分机组请求页数出错*/
		VOIP_EXTENSION_GROUP_HOTNUMBER_EXIST_ERR,			/**<分机组快捷呼叫号码重复*/

		VOIP_DISPATCH_SEQ_OVERRIDE_ERR = 20450,				/**<调度台序号过大*/
		VOIP_DISPATCH_CFG_NULL_ERR,							/**<调度台配置参数为空*/
		VOIP_DISPATCH_ADD_ID_EXIST_ERR,						/**<调度台添加ID已存在*/
		VOIP_DISPATCH_MODIFY_ATTENDANT_NOFOUND_ERR,		/**<总机未找到*/
		VOIP_DISPATCH_ID_NOEXIST_ERR,						/**<调度台查询该ID不存在*/
		VOIP_DISPATCH_LEFT_HAND_ERR,							/**<左手柄号码错误或不存在*/
		VOIP_DISPATCH_RIGHT_HAND_ERR,						/**<右手柄号码错误或不存在*/
		VOIP_DISPATCH_ONDUTY_ERR,							/**<调度值班号码错误或不存在*/
		VOIP_DISPATCH_NO_MDF_ERR,							/**<调度在使用中不允许修改*/
		VOIP_DISPATCH_NO_DEL_ERR,							/**<调度在使用中不允许删除*/
		VOIP_DISPATCH_HAND_EQUAL_ERR,						/**<调度左右手柄号码不允许相同*/
		VOIP_DISPATCH_ONDUTY_EQUAL_ERR,						/**<调度左右手柄号码与夜服号码不允许相同*/
		VOIP_DISPATCH_NAME_ERR,								/**<调度的名称重复*/
		VOIP_DISPATCH_DUTY_STATUS_ERR,						/**<调度值班状态错误*/
		
		VOIP_DISPATCH_LOGIN_LOGGED_IN_ERR = 20500,			/**<调度台已登录*/
		VOIP_DISPATCH_LOGIN_LOGGED_IN_SELF_ERR,			/**<调度台已登录自身*/
		VOIP_DISPATCH_LOGIN_SEQ_OVERRIDE_ERR,				/**<调度台登陆调度台序号过大*/
		VOIP_DISPATCH_LOGIN_FAIL_ERR,						/**<调度台登陆失败*/
		VOIP_DISPATCH_STATUS_OFFLINE_ERR,					/**<调度台离线*/

		VOIP_DISPATCH_LOGOUT_ERR,							/**<调度台已登出*/
		VOIP_DISPATCH_LOGOUT_SELF_ERR,						/**<调度台非法登出*/
		VOIP_DISPATCH_LOGOUT_SEQ_OVERRIDE_ERR,				/**<调度台登出调度台序号过大*/
		VOIP_DISPATCH_LOGOUT_FAIL_ERR,						/**<调度台登出失败*/

		VOIP_DISPATCH_STAT_ERR = 20525,						/**<调度台状态获取失败*/
		VOIP_DISPATCH_ID_ERR,									/**<调度台ID不存在*/
		VOIP_DISPATCH_CALLER_NOEXIST_ERR,					/**<调度员号码不存在*/
		VOIP_DISPATCH_CALLER_STAT_FORBIDDEN_ERR,			/**<调度员状态不允许*/
		VOIP_DISPATCH_STYPE_FORBIDDEN_ERR,					/**<调度员会话不允许*/
		VOIP_DISPATCH_ADD_CONFERENCE_ERR,					/**<加入会议失败*/

		VOIP_LABELKEY_GROUP_OVERRIDE_ERR = 20550,			/**<调度台标签号组号不存在*/
		VOIP_LABELKEY_PAGE_INVALID_ERR,						/**<调度台页码数非法*/
		VOIP_LABELKEY_GROUPID_OVERRIDE_ERR,					/**<调度台标签对应话机组不存在*/
		VOIP_LABELKEY_PERPAGE_OVERRIDE_ERR,					/**<调度台每页分机数不存在*/
		VOIP_LABELKEY_ID_ERR,									/**<调度台标签不存在*/

		VOIP_KEYRIGHT_OCCUPIED_ERR,							/**<调度键权未占用*/
		VOIP_KEYRIGHT_OVERRIDE_ERR,							/**<键权键值非法*/
		VOIP_KEYRIGHT_CALL_ERR,								/**<呼叫键权失败*/
		VOIP_KEYRIGHT_UNHOOK_ERR,							/**<调度员未摘机*/

		VOIP_FUNCKEY_KEYTYPE_ERR = 20600,						/**<功能键键类型错误*/
		VOIP_FUNCKEY_KEYSEQ_ERR,								/**<按键不存在*/
		VOIP_FUNCKEY_CONF_MEMBER_MUTE_ERR,					/**<功能键禁言失败*/
		VOIP_FUNCKEY_MEETING_PRESS_ERR,						/**<会议状态按此键无效*/
		VOIP_FUNCKEY_GROUP_PRESS_ERR,						/**<组呼状态按此键无效*/
		VOIP_FUNCKEY_ALL_PRESS_ERR,							/**<集呼状态按此键无效*/
		VOIP_FUNCKEY_GENERAL_ERR,							/**<按保持键执行失败*/
		VOIP_FUNCKEY_TURN_PRESS_ERR,							/**<按转接键执行失败*/
		VOIP_FUNCKEY_RECORD_PRESS_ERR,						/**<按录音键执行失败*/
		VOIP_FUNCKEY_IGNORE_ERR,								/**<按键无效*/
		VOIP_FUNCKEY_SESSION_TYPE_ERR,						/**<会话类型不支持此按键*/

		VOIP_HOTKEY_KEYTYPE_ERR = 20650,						/**<快捷键键类型错误*/
		VOIP_HOTKEY_KEYSEQ_OVERRIDE_ERR,					/**<快捷键键序不存在*/
		VOIP_HOTKEY_GROUP_EMPTY_ERR,						/**<当前话机组为空*/

		VOIP_NUMBER_CONVERT_OPERATE_TYPE_ERR = 20700,		/**<号码变换操作类型不存在*/
		VOIP_NUMBER_CONVERT_DATA_INVALID_ERR,				/**<号码变换数据不合法*/
		VOIP_NUMBER_CONVERT_QUERY_ID_OVERRIDE_ERR,		/**<号码变换查询ID过大*/
		VOIP_NUMBER_CONVERT_DELETE_ID_OVERRIDE_ERR,		/**<号码变换删除ID过大*/
		VOIP_NUMBER_CONVERT_MODIFY_ID_OVERRIDE_ERR,		/**<号码变换修改ID过大*/

		VOIP_CONFERENCE_SET_REFRESH_ERR=20750,				/**<会议号码刷新内存错误*/
		VOIP_CONFERENCE_SET_INVALID_DATA_ERR,				/**<会议数据不合法*/
		VOIP_CONFERENCE_SET_NUMBER_EXIST_ERR,				/**<会议号码与用户号码重复*/
		
		VOIP_ATTENDANT_OPERATE_TYPE_ERR = 20800,				/**<总机设置类型不存在*/
		VOIP_ATTENDANT_CNT_OVERRIDE_ERR,					/**<总机过多，超过100个*/
		VOIP_ATTENDANT_QUERY_ORGCODE_EMPTY_ERR,			/**<总机查询组织结构为空*/
		VOIP_ATTENDANT_QUERY_EMPTY_ERR,						/**<总机查询为空*/
		VOIP_ATTENDANT_QUERY_ID_OVERRIDE_ERR,				/**<总机查询ID过大*/
		VOIP_ATTENDANT_ADD_ERR,								/**<添加总机失败*/
		VOIP_ATTENDANT_DELETE_ERR,							/**<删除总机失败*/
		VOIP_ATTENDANT_DELETE_ID_OVERRIDE_ERR,				/**<总机删除ID过大*/
		VOIP_ATTENDANT_MODIFY_PHONE_NOFOUND_ERR,			/**<内存中找不到修改的总机号码*/
		VOIP_ATTENDANT_MODIFY_ID_OVERRIDE_ERR,				/**<总机修改ID过大*/
		VOIP_ATTENDANT_EXIST_ERR,							/**<该操作对应总机号已存在*/
		VOIP_ATTENDANT_EXIST_INEXTENSION_ERR,				/**<该操作对应总机号在分机中已存在*/
		VOIP_ATTENDANT_ADD_EMPTY_ERR,						/**<添加总机为空*/

		VOIP_FXSO_TYPE_ERR = 20850,								/**<FXSO查询FXS/FSO类型出错*/
		VOIP_FXSO_NUMBER_EXIST_ERR,							/**<FXSO同一网关下该号码已经存在*/
		VOIP_FXSO_SID_NOTEXIST_ERR,							/**<FXSO同一网关下修改删除时该SID不存在*/
		VOIP_FXSO_GATEWAY_ID_ERR,							/**<FXSO参数查询时网关ID出错*/
		VOIP_FXSO_QUERY_EMPTY_ERR,							/**<FXSO参数查询时查询记录为空*/
		VOIP_FXSO_OPERATE_TYPE_ERR,							/**<FXSO参数设置类型不存在*/
		VOIP_FXSO_CNT_OVERRIDE_ERR,							/**<FXSO参数过多，超过100个*/
		VOIP_FXSO_ADD_ERR,									/**<添加FXSO参数失败*/
		VOIP_FXSO_DELETE_ERR,									/**<删除FXSO参数失败*/
		VOIP_FXSO_DELETE_ID_OVERRIDE_ERR,					/**<FXSO参数删除ID过大*/
		VOIP_FXSO_MODIFY_ID_OVERRIDE_ERR,					/**<FXSO参数修改ID过大*/
		VOIP_FXSO_NUMBER_ERR,								/**<FXS/FXO号码出错*/
		VOIP_FXSO_SAME_NUMBER_ERR,							/**<FXS/FXO号码重复*/
		
		VOIP_GW_ID_ERR = 20900,									/**<网关ID不存在*/
		VOIP_GW_ID_OVERWEIGHT_ERR, 							/**<网关ID超出最大值*/
		VOIP_GW_ID_REQUIRE_ERR,								/**<网关ID申请失败*/
		VOIP_GW_IDENTITY_ERR,									/**<网关标识出错*/
		VOIP_GW_NUM_ERR,										/**<网关号码重复出错*/
		VOIP_GW_INUSED_ERR,									/**<网关使用中禁止修改或删除*/
		VOIP_GW_SAME_IP_ERR,									/**<网关IP重复*/

		VOIP_TRUNK_CFG_NULL_ERR = 20950,						/**<中继配置指针为空*/
		VOIP_TRUNK_ID_OVERRIDE_ERR,							/**<中继ID过大*/
		VOIP_TRUNK_CONFIG_IDENTIFY_ERR,						/**<中继配置标识号错误*/
		VOIP_TRUNK_CONFIG_REFRESH_ERR,						/**<中继配置内存更新失败*/
		VOIP_TRUNK_TID_REQUIRE_FAIL,							/**<中继ID申请失败*/
		VOIP_TRUNK_CONFIG_IDENTIFY_EXIST_ERR,				/**<中继标识号重复*/
	       VOIP_TRUNK_TID_NOEXIST_ERR,							/**<中继tId不存在*/
		VOIP_CIDID_IDENTIFYTYPE_ERR,							/**<CID/DID所属类型(0 中继，1网关)错误*/
		VOIP_CIDID_CFG_NULL_ERR,								/**<CID/DID配置指针指针为空*/
		VOIP_CIDID_CDID_REQUIRE_FAIL,							/**<申请cdid失败*/
		VOIP_CIDID_CONFIG_REFRESH_ERR,						/**<CID/DID配置内存更新失败*/
		VOIP_CIDID_IDENTIFYID_NOEXIST_ERR,					/**<CID/DID识别号不存在*/
		VOIP_CIDID_CDID_OVERRIDE_ERR,						/**<CID/DID的索引ID过大*/
		VOIP_CIDID_IDENTIFYID_OVERRIDE_ERR,					/**<CID/DID识别号过大*/
		VOIP_CIDID_CDID_NOEXIST_ERR,							/**<CID/DID的索引ID不存在*/
              VOIP_TRUNK_GW_QUERY_ERR,								/**<中继/网关组查询均失败*/
              VOIP_TRUNK_SAME_IP_ERR,								/**<中继中存在相同的IP*/
              VOIP_EXTERNAL_GROUP_NAME_ERR,						/**<中继组名称重复*/
              VOIP_EXTERNAL_GROUP_SEQ_OVERRIDE_ERR,				/**<中继组ID过大*/	
              VOIP_EXTERNAL_GROUP_SEQ_EXIST_ERR,					/**<中继组序号已经存在*/
              VOIP_EXTERNAL_GROUP_SEQ_NOEXIST_ERR,				/**<中继组序号不存在*/
              VOIP_EXTERNAL_GROUP_RECORD_ERR,						/**<中继组请求页数出错*/

		VOIP_RT_ID_ERR = 21000,									/**<路由策略ID不存在*/
		VOIP_RT_NAME_ERR,										/**<路由策略名称出错*/
		VOIP_RT_ID_OVERWEIGHT_ERR, 							/**<路由策略ID超出最大值*/
		VOIP_RT_ID_REQUIRE_ERR,								/**<路由策略ID申请失败*/
		VOIP_RT_CONTEXT_ERR, 									/**<路由策略内容(中继/网关组)出错*/
		VOIP_RT_INUSED_ERR,									/**<路由策略使用中禁止修改或删除*/
		VOIP_RT_SAME_TG_ERR,									/**<路由策略存在相同的网关或中继*/
		VOIP_RT_SAME_PRORITY_ERR,							/**<路由策略存在相同的优先级*/
		
		VOIP_DP_ID_ERR = 21050,									/**<拨号方案ID不存在*/
		VOIP_DP_NAME_ERR,										/**<拨号方案名称出错*/
		VOIP_DP_ID_OVERWEIGHT_ERR, 							/**<拨号方案ID超出最大值*/
		VOIP_DP_ID_REQUIRE_ERR,								/**<拨号方案ID申请失败*/
		VOIP_DP_CONTEXT_ERR, 									/**<拨号方案内容(匹配信息为空)出错*/
		VOIP_DP_INUSED_ERR,									/**<拨号方案使用中禁止修改或删除*/
		VOIP_DP_SAME_RT_ERR,									/**<拨号方案使用中存在相同的路由策略*/

		VOIP_VC_NAME_ERR = 21100,								/**<视频会议预案名称出错*/
		VOIP_VC_ID_OVERWEIGHT_ERR,							/**<视频会议预案ID超出最大值*/
		VOIP_VC_ID_ERR,										/**<视频会议预案ID不存在*/
		VOIP_VC_ID_REQUIRE_ERR,								/**<视频会议预案ID申请失败*/
		VOIP_VC_AMOUNT_ERR,									/**<视频会议预案容纳人数过大*/
		VOIP_VC_INUSED_ERR,									/**<视频会议预案使用中禁止修改或删除*/
		VOIP_VC_DEVICECODE_ERR,								/**<视频会议预案主叫设备号不存在*/
		VOIP_VC_AMOUNT_CNT_ERR,								/**<视频会议预案容纳人数不能小于现有的成员数*/

		VOIP_VM_ID_ERR = 21120,									/**<视频会议成员ID不存在*/
		VOIP_VM_ID_REQUIRE_ERR,								/**<视频会议成员ID申请失败*/
		VOIP_VM_NUMBER_ERR,									/**<视频会议成员重复*/
		VOIP_VM_INUSED_ERR,									/**<视频会议成员用中禁止修改或删除*/
		VOIP_VM_DEVICECODE_ERR,								/**<视频会议成员设备号不存在*/

		VOIP_VCOPT_SEIZE_ERR = 21150,							/**<视频会议已开始*/ 
		VOIP_VCOPT_FREE_ERR,									/**<视频会议未开始*/
		VOIP_VCOPT_CALLER_ERR,								/**<视频会议发起者不存在*/
		VOIP_VCOPT_CALLER_ITSELF_ERR,						/**<视频会议发起者不是自身*/
		VOIP_VCOPT_UNKNOWN_ERR,								/**<视频会议未知错误*/
		VOIP_VCOPT_INVITEE_ERR,								/**<视频会议受邀方不存在*/
		VOIP_VCOPT_INVITED_ERR,								/**<视频会议成员已邀请*/
		VOIP_VCOPT_KICKED_ERR,								/**<视频会议成员已踢出*/
		VOIP_VCOPT_UNMUTED_ERR,								/**<视频会议成员已发言*/
		VOIP_VCOPT_MUTED_ERR,								/**<视频会议成员已禁言*/
		VOIP_VCOPT_ORG_ERR,									/**<视频会议室组织节点为空*/
		VOIP_VCOPT_MEMBER_FULL_ERR,							/**<视频会议室人数已满*/
		VOIP_VCOPT_DIFFERENCE_ERR,							/**<视频会议发言用户不在会议中*/
		VOIP_VCOPT_SESSION_ERR,								/**<视频会议会话类型不允许*/
		VOIP_VCOPT_SPEAKER_STAT_ERR,						/**<视频会议发起者状态不允许*/
		VOIP_VCOPT_SPEAKEE_STAT_ERR,						/**<视频会议发言者状态不允许*/
		VOIP_VCOPT_NOT_IN_ERR,								/**<视频会议受邀方不在会议中*/

		VOIP_TALK_ERR = 21200, 									/**<对讲错误*/
		VOIP_TALK_CALLER_ERR,									/**<对讲发起者为空*/
		VOIP_TALK_CALLEE_ERR,									/**<对讲接收者为空*/
		VOIP_TALK_UNKNOWN_ERR,								/**<对讲未知错误*/
		VOIP_TALK_CALLER_SESSION_ERR,						/**<对讲主叫所处会话错误*/
		VOIP_TALK_FREE_ERR,									/**<对讲释放错误*/
		VOIP_EXTENSIONONOFF_CFG_NULL_ERR = 21250,			/**<话单模块分机禁用启用设置参数为空*/
		VOIP_EXTENSIONONOFF_NUMBER_ERR,						/**<话单模块分机禁用启用设置分机号码错误*/
		VOIP_EXTENSIONONOFF_CONFIG_REFRESH_ERR,			/**<话单模块分机禁用启用设置内存更新错误*/
		VOIP_PHONEBILL_TIME_ERR,								/**<话单模块话单时间不能为空*/
		VOIP_PHONEBILL_QUERY_PAGE_INVALID_ERR,				/**<话单模块话单页码不能为0*/
		VOIP_PHONEBILL_QUERY_NUMPERPAGE_INVALID_ERR,		/**<话单模块话单查询条数不能为0*/
		VOIP_PHONEBILL_CFG_CLEAR_ERR,						/**<话单模块话单删除错误*/
		VOIP_PHONEBILL_SUBSCRIBE_USERID_ERR,				/**<话单订阅用户ID错误*/
		
		VOIP_ALARM_VOICE_UNKNOWN_ERROR = 21300,			/**<报警语音错误*/
		VOIP_ALARM_VOICE_FLAG_ERROR,						/**<报警语音标记错误*/
		VOIP_ALARM_VOICE_USR_ERROR,						/**<报警语音用户号码错误*/
		VOIP_ALARM_VOICE_TYPE_ERROR,						/**<报警类型错误*/

		VOIP_SDK_CALL_UNKNOWN_ERROR = 21350,			/**<呼叫接口错误*/
		VOIP_SDK_CALL_FLAG_ERROR,						/**<呼叫接口flag错误*/
		VOIP_SDK_CALL_TYPE_ERROR,						/**<呼叫接口类型不允许或未实现*/
		VOIP_SDK_CALL_ORG_ERROR,							/**<呼叫接口发起方空*/
		VOIP_SDK_CALL_DEST_ERROR,						/**<呼叫接口目标方为空*/
		VOIP_SDK_CALL_STATUS_ERROR,						/**<呼叫接口发起方状态允许*/
              VOIP_RECORD_OPERATE_ERROR = 21400,				/**<录音操作失败*/

		VOIP_FAX_SEND_ALL_FAIL = 21450,					/**<传真发送失败*/
		VOIP_FAX_SEND_PART_FAIL,							/**<传真发送部分失败*/
		VOIP_FAX_SEND_DOWNLOAD_FAIL,					/**<传真发送文件下载失败*/
		VOIP_FAX_SEND_ADD_INFO_FAIL,						/**<传真发送文件加入发送队列失败*/
		VOIP_FAX_QUERY_PAGE_INVALID_ERR,				/*传真查询页码错误*/
		VOIP_FAX_QUERY_NUMPERPAGE_INVALID_ERR,			/*传真查询每页条数错误*/
		VOIP_FAX_DELETE_TIFID_INVALID_ERR,				/*传真删除传真文件ID错误*/
		
}IMDS_FeedbackCode;

#endif

