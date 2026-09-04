/**
 * Copyright (c) 2012, 浙江大华
 * All rights reserved.
 *
 * 文件名称：
 * 文件标识：
 * 摘　　要：Platform SDK 公共定义
 *
 * 当前版本：1.0
 * 原作者　：俞露
 * 完成日期：2012年6月6日
 * 修订记录：创建
 */

#ifndef INCLUDED_DPSDK_DPSDKDEFINE_H
#define INCLUDED_DPSDK_DPSDKDEFINE_H

#include "libdsl/DRefObj.h"

#define BEGIN_NAMESPACE_DPSDK	namespace DPSdk {
#define END_NAMESPACE_DPSDK		}
//#define DPSDK_API   //改为动态库

#ifdef _WIN32

	#ifdef PLATFORM_SDK_EXPORTS
	#define DPSDK_API  __declspec(dllexport)
	#else
	#define DPSDK_API  __declspec(dllimport)
	#endif

	#define DPSDK_CALLTYPE   __stdcall

	#ifndef _WIN32_WINNT
	#define _WIN32_WINNT 0x0502
	#endif	

	#ifndef __int8_t_defined
	#define __int8_t_defined
		typedef signed char			int8_t;
		typedef unsigned char		uint8_t;
		typedef short int			int16_t;
		typedef unsigned short int	uint16_t;
		typedef int					int32_t;
		typedef unsigned int		uint32_t;
		typedef __int64				int64_t;
		typedef unsigned __int64	uint64_t;
	#endif
#else//fixme: delete these defs
//	#include <stdio.h>
	#include <string.h> // memset(), linux platform need this
	#include <stddef.h> // NULL
	#include <stdint.h> // int8_t
//	#include <errno.h>

	#define DPSDK_API

	#define	DPSDK_CALLTYPE

	#define WORD		unsigned short
	#define DWORD		unsigned int
	#define LONG		int
	#define LONGINT		long int
	#define DWORDINT	long int
	#define LPDWORD		DWORD*
	#define BOOL		int
	#define TRUE		1
	#define FALSE		0
	#define BYTE		unsigned char
	#define UINT		unsigned int
	#define HDC			void*
	#define HWND		void*
	#define LPVOID		void*
//	#define NULL		0
	#define LLONG		long
	#define INT64		long long
	#define LDWORD		long 

	#ifndef MAX_PATH
	#define MAX_PATH	260
	#endif
	static inline void memcpy_s(void * dst,size_t nDstSize,void* src,size_t nMaxCount)
	{
		memcpy(dst,src,nDstSize > nMaxCount ? nMaxCount : nDstSize);
	}
#endif


BEGIN_NAMESPACE_DPSDK

#define DPSDK_USER_ID_FLAG_LEN 64
#define DPSDK_LOGN_MSG_LEN		64

typedef enum
{
	DPSDK_MDL_UNKNOW = -1, //未知模块
	DPSDK_MDL_APP,
	DPSDK_MDL_CMS,
	DPSDK_MDL_PCS,
	DPSDK_MDL_DMS,
	DPSDK_MDL_ADS,
	DPSDK_MDL_TRAN,	//中转模块
	DPSDK_MDL_RTSP,
	DPSDK_MDL_FTP,
	DPSDK_MDL_PEC,
	DPSDK_MDL_MGR,
	DPSDK_MDL_AREA,
	DPSDK_MDL_CMS_FORSNVD,
	DPSDK_MDL_SCS,
	DPSDK_MDL_COUNT,   //模块总数
}dpsdk_mdl_type_e;	//默认族类

//////////////////////////////////////////////////////////////////////////
#define CHAR_LEN_512					512
#define DPSDK_IP_LEN					46			// 远端IP地址长度
#define DPSDK_WEBADDRS_LEN				64			// web服务地址长度
#define DPSDK_USER_NAME_LEN				64          // 设备登陆用户名的长度
#define DPSDK_PASSWORD_LEN				64	        // 密码长度
#define DPSDK_PASSWORD_LEN_EX			1024	    // 扩展密码长度为1024
#define DPSDK_VERISON_LEN				64			// 版本号长度
#define DPSDK_ID_LEN					256			// 通配id长度
#define DPSDK_TIME_LEN                  32          // 时间长度
#define DPSDK_CHL_ID_LEN				64			// 通道ID长度
#define DPSDK_DEV_ID_LEN				64			// 设备ID长度
#define DPSDK_PTZTIMETASK_LEN           1024*1024   // 云台定时任务配置长度
#define DPSDK_REC_FILENAME_LEN			64			// 录像文件名长度
#define DPSDK_REC_DISKID_LEN			64	
#define DPSDK_ORG_DBID_LEN		    	32          // 数据库标识	
#define DPSDK_ORG_CODE_LEN              128         // 组织节点长度
#define DPSDK_ORG_NAME_LEN              256         // 组织名称长度
#define DPSDK_ORG_SN_LEN                256         // 组织节点唯一码
#define DPSDK_ORG_TYPE_LEN              16          // 组织节点类型
#define DPSDK_ORG_STATE_LEN             16          // 人员状态
#define DPSDK_ORG_OFFICE_LEN            256         // 组织节点类型
#define DPSDK_ORG_IDENTITY_ID_LEN       256         // 身份ID
#define DPSDK_ORG_MOBILE_LEN            64          // 手机号码
#define DPSDK_ORG_VIRNUMER_LEN          64          // 虚拟号码
#define DPSDK_ORG_GPS_LEN               64          // 组织节点经度
#define DPSDK_ORG_MEMO_LEN              1024        // 组织节点描述
#define DPSDK_XML_LENGTH				(1024*7)	// 用户XML长度
#define DPSDK_POINT_COUNT				128
#define DPSDK_CLIENT_NAME_LEN			64          // 客户端名字长度
#define SERVER_ID_LEN					32			// 服务ID长度
#define DPSDK_SCHEME_NAME_LEN			256			// 预案文件名长度
#define DPSDK_SCHEME_DESC_LEN			512			// 预案描述长度
#define DPSDK_TEMPLATE_NAME_LEN			64			// 时间模板名称长度
#define DPSDK_TEMPLATE_REMARK_LEN		256			// 时间模板说明长度
#define DPSDK_TEMPLATE_FLAG_LEN			512			// 时间模板信息长度
#define	DPSDK_DEVICE_NAME_LEN			256			// 设备名称长度
#define DPSDK_ALARM_INFO_LEN			(4*1024)	// 报警处理意见信息长度
#define DPSDK_ALARM_MSG_LEN				(4*1024)	// 报警查询结果信息长度
#define DPSDK_ALARM_MSGEXTRA_LEN		(4*1024)	// 上传报警附加信息长度，滕州监狱需求，add by huwenjuan20140524
#define DPSDK_ALARM_TITLE_LEN			256			// 报警查询结果title长度
#define DPSDK_ALARM_ID_LEN				128			// 报警id长度
#define DPSDK_PLAN_NAME_LEN				512			// 报警计划名称长度
#define DPSDK_SMS_MSG_LEN					(500*1024)	//客户端主动报警（短信）的长度
#define	DPSDK_COUNT_EVERY_PAGE			50			// 查询结果每页显示条数
#define DPSDK_FILENAME_LEN				256         // 一般文件的长度
#define DPSDK_RECORD_DATE_LEN			10			// 录像查询日期长度
#define DPSDK_RECORD_DAYS_LEN			128			// 录像查询返回天数
#define DPSDK_MAX_TEMPLATE_LEN			32          // 模板时间段
#define DPSDK_MATRIXID_LEN				32			// 矩阵服务器id
#define DPSDK_CODING_LEN				64			// 组织结构coding长度,和协议匹配暂64
#define DPSDK_ALARMCODE_LEN				64			// 报警code长度
#define DPSDK_TAG_SUBJECT_LEN			128			// 打标主题长度
#define DPSDK_TAG_CONTENT_LEN			256			// 打标内容长度
#define DPSDK_TAG_URL_LEN				1024		// 打标图片url地址
#define DPSDK_TAG_PATH_LEN				1024		// 打标图片本地存储path
#define DPSDK_FTP_FILENAME_LEN          256         // ftp文件名称长度
#define DPSDK_FTP_FILESIZE_LEN          32          // ftp文件大小
#define DPSDK_OPTLOG_DESC				1024		// 操作员日志描述
#define DPSDK_MSG_LENGTH                (1024*3)	// 通知消息长度
#define DPSDK_CHANL_NAME_LEN			256			// 通道名称长度,web端支持最长50个字符，还需要utf8转码，因此客户端改为256
#define DPSDK_REMARK_INFO_LEN			256			// 一些备注信息长度
#define DPSDK_SWIPENAME_LEN				64			// 刷卡人名称
#define DPSDK_PHONE_LEN					64			// 手机/电话长度
#define DPSDK_TRANCODE_LEN              20          // 转码字符长度28181使用
#define DPSDK_RTPCODE_LEN               32          // rtp编码长度28181使用
#define DPSDK_LINKRES_CHANGEID			(1024*3)	// 资源绑定修改时服务通知ID们长度
#define DPSDK_TIMESTR_LEN               64          // 时间字符串长度
#define DPSDK_DRIVER_ID_LEN				64			// 车载报警司机ID长度
#define DPSDK_AREA_CODE_LEN				64			// 车载报警司机ID长度
#define DPSDK_AREA_TYPE_LEN				64			// 车载报警司机ID长度
#define DPSDK_AREA_DB_LEN				32			// 车载报警经纬度长度
#define DPSDK_VCS_VIDEO_CODEC_LEN		10			// 视频编码格式长度
#define DPSDK_VCS_RESOLUTION_LEN		10			// 码流的视频分辨率长度
#define DPSDK_FACE_LOCATION_LEN			128			// 历史人脸抓拍地点长度

#define DPSDK_PERSON_NAME_LEN			64			// 人员名称长度
#define DPSDK_PERSON_PROVINCE_LEN		128			// 人员省份长度
#define DPSDK_PERSON_CITY_LEN			128			// 人员城市长度
#define DPSDK_PERSON_ID_LEN				64			// 人员ID长度
#define DPSDK_PERSON_FACEPIC_COUNT		5			// 注册图片个数

#define DPSDK_28181_CHL_COUNT           32			// 28181 通道个数
#define DPSDK_28181_MSG_LENGTH          64			// 28181 消息长度
#define DPSDK_28181_SN_LENGTH			64			// 28181 SN长度
#define DPSDK_28181_ALARM_DES_LEN       128			// 28181 报警描述信息长度

#define DPSDK_DOMAINID_LEN              64			// 域ID长度
#define DPSDK_SERVERCODE_LEN            64			// 服务Code长度
#define DPSDK_VERSION_LEN				64			// 服务version长度
#define DPSDK_SERVER_NAME_LEN			(50*3)		// 服务名称长度
#define DPSDK_SERVER_ORG_CODE_LEN		(90*3)		// 服务所属组装结构Code长度
#define DPSDK_CFGCHANGE_DEVIDS			1024		// 电视墙变更涉及设备ID

//add by jyl 2013.7
#define DPSSDK_CASEID_LEN               32 
#define DPSSDK_CASENAME_LEN             32 
#define DPSSDK_CASEREASON_LEN           256
#define DPSSDK_CASEDEPART_LEN           32  
#define DPSSDK_CASEUNTAKER_LEN          32
#define DPSDK_INTERTYPE_LEN             64
#define DPSDK_NATION_LEN                32          // 民族
#define DPSDK_BIRTHDAY_LEN              32          // 生日
#define DPSDK_ADDR_LEN                  256         // 住址
#define DPSDK_WORKUN_LEN                64          // 工作单位
#define DPSDK_STRING_LEN                128
#define DPSDK_TEMPLATE_LEN              256         // 模板
#define DPSDK_ROOMNAME_LEN              32
#define DPSDK_ROOMID_LEN                32
#define DPSDK_INTERROOMNAME_LEN         64          // 审讯室名
#define DPSDK_INTERCLIENTIP_LEN         32          // 审讯室绑定的客户端IP
#define DPSDK_DEVICEID_LEN              32
#define DPSDK_DEVICEIP_LEN              32          // 审讯主机设备Ip
#define DPSDK_HOSTLOGINNAME_LEN         32          // 审讯主机登录用户名
#define DPSDK_HOSTLOGINPSW_LEN          16          // 审讯主机登录密码
#define DPSDK_TEMPLISTTYPE_LEN          256         // 模板类型 

#define CFL_ERROR_SUCCESS				200
#define CLIENT_ERROR_BASE				420
#define SERVER_ERROR_BASE				520
#define DSS_ERROR_BASE					720
#define DSS_ERROR_CODE_BASE				1000000
#define DSS_DMS_BASE					1000
#define DSS_VMS_BASE					2000
#define DSS_RTSP_BASE					3000
#define DSS_ALARM_BASE					4000
#define DSS_MS_BASE						5000
#define DSS_PCS_BASE					6000
#define DSS_CUTOCU_BASE					7000
#define DSS_SCS_BASE					8000
#define PSS_ERROR_CODE_BASE				1050000
#define DPSDK_IVSPC_DATATIME			24			// 查询记录时间的字段的长度
#define DPSDK_IVSPC_DEPARTMENTNAME		512			// 保存记录的节点名称的长度
#define DPSDK_IVSPC_DEPARTMENTCODE		64			// 保存记录的节点ID的长度	

//报警主机相关
#define DPSDK_ALB_ID_LEN				64			// 数据库ID
#define DPSDK_ALB_USERID_LEN			64			// 用户编号
#define DPSDK_CHAR_LEN_16				16

//交警线
#define DPSDK_ORG_VIRNUMER_LEN          64          // 虚拟号码
#define DPSDK_ORG_TYPE_LEN              16          // 组织节点类型
#define DPSDK_ORG_STATE_LEN             16          // 人员状态
#define DPSDK_ORG_SN_LEN                256         // 组织节点唯一码
#define DPSDK_ORG_OFFICE_LEN            256         // 组织节点类型
#define DPSDK_ORG_NAME_LEN              256         // 组织名称长度
#define DPSDK_ORG_MOBILE_LEN            64          // 手机号码
#define DPSDK_ORG_MEMO_LEN              1024        // 组织节点描述
#define DPSDK_ORG_IDENTITY_ID_LEN       256         // 身份ID
#define DPSDK_ORG_GPS_LEN               64          // 组织节点经度
#define DPSDK_ORG_DBID_LEN		    	32          // 数据库标识
#define DPSDK_ORG_CODE_LEN              128         // 组织节点长度

//康特尔定制需求
#define DPSDK_KANGTEER_GROUP_DATA		1024
#define DPSDK_KANGTEER_DATA				256

//朗坤定制需求
#define DPSDK_QUERY_CHL_COUT			32			// 一次ftp图片查询的通道数限制
#define DPSDK_QUERY_PIC_MAXCOUT			256			// 一次删除的图片数量限制

//end

#define DPSDK_PE_DESC					1024		// 动环模块描述
#define DPSDK_PE_TIME					64			// 动环模块时间


#define DPSDK_PIP_SCREEN_NUM			4			// 画中画分屏个数
#define DPSDK_PIP_SCREEN1_MIN_CHAN_NUM	0			// 屏1最小通道值 
#define DPSDK_PIP_SCREEN1_MAX_CHAN_NUM	15			// 屏1最大通道值 
#define DPSDK_PIP_SCREEN2_MIN_CHAN_NUM	16			// 屏2最小通道值 
#define DPSDK_PIP_SCREEN2_MAX_CHAN_NUM	19			// 屏2最大通道值
#define DPSDK_PIP_SCREEN3_MIN_CHAN_NUM	20			// 屏3最小通道值 
#define DPSDK_PIP_SCREEN3_MAX_CHAN_NUM	23			// 屏3最大通道值
#define DPSDK_PIP_SCREEN4_MIN_CHAN_NUM	24			// 屏4最小通道值 
#define DPSDK_PIP_SCREEN4_MAX_CHAN_NUM	27			// 屏4最大通道值 

#define DPSDK_CUSTOM_MSGLENGTH			1024*3		// 电视墙变更涉及设备ID

#define DPSDK_ZHALARM_TYPE_COUNT		7			// DSS-P750综合报警相关
#define DPSDK_CHAR_256					256
#define DPSDK_CHAR_64					64
#define DPSDK_CHAR_1024					1024
#define WEB_PORT_DEFAULT				80			// web默认端口

#define DPSDK_CHAR_LEN_32				32
#define DPSDK_CHAR_LEN_64				64
#define DPSDK_CHAR_LEN_97				97
#define DPSDK_CHAR_LEN_128				128
#define DPSDK_CHAR_LEN_256				256
#define DPSDK_CHAR_LEN_512				512
#define DPSDK_CHAR_LEN_1024				1024
#define DPSDK_LOGOPIC_NUM_6				6
#define DPSDK_SCS_TEXTLEN				2048			// 发送文字长度

#define A_TREE_ROOT_CODE	"061"	//业务树根节点编码，由之前的004改为061

//////////////////////////////////////////////////////////////////////////

// SDK子模块类型
typedef enum
{
	DPSDK_FUNC_GENERAL			= 1,  // 平台登录和基本业务数据获取
	DPSDK_FUNC_REAL				= 2,  // 实时监视
	DPSDK_FUNC_PTZ				= 3,  // 设备控制
	DPSDK_FUNC_PLAYBACK			= 4,  // 回放
	DPSDK_FUNC_TALK				= 5,  // 语音对讲
	DPSDK_FUNC_INTELLIGENT		= 6,  // 智能分析
	DPSDK_FUNC_ALARM			= 7,  // 报警
	DPSDK_FUNC_BAY				= 8,  // 卡口
	DPSDK_FUNC_TVWALL			= 9,  // 电视墙
	DPSDK_FUNC_EXTRA_M			= 10, // 车载业务
	DPSDK_FUNC_PEC				= 11, // 门禁
	DPSDK_FUNC_GBT28181         = 12, // 28181
	DPSDK_FUNC_SERVERINFO       = 13, // SERVER INFO
	DPSDK_FUNC_SNVD				= 14, // SNVD
	DPSDK_FUNC_PRISON			= 15, // 监狱
	DPSDK_FUNC_EXTRA_A			= 16, // 、总后
	DPSDK_FUNC_ALARM_BUSINESS   = 17, // 报警运营平台
	DPSDK_FUNC_DIAGNOSE			= 18, // 视频质量诊断
	DPSDK_FUNC_IVSPC			= 19, // IVS-PC分组统计
	DPSDK_FUNC_PE				= 20, // 动环 能源
	DPSDK_FUNC_IPTALK			= 21, // IP语音对讲

	DPSDK_FUNC_USER             = 30,
	DPSDK_FUNC_DEVICEMGR        = 31,
	DPSDK_FUNC_DEVCONFIG		= 32,
	DPSDK_FUNC_DEVCONFIGEX		= 33,
	DPSDK_FUNC_AREA				= 34,

	DPSDK_FUNC_CALL				= 50, // 呼叫

}dpsdk_func_mdl_e;


// 媒体流按业务分类 
typedef enum
{
	DPSDK_MEDIA_INVALID,
	DPSDK_MEDIA_REAL,
	DPSDK_MEDIA_PLAYBACK,
	DPSDK_MEDIA_TALK,
	DPSDK_MEDIA_BAY,
	DPSDK_MEDIA_CALL,
	DPSDK_MEDIA_BROADCAST,
}dpsdk_media_func_e;

// 图片上传 
typedef enum
{
	DPSDK_ALARM_FTP_UP,  //-p平台报警抓图ftp上传
	DPSDK_DEFAULT_FTP_UP, //其他抓图ftp上传	

}dpsdk_ftp_up_e;

// 消息类型,用于消息回调中区分
typedef enum
{
	DPSDK_MSG_REQUEST,
	DPSDK_MSG_RESPONSE,
	DPSDK_MSG_NOTIFY,
}dpsdk_msg_type_e;	

// 消息命令字,用于消息回调中识别
typedef enum
{
	DPSDK_CMD_UNKNOWN					= 0,

	DPSDK_CMD_GENERAL_BEGIN				= 1,
	DPSDK_CMD_SENDDATATOMDL,							// 通用协议
	DPSDK_CMD_GENERALJSONTRANSPORT,				// JSON通用协议
	DPSDK_CMD_PRELOGIN,							// 查询是否使用加密登陆
	DPSDK_CMD_LOGIN,							// 登录平台通知
	DPSDK_CMD_LOGIN_WITH_ENCRYPTION,			// 加密登录平台通知
	DPSDK_CMD_LOGOUT,							// 登出平台通知
	DPSDK_CMD_GET_GROUP,						// 获取组信息通知(支持增量)
	DPSDK_CMD_GROUP_CHANGE,						// 组织结构变更通知
	DPSDK_CMD_PARKINGLOT_CHANGE,				// 车场信息变更通知

	DPSDK_CMD_CMS_CLOSE,						// CMS连接断开通知(也可能是初次连接不上)
	DPSDK_CMD_GET_OWNERFILE,					// 获取用户文件通知
	DPSDK_CMD_SAVE_OWNERFILE,					// 保存用户文件通知
	DPSDK_CMD_GET_CONFIGINFO,					// 取得配置/参数信息通知
	DPSDK_CMD_SET_SYNCTIME,						// 设置全网校时开关
	DPSDK_CMD_SAVE_OPTLOG,						// 保存操作员端日志通知
	DPSDK_CMD_GET_MENURIGHT,					// 获取模块权限
	DPSDK_CMD_GET_FUNRIGHT,						// 获取指定功能权限
	DPSDK_CMD_LOAD_MCALIINFO,					// 读取双目组织结构定位信息
	DPSDK_CMD_SAVE_MCALIINFO,					// 保存双目组织结构定位信息
	DPSDK_CMD_MCALIINFO_CHANGE,					// 双目组织结构定位信息变更
	DPSDK_CMD_FTP_OPERATOR,						// FTP操作消息
	//DPSDK_CMD_FTP_TRANSPORT_MODE,				// FTP文件传输模式
	DPSDK_CMD_GET_USERORGINFO,					// 用户组织结构
	DPSDK_CMD_SHAREVIDEO,						// 视频分享
	DPSDK_CMD_SHAREVIDEO_NOTIFY,				// 视频分享通知
	DPSDK_CMD_USERSTATE_NOTIFY,					// 用户状态通知
	DPSKD_CMD_SAVE_UPLOADPICTRUE,				// 保存上传图片信息
	DPSKD_CMD_DATE_CHANGE_NOTIFY,				// 复用的用户，改变了这个用户的信息
	DPSKD_CMD_USERPSW_CHANGE_NOTIFY,			// 用户密码修改
	DPSDK_CMD_ASKFOR_USER_AUTHORITY,			// 获取用户权限
	DPSDK_CMD_ASKFOR_SYSTEM_TIME,				// 全网校时获取服务时间
	DPSKD_CMD_USERPSW_CHANGE,					// 客户端修改用户密码
	DPSDK_CMD_CHANGE_PASSWORD,					// 修改用户密码

	//华鼎辽宁指挥中心需求--begin
	DPSDK_CMD_QUERY_HDDEVICE_INFO,				// 查询华鼎其他厂商的设备信息		CU->DMS
	DPSDK_CMD_QUERY_HDDEVICE_STATUS,			// 查询华鼎其他厂商的设备状态		CU->DMS
	DPSDK_CMD_QUERY_HDPLATFORM_FLOW,			// 查询华鼎其他厂商的平台流量信息	CU->CMS
	//华鼎辽宁指挥中心需求--end

	DPSDK_CMD_SET_MAXWND,						// 修改用户最大可播放数量
	DPSDK_CMD_PEC_SLEEP_UPDATA ,				// 防瞌睡web信息修改，通知PEC，再次请求
	DPSDK_CMD_SLEEP_ALARM   ,
	DPSDK_CMD_SLEEP_SAVEALARM ,
	DPSDK_CMD_GET_LEADER_INFO,					// 针对陕西建行：获取组员所属的组长列表信息
	DPSDK_CMD_NOTIFY_LEADER_CHANGE,				// 针对陕西建行：组员所属的组长信息变更
	DPSDK_CMD_DIR_SEARCH,						// 目录检索
	DPSDK_CMD_GET_LICENSE_EXPIRE_TIME,			// 获取证书到期时间
	DPSDK_CMD_GET_GROUP_BY_TYPE,				// 根据类型获取组信息通知
	DPSDK_CMD_GET_SERVER_INFO,					// 获取服务信息
	DPSDK_CMD_DSST_GROUP_CHANGE,				// DSST组织结构变更通知消息
	DPSDK_CMD_KANGTEER_NOTIFY,					// 康特尔需求
	DPSDK_CMD_LANGKUN_QUERY_FTPPIC,				// 安徽朗坤ftp图片查询请求
	DPSDK_CMD_LANGKUN_QUERY_FTPPIC_RESPONSE,	// 安徽朗坤ftp图片查询请求返回
    DPSDK_CMD_GET_DEVICE_LIST,					// 获取设备列表信息
	DPSDK_CMD_GET_DEVICES_INFO,					// 获取多个设备的详细信息
	DPSDK_CMD_SOCIAL_ALARM_NOTIFY,				// 社会报警平台通知
	DPSDK_CMD_SOCIAL_SETPOLICE_REQUEST,			// 社会报警平台修改处警状态
	DPSDK_CMD_GENERAL_GET_SERVER_SPM_CONFIG,	// 获取服务SPM配置(IP地址和端口号)
	DPSDK_CMD_GENERAL_IM_REF_CHANGE_NOTIFY,		// 即时通信用户列表相关变更通知，针对即时通信
	DPSDK_CMD_GENERAL_USER_ORG_CHANGED_NOTIFY,	// 用户所在组织结构名称变更，针对即时通信
	DPSDK_CMD_SAVE_ROUTINGTASK,					// 保存视频巡检任务
	DPSDK_CMD_CHANGE_USERPASSWORD,				// 修改用户密码
	DPSDK_CMD_SAVE_UPLOADFILE_INFO,				// 保存文件信息
	DPSDK_CMD_OPERATE_REMOTE_FILE,				// 保存远程文件
	DPSDK_CMD_SYNC_TIME_TOCMS,					// 给CMS校时

	DPSDK_CMD_CUSTOM_BEGIN,
	DPSDK_CMD_CUSTOM_CASENOTIFY,				// 增加余姚定制案件信息通知
	DPSDK_CMD_CUSTOM_END,

	DPSDK_CMD_PEOPLE_UPDATANUM,					// 上报应到人数和实到人数信息

	DPSDK_CMD_GET_SPMCONFIG,					// 江苏高院：获取超级市场的配置
	DPSDK_CMD_GET_EMAP_CAR_ICON_TYPE,			// 获取电子地图车辆图标配置
	DPSDK_CMD_JSON_SEND_TO_CMS,					// 发送给cms的通用json协议
	DPSDK_CMD_JSON_SEND_TO_DMS,					// 发送给dms的通用json协议

	DPSDK_CMD_MESSAGE_REQUEST,					// cms message通知
	DPSDK_CMD_GET_RELATIVE_FPT_PATH,			// 获取ftp相对路径
	DPSDK_CMD_GET_USERDEPORGINFO,			    // 用户部门组织结构
	DPSDK_CMD_NOTIFY_LOGIN_FORCED,				// 用户被强制登陆
	DPSDK_CMD_NOTIFY_SUERVISE_MSG,				// 执法监督时间到，cms通知客户端
	DPSDK_CMD_RECONNECT_TO_CMS,					// 重连CMS
	DPSDK_CMD_SERVER_LOGIN_NOTIFY,				// 服务登录成功通知
	DPSDK_CMD_POLLINGTASK_CHANGE_NOTIFY,		// 轮巡任务变更
	DPSDK_CMD_TASKUSER_DELETE_NOTIFY,			// 轮巡任务分享删除
	DPSDK_CMD_HTTPS_NOTIFY,						//通知客户端内嵌web是否使用https
  
	DPSDK_CMD_GENERAL_END				= 80,	

	DPSDK_CMD_MEDIASESSION_BENIN		= 81,
	DPSDK_CMD_VIDEO_RECEIVE_FIRST_DATA,			// 接收第一帧数据通知
	DPSDK_CMD_VIDEO_RTSP_DISCONNECT,			// RTSP连接断开
	DPSDK_CMD_MEDIASESSION_END			= 100,       

	DPSDK_CMD_REAL_BEGIN				= 101,
	DPSDK_CMD_OPEN_VIDEO,						// 请求实时视频
	DPSDK_CMD_CLOSE_VIDEO,						// 关闭实时视频
	DPSDK_CMD_PAUSE_VIDEO,						// 暂停RTSP
	DPSDK_CMD_RESUME_VIDEO,						// 恢复RTSP
	DPSDK_CMD_VIDEO_EXPECTION,					// 实时视频异常 通知 fixme：需细化，之后删除
	DPSDK_CMD_VIDEO_LOCK,						// 视频锁定
	DPSDK_CMD_VIDEO_LOCKNOTIFY,					// 视频锁定通知
	DPSDK_CMD_VIDEO_REOCRD,						// 视频录像操作

	DPSDK_CMD_OPEN_VIDEO_EX				= 150,	// 请求视频扩展-for new Protocol:28181
	DPSDK_CMD_GET_STREAM_URL,					// 获取视频的url路径
	DPSDK_CMD_CLOSE_STREAM_URL,					// 关闭视频url链接

	DPSDK_CMD_OPEN_VIDEO_MGW,					// 请求视频，MGW去流	
	DPSDK_CMD_GET_EXTERNAL_STREAM_URL,			// 获取视频外部url路径
	DPSDK_CMD_OPEN_VIDEO_BY_URL,				// 按rtsp url请求实时视频
	DPSDK_CMD_REAL_PLAY_DESCRIBE_EX,			// 实时视频describe请求
	DPSDK_CMD_OPEN_VIDEO_EX_WITH_DESCRIBE,		// 实时视频及describe请求
	DPSDK_CMD_REAL_END					= 200,

	DPSDK_CMD_DEVICE_BEGIN				= 201,

	DPSDK_CMD_PTZ_BEGIN,
	DPSDK_CMD_PTZ_DIRECTION,					// 云台方向控制
	DPSDK_CMD_PTZ_QUERYPOINT,					// 预置点查询
    DPSDK_CMD_PTZ_QUERYTIMEPOINT,				// 预置点查询(有效时间)
	DPSDK_CMD_PTZ_SETPTZTASK,					// 设置云台定时任务配置
	DPSDK_CMD_PTZ_QUERYPTZTASK,					// 查询云台定时任务配置
	DPSDK_CMD_PTZ_QUERYCRUISE,					// 查询巡航线
	DPSDK_CMD_PTZ_SAVECRUISE,					// 保存巡航线到CMS
	DPSDK_CMD_PTZ_SAVECRUISETODEVICE,			// 保存巡航线到设备
	DPSDK_CMD_PTZ_CAMERAOPERATER,				// 云台变焦，变焦，光圈
	DPSDK_CMD_PTZ_SIT,							// 云台三维定位
	DPSDK_CMD_PTZ_ARRANGE,						// 云台锁定/解锁
	DPSDK_CMD_PTZ_OPENOPER,						// 云台打开关闭（灯光，雨刷，红外线等）
	DPSDK_CMD_PTZ_PREPOINT_OPER,				// 云台 预置点操作(设置，删除，定位)
	DPSDK_CMD_PTZ_TIME_PREPOINT_OPER,			// 云台 预置点操作(设置，删除，定位)(有效期预置点)
    DPSDK_CMD_PTZ_SET_PREPOINT_TIME,			// 设置预置点的有效时间段
	DPSDK_CMD_PTZ_CTRLOUT,						// 联动动作输出
	DPSDK_CMD_PTZ_QUERYALARMOUT,				// 查询报警输出通道开启状态
	DPSDK_CMD_PTZ_QUERYALARMIN,					// 查询报警输入状态
	DPSDK_CMD_PTZ_ALARMINENABLE,				// 报警输入通道启用
	DPSDK_CMD_PTZ_ALARMINREPORT,				// 报警输入状态通知
	DPSDK_CMD_PTZ_QUERYSITINFO,					// 查询云台三维定位信息
	DPSDK_CMD_PTZ_ALARMOUTREPORT,				// 报警输出状态通知
	DPSDK_CMD_FOCUSE_CONTROL,					// 电动聚焦控制
	DPSDK_CMD_QUERY_FOCUSE_STATUE,				// 查询电动聚焦状态
    DPSDK_CMD_PTZ_SITALARMINFO,					// 云台定位报警信息
	DPSDK_CMD_PTZ_QUERYSTATUS,					// 云台状态查询
	DPSDK_CMD_PTZ_SUBPTZALARM,					// 订阅云台报警
	DPSDK_CMD_PTZ_CTRLOUT_RESULT,				// 联动动作输出结果返回
	DPSDK_CMD_PTZ_LOCKSTATUS,					// 云台锁定状态变更通知
	DPSDK_CMD_DEVICE_CLUSTER_STATUS,			// NVR主备状态
	DPSDK_CMD_FISHEYE_SETINFO,					// 鱼眼配置
	DPSDK_CMD_FISHEYE_CONTROL,					// 鱼眼控制
	DPSDK_CMD_ALARMOUT_MODLE,					// 报警输出通道模式
	DPSDK_CMD_PTZ_QUERYPOINT_EX,				// 预置点查询(添加守望点信息)
	DPSDK_CMD_SET_OSDINFO,						// 设置OSD字幕叠加消息
	DPSDK_CMD_PTZ_QUERYIDLE,					// 查询云台空闲动作消息
	DPSDK_CMD_PTZ_SETIDLE,						// 设置云台空闲动作消息
	DPSDK_CMD_PTZ_QUERYPTZPARAM,				// 查询球机云台参数
	DPSDK_CMD_PTZ_SETPTZPARAM,					// 设置球机云台参数
	DPSDK_CMD_PTZ_END,

	DPSDK_CMD_DMS_DISCONNECT,					// 断开DMS服务通知
	DPSDK_CMD_DMS_CONNECT,						// 连接DMS服务通知
	DPSDK_CMD_PTZ_NOTIFY,						// 云台消息通知
	DPSDK_CMD_DEVICE_STATUS_NOTIFY,				// 设备状态通知
	DPSDK_CMD_QUERY_NVRCHNL_STATUS,				// 查询NVR设备通道状态
	DPSDK_CMD_CHNL_STATUS_NOTIFY,				// 通道状态通知
	DPSDK_CMD_NVRCHNL_STATUS,					// NVR设备通道状态
	DPSDK_CMD_DEVICEVIEW_STATUS,				// 查询设备可视域状态
	DPSDK_CMD_CHNLVIEW_STATUS,					// 查询通道可视域状态
	DPSDK_CMD_CHNLVIEW_SET,						// 设置通道可视域
	DPSDK_CMD_REPORT_CHANNELVIEW,				// 可视域信息上报
	DPSDK_CMD_PTZ_QUERYLOTPOINTS,				// 批量预置点查询
	DPSDK_CMD_QUERY_HEAT_MAP,					// 查询前端设备热度图信息
	DPSDK_CMD_DEV_SNAP_PICTURE,					// 前端设备抓图
	DPSDK_CMD_START_GENERATE_WIDEVIEW,			// 开始生产全景图
	DPSDK_CMD_STOP_GENERATE_WIDEVIEW,			// 停止获取全景云台图片
	DPSDK_CMD_GET_WIDEVIEW_STATE,				// 获取全景图读取进度
	DPSDK_CMD_GET_WIDEVIEW_POINTS,				// 根据普通云台坐标获取到全景图云台坐标
	DPSDK_CMD_GET_PTZ_COORDINATE,				// 根据全景图云台坐标获取到普通云台坐标
	DPSDK_CMD_GET_WIDEVIEW_IMGDATA,				// 获取全景图片数据
	DPSDK_CMD_GET_PTZ_STATUS,					// 获取设备当前的位置信息
	DPSDK_CMD_CONNECT_DMS_BY_CHNLID,			// 连接通道ID对应的DMS服务
	DPSDK_CMD_DEVICE_END				= 300,

	DPSDK_CMD_PLAYBACK_BEGIN			= 301,
	DPSDK_CMD_QUERY_RECORD,						// 查询录像
	DPSDK_CMD_QUERYDATE_HASRECORD,				// 查询指定时间内有录像的日期（单通道）
	DPSDK_CMD_START_PLAYBACK_FILE,				// 按文件开始回放
	DPSDK_CMD_START_PLAYBACK_TIME,				// 按时间开始回放
	DPSDK_CMD_STOP_PLAYBACK,					// 停止回放
	DPSDK_CMD_SEEK_PLAYBACK,					// 定位回放
	DPSDK_CMD_PAUSE_PLAYBACK,					// 暂停回放
	DPSDK_CMD_RESUME_PLAYBACK,					// 恢复回放
	DPSDK_CMD_SETSPEED_PLAYBACK,				// 设置回放速度
	DPSDK_CMD_PLAYBACK_DATAOVER,				// 收到0包大小的通知  
	DPSDK_CMD_QUERY_ALARMRECORD,				// 查询报警录像
	DPSDK_CMD_QUERY_TAGINFO,					// 查询打标信息
	DPSDK_CMD_OPERATOR_TAGINFO,					// 操作打标信息
	DPSDK_CMD_OPERATOR_TAGIMAGE,				// 操作打标图片
	DPSDK_CMD_SS_EXPECTION,						// SS服务异常
	DPSDK_CMD_OPTION_PLAYBACK,					// 保活
	DPSDK_CMD_QUERY_FIRSTRECORD,				// 查询第一段录像开始时间
	DPSDK_CMD_DELETE_PLAYBACK_FILE,
	DPSDK_CMD_GET_PBBYTIME_URL,					// 获取回放URL
	DPSDK_CMD_CLOSE_PBBYTIME_URL,				// 释放回放URL
	DPSDK_CMD_START_PLAYBACK_URL,				// 按rtsp url开始回放
	DPSDK_CMD_QUERY_RECORD_BY_FILE_ID,			// 京东项目定制，根据实时视频文件ID查询录像信息
	
	DPSDK_CMD_START_PLAYBACK_FILE_EX	= 350,	//for new Protocol:28181
	DPSDK_CMD_START_PLAYBACK_TIME_EX,
	DPSDK_CMD_PLAYBACK_TIME_DESCRIBE_EX = 352,
	DPSDK_CMD_PLAYBACK_FILE_DESCRIBE_EX,

	DPSDK_CMD_PLAYBACK_END				= 400,

	DPSDK_CMD_TALK_BEGIN				= 401,
	DPSDK_CMD_START_TALK,						// 请求语音对讲
	DPSDK_CMD_STOP_TALK,						// 关闭语音对讲
	DPSDK_CMD_PAUSE_TALK,						// 暂停对讲
	DPSDK_CMD_RESUME_TALK,						// 恢复对讲
	DPSDK_CMD_TALK_EXPECTION,					// 对讲异常 通知 fixme：需细化，之后删除
	DPSDK_CMD_OPER_TALK_FILE,					// 对讲录像文件上传下载
	DPSDK_CMD_SAVE_TALK_FILE_INFO,				// 对讲录像文件信息保存
	DPSDK_CMD_QUERY_TALK_FILE_INFO,				// 对讲录像文件查询
	DPSDK_CMD_START_BROADCAST,					// 请求广播Broadcast
	DPSDK_CMD_STOP_BROADCAST,					// 关闭广播
	DPSDK_CMD_VOICE_FILE_PUTIN,					// 语音文件投放
	DPSDK_CMD_VOICE_PUTIN_STOP,					// 语音投放停止
	DPSDK_CMD_START_TALK_EX,					// 打开国标广播-for new Protocol:28181
	DPSDK_CMD_TALK_END					= 450,

	DPSDK_CMD_ALARM_BEGIN				= 451,
	DPSDK_CMD_GET_SCHEMELIST,					// 获取预案列表
	DPSDK_CMD_GET_SCHEMEFILE,					// 获取单个预案
	DPSDK_CMD_SAVE_SCHEMEFILE,					// 保存单个预案
	DPSDK_CMD_DEL_SCHEMEFILE,					// 删除预案文件
	DPSDK_CMD_GET_TIMETEMPLATE,					// 获取时间模板
	DPSDK_CMD_ADS_LOGIN,						// ADS登陆 fixme:需移到内部
	DPSDK_CMD_ADS_COMMSTATUS,					// ADS交互状态通知
	DPSDK_CMD_REPORT_ALARM,						// 报警上报
	DPSDK_CMD_ALARM_ENABLE,						// 报警使能 CU->ADS
	DPSDK_CMD_QUERY_ALARMCOUNT,					// 查询报警数量 CU->ADS
	DPSDK_CMD_QUERY_ALARM,						// 查询报警信息 CU->ADS
	DPSDK_CMD_SCHEME_INVALIDATE,				// 报警关闭 CU->ADS
	DPSDK_CMD_ALARM_CONFIRM,					// 报警确认 CU->ADS
	DPSDK_CMD_NOTIFY_ALARMMSG,					// 报警业务相关更改通知 CMS->CU
	DPSDK_CMD_QUERY_IVSB_ALARMPIC,				// IVS-B报警图片获取
	DPSDK_CMD_REPORT_PECCANCY_ALARM,			// 围栏报警上报
	DPSDK_CMD_REQUEST_ALARM,					// 报警消息发送 add by minjie 2014-03-28
	DPSDK_CMD_QUERY_DOORINANDOUT,				// 出入门禁消息发送 add by huwenjuan 2014-05-20
	DPSDK_CMD_TRANSFER_ALARM,					// 报警转移
	DPSDK_CMD_CLIENT_ALARM_TO_SERVER,			// 客户端报警到服务
	DPSDK_CMD_QUERY_ZHALARM,					// DSS-P750查询综合报警信息 CU->ADS
	DPSDK_CMD_UPDATE_ALARM_PICPATH,				// 手抓图片路径消息发送
	DPSDK_CMD_ALARM_ACCEPT_CAPACITY,        	// 报警接收能力
	DPSDK_CMD_GET_SHOW_LEVEL_ALARM_TYPE,    	// 获取显示等级报警类型信息 
	DPSDK_CMD_GET_CUSTOM_ALARM_TYPE,    		// 获取自定义报警类型信息 
	DPSDK_CMD_QUERY_ALLUSEREXTINFO,				// 向ADS获取用户通讯录
	DPSDK_CMD_SENDAPPALARM,						// 由客户端主动向ADS发送报警

	DPSDK_CMD_GET_SYSTEM_ALARM_TYPE     =479,	// 获取自定义报警类型信息 
	
	DPSDK_CMD_REPORT_ALARM_NEW			= 480,	// 新报警上报流程
	DPSDK_CMD_QUERY_RFID_ALARM			= 484,	// 查询RFID报警
	DPSDK_CMD_ALARM_END					= 500,

	DPSDK_CMD_INTELLIGENT_BEGIN			= 501,	// IVS模块开始
	DPSDK_CMD_GET_IVSRULE,						// 获取智能规则
	DPSDK_CMD_QUERY_IVSPC_CONUT,				// IVS-PC查询总数
	DPSDK_CMD_QUERY_IVSPC_BYPAGE,				// IVS-PC分页查询
	DPSDK_CMD_QUERY_IVSPC_STOP,					// IVS-PC停止查询
	DPSDK_CMD_MANUAL_TRACK,						// ISD手动跟踪
	DPSDK_CMD_MASTERSLAVE_TRACK,				// IVS-M主从手动跟踪
	DPSDK_CMD_FIXEDPOINT_TRACK,					// IVS-M主从定点跟踪
	DPSDK_CMD_INTELLIGENT_END			= 550,	// IVS模块结束

	DPSDK_CMD_PEC_BEGIN					= 551,	// PEC模块开始
	DPSDK_CMD_PES_ACTIVE_BEGIN,
	DPSDK_CMD_PEC_DOOR_CONTROL,					// 门控制
	DPSDK_CMD_PEC_ALARMHOST_CONFIG,				// 报警主机配置
	DPSDK_CMD_PEC_QUERY_AHOST_ABILITY,			// 查询报警主机能力
	DPSDK_CMD_PEC_QUERY_AHOST_DEFENCE,			// 查询报警主机防区信息
	DPSDK_CMD_PEC_QUERY_DOORINFO,				// 查询门信息
	DPSDK_CMD_PEC_POWERGRID_CONTROL,			// 电网控制
	DPSDK_CMD_PEC_POWERGRID_REPORT,				// 电网设备信息上报
	DPSDK_CMD_PEC_QUERY_DISPACHER_CHNL_STATUS,	// 查询指挥调度设备的通道状态
	DPSDK_CMD_PES_ACTIVE_END,
	DPSDK_CMD_PEC_SAVE_DOORINFO,				// 保存开门记录
	DPSDK_CMD_PEC_QUERY_CARDINFO,				// 获取门禁卡信息
	DPSDK_CMD_PEC_DEVICE_STATUS,				// 设备状态上报
	DPSDK_CMD_PEC_AHOST_REPORT,					// 报警主机状态上报
	DPSDK_CMD_PEC_DOOR_REPORT,					// 门状态上报
	DPSDK_CMD_PEC_SAVE_PICURL,					// 保存门禁图片到ftp
	DPSDK_CMD_PEC_SAVEALARM_PICURL,				// 保存报警图片到ftp
	
	DPSDK_CMD_PEC_GET_LINKRESOURCE,				// 获取绑定视频资源
	DPSDK_CMD_PEC_LINKRES_CHANGENOTIFY,			// 资源改变通知
	DPSDK_CMD_PEC_LINKRES_CHANGE_RESOURCE,		// 资源改变获取信息
	DPSDK_CMD_PEC_SAVE_ROADGATEINFO,			// 保存开闸记录
	DPSDK_CMD_PEC_QUERY_CARINFO,				// 获取车辆的红黑白名单信息
	DPSDK_CMD_PEC_ROADGATE_CONTROL,				// 道闸控制
	DPSDK_CMD_PEC_SCSDATA_REPORT,				// 动环SCS实时数据上报
	DPSDK_CMD_PEC_DISPACHER_REPORT,				// 指挥调度通道状态上报
	DPSDK_CMD_PEC_QUERY_FTPFILELIST,            // 查询FTP文件列表 
	DPSDK_CMD_PEC_NOTIFY_MODIFY,                // 通知FTP上传或删除了文件
	DPSDK_CMD_PEC_QUERY_AHOST_ALARMOUT_STATUS,	// 查询报警主机输出通道状态
	DPSDK_CMD_PEC_ENV_QUERY,					// CFLCUEnvQueryRequest协议透传信令
	DPSDK_CMD_PEC_BROADCAST_REPORT,				// 业翔广播状态上报
	DPSDK_CMD_PEC_END					= 600,	// PEC模块结束

	DPSDK_CMD_TVWALL_BEGIN				= 601,	// TVWALL 开始
	DPSDK_CMD_GET_TVWALL_LIST,					// 取得TVWALL列表信息
	DPSDK_CMD_GET_TVWALL_INFO,					// 取得TVWALL xml信息
	DPSDK_CMD_MAPTO_TVWALL,						// 控制大屏
	DPSDK_CMD_DECODER_CONFIG,					// 解码器配置（电视墙配置）
	DPSDK_CMD_TVWALL_SCHEME_CONFIG,				// 预案配置
	DPSDK_CMD_TVWALL_GET_RUN_TASK,				// 获取设备当前任务信息
	DPSDK_CMD_TVWALL_POWERCONTROL,				// 电源控制
	DPSDK_CMD_TVWALL_SET_SIGNAL,				// 设置信号
	DPSDK_CMD_TVWALL_GET_SIGNAL,				// 获取信号
	DPSDK_CMD_TVWALL_NOTIFY,					// tvwall通知消息 CMS->CU
	DPSDK_CMD_TVWALL_SCHEME_LIST,				// 获取任务列表
	DPSDK_CMD_TVWALL_SCHEME_INFO,				// 获取任务信息(或场景信息)
	DPSDK_CMD_TVWALL_DEL_TASK,					// 删除一个任务
	DPSDK_CMD_TVWALL_MODIFY_TASK_BASEINFO,		// 修改任务基本信息（名称或描述）
	DPSDK_CMD_TVWALL_LAYOUT_CFG,				// 电视墙布局
	DPSDK_CMD_TVWALL_SNVD_PORT_SPEED,			// 设置SNVD端口上墙播放速度
	DPSDK_CMD_PIPMAPTO_TVWALL,					// 安徽三联项目定制画中画上墙功能
	DPSDK_CMD_TVWALL_ARRANGE,					// 电视墙锁定
	DPSDK_CMD_TVWALL_ARRANGE_NOTIFY,			// 电视墙锁变更通知
	DPSDK_CMD_TVWALL_RUNINFO,					// 查询电视墙计划运行信息
	DPSDK_CMD_TVWALL_RUNINFO_NOTIFY,			// 电视墙运行信息通知
	DPSDK_CMD_TVWALL_SCREEN_ADDFRAME,			// 屏幕加框
	DPSDK_CMD_TVWALL_CURRENT_TASK,				// 当前电视墙正执行的任务或计划 
	DPSDK_CMD_TVWALL_TVWALLINFO_BY_SN,			// 通过sn查询电视墙信息
	DPSDK_CMD_TVWALL_END				= 650,	// TVWALL 结束


	DPSDK_CMD_BAY_BEGIN					= 700,
	DPSDK_CMD_PCS_LOGIN,						// 登录Pcs平台
	DPSDK_CMD_PCS_LOGOUT,						// 登出Pcs平台
	DPSDK_CMD_PCS_CLOSE,						// 与PCS连接断开 通知；触发了OnClose，也可能是初次连接不上
	DPSDK_CMD_BAY_START_MONITOR,				// 打开图片监控
	DPSDK_CMD_BAY_STOP_MONITOR,					// 关闭图片监控
	DPSDK_CMD_BAY_RTPCLOSE_NOTIFY,				// rtp断线通知
	DPSDK_CMD_BAY_DPALARM_NOTIFY,				// 违章报警
	DPSDK_CMD_BAY_WANTED_NOTIFY,				// 布控报警
	DPSDK_CMD_POLICE_SURVEY_NOTIFY,				// 第三方布控
	DPSDK_CMD_BAY_QUERY_PARKINGSTATUS,			// 查询停车信息
	DPSDK_CMD_BAY_PARKINGSTATUS_NOTIFY,			// 通知停车变更的信息
	DPSDK_CMD_BAY_SUBSCRIBE_TRAFFIC_FLOW,		// 交通流量订阅
	DPSDK_CMD_BAY_REPORT_TRAFFIC_FLOW,          // 车道流量上报
	DPSDK_CMD_BAY_REPORT_DEV_TRAFFIC_FLOW,		// 交设备流量上报
	DPSDK_CMD_BAY_SUBSCRIBE_AREA_SPEED,		    // 区间测速订阅
	DPSDK_CMD_BAY_WRITE_TRAFFIC_VIOLATION,		// 违章信息写入
	DPSDK_CMD_BAY_QUERY_TRAFFIC_VIOLATION,		// 违章信息查询
	DPSDK_CMD_BAY_REPORT_SPAN_TEST,             // 区间测速
	DPSDK_CMD_BAY_CARINFO_NOTIFY,				// 进出口车辆通知	
	DPSDK_CMD_BAY_QUERYALLWINDING,				// 查询所有线圈信息
	DPSDK_CMD_BAY_MFALARM,						// 硬件故障报警
	DPSDK_CMD_BAY_ABNORMAL_NOTIFY,				// 设备上报图片异常通知

	//人脸卡口
	DPSDK_CMD_BAY_FACEALARM_NOTIFY,		//人脸识别报警通知
	DPSDK_CMD_BAY_FACE_OPT,						//人脸卡口相关操作
	DPSDK_CMD_BAY_GENERAL_NOTIFY,	//通用Json通知
	DPSDK_CMD_BAY_GET_STATUS,
	DPSDK_CMD_BAY_END					= 750,	

	DPSDK_CMD_DEVCONFIG_BEGIN			= 751,			
	DPSDK_CMD_DEVCONFIG_SET,                    // 设备配置设置
	DPSDK_CMD_DEVCONFIG_GET,                    // 设备配置获取
	DPSDK_CMD_DEVCONFIG_END				= 760,

	DPSDK_CMD_DEVCONFIG_EX_BEGIN		= 761,
	DPSDK_CMD_DEVCONFIG_SET_EX,                 // 设备配置设置补充
	DPSDK_CMD_DEVCONFIG_GET_EX,                 // 设备配置获取补充
	DPSDK_CMD_DEVCONFIG_OPERATOR_EX,			// 设备配置-设备操作
	DPSDK_CMD_DEVCONFIG_SEARCH_EX,				// 设备配置-设备操作
	DPSDK_CMD_DEVCONFIG_DEVICE_OUT,				// 设备断线通知
	DPSDK_CMD_DEVCONFIG_DEVICE_IN,				// 设备配置-设备上线通知
	DPSDK_CMD_DEVCONFIG_EX_END			= 770,

	DPSDK_CMD_DEVMGR_BEGIN				= 900,
	DPSDK_CMD_START_SEARCH_DEVICES,				// 设备搜索
	DPSDK_CMD_DEVICEINFO_BYSEARCH,				// 设备搜索回调
	DPSDK_CMD_STOP_SEARCH_DEVICES,				// 停止设备搜索
	DPSDK_CMD_GET_DEVICE_TEMPINFO,				// 临时获取设备信息
	DPSDK_CMD_DEVALARMOUTPUTSTATE_OPR,			// 设备报警输出通道开关状态操作
	DPSDK_CMD_DEVICE_CAPTUREPIC,				// 抓取通道视频图片（添加设备时使用）
	DPSDK_CMD_DEVMGR_END				= 1000,

	DPSDK_CMD_EXTRA_M_BEGIN				= 1001,
	DPSDK_CMD_EXTRA_M_ASKFOR_AREA_INFO,			// 获取电子围栏信息
	DPSDK_CMD_EXTRA_M_ASKFOR_RELATION,			// 获取设备围栏关系
	DPSDK_CMD_EXTRA_M_ASKFOR_AREA_POINTS,		// 获取电子围栏点位信息
	DPSDK_CMD_EXTRA_M_ASKFOR_AREA_RIGHTS,		// 获取围栏权限
	DPSDK_CMD_EXTRA_M_ASKFOR_LAST_GPS_STATUS,	// 获取最后一次GPS信息
	DPSDK_CMD_EXTRA_M_ASKFOR_LAST_DEV_STATUS,	// 获取最后一次设备信息
	DPSDK_CMD_EXTRA_M_ASKFOR_LAST_GAS_STATUS,	// 获取最后一次油耗信息
	DPSDK_CMD_EXTRA_M_ADD_AREA,					// 增加电子围栏
	DPSDK_CMD_EXTRA_M_DEL_AREA,					// 删除电子围栏
	DPSDK_CMD_EXTRA_M_MOD_AREA,					// 修改电子围栏
	DPSDK_CMD_EXTRA_M_UPLOAD_RELATION,			// 上传设备与围栏关系给服务
	DPSDK_CMD_EXTRA_M_ADD_AREA_IN_DEV,			// 增加设备与电子围栏的关联
	DPSDK_CMD_EXTRA_M_DEL_AREA_IN_DEV,			// 删除设备与电子围栏的关联
	DPSDK_CMD_EXTRA_M_NOTIFY_AREA_CHANGE,		// 电子围栏改变通知消息
	DPSDK_CMD_EXTRA_M_NOTIFY_RELATION_CHANGE,	// 关联关系改变通知消息
	DPSDK_CMD_EXTRA_M_SET_OSDINFO,				// OSD字幕叠加消息
	DPSDK_CMD_EXTRA_M_START_RECORD,				// 开始手动录像
	DPSDK_CMD_EXTRA_M_STOP_RECORD,				// 关闭手动录像
	DPSDK_CMD_EXTRA_M_SET_CFGINFO,				// 文本信息
	DPSDK_CMD_EXTRA_M_SNAP_REMOTEDEVICE,		// 远程设备抓图
	DPSDK_CMD_EXTRA_M_NOTIFY_DEVICESNAP,		// 设备抓图回调
	DPSDK_CMD_EXTRA_M_DEVICE_REC_2_PLATFORM,	// 设备上传录像到平台，俄罗斯需求引入
	DPSDK_CMD_EXTRA_M_SET_OSDINFO_EX,			// 南京地铁项目OSD字幕叠加消息==>比DPSDK_CMD_EXTRA_M_SET_OSDINFO多设备id和（还有一个通道号不一样）
	DPSDK_CMD_EXTRA_M_DEVICE_GPS_2_CMS,			// 设备GPS上传给CMS
	DPSDK_CMD_EXTRA_M_GETDEV_ALLCONFIGINFO,	    // 获取设备相关配置信息
	DPSDK_CMD_EXTRA_M_GETDEV_VERSION,			// 获取设备版本
	DPSDK_CMD_EXTRA_M_GETDEV_HARDDISK,			// 获取设备硬盘信息
	DPSDK_CMD_EXTRA_M_GETDEV_ENCODED,			// 获取设备解码信息
	DPSDK_CMD_EXTRA_M_GETDEV_SNAPINFO,			// 获取设备抓图配置信息
	DPSDK_CMD_EXTRA_M_SAVEDEV_ALLCONFIG,		// 设置设备的各类属性
	DPSDK_CMD_EXTRA_M_FORMAT_HARDDIST,			// 格式化设备硬盘分区
	DPSDK_CMD_EXTRA_M_SAVEDEV_ENCODED,			// 设置设备解码信息
	DPSDK_CMD_EXTRA_M_SAVEDEV_SNAPINFO,			// 设置设备抓图配置信息
	DPSDK_CMD_EXTRA_M_CLEARDEVICEALARM,			// 清除设备报警
	DPSDK_CMD_EXTRA_M_GETDEVICE_THIRDSTREAM,	// M获取设备3码流类型
	DPSDK_CMD_EXTRA_M_DEV3GFLOWINFO,			// cms主动发送各个设备3g流量信息
	DPSDK_CMD_EXTRA_M_GETDEVINFOBYREGDEVID,		// 通过设备注册id获取设备信息
	DPSDK_CMD_EXTRA_M_GETUSERINFOLIST,			// 获取用户信息列表
	DPSDK_CMD_EXTRA_M_GETCLASSCHANGEINFO,		// 获取交接班信息
	DPSDK_CMD_EXTRA_M_NOTIFY_USERINFOCHANGE,	// 用户信息改变通知
	DPSDK_CMD_EXTRA_M_SAVECLASSCHANGEMSG,		// 保存交接班信息
	DPSDK_CMD_EXTRA_M_DEVICE_RECORD_UPLOAD_RES,	// 设备录像上传结果通知
	DPSDK_CMD_EXTRA_M_OPERATEOSDTEMPLAT,		// OSD信息模块的增删改
	DPSDK_CMD_EXTRA_M_GETOSDTEMPLATINFO,		// 获取OSD信息模板
	DPSDK_CMD_EXTRA_M_GETHISTORYOSDINFO,		// 获取历史OSD/SMS信息
	DPSDK_CMD_EXTRA_M_SENDSMSINFO,				// 发送短信信息
	DPSDK_CMD_EXTRA_M_GETAREATIMERANGEINFO,		// 获取围栏时间信息
	DPSDK_CMD_EXTRA_M_SETAREATIMERANGEINFO,		// 设置围栏时间信息
	DPSDK_CMD_EXTRA_M_GETDATABASETYPE,			// 获取服务数据库类型
	DPSDK_CMD_EXTRA_M_GETDEV_AUTOCHEKINFO,			//获取设备自检信息
	DPSDK_CMD_EXTRA_M_GETDEV_RECODINFO,					//设备本机录像
	DPSDK_CMD_EXTRA_M_SAVEDEV_RECODINFO,				//保存设备本机录像
	DPSDK_CMD_EXTRA_M_GETOWNLINEINFO,						//获取有权限的线路信息
	DPSDK_CMD_EXTRA_M_GETBUSSCHEDULESINFO,			//获取车辆的排班信息
	DPSDK_CMD_EXTRA_M_GETLASTSTATIONS,						//获取最后到站信息
	DPSDK_CMD_EXTRA_M_NOTITY_SCHEDULE_CHENGED,	//排班信息修改通知
	DPSDK_CMD_EXTRA_M_NOTIFY_SCHEDULESTATE_CHANGED,	//排班状态修改通知
	DPSDK_CMD_EXTRA_M_GETDRIVERMOBILENUMBER,		// 获取司机手机号码
	DPSDK_CMD_EXTRA_M_NOTIFY_DISPITCH_INFO,//调度结果信息
	DPSDK_CMD_EXTRA_M_NOTIFY_CUSTARTPATROL,//开始巡更任务
	DPSDK_CMD_EXTRA_M_RELOAD_VIDEO_PATROL_PLAN,//重新加载巡更计划
	DPSDK_CMD_EXTRA_M_NOTIFY_CUUPDATEREPLYFAST,//快速回复
	DPSDK_CMD_EXTRA_M_NOTIFY_CAR_RELATION,		// 车辆关联关系改变通知
	DPSDK_CMD_EXTRA_M_END				= 1100,

	DPSDK_CMD_GBT28181_BEGIN			= 1101,
	DPSDK_CMD_GBT28181_ADJUST_TIME,
	DPSDK_CMD_GBT28181_GET_DEVICE_STATUS,
	DPSDK_CMD_GBT28181_GET_DEVICE_INFO,
	DPSDK_CMD_GBT28181_START_MANUAL_RECORD,
	DPSDK_CMD_GBT28181_STOP_MANUAL_RECORD,
	DPSDK_CMD_GBT28181_DEVICE_RECOVERY,
	DPSDK_CMD_GBT28181_STOP_RECOVERY,
	DPSDK_CMD_GBT28181_DEVICE_ALARM_RESET,
	DPSDK_CMD_GBT28181_DEVICE_REBOOT,
	DPSDK_CMD_GBT28181_DEVICE_ALARM_NOTIFY,
	DPSDK_CMD_GBT28181_GET_DECODER_DEVICE_STATUS,
	DPSDK_CMD_GBT28181_GET_DECODER_DEVICE_INFO,
	DPSDK_CMD_GBT28181_DECODER_DEVICE_REBOOT,
	DPSDK_CMD_GBT28181_END				= 1200,

	DPSDK_CMD_SERVER_INFO_BEGIN			= 1201,
	DPSDK_CMD_SERVER_INFO_QUERY_SERVER_LIST,
	DPSDK_CMD_SERVER_INFO_QUERY_CMS,
	DPSDK_CMD_SERVER_INFO_QUERY_DMS,
	DPSDK_CMD_SERVER_INFO_QUERY_ADS,
	DPSDK_CMD_SERVER_INFO_QUERY_MTS,
	DPSDK_CMD_SERVER_INFO_QUERY_SS,
	DPSDK_CMD_SERVER_INFO_QUERY_VMS,
	DPSDK_CMD_SERVER_INFO_QUERY_PTS,
	DPSDK_CMD_SERVER_INFO_QUERY_PCS,
	DPSDK_CMD_SERVER_INFO_RESTRART,
	DPSDK_CMD_SERVER_INFO_REPORT_STATUS,
	DPSDK_CMD_SERVER_INFO_END			= 1300,

	DPSDK_CMD_SNVD_BEGIN				= 1301,
	DPSDK_CMD_SNVD_REGISTR_CMS,
	DPSDK_CMD_SNVD_CMS_CLOSE,
	DPSDK_CMD_SNVD_MATRIX_CONTROL,
	DPSDK_CMD_SNVD_MATRIX_PORT_CONTROL,
	DPSDK_CMD_SNVD_END					= 1400,

	//add by jyl
	DPSDK_CMD_PRISON_BEGIN				= 1401,
	DPSDK_CMD_PRISON_SYNCTIME,                   // 时间同步
	DPSDK_CMD_PRISON_INTEPERINFO,      			 // 审讯人员信息获取
	DPSDK_CMD_PRISON_INTECASEINFO,     			 // 审讯信息
	DPSDK_CMD_PRISON_SAVEINFO,         			 // 保存案件人信息
	DPSDK_CMD_PRISON_SAVEINTEINFO,     			 // 保存审讯信息
	DPSDK_CMD_PRISON_SAVECASEINFO,     			 // 保存案件信息
	DPSDK_CMD_PRISON_DOWNLOADELC,      			 // 下载电子笔记
	DPSDK_CMD_PRISON_GENERALMS,        			 // 通用消息
	DPSDK_CMD_PRISON_GETINTERLABINFO,  			 // 获得审讯标签信息
	DPSDK_CMD_PRISON_GETINTERUSERGRO,            // 获取审讯用户组
	DPSDK_CMD_PRISON_GETSINGCASEINFO,            // 获取单个案例信息
	DPSDK_CMD_PRISON_LASTEINTERSEQ,              // 最近审讯请求
	DPSDK_CMD_PRISON_NOTETEMPLATE,               // 电子模板
	DPSDK_CMD_PRISON_COMMSENTENCE,               // 一般判决
	DPSDK_CMD_PRISON_NOTIFYALL,                  // 所有通报
	DPSDK_CMD_PRISON_LOGININTERROGATION,         // 登录审讯室
	DPSDK_CMD_PRISON_GETNOTETEMPLIST,            // 获得电子模版
	DPSDK_CMD_PRISON_QUERYTAG,					 // 卷宗查询(重点标签)
	DPSDK_CMD_PRISON_ADDTRIALTAG,				 // 审讯打标
	DPSDK_CMD_PRISON_SXFTP,						 // 审讯FTP上传下载

	DPSDK_CMD_PRISON_GETDEVBURNERINFO,			 // 获取刻录主机信息
	DPSDK_CMD_PRISON_SETDEVBURNERHEADER,		 // 设置刻录片头设置
	DPSDK_CMD_PRISON_CONTROLDEVBURNER,			 // 控制刻录主机
	DPSDK_CMD_PRISON_GETBURNERCDSTATE,			 // 获取刻录实时状态信息
	DPSDK_CMD_PRISON_GETENCODEPLAN,				 // 获取编码计划
	DPSDK_CMD_PRISON_SETENCODEPLAN,				 // 设置编码计划
	DPSDK_CMD_PRISON_SETBURNRECORDFORMAT,		 // 刻录格式设置
	DPSDK_CMD_PRISON_BRUNSTATUS_NOTIFY,			 // 刻录状态主动通知
	DPSDK_CMD_PRISON_SAVEBURNPARAM,				 // 保存刻录参数
	DPSDK_CMD_PRISON_QUERYBURNPARAM,			 // 查询刻录参数
	DPSDK_CMD_PRISON_VOICE_IMPEL,				 // 语音激励
	DPSDK_CMD_PRISON_DVD_CONTROL,				 // DVD控制
	DPSDK_CMD_PRISON_SETCOMBINEDSCREEN,			 // 设置组合屏信息
	DPSDK_CMD_PRISON_GETCOMBINEDSCREEN,			 // 获取组合屏信息
	DPSDK_CMD_PRISON_MANAGEBROADCAST_NOTIFY,	 // 播控管理消息通知
	DPSDK_CMD_PRISON_COURTSNAP,					 // 请求庭审抓图
	DPSDK_CMD_PRISON_SETMATRIX,					 // 设置矩阵信息
	DPSDK_CMD_PRISON_RESETMATRIX,				 // 还原矩阵信息
	DPSDK_CMD_PRISON_CONTROLLIVE,				 // 禁止/允许直播控制
	DPSDK_CMD_PRISON_VOICEBROADCAST,			 // 请求语音播报

	DPSDK_CMD_PRISON_DElETETRIALTAG,			 // 删除标签
	
	DPSDK_CMD_NOTIFY_BEGIN_HANDLE_CASE		    = 1447,      //开始办案
	DPSDK_CMD_NOTIFY_END_HANDLE_CASE			= 1448,	    //结束办案
	DPSDK_CMD_NOTIFY_RELOAD_INTERROGATION				= 1449,		//重新读取审讯信息
	DPSDK_CMD_PRISON_UPLOADFILEBURNED,			// 附件上传
	DPSDK_CMD_PRISON_QUERYBURNERDEVINFO,		// 查询光盘信息-新
	DPSDK_CMD_PRISON_GETDISKINFO,				// 获取设备磁盘容量
	DPSDK_CMD_PRISON_CONTROLBACKUP=1454,				//备份控制
	DPSDK_CMD_PRISON_END				= 1500,
	//end by jyl

	DPSDK_CMD_EXTRA_A_BEGIN				= 1501,
	DPSDK_CMD_GET_ORG_TREE,						// 获取业务组织
	DPSDK_CMD_NOTIFY_ORG_TREE,					// 通知业务组织变更
	DPSDK_CMD_GET_ALL_DOMAIN_INFO,				// 获取全部域信息
	DPSDK_CMD_NOTIFY_ALL_DOMAIN_INFO,			// 通知域信息变更
	DPSDK_CMD_NOTIFY_DOMAIN_STATUS,				// 通知域状态变更
	DPSDK_CMD_GET_USERCAMERAID,					// 获取视频资源绑定
	DPSDK_CMD_NOTIFY_RELATION,					// 通知视频资源变更
	DPSDK_CMD_TO_CU,							// 对讲交互
	DPSDK_CMD_TALK_LOG,							// 对讲日志
	DPSDK_CMD_SHARE_RTSPURL,					// 分享RTSP
	DPSDK_CMD_NOTIFY_RTSPURL,					// 通知RTSP
	DPSDK_CMD_PLAY_RTSPURL,						// 播放RTSP
	DPSDK_CMD_TEARDOWN_RTSPURL,					// 断开RTSP
	DPSDK_CMD_GET_MENUTOOL,						// 获取菜单导航
	DPSDK_CMD_GET_NEWS,							// 获取新闻
	DPSDK_CMD_NOTIFY_NEWS,						// 新闻通知
	DPSDK_CMD_NOTIFY_MOD_NAVIGATION,            // 通知修改导航栏
	DPSDK_CMD_EXTRA_A_END				= 1600,

	//add by djm 20131025 报警运营平台增加
	DPSDK_CMD_ALARM_BUSINESS_BEGIN      = 1601,
	DPSDK_CMD_CHN_ALARMTYPE_QUERY,              // 报警类型查询
	DPSDK_CMD_ALARM_HOST_CONTROL,				// 报警主机控制 add by minjie 2013-11-29
	DPSDK_CMD_CUSTOMERINFO_QUERY,				// 客户资料(联系方式)查询
	DPSDK_CMD_CUSTOMERINFO_NOTIFY,				// 客户资料(及联系方式)增删改通知
	DPSDK_CMD_VIDEOALARMHOST_QUERY,				// 视频报警主机查询
	DPSDK_CMD_VIDEOALARM_QUERY,					// 视频报警主机报警查询
	DPSDK_CMD_REPORT_ALARMHOST_STATUS,			// DMS 报警主机布防、撤防、旁路与取消旁路状态上报 add by zxb 12-4-2013
	DPSDK_CMD_DEFENDCUSTOMER_QUERY,				// 布撤防客户查询
	DPSDK_CMD_ONLINECUSTOMER_QUERY,				// 在线离线客户查询
	DPSDK_CMD_SERVICETIMEOUT_NOTIFY,			// 保险-服务到期提醒
	DPSDK_CMD_VIDEOALARMCOUNT_QUERY,			// 报警查询总数添加
	DPSDK_CMD_QUERY_ALARMREDEAL_TIME,			// 获取二次处理时间间隔
	DPSDK_CMD_SENDMESSAGE,						// 短信发送
	DPSDK_CMD_QUERY_ONLNEUSER_BY_ROLE,			// 查询同角色在线用户
	DPSDK_CMD_WRITE_CASE_INFO,					// 立案信息写入
	DPSDK_CMD_QUERY_110_ONLINEUSER_ROLE,		// 查询110用户列表
	DPSDK_CMD_QUERY_ALL_USERS,					// 查询所有用户列表
	DPSDK_CMD_UPLOAD_LOG_ONDUTY,				// 上传值班日志信息
	DPSDK_CMD_QUERY_USER_DUTY_LOGIN,			// 查询用户签入or签出
	DPSDK_CMD_VIDEOALARM_QUERY_NEW,				// 视频报警主机报警查询
	DPSDK_CMD_VIDEOALARMCOUNT_QUERY_NEW,		// 报警查询总数添加
	DPSDK_CMD_PHONE_SUBSCRIBE_ALARM,			// 手机订阅报警
	DPSDK_CMD_UPLOAD_LOG_QUERRY,				// 报警运营-查询当值人员交接班日志
	// 报警运营-重点区域进出记录--START
	DPSDK_CMD_SENSITIVE_REC_UPLOAD,				// 上传/更新
	DPSDK_CMD_SENSITIVE_REC_QUERRY,				// 查询
	// 报警运营-上传重点区域进出记录--START
	DPSDK_CMD_ALARM_BUSINESS_END		= 1700,
	//end by djm 
	
	DPSDK_CMD_FACE_MANAGE_BEGIN			= 1701,				
	DPSDK_CMD_EXTRACT_FACEPIC,					// 通过大图获取人脸图片
	DPSDK_CMD_OPERATE_FACE_LIB,					// 添加/修改/删除 人脸识别布控（黑白名单）
	DPSDK_CMD_QUERY_FACE_COUNT,					// 查询匹配的人脸数量(黑白名单，历史库)
	DPSDK_CMD_QUERY_FACE_DATA,					// 请求具体匹配数据(黑白名单，历史库)
	DPSDK_CMD_STOP_FACE_QUERY,					// 停止当前人脸库查询会话
	DPSDK_CMD_QUERY_IVSFALARM_COUNT,			// 查询人脸报警数量
	DPSDK_CMD_QUERY_IVSFALARM_DATA,				// 请求人脸报警具体数据
	DPSDK_CMD_STOP_IVSFALARM_QUERY,				// 停止人脸报警查询会话
	DPSDK_CMD_GET_IVSFALARM_PIC,				// 获取人脸报警指定的全景图片
	DPSDK_CMD_GET_IVSFPIC_BYURL,				// 通过URL获取图片
	DPSDK_CMD_NOTIFY_QUERYPROGRESS,				// 上报查询进度
	DPSDK_CMD_RECONGNITION_ATTENDANCE,			// 添加/修改/删除 人脸识别布控（黑白名单）
	DPSDK_CMD_FACE_MANAGE_END			= 1800,
	
	DPSDK_CMD_DIAGNOSE_BEGIN			= 1801,
	DPSDK_CMD_QUERY_DAIGNOSECOUNT,				// 查询视频质量诊断异常数
	DPSDK_CMD_GET_DIAGNOSEDATE,					// 获取视频质量诊断异常结果
	DPSDK_CMD_STOP_DIAGNOSE,					// 停止获取结果
	DPSDK_CMD_QUERY_DIAGNOSECHN_DATE,			// 查询通道视频诊断结果
	DPSDK_CMD_QUERY_DIAGNOSECHN_COUNT,			// 查询通道历史诊断数
	DPSDK_CMD_GET_DIAGNOSECHN_DATE,				// 获取通道诊断结果
	DPSDK_CMD_STOP_DIAGNOSECHN,					// 停止获取通道结果
	DPSDK_CMD_DIAGNOSE_END				= 1900,
	
	DPSDK_CMD_REPORT_IVSPC_BEGIN		= 1901,
	DPSDK_CMD_REPORT_IVSPC_COUNT,				// 上报IVS-PC人数按组统计
	DPSDK_CMD_GET_IVSPC_COUNT,					// 查询IVS-PC人数按组统计
	DPSDK_CMD_REPORT_IVSPC_END			= 1904,

	DPSDK_CMD_POWERENERGY_BEGIN			= 2000,
	//DPSDK_CMD_QUERY_DATACOUNT,				// 获取查询数据数量
	//DPSDK_CMD_QUERY_HISTORY_DATA,				// 获取仪表历史信息
	//DPSDK_CMD_STOP_QUERY,						// 停止获取数据
	DPSDK_CMD_POWERENERGY_DATAREPORT,			// 动环实时数据上报
	//DPSDK_CMD_POWERENERGY_DATAREPOET_NVS,		// NVS动环实时数据上报DMS->CU

	DPSDK_CMD_POWENERGY_PES_ACTIVE_BEGIN,		// cu->pes 动环控制命令走pes
	DPSDK_CMD_POWERENERGY_CONTROL,				// 动环开关控制
	DPSDK_CMD_POWERENERGY_GETSTATUS,			// 获取动环当前开或者关的状态
	DPSDK_CMD_POWENERGY_PES_ACTIVE_END,			//
	DPSDK_CMD_POWERENERGY_QUERY_PIC,			// 查询动环图片
	DPSDK_CMD_POWERENERGY_DATA_COUNT,			// 查询动环历史数据数量
	DPSDK_CMD_POWERENERGY_HISTORY_DATA,			// 查询动环历史数据CU->CMS
	DPSDK_CMD_POWERENERGY_END			= 3000,

	DPSDK_CMD_SCS_BEGIN					= 3001,
	DPSDK_CMD_SCS_LOGIN,						// 登录Scs平台
	DPSDK_CMD_START_CALL,						// 发起呼叫
	DPSDK_CMD_STOP_CALL,						// 停止呼叫
	DPSDK_CMD_CEASE_CALL,						// 释放呼叫
	DPSDK_CMD_INVITE_CALL,						// 呼叫邀请
	DPSDK_CMD_BYE_CALL,							// 呼叫被中断
	DPSDK_CMD_MODIFY_CALL_STATUS,				// 修改呼叫状态
	DPSDK_CMD_CALL_EXPECTION,					// 呼叫异常
	DPSDK_CMD_CALL_INVITE_NOTIFY,				// 接收呼叫通知
	DPSDK_CMD_CALL_STOP_NOTIFY,					// 呼叫挂断通知
	DPSDK_CMD_SCS_MESSAGE_NOTIFY,				// 接收SCS服务的主动通知
	DPSDK_CMD_SCS_MESSAGE_TEXT,					// 发送文字
	DPSDK_CMD_SCS_TEXT_NOTIFY,					// 接收SCS服务文字

	DPSDK_CMD_START_VT_CALL,					// 可视对讲发起呼叫
	DPSDK_CMD_STOP_VT_CALL,						// 可视对讲停止呼叫
	DPSDK_CMD_BUSY_VT_CALL,						// 可视对讲呼叫繁忙
	DPSDK_CMD_CANCEL_VT_CALL,					// 主叫方取消呼叫
	DPSDK_CMD_REJECT_VT_CALL,					// 被叫方拒绝呼叫
	DPSDK_CMD_CEASE_VT_CALL,					// 释放可视对讲呼叫
	DPSDK_CMD_INVITE_VT_CALL,					// 可视对讲呼叫邀请
	DPSDK_CMD_BYE_VT_CALL,						// 可视对讲呼叫被中断
	DPSDK_CMD_MODIFY_VT_CALL_STATUS,			// 可视对讲修改呼叫状态
	DPSDK_CMD_VT_CALL_EXPECTION,				// 可视对讲呼叫异常
	DPSDK_CMD_VT_CALL_INVITE_NOTIFY,			// 可视对讲接收呼叫通知
	DPSDK_CMD_VT_CALL_STOP_NOTIFY,				// 呼叫挂断通知
	DPSDK_CMD_VT_CALL_MESSAGE,					// 信息分发和快递通知

	DPSDK_CMD_RING_CALL,						// 发送响铃
	DPSDK_CMD_RING_NOTIFY,						// 响铃通知
	DPSDK_CMD_SCS_LOGOUT				= 3030,	// 登出	
	DPSDK_CMD_SCS_APP_NOTIFY			= 3031, // 发给APP的通知消息
	DPSDK_CMD_SCS_END					= 3100,			

	DPSDK_CMD_MESSAGE_NEW_ORG_BEGIN		= 3101,
	DPSDK_CMD_MESSAGE_GET_ALL_ORG_TREE,			// 加载组织树
	DPSDK_CMD_MESSAGE_ADD_ORG,					// 增加组织节点
	DPSDK_CMD_MESSAGE_MODIFY_ORG,				// 修改组织节点
	DPSDK_CMD_MESSAGE_DELETE_ORG,				// 删除组织节点
	DPSDK_CMD_MESSAGE_GET_DEVICE_INFO,			// 获取设备信息
	DPSDK_CMD_MESSAGE_ADD_DEVICE,				// 增加设备
	DPSDK_CMD_MESSAGE_MODIFY_DEVICE,			// 修改设备
	DPSDK_CMD_MESSAGE_DELETE_DEVICE,			// 删除设备
	DPSDK_CMD_MESSAGE_USER_ROLE_CHANGED,		// 用户角色变更
	DPSDK_CMD_MESSAGE_ROLE_ORG_CHANGED,			// 角色组织变更
	DPSDK_CMD_MESSAGE_LOGIC_ORG_CHANGED,		// 逻辑组织变更
	DPSDK_CMD_MESSAGE_CHANNEL_RIGHT_CHANGED,	// 通道权限变更
	DPSDK_CMD_MESSAGE_CODEINFO_CHANGED,			// 节点<通道或设备>所属组织及排序变更
	DPSDK_CMD_MESSAGE_GETGROUP_SNAPSHOT,		// 获取组织快照
	DPSDK_CMD_MESSAGE_GETDEVICE_DETAIL,			// 获取设备详细信息
	DPSDK_CMD_MESSAGE_GETORG_DETAIL,			// 获取组织详细信息

	DPSDK_CMD_MESSAGE_NEW_ORG_END		=3200,	

	//IP对讲 add by huwenjuan
	DPSDK_CMD_IPTALK_BEGIN				= 3201,		
	DPSDK_CMD_IPTALK_INVITE				= 3202,		// 设备发起对讲
	DPSDK_CMD_IPTALK_HANGUP				= 3203,		// 设备挂断对讲
	DPSDK_CMD_IPTALK_IGNORE             = 3204,     // 忽略对讲
	DPSDK_CMD_IPTALK_END				= 3300,

	DPSDK_CMD_GENERAL_EXTRA_BEGIN		= 4101,
	DPSDK_CMD_MODIFY_LOGO				= 4102,		// 修改图标通知
	DPSDK_CMD_MODIFY_MENURIGHT			= 4103,		// 客户端模块权限修改
	DPSDK_CMD_GET_CHNLID_BY_SITE_CODE	= 4104,		// 浙江华立通信集团有限公司：通过工地号获取通道ID
	DPSDK_CMD_CONNECT_TO_SCS			= 4106,		// 连接SCS
	DPSDK_CMD_WEB_PORT_CHANGE_NOTIFY	= 4107,		// 通知客户端web端口改变
	DPSDK_CMD_GENERAL_EXTRA_END			= 4200,

	DPSDK_CMD_END						= 5000,		
}dpsdk_cmd_e;

//消息错误码(DPSDK 区间5001-7000.),用于消息回调中判断
typedef enum
{

	//<0 同步返回错误
	DPSDK_RET_SYNC_FAIL					= -1,
	
	DPSDK_RET_SUCCESS					= 0,			// 成功																   
	DPSDK_RET_SERIALIZE_PDU_FAILED,						// 协议解析失败
	DPSDK_RET_SENDDATA_FAILED,							// 数据发送失败
	DPSDK_RET_NET_CONNECT_FAILED,						// 连接远端失败
	DPSDK_RET_ALREADY_LOGIN,							// 登录已存在
	DPSDK_RET_ALREADY_LOGOUT,							// 已登出
	DPSDK_RET_SERIALIZE_XML_FAILED,						// Xml解析失败
	DPSDK_RET_NODE_NO_RIGHT,							// 无操作权限	
	DPSDK_RET_UNKNOW_DEVICE,							// 未知设备
	DPSDK_RET_UNKNOW_CHANNEL,							// 未知通道
	DPSDK_RET_DEVICE_OFFLINE,							// 设备离线
	DPSDK_RET_RTSP_CONNECT_FAILED,						// rtsp连接失败
	DPSDK_RET_RTP_LISTEN_FAILED,						// rtp监听失败
	DPSDK_RET_RTP_CONNECT_FAILED,						// rtp连接失败
	DPSDK_RET_PARSE_TRANSPORT_FAILED,					// rtsp解析端口失败
	DPSDK_RET_ALREADY_CANCELED,							// 命令已被取消
	DPSDK_RET_UNKNOWN_SESSION,							// 无效的session fixme:检查已有情况统一为此应答
	//talk相关									   
	DPSDK_RET_TALK_INNVALIDPARAM,						// 对讲参数有误
	DPSDK_RET_TALK_NOT_SUPPORT,							// 对讲不支持									   
	DPSDK_RET_DMSSESSION_NOT_FOUND,						// 没找到对应的dmsSession
	//alarm相关									   
	DPSDK_RET_ADSSESSION_NOT_FOUND,						// 未找到ADS
	DPSDK_RET_ADSSESSION_NOT_LOGIN,						// 未登录成功ADS
	DPSDK_RET_DATABASE_NO_RECORD,						// 没有找到ALARM相关记录
	DPSDK_RET_ALARMTYPE_NOT_MATCH,						// 报警类型不匹配
	
	//回放										   
	DPSDK_RET_PLAYBACK_SESSION_NOT_FOUND,				// 无法找到回放会话
	DPSDK_RET_PLAYBACK_UNKNOW_PLAYTYPE,					// 无法区分播放类型
	DPSDK_RET_PLAYBACK_NETSDK_SEEK_FAIL,				// 网络SDK的seek命令失败
	DPSDK_RET_PLAYBACK_SEEK_SIZE_ERROR,					// 回放定位的size错误
	DPSDK_RET_PLAYBACK_SEEK_TIME_ERROR,					// 回放定位的时间错误
	DPSDK_RET_PLAYBACK_DEVICE_NOT_FOUND,				// 回放时没有找到想要的设备
	DPSDK_RET_PLAYBACK_PLAY_REPEAT,						// 该通道只允许回放一路
	DPSDK_RET_INVALID_CONFIGTYPE,						// 该配置信息的类型不支持
	DPSDK_RET_UNSUPPORTED_STREAM,						// 该码流类型不支持
	DPSDK_RET_PLAYBACK_NOTFIND_DEV,						// 设备信息未找到
	DPSDK_RET_PLAYBACK_PARAM,							// 回放参数错误
	DPSDK_RET_PLAYBACK_PARAM_CAMERA,					// 回放未知摄像头
	DPSDK_RET_FTPSERVER_NOT_FIND,						// FTP服务器没找到
	DPSDK_RET_FTPCURL_ERROR,							// 调用curl返回错误
	DPSDK_RET_FTPCURL_LOCALFILE_NOT_OPEN,				// 调用curl返回未找到本地文件
	DPSDK_RET_FTPCURL_LOCALFILE_NOT_READ,				// 调用curl返回打开本地文件出错
	DPSDK_RET_FTPCURL_FTPFILE_ERROR,					// 调用curl返回操作远程文件出错
	DPSDK_RET_FTPCURL_FREE_ERROR,						// 调用curl返回释放出错
	DPSDK_RET_PCS_ERROR,                        		// PCS发生错误
	DPSDK_RET_PES_ERROR,                        		// PES发生错误
	DPSDK_RET_PES_NOT_LOGIN,							// 未登陆到PES
	DPSDK_RET_PES_ENCODE_AHSOTCMD_FAILED,       		// 报警主机命令组包失败
	DPSDK_RET_PES_ENCODE_DCTRL_FAILED,          		// 门禁命令组包失败
	DPSDK_RET_PES_ENCODE_PGRID_FAILED,          		// 电网命令组包失败

	DPSDK_RET_CHANNEL_EMPTY,							// 通道号为空
	DPSDK_RET_MSG_EMPTY,								// 处理消息为空
	DPSDK_RET_MSG_INVALID_CMD,							// 未定义的消息操作
	DPSDK_RET_DECODE_PDU_FAILED,						// 协议解析失败
	DPSDK_RET_SENDDATA_EMPTY,							// 发送数据为空
	DPSDK_RET_PESSESSION_NOT_FOUND,						// 没找到对应的pesSession
	DPSDK_RET_ALARMREPORT_NEW_FAILED,					// 报警消息中内存申请失败
	DPSDK_RET_PCS_NOT_LOGIN,							// 未登陆到PCS
	DPSDK_RET_RTSPMDL_NOT_FIND,							// 没找到对应的RTSPMDL
	DPSDK_RET_RTSPMSG_INVALID_CMD,						// 未定义的RTSP消息操作
	DPSDK_RET_LOAD_XML,									// 解析Xml失败
	
	//配置模块ex
	DPSDK_RET_CONFIGEX_LOGIN_FAIL,						// 设备登陆失败
	DPSDK_RET_CONFIGEX_LOGINOUT_FAIL,					// 设备登出失败

	//返回netsdk的错误
	DPSDK_RET_NETSDK_ERROR,
	DPSDK_RET_DEVCONFIG_STRUCT_UNABLE_OPERATOR,			// 该结构不支持该操作,e.g.某个结构体不支持get操作(或者set操作)
	DPSDK_RET_LOCAL_INVALID_USERNAME,
	DPSDK_RET_LOCAL_INVALID_PASSWORD,

	//服务返回错误未定义
	DPSDK_RET_CMS_RET_ERROR,
	DPSDK_RET_DMS_RET_ERROR,
	DPSDK_RET_PCS_RET_ERROR,
	DPSDK_RET_RTSP_RET_ERROR,
	
	DPSDK_RET_ADSCOMFIRM_FAIL,							// 报警处理失败

	DPSDK_RET_CMS_ERR_NOT_FOUND,
	DPSDK_RET_NO_FOUND_MGW,								// 无可用的MGW服务
	DPSDK_RET_ALARM_TRANSFER_FAILED,					// 报警转移失败
	DPSDK_RET_LOAD_JSON_FAILED,							// 解析Json失败
	DPSDK_RET_ERROR_EXCEED_PLAYBACK_LIMT = 592,			//请求回放次数超过配置权限次数
	DPSDK_RET_END						 = 5000,

	// CMS返回开始，不做返回值判断
	SERVER_RET_CMS_ERR_BEGIN            = DSS_ERROR_CODE_BASE,
	SERVER_RET_CMS_ERR_QUERY_PU_SUCCESS,				// 查询全部录像时,只有前端查询成功
	SERVER_RET_CMS_ERR_QUERY_CENTER_SUCCESS,			// 查询全部录像时,只有中心查询成功
	
	// CMS客户端协议返回开始，不做返回值判断
	SERVER_RET_CMS_CLIENT_ERROR_BEGIN   = SERVER_RET_CMS_ERR_BEGIN + CLIENT_ERROR_BASE,
	SERVER_RET_CMS_ERR_NO_USER_ID,						// 用户ID不存在
	SERVER_RET_CMS_ERR_NO_USER_NAME_TO_ID,				// 该用户名匹配不到ID
	SERVER_RET_CMS_ERR_NO_USER_NAME,					// 用户名不存在
	SERVER_RET_CMS_ERR_PASSWORD_INVALID,				// 密码无效
	SERVER_RET_CMS_ERR_INVALID_USER_ID,					// 无效的用户ID
	SERVER_RET_CMS_ERR_USER_LOCKED,						// 用户被锁定
	SERVER_RET_CMS_ERR_SESSION_EXIST,					// 用户已经存在登录会话
	SERVER_RET_CMS_ERR_NO_SESSION,						// 会话不存在
	SERVER_RET_CMS_ERR_SERVER_REGISTERED,				// 服务已经注册
	SERVER_RET_CMS_ERR_SERVER_NOT_REGISTER,				// 功能服务没有注册
	SERVER_RET_CMS_ERR_INVALID_CAMERA_ID,				// 摄像头id无效
	SERVER_RET_CMS_ERR_NO_DEVICE,						// 找不到设备
	SERVER_RET_CMS_ERR_MEDIA_SESSION_EXIST,				// 媒体会话已存在
	SERVER_RET_CMS_ERR_GRANT_SESSION_EXIST,				// 授权会话已存在
	SERVER_RET_CMS_ERR_NO_CAMERA_ROW,					// 找不到摄像头表
	SERVER_RET_CMS_ERR_UNKNOWN_TYPE,					// 无效的类型值
	SERVER_RET_CMS_ERR_TOO_MANY_GROUP_COUNT,			// 用户从属的组太多
	SERVER_RET_CMS_ERR_TOO_MANY,						// 数量太多
	SERVER_RET_CMS_ERR_EXIST_HIGH_USER,					// 存在高级别用户 add by fengjian 2012.8.8
	SERVER_RET_CMS_ERR_REACH_SESSION_LIMIT,				// 用户并发登陆数达到上限 
	SERVER_RET_CMS_ERR_USER_TIMEOUT,					// 用户已过期
	SERVER_RET_CMS_ERR_INVALID_MAC_ADDR,				// 无效的MAC地
	SERVER_RET_CMS_ERR_UNAUTHORIZED,					// 需要加密认证
	SERVER_RET_CMS_ERR_INVALID_CU_VERSION,				// 客户端版本错误
	SERVER_RET_CMS_ERR_INVALID_PHONE_NUM,				// 无效的手机号码
	SERVER_RET_CMS_ERR_PASSWORD_LOCKED,					// 密码被锁定（暂时不能登陆，会自动解锁）
	SERVER_RET_CMS_ERR_INVALID_IP = SERVER_RET_CMS_CLIENT_ERROR_BEGIN + 28,				// 无效的IP地址
	SERVER_RET_CMS_ERR_IP_ADDR_NOT_IN_LIST = SERVER_RET_CMS_CLIENT_ERROR_BEGIN + 41,	//IP地址不在白名单内

	SERVER_RET_CMS_CLIENT_ERROR_END = SERVER_RET_CMS_ERR_BEGIN + CLIENT_ERROR_BASE + 100,

	// CMS服务协议返回开始，不做返回值判断
	SERVER_RET_CMS_SERVER_ERROR_BEGIN   = SERVER_RET_CMS_ERR_BEGIN + SERVER_ERROR_BASE,
	SERVER_RET_CMS_ERR_NO_CONNECTION,					// 连接不存在
	SERVER_RET_CMS_ERR_INVALID_SERVER,					// 未在系统中登记的服务
	SERVER_RET_CMS_ERR_NO_DOMAIN,						// 服务域不存在
	SERVER_RET_CMS_ERR_NO_SERVER_BEAN,					// 服务对象不存在
	SERVER_RET_CMS_ERR_NO_MTS_TO_USE,					// 没有MTS可用
	SERVER_RET_CMS_ERR_SESSION_DELETE,					// 会话已经拆除
	SERVER_RET_CMS_ERR_SERVER_RECONNECT,				// 功能服务正在重连
	SERVER_RET_CMS_ERR_ADD_CAMERA_FAILED,				// 添加摄像头失败
	SERVER_RET_CMS_ERR_ADD_CLIENT_FAILED,				// 添加客户端失败
	SERVER_RET_CMS_ERR_DATABASE_ACCESS_FAILED,			// 数据库访问失败
	SERVER_RET_CMS_ERR_DATABASE_NO_RECORD,				// 数据库没有记录
	SERVER_RET_CMS_ERR_DATA_TOO_LONG,					// 数据太长了
	SERVER_RET_CMS_ERR_NO_GROUPS_OF_USER,				// 没有找到用户所从属的组
	SERVER_RET_CMS_ERR_QUERY_RECORD_FAILED,				// 查询录像失败
	SERVER_RET_CMS_ERR_OTHER_USER_PLAYBACK,				// 其他用户在回放该摄像头
	SERVER_RET_CMS_ERR_REACH_PU_PLAYBACK_LIMIT,			// 达到前端回放地限制
	SERVER_RET_CMS_ERR_NO_DMS_TO_USE,					// 没有DMS可用
	SERVER_RET_CMS_ERR_DEV_GRANT_CHANGED,				// 设备授权更改到其他服务
	SERVER_RET_CMS_ERR_ADD_DVR_FAILED,					// 添加DVR失败
	SERVER_RET_CMS_ERR_GRANT_FAILED,					// 授权到DMS失败
	SERVER_RET_CMS_ERR_SS_PLAYBACK_FAILED,				// SS回放失败
	SERVER_RET_CMS_ERR_REACH_SYSTEM_LIMIT,				// 达到系统上限
	SERVER_RET_CMS_ERR_INVALID_DEVICE_PROVIDER,			// 无效的设备厂家
	SERVER_RET_CMS_ERR_NO_URL,							// 没有升级URL
	SERVER_RET_CMS_ERR_NO_SS_TO_USE,					// 没有SS可用
	SERVER_RET_CMS_ERR_PU_QUERY_TIMEOUT,				// 前端查询超时
	SERVER_RET_CMS_ERR_PU_QUERY_RECORD_FAILED,			// 前端查询录像失败
	SERVER_RET_CMS_ERR_NO_MTS_FOR_DEVICE,				// 没有和这个设备管理的MTS
	SERVER_RET_CMS_ERR_DEVICE_IN_TALKING,				// 设备正在进行语音对讲
	SERVER_RET_CMS_ERR_DEVICE_NOT_TALKING,				// 设备没有在进行语音对讲
	SERVER_RET_CMS_ERR_ENCODE_PDU,						// CMS在准备应答时候，进行Encode操作失败
	SERVER_RET_CMS_ERR_DECODE_PDU,						// CMS在准备应答时候，进行Decode操作失败
	SERVER_RET_CMS_ERR_NOT_FOUND_LOWER_DOMAIN,			// 没有找到下级域
	SERVER_RET_CMS_ERR_NOT_LOGIN_LOWER_DOMAIN,			// 未登陆下级域
	SERVER_RET_CMS_ERR_NO_RIGHT,						// 无权限
	SERVER_RET_CMS_ERR_QUERY_ALARM_FAILED,				// 查询报警失败
	SERVER_RET_CMS_ERR_DEIVCE_OFFLINE,					// 设备不在线
	SERVER_RET_CMS_ERR_LOWER_DOMAIN_EXCEPTION,			// 下级域异常
	SERVER_RET_CMS_ERR_ALARM_PRE_RECORD_OPENED,			// 报警预录已经打开
	SERVER_RET_CMS_ERR_RECONNECT_DEVICE,				// 功能服务正在重连设备
	SERVER_RET_CMS_ERR_SEND_FUN_SVR_REQ_FAIL,			// 向功能服务器发送请求失败

//add by fengjian 2012.8.7
    SERVER_RET_CMS_ERR_CU_START_RECORD_FAIL,
	SERVER_RET_CMS_ERR_CU_RECORING_NOW,
	SERVER_RET_CMS_ERR_CU_STOP_RECORD_FAIL,
	SERVER_RET_CMS_ERR_CU_OTHERUSER_RECORDING,
	// 实时录像请求错误码
	SERVER_RET_CMS_ERR_CU_START_RECORD_RUNNING = DSS_ERROR_CODE_BASE + 566,
	SERVER_RET_CMS_ERR_CU_START_RECORD_LIMITE,
	SERVER_RET_CMS_ERR_CU_START_RECORD_NO_SS,
	SERVER_RET_CMS_ERR_NO_PES_TO_USE,					// 没有可用的PES服务器 [2/24/2011 13585]
//add end 
	SERVER_RET_CMS_ERR_UNKNOWN_PROTOCOL,				// 不支持的协议类型
	SERVER_RET_CMS_ERR_CONFIG_FILE_TIMEOUT,				// 组配置文件过期
	SERVER_RET_CMS_ERR_NO_BOLCK,						// 无可用的block
	// CMS返回结束
	SERVER_RET_CMS_ERR_END = SERVER_RET_CMS_ERR_BEGIN + 1000,

	// DMS返回开始，不做返回值判断
	SERVER_RET_DMS_ERR_BEGIN = DSS_ERROR_CODE_BASE + DSS_DMS_BASE,
	// DMS客户端协议返回开始，不做返回值判断
	SERVER_RET_DMS_CLIENT_ERROR_BEGIN = SERVER_RET_DMS_ERR_BEGIN + CLIENT_ERROR_BASE,
	SERVER_RET_DMS_ERR_NO_PRIVILEGE,					// 没有权限
	SERVER_RET_DMS_CLIENT_ERROR_END = SERVER_RET_DMS_ERR_BEGIN + CLIENT_ERROR_BASE + 100,

	// DMS服务协议返回开始，不做返回值判断
	SERVER_RET_DMS_SERVER_ERROR_BEGIN  = SERVER_RET_DMS_ERR_BEGIN + SERVER_ERROR_BASE,
	SERVER_RET_DMS_ERR_PTZ_FAILED,						// 云台内部控制出错
	SERVER_RET_DMS_ERR_CONFIG_SET_FAILED,				// 设备配置内部控制出错
	SERVER_RET_DMS_ERR_CONFIG_GET_FAILED,				// 设备配置内部控制出错
	SERVER_RET_DMS_ERR_CAMERA_OCCUPY,					// 摄像头被其他用户锁定
	SERVER_RET_DMS_ERR_PTZ_ACCESS_FAILED,				// 象云台协商管理模块请求访问失败
	SERVER_RET_DMS_ERR_TCP_COMM_NO_CLIENT,				// 用户连接没有绑定到授权的客户端
	SERVER_RET_DMS_ERR_CLIENT_UNIT_NOT_FOUND,			// 没有找到没有添加过的客户端
	SERVER_RET_DMS_ERR_DEVICE_NOT_FOUND,				// 设备没找到
	SERVER_RET_DMS_ERR_PRIVILEGE_NOT_FOUND,				// 没有找到授权信息
	SERVER_RET_DMS_ERR_UNKNOWN_COMMAND,					// 未知命令
	SERVER_RET_DMS_ERR_OCCUPY_BY_HIGHER_USER,			// 被高级用户占用
	SERVER_RET_DMS_ERR_NORMAL_LOCK_FAILED,				// 需要Server检查的Lock失败错误
	SERVER_RET_DMS_ERR_OCCUPY_BY_OTHER_USER,			// 被其他用户占用
	SERVER_RET_DMS_ERR_NORMAL_UNLOCK_FAILED,			// 需要Server检查的UnLock失败错误
	SERVER_RET_DMS_ERR_NO_DEVICE,
	SERVER_RET_DMS_ERR_NO_RIGHT,
	SERVER_RET_DMS_ERR_NOT_FOUND_LOWER_DOMAIN,
	SERVER_RET_DMS_ERR_NOT_LOGIN_LOWER_DOMAIN,
	SERVER_RET_DMS_ERR_QUERY_DIAGNOSIS_ID,				// 查询视频诊断ID失败
	SERVER_RET_DMS_ERR_QUERY_DIAGNOSIS_TYPE_COUNT,		// 查询视频诊断类型数目失败
	SERVER_RET_DMS_ERR_QUERY_DIAGNOSIS_INFO,			// 查询视频诊断信息失败
	SERVER_RET_DMS_ERR_STOP_QUERY_DIAGNOSIS_INFO,		// 停止视频诊断信息查询失败
	SERVER_RET_DMS_ERR_START_QUERY_PERSON_COUNT,		// 开始查询人数统计信息失败
	SERVER_RET_DMS_ERR_QUERY_PERSON_COUNT,				// 查询人数统计信息失败
	SERVER_RET_DMS_ERR_STOP_QUERY_PERSON_COUNT,			// 停止人数统计信息查询失败
	// DMS返回结束
	SERVER_RET_DMS_ERR_END = SERVER_RET_DMS_ERR_BEGIN + 1000,

	SERVER_RET_VMS_ERR_BEGIN = DSS_ERROR_CODE_BASE + DSS_VMS_BASE,
	// DMS服务协议返回开始，不做返回值判断
	SERVER_RET_VMS_SERVER_ERROR_BEGIN  = SERVER_RET_VMS_ERR_BEGIN + SERVER_ERROR_BASE,
	// 失败-其他原因
	SERVER_RET_VMS_ERR_FAILED = SERVER_RET_VMS_SERVER_ERROR_BEGIN,
	SERVER_RET_VMS_ERR_ID_ALREADY_EXIST,				// NVD ID已存在
	SERVER_RET_VMS_ERR_INVALID_ID,						// 无效的ID
	SERVER_RET_VMS_ERR_REACH_LIMIT,						// 达到上限
	SERVER_RET_VMS_ERR_DEVICE_NOT_SUPPORT,				// 设备不支持
	SERVER_RET_VMS_ERR_CONFIG_TVWALL_FAILED,			// 电视墙配置失败
	SERVER_RET_VMS_ERR_GET_VIRTUAL_CHANNEL_FAILED,		// 获取融合屏虚拟通道失败
	SERVER_RET_VMS_ERR_SCREEN_SPLIT_FAILED,				// 分割操作失败
	SERVER_RET_VMS_ERR_OPEN_WINDOW_FAILED,				// 开窗窗口失败 
	SERVER_RET_VMS_ERR_MOVE_WINDOW_FAILED,				// 窗口移动失败
	SERVER_RET_VMS_ERR_SET_WINDOW_TOP_FAILED,			// 窗口置顶失败
	SERVER_RET_VMS_ERR_CLOSE_WINDOW_FAILED,				// 关闭窗口失败
	SERVER_RET_VMS_ERR_SET_SOURCE_FAILED,				// 设置视频源失败 
	SERVER_RET_VMS_ERR_CLOSE_SOURCE_FAILED,				// 关闭视频源失败
	SERVER_RET_VMS_ERR_GET_SCENE_FAILED,				// 获取场景失败
	SERVER_RET_VMS_ERR_SET_SCENE_FAILED,				// 设置场景失败
	SERVER_RET_VMS_ERR_NETSDK_PACKET_DATA_FAILED,		// 大华netsdk打包数据失败
	SERVER_RET_VMS_ERR_ALARM_OUT_CONTROL_FAILED,		// 报警输出控制失败
	SERVER_RET_VMS_ERR_RESTART_FAILED,					// 设备远程重启失败 
	SERVER_RET_VMS_ERR_QUERY_STATUS_FAILED,				// 设备状态信息查询失败
	SERVER_RET_VMS_ERR_QUERY_SYS_INFO_FAILED,			// 设备系统信息失败
	SERVER_RET_VMS_ERR_TVWALL_LOCKED,					// 电视墙已锁定
	SERVER_RET_VMS_ERR_LOCK_FAILED,						// 电视墙锁定失败
	SERVER_RET_VMS_ERR_DEVICE_OFFLINE,                  //设备离线
	// VMS返回结束
	SERVER_RET_VMS_ERR_END = SERVER_RET_VMS_ERR_BEGIN + 1000,


	SERVER_RET_RTSP_ERR_BEGIN = DSS_ERROR_CODE_BASE + DSS_RTSP_BASE,
	// RTSP服务协议返回开始，不做返回值判断
	SERVER_RET_RTSP_SERVER_ERROR_BEGIN  = SERVER_RET_RTSP_ERR_BEGIN + SERVER_ERROR_BASE,
	SERVER_RET_RTSP_ERR_RECONNECT_DEVICE,				// 正在重连设备
	// RTSP返回结束
	SERVER_RET_RTSP_ERR_END = SERVER_RET_RTSP_ERR_BEGIN + 1000,

	SERVER_RET_ALARM_ERR_BEGIN = DSS_ERROR_CODE_BASE + DSS_ALARM_BASE + DSS_ERROR_BASE,                
	SERVER_RET_ALARM_ERR_URL,
	SERVER_RET_ALARM_ERR_RES,							// 无效的数据
	SERVER_RET_ALARM_ERR_MDL_TYPE,						// 无效的单元类型
	SERVER_RET_ALARM_ERR_SCHEME_INDEX,					// 无效的预案索引
	SERVER_RET_ALARM_ERR_SCHEME_TYPE,					// 无效的预案类型
	SERVER_RET_ALARM_ERR_SCHEME_STRING,					// 预案字符串解析失败
	SERVER_RET_ALARM_ERR_ALARM_NODE,					// 无效的报警节点
	SERVER_RET_ALARM_ERR_TRANSFER_LEADER_OFFLINE,		// 报警转移的组长不在线
	SERVER_RET_ALARM_ERR_TRANSFER_UNKNOW_TYPE,			// 报警转移的参数错误
	SERVER_RET_ALARM_ERR_TRANSFER_NO_SESSION,			// 报警转移网络转发失败
	// ALARM返回结束
	SERVER_RET_ALARM_ERR_END = SERVER_RET_ALARM_ERR_BEGIN + 1000,


	SERVER_RET_MS_ERR_BEGIN = DSS_ERROR_CODE_BASE + DSS_MS_BASE,                
	SERVER_RET_MS_CLIENT_ERROR_BEGIN = SERVER_RET_MS_ERR_BEGIN + CLIENT_ERROR_BASE,
	SERVER_RET_MS_ERR_ALREADY_LOGIN,					// 已经登录
	SERVER_RET_MS_ERR_INVALID_SESSION_ID,				// 无效的会话ID
	SERVER_RET_MS_ERR_NOT_LOGIN,						// 未登录
	SERVER_RET_MS_ERR_INVALID_CONNECTION,				// 无效连接
	SERVER_RET_MS_ERR_INVALID_DEV_TYPE,					// 无效的设备类型
	SERVER_RET_MS_ERR_INVALID_CAMERA_ID,				// 无效的摄像头id
	SERVER_RET_MS_ERR_CAMERA_SESSION_EXIST,				// 摄像头已经添加过
	SERVER_RET_MS_ERR_NO_CAMERA_SESSION,				// 摄像头会话不存在
	SERVER_RET_MS_ERR_FIND_SAME_TOKEN,					// 找到相同的token
	SERVER_RET_MS_ERR_UNKNOWN_RECORD_TYPE,				// 无法识别的录像类型
	SERVER_RET_MS_ERR_INVALID_FILE_NAME,				// 无效的录像文件名称
	SERVER_RET_MS_ERR_INVALID_TIME_VALUE,				// 无效的录像时间值
	SERVER_RET_MS_ERR_NOT_FOUND_SESSION,				// 没有找到会话
	SERVER_RET_MS_ERR_INVALID_RTSP_URL,					// 无效的RTSP URL
	SERVER_RET_MS_ERR_PLAN_EXIST,						// 计划已经存在
	SERVER_RET_MS_CLIENT_ERROR_END = SERVER_RET_MS_CLIENT_ERROR_BEGIN + 100,

	SERVER_RET_MS_SERVER_ERROR_BEGIN = SERVER_RET_MS_ERR_BEGIN + SERVER_ERROR_BASE,
	SERVER_RET_MS_ERR_DEV_NOT_LOGIN,					// 设备还未登录
	SERVER_RET_MS_ERR_SDK_OPERATE_FAILED,				// sdk调用失败
	SERVER_RET_MS_ERR_SESSION_USE_OUT,					// 会话用完
	SERVER_RET_MS_ERR_RTSP_CONNECT_FAILED,				// rtsp连接失败
	SERVER_RET_MS_ERR_RTP_LISTEN_FAILED,				// RTP侦听失败
	SERVER_RET_MS_ERR_RTSP_SETUP_FAILED,				// RTSP Setup操作失败
	SERVER_RET_MS_ERR_RTSP_PLAY_FAILED,					// RTSP PLAY操作失败
	SERVER_RET_MS_ERR_ADD_RTP_SESSION_FAILED,			// 添加RTP SESSION到serverbase失败
	SERVER_RET_MS_ERR_DISK_SPACE_NOT_ENOUGH,			// 磁盘空间不足
	SERVER_RET_MS_ERR_OPEN_FILE_FAILED,					// 文件打开失败
	SERVER_RET_MS_ERR_NOT_FOUND_RTSP_CLIENT,			// 找不到RTSP客户端连接
	SERVER_RET_MS_ERR_RTSP_DISCONNECTED,				// RTSP连接断开
	SERVER_RET_MS_ERR_RECORD_QUERY_TIMEOUT,				// 录像查询超时
	SERVER_RET_MS_ERR_SDK_CALLBACK_INVALID_DATA,		// sdk 返回数据不正确
	SERVER_RET_MS_ERR_SNAP_STORE_PATH_INVALID,			// 设置的SS端SNAP存储路径有问题
	SERVER_RET_MS_ERR_SNAP_STORE_FILE_FAILED,			// SS在存储文件时候操作失败
	SERVER_RET_MS_ERR_SNAP_ENCODE_FAILED,				// SS在编码回复pdu时候失败
	SERVER_RET_MS_ERR_IFRAME_2_BMP,						// SS在转换I帧到BMP时候失败
	SERVER_RET_MS_ERR_DUPLICATE_PLAN_FOUND,				// 重复的PlanId发现
	SERVER_RET_MS_ERR_SDK_CALLBACK_TIMEOUT,				// SDK调用Callback超时，没有返回数据																						   
	SERVER_RET_MS_ERR_NOT_FOUND_SESSION_ID,				// 未找到camera_session_id
	SERVER_RET_MS_ERR_INVALID_STREAM_TYPE,				// 非法的码流类型
	SERVER_RET_MS_ERR_ADD_LIVECHANNEL_FAILED,			// 添加直播频道失败
	SERVER_RET_MS_ERR_GET_TALKDECODE_FAILED,			// 获取对讲格式失败
	SERVER_RET_MS_ERR_LOGIN_DEV_FAILED,					// 登陆语音设备失败
	SERVER_RET_MS_ERR_NOT_MATCH_AUDIO_TYPE,				// 音频格式不匹配
	SERVER_RET_MS_ERR_NOT_FOUND_DISK,					// 未找到磁盘
	SERVER_RET_MS_ERR_NOT_FOUND_RECORD_PLAN,			// 未找到录像计划
	SERVER_RET_MS_SERVER_ERROR_END = SERVER_RET_MS_SERVER_ERROR_BEGIN + 100,
	// MS返回结束
	SERVER_RET_MS_ERR_END = SERVER_RET_MS_ERR_BEGIN + 1000,

	// PCS服务协议返回开始，不做返回值判断
	SERVER_RET_PCS_ERR_BEGIN = DSS_ERROR_CODE_BASE + DSS_PCS_BASE,
	SERVER_RET_PCS_ERR_NOT_FOUND = SERVER_RET_PCS_ERR_BEGIN + 404,			// 级联设备未下发
	SERVER_RET_PCS_ERR_NOT_ACCEPTABLE = SERVER_RET_PCS_ERR_BEGIN + 406,		// 级联订阅，本级PTS监听失败
	SERVER_RET_PCS_ERR_DEVICE_OFFLINE = SERVER_RET_PCS_ERR_BEGIN + 710,		// 设备断线
	SERVER_RET_PCS_ERR_DOMIAN_OFFLINE = SERVER_RET_PCS_ERR_BEGIN + 713,		// 下级域不在线
	SERVER_RET_PCS_ERR_PTS_CANNOT_PING = SERVER_RET_PCS_ERR_BEGIN + 714,	// 上级连接下级PTS失败
	SERVER_RET_PCS_ERR_NO_ACK = SERVER_RET_PCS_ERR_BEGIN + 715,				// 无应答
	SERVER_RET_PCS_ERR_END = SERVER_RET_PCS_ERR_BEGIN + 1000,				// PCS返回结束

	SERVER_RET_CUTOCU_ERR_BEGIN = DSS_ERROR_CODE_BASE + DSS_CUTOCU_BASE,
	SERVER_RET_CUTOCU_ERR_INVALID_CAMERA_USER_RELATION,	// 不存在的绑定关系
	SERVER_RET_CUTOCU_ERR_USER_NOT_ONLINE, 				// 用户不在线
	SERVER_RET_CUTOCU_ERR_GRADE_IS_LOWER,				// 等级较低
	SERVER_RET_CUTOCU_ERR_TIMEOUT,						// CUTOCU超时 
	SERVER_RET_CUTOCU_ERR_END,

	DPSDK_RET_PSS_BEGIN = PSS_ERROR_CODE_BASE,			// PSS扩展错误码
	DPSDK_RET_PSS_NOT_SUPPORT_DEV_VERSION,				// 不支持的设备版本
	DPSDK_RET_PSS_END = PSS_ERROR_CODE_BASE + 50000,

	// SCS服务错误码开始
	SERVER_RET_SCS_ERR_BEGIN = DSS_ERROR_CODE_BASE + DSS_SCS_BASE,
	// SIP协议返回失败
	SERVER_RET_SCS_ERR_SIP_ERROR = SERVER_RET_SCS_ERR_BEGIN + 500,
	// SCS服务错误码结束
	SERVER_RET_SCS_ERR_END = SERVER_RET_SCS_ERR_BEGIN + 1000,
	DPSDK_RET_FIRST_LOGIN = 11314,//首次登陆
	DPSDK_RET_MOD_USER_ORGINATION = 51020,				//修改用户所属部门
	//视频接力
	DPSDK_RET_VIDEO_GRID_INFO_CHANGE	    = 51035,		//网格信息变更
	DPSDK_RET_VIDEO_GRID_ADJOIN_CHAGE	    = 51036,		//网格临接信息变更
	DPSDK_RET_VDEO_GRID_LINIK_DEV_CHAGE		= 51037,		//网格关联设备变更
	DPSDK_RET_VIDEO_RFID_DEV_JOIN_CHANGE	= 51038,		//射频网格临接信息
}dpsdk_retval_e;

// 实时监视异常状态定义
typedef enum
{
	Real_Exception_MTS_Unregistered,		 // MTS注销，监视需要重连
	//Real_Exception_Right_Canceled,		 // 权限取消，监视需要关闭
	//Real_Exception_Dev_Removed,			 // 设备从系统中剔除，监视需要关闭
	//Real_Exception_OpenPlayPort_Error,	 // 解码端口打开失败
	Real_Exception_Session_Removed,			 // 会话被服务端拆除
	//RealMonitor_Notify_DevVistor_Disc,	 // 直连设备断线，监视需要关闭
	//Real_Exception_DevVisitRight_Canceled, // 直连权限取消，监视需要关闭
	//Real_Exception_Proxy_Canceled,		 // 代理踢掉会话
}EnumRealException;

//数据传输通知
typedef enum
{
	MEDIA_FIRST_RECEIVE,				// 打开视频首次收到码流
	DATA_RECIVE_OVER,                   // 收到0包后的通知
	BAY_RTP_CLOSE,						// rtp连接断开
}dpsdk_media_notify_e;

typedef enum
{
	OP_FTP_TYPE_UNKNOW		=0,
	OP_FTP_TYPE_DOWN		=0x01,	// 下载
	OP_FTP_TYPE_UP			=0x02,	// 上传
	OP_FTP_TYPE_DELETE		=0x03,	// 删除
	OP_FTP_TYPE_QUERYFILELIST = 0x04,  //查询文件列表
}dpsdk_operator_ftp_type_e;

typedef enum{
	MODE_PORT,								// 主动模式
	MODE_EPSV,								// 被动扩展模式
	MODE_PASV,								// 被动模式
}dpsdk_ftp_transport_mode_e;

typedef enum
{
	CFG_DEVICE_NORMAL		=0,		// 普通ID，使用老协议获取设备树（本身有限制，为兼容老的平台故暂时保留）
	CFG_DEVICE_INCLUDE_$	=0x01,	// ID中包含$符号，使用新协议获取设备树，后续统一切换为该种方式
}dpsdk_config_deviceid_type_e;

//是否检查权限
typedef enum
{
	DPSDK_CHECK_RIGHT = 0,		// 检查
	DPSDK_NOT_CHECK_RIGHT = 1,	// 不检查
}dpsdk_check_right_e;

//载荷类型，俗称trackid
typedef enum
{
	DPSDK_TRACKID_ES = 101,		// ES包
	DPSDK_TRACKID_PS = 501,		// PS包
	DPSDK_TRACKID_DHAV = 701,	// 大华帧
	DPSDK_TRACKID_TS = 901,		// TS包
}dpsdk_trackid_type_e;

typedef enum
{
	MESSAGE_TYPE_OSD = 1,		// OSD
	MESSAGE_TYPE_SMS,			// SMS
}dpsdk_sdk_message_type_e;

typedef enum 
{
	POWERGRID_CMD_PROGARM,
	POWERGRID_CMD_OPEN			= 1,			//供电
	POWERGRID_CMD_CLOSE			= 2,			//断电
	POWERGRID_CMD_CANCELALARM	= 3,			//消警
}dpsdk_powergrid_cmd_e;


typedef enum
{
	DPSDK_NEED_ALARM = 0,		// 需要报警
	DPSDK_NOT_NEED_ALARM = 1,	// 不需要报警
}dpsdk_get_alarm_e;

//卡口业务类型
typedef enum
{
	BAY_MONITOR_CAR = 1,		//车辆
	BAY_MONITOR_FACE = 2,		//人脸
}dpsdk_bay_monitor_e;

typedef enum
{
	DPSDK_GET_DEVID_BY_DGP = 0,		//采用DGP获取设备ID（一般情况下都是这种）
	DPSDK_GET_DEVID_BY_CHNID = 1,	//通过通道ID解析出设备ID（当没有获取设备组织XML的情况下采用这种）
}dpsdk_get_devid_type_e;

typedef enum
{
	DPSDK_H264,			//h264
	DPSDK_MPEG4,		//mpeg4
	DPSDK_JPEG,			//jpeg
}dpsdk_video_codec;

typedef enum
{
	DPSDK_1080P,		//1080p
	DPSDK_130M,			//130M
	DPSDK_720P,			//720p
	DPSDK_D1,			//D1
	DPSDK_CIF,			//CIF
	DPSDK_QCIF,			//QCIF
	DPSDK_VGA,			//VGA
	DPSDK_QVGA,			//QVGA
}dpsdk_resolution ;

typedef struct ReDirectParma
{
	dpsdk_video_codec	_videocodec;		//视频编码格式
	dpsdk_resolution	_resoultion;		//视频分辨率
	int					_fps;				//帧率
	int					_bps;				//码率

	ReDirectParma()
	{
		_videocodec = DPSDK_H264;
		_resoultion = DPSDK_1080P;
		_fps = 25;
		_bps = 256;
	}
}Open_video_Re_Direct;

// 实时码流类型
typedef enum
{
	STREAM_ALL		= 0,		// 0-全部
	STREAM_MAIN		= 1,		// 1-主码流
	STREAM_SUB,					// 2-辅码流
	STREAM_THIRD,				// 3-三码流
	STREAM_SIGNAL	= 5,		// 5-M60本地信号
}encdev_stream_e;

typedef enum
{
	DPSDK_GET_DEVINFO_BY_UNCOMPRESS = 0,		// 采用非压缩方式获取设备信息
	DPSDK_GET_DEVINFO_BY_COMPRESSED = 1,		// 采用压缩方式获取设备信息
}dpsdk_get_devinfo_compress_type_e;

// 摄像头类型
typedef enum
{
	CAMERA_TYPE_NORMAL,						// 枪机
	CAMERA_TYPE_SD,							// 球机
	CAMERA_TYPE_HALFSD,						// 半球
	CAMERA_TYPE_EVIDENCE,                   // 证据通道
	CAMERA_TYPE_ZOOM_NORMAL,						// 变倍枪机通道，球机功能
	CAMERA_TYPE_NORMAL_HD					= 5,	// 网络高清枪机，福建高速项目新增摄像头类型begin
	CAMERA_TYPE_SD_HD						= 6,	// 网络高清球机
	CAMERA_TYPE_NORMAL_SIMULATION_SD		= 8,	// 模拟标清枪机
	CAMERA_TYPE_SD_SIMULATION_SD			= 9,	// 模拟标清球机
	CAMERA_TYPE_HALFSD_SIMULATION_SD		= 10,	// 模拟标清半球
	CAMERA_TYPE_NORMAL_SIMULATION_HD		= 11,	// 模拟高清枪机
	CAMERA_TYPE_SD_SIMULATION_HD			= 12,	// 模拟高清球机
	CAMERA_TYPE_HALFSD_SIMULATION_HD		= 13,	// 模拟高清半球
	CAMERA_TYPE_HALFSD_HD					= 14,	// 网络高清半球，福建高速项目新增摄像头类型end
	CAMERA_TYPE_TRACK_SD					= 15,	// 轨道球机
	CAMERA_TYPE_SOLDIER,							// 单兵
	CAMERA_TYPE_VEHICLE,							// 车载
	CAMERA_TYPE_PORTABLEBOX							// 便携箱
}camera_type_e;

// 解码器视频来源方式
typedef enum
{
	DECODE_MODE_UNDEFINE,					// 未定义
	DECODE_MODE_ACTIVE,						// 主动
	DECODE_MODE_PASSIVE,					// 被动
	DECODE_MODE_PUSH,						// 推流
}decode_mode_e;

// 获取节点深度类型
typedef enum
{
	GET_ORG_DEPTH_TYPE_ALL			= -1,			// 获取所有子孙节点
	GET_ORG_DEPTH_TYPE_SELF			= 0,			// 获取自身
	GET_ORG_DEPTH_TYPE_CHILD		= 1,			// 获取子节点
}dpsdk_get_org_depth_type_e;

// DPSDK是否缓存组织
typedef enum
{
	DPSDK_GROUP_CACHE				= 0,	//缓存组织
	DPSDK_NO_GROUP_CACHE			= 1		//不缓存组织
}dpsdk_group_cache_type_e;

// DPSDK获取业务组织是否过滤基本组织
typedef enum
{
	DPSDK_GROUP_FILTER				= 0,	//过滤基本组织
	DPSDK_NO_GROUP_FILTER			= 1,	//不过滤基本组织
}dpsdk_group_filter_e;

// SCS服务消息传输模式
typedef enum
{
	DPSDK_SCS_TRANSPORT_MODE_SIP	= 0,	//SCS服务消息通过SIP传输
	DPSDK_SCS_TRANSPORT_MODE_HTTP	= 1,	//SCS服务消息通过HTTP传输
}dpsdk_scs_transport_mode;

//tcp 连接方式
typedef enum
{
	DPSDK_TCPMODE_DEFAULT			= 0,	//默认连接方式
	DPSDK_TCPMODE_ACTIVE			= 1,	//tcp 主动连接方式
	DPSDK_TCPMODE_PASSIVE			= 2		//tcp 被动连接方式
}dpsdk_tcpmode;
//////////////////////////////////////////////////////////////////////////

// 回调消息的基类,用于向应用层反馈事件.可根据命令字转换为具体消息以获取更多参数
class DPSDK_API DPSDKCBMessage : public dsl::DRefObj
{
public:
	int		m_cmd;			//消息命令字,	见dpsdk_cmd_e
	int		m_msgType;		//消息类型,		应答或通知，见dpsdk_msg_type_e
	int		m_sequence;		//异步顺序码,	用于与请求相匹配
	int		m_retVal;		//错误码,		见dpsdk_retval_e

	virtual ~DPSDKCBMessage(){}
	DPSDKCBMessage( int cmd = DPSDK_CMD_UNKNOWN,int msgType = DPSDK_MSG_RESPONSE,int seq = 0,int retVal = 0 ){ 
		m_cmd = cmd; m_msgType = msgType; m_sequence = seq; m_retVal = retVal;}
};

/** 消息回调函数统一定义. 
    @param int dpsdkId					暂不用
    @param DPSDKCBMessage* cbMsg		回调消息
    @param void* pUserParam				用户参数
	@return								
*/
typedef int ( DPSDK_CALLTYPE *fDPSDKCallback )( int dpsdkId, DPSDKCBMessage* cbMsg, void* pUserParam );

/** 视频回调函数定义. 
    @param int session						对应请求时返回的session
    @param dpsdk_media_func_e mediaType		媒体流对应的业务
    @param const char * nodeId				数据对应的通道/设备ID
    @param int paramVal						扩展值;mediaType为real时，为streamType;
    @param char * pData						媒体流数据
    @param int dataLen						数据长度 
    @param void * pUserParam				用户参数,见addCallbackInfo
*/
typedef int ( DPSDK_CALLTYPE *fMediaDataCallback )( int session, dpsdk_media_func_e mediaType, const char* nodeId, int paramVal, char* pData, int dataLen, void* pUserParam);

/** 对讲回调函数定义. 
    @param char * pData						媒体流数据
    @param int dataLen						数据长度 
    @param void * pUserParam				用户参数,见AudioUserParam
*/
typedef void (DPSDK_CALLTYPE  *fAudioDataCallback)( char* pData, int dataLen, void* pUserParam );

/** 对讲回调函数定义，用于广播发送音频给特定设备. 
    @param char * pData						媒体流数据
    @param int dataLen						数据长度 
    @param void * pUserParam				用户参数,见AudioUserParam
	@param int iSessionID					对讲SessionID，用于区分哪路对讲
*/
typedef void (DPSDK_CALLTYPE *fAudioDataCallbackEx)( char* pData, int dataLen, void* pUserParam, int iSessionID );


typedef struct tagDPSDK_Param
{
	char	szUserIdFlag[DPSDK_USER_ID_FLAG_LEN];		//用户id标识符
}DPSDK_Param_t;

typedef enum
{
	DPSDK_IPPROTO_UDP = 1,	    //UDP
	DPSDK_IPPROTO_TCP,			//TCP
}dpsdk_ipproto_type_e;
typedef struct tagDPSDK_CreateParam
{
	dpsdk_ipproto_type_e	eSipProto;		//用户id标识符
	char					szSCAgent[CHAR_LEN_512];					// SCAgent设置，默认为DSSCClient，可设置为APPClient
	tagDPSDK_CreateParam()
	{
		eSipProto = DPSDK_IPPROTO_UDP;
		memset(szSCAgent,0,sizeof(szSCAgent));
	}
}DPSDK_CreateParam_t;

//////////////////////////////////////////////////////////////////////////
END_NAMESPACE_DPSDK

#endif

