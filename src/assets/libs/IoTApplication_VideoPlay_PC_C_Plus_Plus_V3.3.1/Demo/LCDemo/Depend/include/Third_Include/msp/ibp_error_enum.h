/**
 * Copyright (c) 2014~2015, 浙江大华系统工程有限公司 All rights reserved.
 * \file		ibp_error_enum.h
 * \brief		ibp_error_enum
 * \author		24997
 * \date		2016年6月28日
 * \note		eIBP_Err错误码信息
 */
#ifndef _IBP_ERROR_ENUM_H_
#define _IBP_ERROR_ENUM_H_

/**
* @defgroup 错误码
* @{
*/

/**
@brief 错误码信息
@remarks
@see
*/
typedef enum {
	IBP_Err_OK = 200,										///<正确错误码
	
	IBP_Err_Common_Begin = 300,								///<通用错误码开始
	IBP_Err_Common_XML_NULL,								///<xml为空
	IBP_Err_Common_XML_ERR,									///<xml异常
	IBP_Err_Common_No_Buffers,								///<缓存不够
	IBP_Err_Common_SendMsg_Failed,							///<消息发送失败
	IBP_Err_Common_PARAM_ERR,								///<参数错误
	IBP_Err_Common_Device_Offline,							///<设备掉线
	IBP_Err_Common_IpPort_Dup,								///<dvr设备的IP,port重复
	IBP_Err_Common_NETSDK,									///<netsdk错误
	IBP_Err_NO_RIGHTS,										///<没有操作权限
	IBP_Err_CANNOT_FIND_DEVICE,								///<没有找到请求的设备
	IBP_Err_CANNOT_FIND_USER,								///<由SessionId没有找到UserId
	IBP_Err_Common_IbpProtocol_NULL,						///<协议为空
	IBP_Err_Common_Socket_Err,								///<socket建立异常
	IBP_Err_SerialPort_InUse,								///<串行口正在被使用
	IBP_Err_SerialPort_OpenFailed,							///<串口打开失败
	
	IBP_Err_DB_Begin = 400,									///<数据库错误码开始
	IBP_Err_DBConnect_Fail = 400,							///<数据库的错误码放在一起，连接错误
	IBP_Err_DBOperate_Fail,									///<数据库增删改错误
	IBP_Err_DBQuery_Fail,									///<数据库查询错误
	IBP_Err_DBOperate_Fail_RecordNotExists,					///<数据库操作的记录不存在
	IBP_Err_DB_End = 499,									///<数据库错误码结束
	
	IBP_ERR_COMMON_OUTPROCESS_Begin = 900,					///<关键错误码分开处理开始
	IBP_ERR_COMMON_OUTPROCESS_NO_SESSION = 900,				///<outprocess找不到句柄
	IBP_ERR_COMMON_OUTPROCESS_SERVICE_UNAVAILABLE,			///<outprocess服务不可用
	IBP_ERR_COMMON_OUTPROCESS_NOT_FOUND_BYSEQ,				///<没有找到peer
	IBP_ERR_COMMON_OUTPROCESS_PROTOCOL_NULL,				///<协议为空
	IBP_ERR_COMMON_OUTPROCESS_End = 909,					///<关键错误码分开处理结束
	
	IBP_ERR_COMMON_LOADBALANCE_CMU_ALEADY_LOGIN = 910,		///<负载均衡CMU已经登录
	IBP_ERR_COMMON_LOADBALANCE_NOT_MASTER,					///<负载均衡无master
	IBP_Err_Common_End = 999,								///<通用错误结束
	
	IBP_Err_CMU_Begin = 1000,								///<CMU开始
	IBP_Err_Nothing_Found,									///<未找到
	IBP_Err_KEY_CONFLICT,									///<关键字冲突
	IBP_Err_USERNAME_CONFLICT,								///<用户名冲突
	IBP_Err_USER_NOT_LOGON,									///<用户未登录
	IBP_Err_USERNAME_NONEXISTENT,							///<用户名不存在
	IBP_Err_ERROR_PASSWORD,									///<密码错误
	IBP_Err_USER_LOCKED,									///<用户锁定
	IBP_Err_USER_OUT_OF_DATE,								///<用户过期
	IBP_Err_USER_NOT_IN_DATE,								///<用户不在使用期内
	IBP_Err_USER_MULT_LOGIN,								///<用户重复登录
	IBP_Err_USER_ADMIN_ONLINE_OVER,							///<admin在线超过限制
	IBP_Err_USER_USER_ONLINE_OVER,							///<用户在线超过限制
	IBP_Err_USER_MAX,										///<用户达到最大值	
	IBP_Err_EXT_PASSWORD_ERR,								///<话机密码不能为空
	IBP_Err_EXT_NUMBER_DUPLICATE,							///<话机号码与已有号码或备号重复
	IBP_Err_EXT_ATTENDANT_DUPLICATE,						///<话机号码与总机号码重复
	IBP_Err_EXT_EMPTY_ERR,									///<分机号码为空
	IBP_Err_ORG_DEL_HAVSUBORG,								///<挂有组织，不能删除该组织
	IBP_Err_ORG_DEL_HAVSUBDEV,								///<挂有设备，不能删除该组织
	IBP_Err_ORG_DEL_HAVUSER,								///<挂有用户，不能删除该组织
	IBP_Err_ORG_DEL_HAVDOMAIN,								///<挂有域，不能删除该组织
	IBP_Err_DOMAIN_ID_ERR,									///<DomainId 错误
	IBP_Err_CMU_ORG_NOT_EXIST,								///<组织不存在
	IBP_Err_CMU_SAME_CODE_DEV_NOT_EXIST,					///<不存在该编码设备
	IBP_Err_CMU_SAME_CODE_DEV_EXIST,						///<已存在该编码设备
	IBP_Err_CMU_OLD_DEV_NOT_EXIST,							///<原设备不存在
	IBP_Err_CMU_PARENT_DEV_NOT_EXIST,						///<父设备不存在
	IBP_Err_CMU_Not_Match_Database,						///<Cmu和数据库版本不匹配
	IBP_Err_ORG_DEL_HAVROLE,								///<挂有角色，不能删除该组织
	IBP_Err_USER_BIND_OTHER_DEVICE,								///<用户绑定了其他设备
	IBP_Err_CMU_End = 1099,									///<CMU结束
	
	IBP_Err_VTDU_Begin = 1100,								///<VTDU结束
	IBP_Err_Start_Unfinished,								///<VTDU启动未完成
	IBP_Err_Not_Find_VRU,									///<未发现vru
	IBP_Err_No_Enough_Capability,							///<没有足够的能力
	IBP_Err_Device_Not_Support,								///<设备不支持
	IBP_Err_Cannot_Find_Device,								///<查找不到设备
	IBP_Err_Not_Find_Slave,									///<找不到slave
	IBP_Err_SendMsg_MasterToSlave,							///<master向slave发送消息失败
	IBP_Err_SendMsg_MasterToDomain,							///<master向其他域发送消息失败
	IBP_Err_Device_Offline,									///<设备掉线
	IBP_Err_DllName_Empty,									///<dll名为空
	IBP_Err_Record_Seek_Format,								///<录像拖动格式错误
	IBP_Err_Cascade_Server_Offline,							///<级联服务rtsp链接掉线
	IBP_Err_Channel_Used_In_Talking,						///<语音对讲-通道处于使用状态，用于语音限制
	IBP_Err_Channel_Used_In_Playing,						///<录像回放-通道处于使用状态，用于录像回放限制
	IBP_Err_RtspToken_Invalid,								///<rtsp token无效
	IBP_Err_Channel_In_Closing,								///<通道处于正在关闭状态
	IBP_Err_Not_Find_Channel,								///<未找到通道
	IBP_Err_Rtsp_Disconnect,								///<rtsp连接断开
	IBP_Err_Cascade_Connect,								///<连接级联服务失败
	IBP_Err_No_Port_For_Use,								///<没有端口可使用
	IBP_Err_Play_No_Setup,									///<发送rtsp play前未发送setup消息
	IBP_Err_RTP_Build,										///<码流传输网络建立失败
	IBP_Err_Add_Node_Into_SendList,							///<加入发送列表失败
	IBP_Err_Delete_Node_Failed,								///<删除node失败
	IBP_Err_Record_Download_Finished,						///<录像下载完成
	IBP_Err_No_Record_Files,								///<没有录像文件
	IBP_Err_Receiver_Net_Build,								///<码流接收器网络建立失败
	IBP_Err_SS_Open_File_Failed,							///<ss打开文件失败
	IBP_Err_Msg_Save_Timeout,								///<消息保存超时
	IBP_Err_Not_Find_PlayInfo,								///<找不到播放信息
	IBP_Err_Red5_Connect,									///<连接red5失败
	IBP_Err_Query_UserId_Failed,							///<查询用户ID失败
	IBP_Err_Get_ChannelIndex_Failed,						///<获取通道索引失败
	IBP_Err_Not_Find_USB_Proxy,								///<获取usb代理服务失败
	IBP_Err_Red5_Connech_Already,							///<和red5的连接已经存在
	IBP_Err_Notfound_Startvideo_Request,					///<没有找到请求消息
	IBP_Err_Notfound_Active_Url,							///<没有找到有效的URL
	IBP_Err_VTDU_End = 1199,								///<VTDU结束
	
	IBP_Err_DMU_Begin = 1200,								///<DMU结束
	IBP_Err_DEVICE_OFFLINE,									///<操作的设备离线
	IBP_Err_PTZCONTROL_BYSENIOR,							///<高级用户正在云台控制
	IBP_Err_PTZCONTROL_ASSENIOR,							///<抢占低级用户的云台控制权
	IBP_Err_PTZCONTROL_LOCKBYOTHER,							///<云台被其他用户锁定
	IBP_Err_PTZCONTROL_NOTLOCK,								///<云台没有锁定
	IBP_Err_SERVICE_UNAVAILABLE,							///<当前DMU服务不可用
	IBP_Err_MASTER_SENDTO_SLAVE,							///<Master向Slave发送失败
	IBP_Err_UPMASTER_SENDTO_UPMASTER,						///<UpMaster向LowMaster发送失败
	IBP_Err_UNKNOWMODLE,									///<DMU变成Unknown
	IBP_Err_LOGIN_SAMEIPPORT,								///<重复登录设备
	IBP_Err_LOGIN_DEVICE_FAIL,								///<登录设备失败
	IBP_Err_SCS_OPT_FAILURE,								///<动环操作失败
	IBP_Err_NOT_FIND_DEVID_BY_DOMCODE,						///<根据DomCode，没有找到DevId
	IBP_Err_CANNOT_MODIFY_PREPOINT,							///<不能修改预置位，因为关联一次设备
	IBP_Err_FETCH_GRAPHY_BUSY,								///<正在抓图，请稍后再试
	IBP_Err_FETCH_GRAPHY_UNKNOWN_ERROR,						///<抓图未知错误
	IBP_Err_FETCH_GRAPHY_DEVICE_OFF,						///<抓图过程设备断线
	IBP_Err_PTZCONTROL_LOCKBYSELF,							///<云台已经被自己锁定
	IBP_Err_DMU_OTHERQUERYING,								///<其他用户正查询
	IBP_Err_CANNOT_SUPPORT_DECORDER_TYPE,					///<不支持的解码器类型
	IBP_Err_DMU_End = 1299,									///<DMU结束
	
	IBP_Err_VRU_Begin = 1300,								///<VRU结束
	IBP_Err_NOSLAVE_AVALIABLE,								///<没有Slave可用
	IBP_Err_NOTSUPPORTED,									///<功能不支持
	IBP_Err_DATABASE_FAILED,								///<数据库操作失败
	IBP_Err_PlanData_Empty,									///<计划配置为空
	IBP_Err_VRU_Start_Unfinished,							///<vru启动未完成
	IBP_Err_Not_Find_VTDU,									///<未找到vtdu
	IBP_Err_RtspConnect_Failed,								///<
	IBP_Err_CreateChannel_Failed,							///<
	IBP_Err_RTP_Build_Failed,								///<
	IBP_Err_No_RtpPort_For_Use,								///<
	IBP_Err_Channel_Used_In_Storing,						///<通道处于使用状态，用于存储
	IBP_Err_AddStreamId_Failed,								///<存储时添加流id失败
	IBP_Err_Receive_Data_Timeout,							///<接受码流超时
	IBP_Err_Server_Disconnect,								///<和服务的连接断开
	IBP_Err_Device_Disconnect,								///<设备连接断开
	IBP_Err_Add_CqfsSession_Failed,							///<添加cqfssession失败
	IBP_Err_ReceiveStream_Timeout,							///<接受流超时
	IBP_Err_Right_Alter,									///<权限改变
	IBP_Err_Device_Alter,									///<设备信息改变
	IBP_Err_Over_RecordNum,									///<超过最大录音个数
	IBP_Err_VRU_End = 1399,									///<VRU结束
	
	IBP_Err_LKU_Begin = 1400,								///<LKU结束
	IBP_Err_LKU_End = 1499,									///<LKU结束
	
	IBP_Err_LMU_Begin = 1500,								///<LMU结束
	IBP_Err_LMU_End = 1599,									///<LMU结束
	
	IBP_Err_UAS_Begin = 1600,								///<UAS错误码开始
	IBP_Err_UAS_Cmu,										///<UAS中CMU模块错误
	IBP_Err_UAS_Dmu_Master,									///<UAS中Dmu Master模块错误
	IBP_Err_UAS_Dmu_Slave,									///<UAS中Dmu Slave模块错误
	IBP_Err_UAS_Vtdu,										///<UAS中Vtdu模块错误
	IBP_Err_UAS_Logic,										///<UAS中逻辑模块错误
	IBP_Err_UAS_Sip,										///<UAS中Sip错误
	IBP_Err_UAS_Rtsp,										///<UAS中Rtsp错误
	IBP_Err_UAS_Pg,											///<UAS中Pg错误
	IBP_Err_UAS_Res,										///<UAS中应答协议错误
	IBP_Err_UAS_End = 1699,									///<UAS错误码结束
	
	IBP_Err_UAC_Begin = 1700,								///<UAC错误码开始
	IBP_Err_UAC_End = 1799,									///<UAC错误码结束
	
	IBP_ERR_ADAPTER_BEGIN = 1800,							///<设备适配器开始
	IBP_ERR_ADAPTER_CANNOT_FIND_DEV,						///<没有找到设备对象
	IBP_ERR_ADAPTER_DYNAMICCAST_FAILD,						///<转化错误
	IBP_ERR_ADAPTER_DVR_IPPORT_DUP,							///<DVR IP Port
	IBP_ERR_ADAPTER_DLL_LOAD_FAIL,							///<DLL加载错误
	IBP_ERR_ADAPTER_PARAMTER_ERROR,							///<参数错误
	IBP_ERR_ADAPTER_DEVICE_OFFLINE,							///<设备下线
	
	IBP_ERR_ADAPTER_SDK_BEGIN = 1850,						///<适配器SDK开始
	IBP_ERR_ADAPTER_SDK_USER_PASSWORD_ERROR,				///<用户密码错误
	IBP_ERR_ADAPTER_SDK_LOG_TIMEOUT,						///<登陆超时
	IBP_ERR_ADAPTER_SDK_USER_LOCKED,						///<用户锁定
	IBP_ERR_ADAPTER_SDK_ILLEGAL_USER,						///<非法用户
	IBP_ERR_ADAPTER_SDK_RESOURCE_ERROR,						///<资源错误
	IBP_ERR_ADAPTER_SDK_LOGNET_ERROE,						///<网络错误
	IBP_ERR_ADAPTER_SDK_PING_ERROE,							///<PING错误
	IBP_ERR_ADAPTER_SDK_MAX_USERNUM,						///<超过最大用户数量
	IBP_ERR_ADAPTER_SDK_REAL_PLAY,							///<实时视频播放
	IBP_ERR_ADAPTER_SDK_VEDIO_STOP,							///<视频停止
	IBP_ERR_ADAPTER_SDK_REAL_TALK,							///<语音对讲
	IBP_ERR_ADAPTER_SDK_TALK_STOP,							///<对讲停止
	IBP_ERR_ADAPTER_SDK_CHANNEL_USED_IN_PLAYING,			///<该通道用户正在使用
	IBP_ERR_ADAPTER_SDK_RECORD_DOWNLOAD_FINISHED,			///<录像下载完成
	IBP_ERR_ADAPTER_SDK_LOGIN_DEVICE_FAIL,					///<登陆设备失
	IBP_ERR_ADAPTER_SDK_API = 1898,							///<API错误
	IBP_LICENSE_DEVADD_DENY,								///<拒绝添加设备
	IBP_LICENSE_DEVTYPE_DENY,								///<拒绝添加该设备类型
	IBP_LICENSE_ACCEPT_OVER,								///<license接收能力超过
	IBP_ERR_ADAPTER_END = 1899,								///<设备适配器结束
	
	IBP_Err_MCU_Begin = 1900,								///<MCU开始
	IBP_Err_MCU_UNKNOWMODEL,								///<服务模式为Unknown
	IBP_Err_MCU_NOT_MASTER,									///<不是master
	IBP_Err_MCU_INVALID_CONNECTION,							///<无效连接
	IBP_Err_MCU_INVALID_PARAM,								///<无效参数
	IBP_Err_MCU_NO_USER_ID,									///<用户id不存在
	IBP_Err_MCU_NO_IMSDINFO,								///<用户关联的IMDS信息找不到
	IBP_Err_MCU_KEY_CONFLICT,								///<关键字冲突
	IBP_Err_MCU_PASSWORD_INVALID,							///<密码错误
	IBP_Err_MCU_LOGIN_ALREADY,								///<已经登录
	IBP_Err_MCU_MEETING_ID_INVALID,							///<会议室id无效
	IBP_Err_MCU_NOT_LOGIN,									///<没有登录
	IBP_Err_MCU_MEETING_LOCKED,								///<会议室被锁定
	IBP_Err_MCU_NO_SIP_SERVER,								///<没有sip服务器
	IBP_Err_MCU_SIP_INIT,									///<sip初始化失败
	IBP_Err_MCU_SIP_REGISTER,								///<sip 注册失败
	IBP_Err_MCU_NOT_MAINSPEAKER,							///<不是主讲人
	IBP_Err_MCU_USER_OFFLINE,								///<用户不在线
	IBP_Err_MCU_SESSION_INVALID,							///<无效session
	IBP_Err_MCU_NO_CALLERNUMBER,							///<无虚拟主叫号码可用
	IBP_Err_MCU_HOOK_ERR,									///<摘机错误
	IBP_Err_MCU_MAX_USER_LIMIT,								///<达到用户最大数上限
	IBP_Err_MCU_IMDS_OFFLINE,								///<IMDS服务离线
	IBP_Err_MCU_MEET_NOT_MODIFY,							///<会议进行中不能修改
	IBP_Err_MCU_EMERGENCY_MEETING_EXIST,					///<已经存在应急会议
	IBP_Err_MCU_PHONE_IS_CALLING,							///<电话正在拨打中
	IBP_Err_MCU_PHONE_STATE_WRONG,							///<电话状态错误
	IBP_Err_MCU_FEATURE_NOT_SUPPORTED,						///<不支持该功能
	IBP_Err_MCU_COLLECTION_IS_EXISTED,						///<联系人信息已经被收藏
	IBP_Err_MCU_ROOM_IS_NOT_EXISTED,						///<会议室不存在
	IBP_Err_MCU_ADGU_OFFLINE,								///<ADGU服务离线
	IBP_Err_MCU_MEMBER_IS_IN_THE_MEETING,					///<已经在会议室内
	IBP_Err_MCU_DOMAIN_ERROR,								///<域错误
	IBP_Err_MCU_MEMBER_IS_IN_OTHER_MEETING,					///<用户已经在其他会议室内
	IBP_Err_MCU_MEETING_IS_NOT_EXISTED,						///<会议不存在
	IBP_Err_MCU_MAIN_SPEAKER_IS_NOT_EXISTED,						///<主讲人不存在
	IBP_Err_MCU_End = 1999,									///<MCU结束
	
	IBP_Err_IIS_Begin = 2000,								///< IIS 开始
	IBP_Err_IIS_NOT_MASTER,									///<不是master
	IBP_Err_IIS_PlanNotExist,								///<计划不存在
	IBP_Err_IIS_UnknownOpt,									///<未知操作
	IBP_Err_IIS_AddTaskFail,								///<添加任务失败
	IBP_Err_IIS_UpdateTaskFail,								///<任务配置更新失败
	IBP_Err_IIS_DeleteTaskFail,								///<任务删除失败
	IBP_Err_IIS_AddPointFail,								///<添加巡检点失败
	IBP_Err_IIS_UpdatePointFail,							///<更新巡检点失败
	IBP_Err_IIS_DeletePointFail,							///<删除巡检点失败
	IBP_Err_IIS_AddTimeSchduleFail,							///<添加时间模板失败
	IBP_Err_IIS_UpdateTimeSchduleFail,						///<更新时间模板失败
	IBP_Err_IIS_DeleteTimeSchduleFail,						///<删除时间模板失败
	IBP_Err_IIS_QueryTaskFail,								///<查询任务失败
	IBP_Err_IIS_QueryPointFail,								///<查询巡检点失败
	IBP_Err_IIS_QueryTimeTemplateFail,						///<查询时间模板失败
	IBP_Err_IIS_CreatePlayFailed,							///<创建播放Instance失败
	IBP_Err_IIS_SnapshotFailed,								///<抓图失败
	IBP_Err_IIS_ExcutePlanFailed,							///<计划执行成功和失败
	IBP_Err_IIS_PlanStarted,								///<计划已经开始
	IBP_Err_IIS_PlanStopped,								///<计划已经结束
	IBP_Err_IIS_CalIrIndexError,							///<红外指标计算失败
	IBP_Err_IIS_CalIrTempDiffError,							///<红外温差计算失败
	IBP_Err_IIS_PlanSubscribeFailed,						///<计划订阅失败
	IBP_Err_IIS_End = 2099,									///<IIS结束
	
	IBP_Err_FS_Begin = 2100,								///<FS 开始
	IBP_Err_FS_NOT_MASTER,									///<不是master
	IBP_Err_FS_End = 2199,									///<FS结束
	
	IBP_Err_ADGU_Begin = 2200,								///<ADGU开始
	IBP_Err_ADGU_UNKNOWMODEL,								///<服务模式为Unknown
	IBP_Err_ADGU_NOT_MASTER,								///<不是master
	IBP_Err_ADGU_INVALID_CONNECTION,						///<无效连接
	IBP_Err_ADGU_INVALID_PARAM,								///<无效参数
	IBP_Err_ADGU_NO_USER_ID,								///<用户id不存在
	IBP_Err_ADGU_KEY_CONFLICT,								///<关键字冲突
	IBP_Err_ADGU_RTSP,										///<ADGU中Rtsp错误
	IBP_Err_ADGU_IPPORT,									///<ADGU地址错误
	IBP_Err_ADGU_ID_MAPPING,								///<ADGU设备id映射错误
	IBP_Err_ADGU_VIDEO_IS_OPEN,								///<ADGU中视频已打开
	IBP_Err_ADGU_INVITE_FAILED,								///<ADGU  INVITE请求失败
	IBP_Err_ADGU_VIDEO_HAS_BEEN_CLOSED,						///<ADGU视频已经被关闭
	IBP_Err_ADGU_BYE_FAILED,								///<ADGU  BYE请求失败
	IBP_Err_ADGU_CAN_NOT_GET_RTP_INFO,						///<ADGU获取RTP信息失败
	IBP_Err_ADGU_MEDIA_SESSION_IS_NULL,						///<ADGU媒体信息为空
	IBP_Err_ADGU_End = 2299,								///<ADGU结束
	
	IBP_Err_VMU_Begin = 2300,								///<VMU开始
	IBP_Err_VMU_UNKNOWMODEL,								///<服务模式为Unknown
	IBP_Err_VMU_NOT_MASTER,									///<不是master
	IBP_Err_VMU_INVALID_CONNECTION,							///<无效连接
	IBP_Err_VMU_INVALID_PARAM,								///<无效参数
	IBP_Err_VMU_KEY_CONFLICT,								///<关键字冲突
	IBP_Err_VMU_RTSP,										///<VMU中Rtsp错误
	IBP_Err_VMU_IPPORT,										///<VMU地址错误
	IBP_Err_VMU_SERVER_NOT_REGISTER,						///<VMU没有注册
	IBP_Err_VMU_NOT_FOUND_NVD,								///<没有找到NVD
	IBP_Err_VMU_ENCODE_PDU,									///<
	IBP_Err_VMU_DECODE_PDU,									///<
	IBP_Err_VMU_SERVER_RETURN_ERR,							///<VMU服务返回失败
	IBP_Err_VMU_End = 2399,									///<VMU结束
	
	IBP_Err_LCU_Begin = 2400,								///<LCU开始
	IBP_Err_LCU_UNKNOWMODEL,								///<服务模式为Unknown
	IBP_Err_LCU_NOT_MASTER,									///<不是master
	IBP_Err_LCU_INVALID_CONNECTION,							///<无效连接
	IBP_Err_LCU_INVALID_PARAM,								///<无效参数
	IBP_Err_LCU_ENCODE_PDU,									///<
	IBP_Err_LCU_DECODE_PDU,									///<
	IBP_Err_LCU_End = 2499,									///<LCU结束
	
	IBP_Err_License_Begin = 2500,								///<License开始
	IBP_Err_License_DevTypeNotSupported,					///<License不支持该设备类型
	IBP_Err_License_ManufactureNotSupported,					///<License不支持该厂商类型
	IBP_Err_License_UserTypeNotSupported,					///<License不支持该用户类型
	IBP_Err_License_DevNumberNotSupported,					///<该类型设备数量超出License限制
	IBP_Err_License_UserNumberNotSupported,					///<该类型用户数量超出License限制
	IBP_Err_License_RunTimeError,							///<运行时间超出License限制
	IBP_Err_License_End = 2699,									///<License结束

	IBP_Err_SDK_Begin = 10000,								///<SDK开始
	IBP_Err_SDK_Com_Begin = 10000,							///<SDK通用开始
	IBP_Err_SDK_Com_Timeout = 10000,						///<超时
	IBP_Err_SDK_Com_NotFound_OriReq,						///<没有找到原始请求消息
	IBP_Err_SDK_Com_ReqRes_NotSeq,							///<请求和回复命令对不起来
	IBP_Err_SDK_Com_Res_NULL,								///<回复消息为空
	IBP_Err_SDK_Com_LenOver,								///<长度不够
	IBP_Err_SDK_Manager_Failed,								///<SDK manager 初始化失败
	IBP_Err_SDK_Thread_Failed,								///<SDK 启动线程失败
	IBP_Err_SDK_UserCheck_Failed,							///<用户密码校验失败
	IBP_Err_SDK_Response_Null,								///<返回消息体为空
	IBP_Err_SDK_ConnectServer_Error,						///<SDK连接服务错误
	IBP_Err_SDK_Com_End	= 10999,							///<SDK通用结束
	
	IBP_Err_SDK_CMU_Begin = 11000,							///<CMU开始
	IBP_Err_SDK_CMU_End = 11099,							///<CMU结束
	
	IBP_Err_SDK_VTDU_Begin = 11100,							///<VTDU开始
	IBP_Err_SDK_Not_Connect,								///<未连接vtdu
	IBP_Err_SDK_Not_Find_Session,							///<未找到session
	IBP_Err_SDK_No_RtspConnect,								///<未建立rtsp连接
	IBP_Err_SDK_No_RtspSetup,								///<未进行setup流程
	IBP_Err_SDK_No_RtspPlay,								///<未进行play流程
	IBP_Err_SDK_RTP_Connect_Failed,							///<码流接受对端建立失败
	IBP_Err_SDK_VTDU_End = 11199,							///<VTDU结束
	
	IBP_Err_SDK_DMU_Begin = 11200,							///<DMU开始
	IBP_Err_SDK_DMU_End = 11299,							///<DMU结束
	
	IBP_Err_SDK_VRU_Begin = 11300,							///<VRU开始
	IBP_Err_SDK_RtspConnect_Failed,							///<
	IBP_Err_SDK_VRU_End = 11399,							///<VRU结束
	
	IBP_Err_SDK_LKU_Begin = 11400,							///<LKU开始
	IBP_Err_SDK_LKU_End = 11499,							///<LKU结束
	
	IBP_Err_SDK_LMU_Begin = 11500,							///<LMU开始
	IBP_Err_SDK_LMU_End = 11599,							///<LMU结束
	
	IBP_Err_SDK_FS_Begin = 11600,							///<FS开始
	IBP_Err_SDK_Generate_GUID_Failed,						///<生成文件GUID失败
	IBP_Err_SDK_File_GUID_Invalid,							///<文件GUID无效
	IBP_Err_SDK_FileInfo_Wrong,								///<文件信息填写错误
	IBP_Err_SDK_FilePath_Wrong,								///<文件路径填写填写错误
	IBP_Err_SDK_File_Open_Failed,							///<文件打开失败
	IBP_Err_SDK_File_Exist,									///<同名文件已存在
	IBP_Err_SDK_File_Not_Exist,								///<上传/下载文件不存在
	IBP_Err_SDK_File_Size_Limited,							///<上传文件太大（超过2G）
	IBP_Err_SDK_Disk_Full,									///<本地/服务器磁盘空间已满
	IBP_Err_SDK_File_In_Use,								///<文件正在使用,正在上传或正在下载
	IBP_Err_SDK_FileInfo_Lost,								///<内存中文件信息丢失,不能写入数据库
	IBP_Err_SDK_Logic_Wrong,								///<逻辑错误，需要修改
	IBP_Err_SDK_New_Buf_Failed,								///<申请空间失败
	IBP_Err_SDK_Write_Database_Failed,						///<写入数据库失败
	IBP_Err_SDK_File_Del_Failed,							///<文件删除失败
	IBP_Err_SDK_File_Downloading,							///<文件正在下载中
	IBP_Err_SDK_Make_Dir_Failed,							///<创建文件夹失败
	IBP_Err_SDK_FS_End = 11799,								///<FS结束
	
	IBP_Err_SDK_ADAPTER_Begin = 11800,						///<SDK ADAPATER 开始
	IBP_Err_SDK_ADAPTER_SnapshotFailed,						///<抓图失败
	IBP_Err_SDK_ADAPTER_End = 11899,						///<SDK ADAPATER结束


	IBP_Err_CANNOT_FIND_FUNCTION = 13900,					//查找不到该函数
	IBP_Err_CANNOT_LOGIN_MORE_PLATFORM,						//无法登陆更多的平台
	IBP_Err_Not_Find_PlatForm,								//无法找到该平台
	IBP_Err_PlatForm_OffLine,								//该平台离线
	IBP_Err_Not_Find_DMU,									//无法找到DMU


	IBP_Err_PLAY_Begin = 14000,								//SDK播放库部分开始
	IBP_Err_PLAY_LoadLibraryFailed,							//加载解码库失败
	IBP_Err_PLAY_GetProcAddrFailed,							//加载解码库函数地址失败
	IBP_Err_PLAY_CannotCreateInvalidChannel,				//无法创建一个类型为“无效”的频道
	IBP_Err_PLAY_NoneFreePort,								//创建频道失败（解码库没有空闲的port）
	IBP_Err_PLAY_NoneFreeChannel,							//申请不到空闲频道
	IBP_Err_PLAY_OutBoundChannel,							//频道号越界
	IBP_Err_PLAY_ReleaseFreeChannel,						//无法释放空闲的频道
	IBP_Err_PLAY_CannotOperateFreeChannel,					//无法操作空闲的频道

	IBP_Err_PLAY_CannotPlayWhenNotStreamType,				//当前不处于流模式，无法播放
	IBP_Err_PLAY_CannotPlayWhenIsPlaying,					//当前已正在播放中，无法播放
	IBP_Err_PLAY_CannotPlayWhenNoneWindow,					//当前还未添加窗口，无法播放
	IBP_Err_PLAY_SetStreamOpenModeFailed,					//设置流打开的模式时失败
	IBP_Err_PLAY_OpenStreamFailed,							//打开流失败
	IBP_Err_PLAY_SetDisplayBufFailed,						//设置显示缓冲失败
	IBP_Err_PLAY_PlayStreamFailed,							//播放流失败
	
	IBP_Err_PLAY_CannotPlayWhenNotFileType,					//当前不处于文件模式，无法播放
	IBP_Err_PLAY_FileNameIsNull,							//文件名称为NULL
	IBP_Err_PLAY_OpenFileFailed,							//打开文件失败
	IBP_Err_PLAY_PlayFileFailed,							//播放文件失败

	IBP_Err_PLAY_CannotStopWhenIsNotPlaying,				//当前不在播放中，无法停止播放

	IBP_Err_PLAY_CannotInputWhenNotStreamType,				//当前不处于流模式，无法送入数据
	IBP_Err_PLAY_CannotInputWhenIsNotPlaying,				//当前不在播放中，无法送入数据
	IBP_Err_PLAY_InputFailed,								//送入数据失败

	IBP_Err_PLAY_CannotSetDecodeWhenAudioRecording,			//录音采集模式下，无法设置解码模式
	IBP_Err_PLAY_CannotSetDecodeWhenNotStreamType,			//当前不处于流模式，无法设置解码模式
	IBP_Err_PLAY_CannotSetDecodeWhenIsNotPlaying,			//当前不在播放中，无法设置解码模式
	IBP_Err_PLAY_SetDecodeFailed,							//设置解码模式失败
	IBP_Err_PLAY_DoNotSupportHardDecode,					//你的电脑不支持硬解码

	IBP_Err_PLAY_CannotGetDecodeWhenAudioRecording,			//录音采集模式下，无法获取解码模式
	IBP_Err_PLAY_CannotGetDecodeWhenNotStreamType,			//当前不处于流模式，无法获取解码模式

	IBP_Err_PLAY_CannotAddMoreWindow,						//无法添加更多的窗口
	IBP_Err_PLAY_CannotAddExistenceWindow,					//无法添加已存在的窗口
	IBP_Err_PLAY_CannotRemoveFirstWindowWhenPlaying,		//无法删除正在播放的“主”窗口
	IBP_Err_PLAY_CannotRemoveInexistenceWindow,				//无法删除不存在的窗口

	IBP_Err_PLAY_CannotSnapWhenNotPlaying,					//当前不在播放中，无法抓图
	IBP_Err_PLAY_CannotSnapWhenHardDecode,					//当前处于硬解码模式，无法抓图
	IBP_Err_PLAY_GetPictureSizeFailed,						//获取图片原始尺寸失败
	IBP_Err_PLAY_SnapFailed,								//抓图失败

	IBP_Err_PLAY_CannotOpenSoundWhenNotPlaying,				//当前不在播放中，无法打开声音
	IBP_Err_PLAY_OenSoundFailed,							//打开声音失败
	IBP_Err_PLAY_CannotCloseSoundWhenNotPlaying,			//当前不在播放中，无法关闭声音
	IBP_Err_PLAY_CloseSoundFailed,							//关闭声音失败

	IBP_Err_PLAY_CannotGetVolumeWhenNotPlaying,				//当前不在播放中，无法获取音量值
	IBP_Err_PLAY_GetVolumeFailed,							//获取音量值失败
	IBP_Err_PLAY_CannotSetVolumeWhenNotPlaying,				//当前不在播放中，无法设置音量值
	IBP_Err_PLAY_SetVolumeFailed,							//设置音量值失败

	IBP_Err_PLAY_CannotGetColorWhenNotPlaying,				//当前不在播放中，无法获取色彩值
	IBP_Err_PLAY_GetColorFailed,							//获取色彩值失败
	IBP_Err_PLAY_CannotSetColorWhenNotPlaying,				//当前不在播放中，无法设置色彩值
	IBP_Err_PLAY_SetColorFailed,							//设置色彩值失败

	IBP_Err_PLAY_CannotPlayControlWhenNotPlayback,			//当前不在回放模式下，无法进行播放控制
	IBP_Err_PLAY_CannotPlayControlWhenNotPlaying,			//当前不在播放中，无法行播放控制
	IBP_Err_PLAY_PlayControlFailed,							//播放控制失败

	IBP_Err_PLAY_CannotSetPositionWhenNotFileType,			//当前不在文本回放模式下，无法设置播放进度值
	IBP_Err_PLAY_CannotSetPositionWhenNotPlaying,			//当前不在播放中，无法设置播放进度值
	IBP_Err_PLAY_OutBoundPosition,							//position值越界
	IBP_Err_PLAY_SetPositionFailed,							//设置播放进度失败
	IBP_Err_PLAY_CannotGetPositionWhenNotFileType,			//当前不在文本回放模式下，无法获取播放进度值
	IBP_Err_PLAY_CannotGetPositionWhenNotPlaying,			//当前不在播放中，无法获取播放进度值
	IBP_Err_PLAY_GetPositionFailed,							//获取播放进度失败

	IBP_Err_PLAY_CannotGetTotalFrameWhenNotFileType,		//当前不在文件回放模式下，无法获取文件总帧数
	IBP_Err_PLAY_CannotGetTotalFrameWhenNotPlaying,			//当前不在播放中，无法获取文件总帧数
	IBP_Err_PLAY_GetTotalFrameFailed,						

	IBP_Err_PLAY_CannotGetCurrentFrameWhenNotFileType,		//当前不在文件回放模式下，无法获取文件当前帧数
	IBP_Err_PLAY_CannotGetCurrentFrameWhenNotPlaying,		//当前不在播放中，无法获取文件当前帧数
	IBP_Err_PLAY_GetCurrentFrameFailed,						//获取文件当前帧数失败
	IBP_Err_PLAY_CannotSetCurrentFrameWhenNotFileType,		//当前不在文件回放模式下，无法设置文件当前帧数
	IBP_Err_PLAY_CannotSetCurrentFrameWhenNotPlaying,		//当前不在播放中，无法设置文件当前帧数
	IBP_Err_PLAY_SetCurrentFrameFailed,						//设置文件当前帧数失败

	IBP_Err_PLAY_CannotGetCurrentTimeWhenNotPlayback,		//当前不在回放模式下，无法获取当前播放时间
	IBP_Err_PLAY_CannotGetCurrentTimeWhenNotPlaying,		//当前不在播放中，无法获取当前播放时间
	IBP_Err_PLAY_GetCurrentTimeFailed,						//获取当前播放时间失败

	IBP_Err_PLAY_CannotGetRemainWhenNotPlayback,			//当前不在回放模式下，无法获取当前剩余帧数
	IBP_Err_PLAY_CannotGetRemainWhenNotPlaying,				//当前不在播放中，无法获取当前剩余帧数
	IBP_Err_PLAY_GetRemainFailed,							//获取当前剩余帧数失败

	IBP_Err_PLAY_CannotGetPictureSizeWhenAudioRecording,	//当前处于语音采集中，无法获取图片尺寸
	IBP_Err_PLAY_CannotGetPictureSizeWhenNotPlaying,		//当前不在播放中，无法获取图片尺寸

	IBP_Err_PLAY_CbIsNull,									//传入的cb为NULL
	IBP_Err_PLAY_SetDrawCallbackFailed,						//设置显示结束回调函数失败
	IBP_Err_PLAY_SetFileEndCallbackFailed,					//设置文件结束回调函数失败

	IBP_Err_PLAY_BuffIsNull,								//传入的buff为NULL
	IBP_Err_PLAY_OutBoundCmd,								//传入的命令字越界
	IBP_Err_PLAY_DoNotSupportQueryMedia,					//不支持查询媒体信息
	IBP_Err_PLAY_QueryInfoFailed,							//查询信息失败

	IBP_Err_PLAY_StartAudioRecordWhenNotAudioRecording,		//当前不处于语音采集模式，无法开启语音采集
	IBP_Err_PLAY_StartAudioRecordFailed,					//开启语音采集失败
	IBP_Err_PLAY_StopAudioRecordWhenNotAudioRecording,		//当前不处于语音采集模式，无法关闭语音采集
	IBP_Err_PLAY_StopAudioRecordFailed,						//关闭语音采集失败

	IBP_Err_PLAY_UnknownError = 14198,						//未知错误
	IBP_Err_PLAY_End = 14199,								//SDK播放库部分结束	

	IBP_Err_SDK_Pcc_Start = 14200,							//PCC_SDK开始
	IBP_Err_SDK_Pcc_IP_Info = IBP_Err_SDK_Pcc_Start,		//IP解析失败
	IBP_Err_SDK_Pcc_Media_Node,								//没有mediaNode可以用
	IBP_Err_SDK_Pcc_Media_Node_Timeout,						//发送超时
	IBP_Err_SDK_Pcc_Open_Local,								//打开本地
	IBP_Err_SDK_Pcc_End = 14299,
	
	IBP_Err_SDK_END = 20000,								///<SDK结束

}eIBP_Err;

/** @} */

#endif

