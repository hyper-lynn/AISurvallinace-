/**
 * Copyright (c) 2012, 浙江大华
 * All rights reserved.
 *
 * 文件名称：
 * 文件标识：
 * 摘　　要：Platform SDK的接口文件,监狱子模块
 *
 * 当前版本：1.0
 * 原作者　：15693
 * 完成日期：2013年7月3日
 * 修订记录：创建
 */

#ifndef INCLUDED_DPSDK_DPSDKPRISON_H
#define INCLUDED_DPSDK_DPSDKPRISON_H

#include "DPSDK.h"
#include <string>
#include <vector>
#include <deque>
#include "DPSDKGeneral.h"
#include "DPSDKPtz.h"

BEGIN_NAMESPACE_DPSDK
//////////////////////////////////////////////////////////////////////////
// add by jyl 2013.7
// 案件信息
typedef struct DPSDK_API CaseInfo
{
	char  					szCaseID[DPSSDK_CASEID_LEN];			     
	char  					szCaseName[DPSSDK_CASENAME_LEN];		 
	char  					szCaseReason[DPSSDK_CASEREASON_LEN]; 
	char  					szCaseDepartment[DPSSDK_CASEDEPART_LEN];		 
	char  					szCaseUnderTaker[DPSSDK_CASEUNTAKER_LEN];         
}CaseInfo_t;

// 人信息
typedef struct DPSDK_API PersonInfo
{
	uint32_t 				szCaseSeq;
	char     				szCaseReferPerson[DPSSDK_CASEREASON_LEN];			    
	char     				szCaseRemark[DPSSDK_CASEREASON_LEN];			        
	char     				szCaseRecordName[DPSSDK_CASEREASON_LEN];	            
	char     				szCDID[DPSSDK_CASEID_LEN];				            
	char     				szRecordPerson[DPSSDK_CASEDEPART_LEN];                
}PersonInfo_t;

// 审讯信息
typedef struct DPSDK_API TrialInfo
{
	char    				szPersonName[DPSSDK_CASENAME_LEN];					// 审讯对象
	char    				szInterrogateType[DPSDK_INTERTYPE_LEN];				// 审讯类型
	char    				szInterrogateAddr[DPSSDK_CASEDEPART_LEN];			// 审讯地址
	char    				szInterrogateName[DPSSDK_CASENAME_LEN];				// 审讯名称
	char    				szInterrogateDept[DPSSDK_CASEDEPART_LEN];			// 审讯部门
	char    				szInterrogatePerson[DPSSDK_CASENAME_LEN];			// 审讯人
	uint32_t  				szInterrogateStartTime;								// 查询开始时间
	uint32_t  				szInterrogateEndTime;								// 查询结束时间
}TrialInfo_t;

// 保存案件人信息
typedef struct DPSDK_API STrialCaseInfo
{
	uint32_t  				nId;
	char    				szCaseID[DPSSDK_CASEID_LEN];
	char    				szName[DPSSDK_CASENAME_LEN];
	uint32_t  				nAge;
	char    				szSex;
	char    				szType[DPSSDK_CASEUNTAKER_LEN];
	int     				nTrialSeq;

}STrialCaseInfo_t;

// 保存审讯人信息
typedef struct DPSDK_API STrialPerInfo
{
	char    				szTrialObjIDCard[DPSSDK_CASEID_LEN];				// 身份证号码
	char    				szTrialObjNation[DPSDK_NATION_LEN];					// 民族
	char    				szTrialObjBirthDay[DPSDK_BIRTHDAY_LEN];				// 出生日期
	char    				szTrialObjAddr[DPSDK_ADDR_LEN];						// 住址
	char    				szTrialObjWorkUnits[DPSDK_WORKUN_LEN];				// 工作单位
	char    				szTrialObjTelephone[DPSDK_PHONE_LEN];				// 联系电话

}STrialPerInfo_t;

// 保存审讯信息
typedef struct DPSDK_API STrialInfo
{
	uint32_t   				 nId;
	char       				 szCaseID[DPSSDK_CASEID_LEN];
	uint32_t   				 nInterrogateSeq;
	char       				 szInterrogateType[DPSDK_INTERTYPE_LEN];
	char       				 szInterrogateAddress[DPSDK_ADDR_LEN];
	char       				 szInterrogateName[DPSSDK_CASENAME_LEN];
	char       				 szInterrogateDep[DPSSDK_CASENAME_LEN];
	char       				 szInterrogatePerson[DPSSDK_CASENAME_LEN];
	char       				 szNotePerson[DPSSDK_CASENAME_LEN];
	char       				 szRecordPerson[DPSSDK_CASEDEPART_LEN];
	char       				 szCDID[DPSSDK_CASEID_LEN];
	uint32_t   				 nInterrogateStarttime;
	uint32_t   				 nInterrogateEndtime;
	uint32_t   				 nInterrogateRoomId;
	int        				 nInterroagionStatus;								// 审讯状态，0-初始值，1-审讯开始，2-审讯结束
	int        				 ndbOperator;
}STrialInfo_t;

// 保存案例信息
typedef struct DPSDK_API SCaseInfo
{
	uint32_t   				 nId;
	char       				 szCaseID[DPSSDK_CASEID_LEN];
	char       				 szCaseName[DPSSDK_CASENAME_LEN];
	char       				 szCaseReason[DPSSDK_CASEREASON_LEN];
	char       				 szCaseDep[DPSSDK_CASENAME_LEN];
	char       				 szCaseUnderTaker[DPSSDK_CASEUNTAKER_LEN];
	char       				 szCaseRemark[DPSSDK_CASEREASON_LEN];
	uint32_t   				 nCaseSeq;
	char       				 szCaseReferPerson[DPSSDK_CASEREASON_LEN];			// 涉案人员
	char       				 szCaseRecordName[DPSSDK_CASEREASON_LEN];			// 录像名称
	int        				 ndbOperator;
}SCaseInfo_t;

// 电子模板信息
typedef struct DPSDK_API SNoteTemp
{
	uint32_t  				nId;
	char    				szTemplateType[DPSDK_TEMPLATE_LEN];					// 256
	char    				szTemplateName[DPSDK_TEMPLATE_LEN];					// 256
	int     				nDbOperator;     
}SNoteTemp_t;

// 所有通报
typedef struct DPSDK_API SNotifyAll
{
	char   					szUserName[DPSDK_USER_NAME_LEN];					// 32
	char   					szIp[DPSDK_IP_LEN];
	char   					szRoomName[DPSDK_ROOMNAME_LEN];
	char   					szRoomId[DPSDK_ROOMID_LEN];
	int    					nStatus;											// 1-上线， 0 - 下线
	int    					nFirstTimeAsk;										// 1 - The first time request online list, else 0;
}SNotifyAll_t;

typedef struct DPSDK_API SNotifyAll_Res
{
	char   					sz_userName[DPSDK_USER_NAME_LEN];
	char   					sz_ip[DPSDK_IP_LEN];
	char   					sz_roomName[DPSDK_ROOMNAME_LEN];
	char   					sz_roomId[DPSDK_ROOMID_LEN];
	int    					n_status;											// 1-上线， 0 - 下线
}SNotifyAll_Res_t;

typedef struct DPSDK_API SInterrogationRoomInfo
{
	int  					nInterrogationRoomId;                 				// 审讯室Id
	char 					szInterrogationRoomName[DPSDK_INTERROOMNAME_LEN];  	// 审讯室名			
    char 					szInterrogationClientIP[DPSDK_INTERCLIENTIP_LEN];	// 审讯主机设备Ip				
    char 					szDeviceId[DPSDK_DEVICEID_LEN];                     
    char 					szDevIP[DPSDK_DEVICEIP_LEN];         				// 审讯室绑定的客户端IP 				
	int         			nDevPort;											// 审讯主机设备端口
	char 					szHostLoginName[DPSDK_HOSTLOGINNAME_LEN];			// 审讯主机登录用户名  				
	char 					szHostLoginPSW[DPSDK_HOSTLOGINPSW_LEN];				// 审讯主机登录密码              				
         				
}SInterrogationRoomInfo_t;

typedef struct DPSDK_API SNoteTempList
{
	int						nId;                           						// 模板id
	char					szTemplateType[DPSDK_TEMPLISTTYPE_LEN];  			// 模板类型
	char					szTemplateName[DPSDK_FILENAME_LEN];					// 模板名

}SNoteTempList_t;

//刻录片头
typedef struct DPSDK_API DevBurnerInfoHeader
{
	char					m_deviceId[DPSDK_CHAR_LEN_32];						// 设备ID
	char					m_password[DPSDK_CHAR_LEN_64];						// 叠加密码
	char					m_caseId[DPSDK_CHAR_LEN_256];						// 1.案件编号
	char					m_trialSeq[DPSDK_CHAR_LEN_256];						// 2.案件序号/审讯序号
	//uint32_t				m_trialSeq;											// 2.案件序号/审讯序号
	char					m_caseUnderTaker[DPSDK_CHAR_LEN_256];				// 3.办案人员
	char					m_caseDep[DPSDK_CHAR_LEN_256];						// 4.办案单位	
	char					m_caseReason[DPSDK_CHAR_LEN_256];					// 5.涉嫌名称
	char					m_caseReferPerson[DPSDK_CHAR_LEN_256];				// 6.涉案人员
	char					m_caseRemark[DPSDK_CHAR_LEN_256];					// 7.案卷备注
	char					m_caseRecordName[DPSDK_CHAR_LEN_256];				// 8.录像名称
	char					m_RecordNum[DPSDK_CHAR_LEN_32];						// 9.光盘编号
	char					m_recordPerson[DPSDK_CHAR_LEN_256];					// 10.刻录人
	bool					m_dataCheckOsdEn;									// 11.光盘刻录数据校验配置/叠加使能
	bool					m_AttachFileEn;										// 12.附加文件使能
	bool					m_multiBurnerDataCheck;								// 13.多光盘一致性校验使能
	uint32_t				m_multiBurnerDataCheckSpeed;						// 14.校验速度校验速度 0 高速（头尾数据校验）,1 正常（随机数据校验）,2 低速 （全盘数据校验）,默认0

	DevBurnerInfoHeader()
	{
		memset(m_deviceId,0,DPSDK_CHAR_LEN_32);
		memset(m_password,0,DPSDK_CHAR_LEN_64);
		memset(m_caseId,0,DPSDK_CHAR_LEN_256);
		memset(m_trialSeq,0,DPSDK_CHAR_LEN_256);
		memset(m_caseUnderTaker,0,DPSDK_CHAR_LEN_256);
		memset(m_caseDep,0,DPSDK_CHAR_LEN_256);
		memset(m_caseReason,0,DPSDK_CHAR_LEN_256);
		memset(m_caseReferPerson,0,DPSDK_CHAR_LEN_256);
		memset(m_caseRemark,0,DPSDK_CHAR_LEN_256);
		memset(m_caseRecordName,0,DPSDK_CHAR_LEN_256);
		memset(m_RecordNum,0,DPSDK_CHAR_LEN_32);
		memset(m_recordPerson,0,DPSDK_CHAR_LEN_256);
		m_dataCheckOsdEn = false;
		m_AttachFileEn = false;
		m_multiBurnerDataCheck = false;
		m_multiBurnerDataCheckSpeed = 1;
	}
}DevBurnerInfoHeader_t;

//审讯表单属性名
typedef struct DPSDK_API TrialFormAttrName
{
	char					m_caseIdAttr[DPSDK_CHAR_LEN_32];					// 案件编号
	char					m_trialSeqAttr[DPSDK_CHAR_LEN_32];					// 案件序号/审讯序号
	char					m_caseUnderTakerAttr[DPSDK_CHAR_LEN_32];			// 办案人员
	char					m_caseDepAttr[DPSDK_CHAR_LEN_32];					// 办案单位
	char					m_caseReasonAttr[DPSDK_CHAR_LEN_32];				// 涉嫌名称
	char					m_caseReferPersonAttr[DPSDK_CHAR_LEN_32];			// 涉案人员
	char					m_caseRemarkAttr[DPSDK_CHAR_LEN_32];				// 案卷备注
	char					m_caseRecordNameAttr[DPSDK_CHAR_LEN_32];			// 录像名称
	char					m_trialObjNameAttr[DPSDK_CHAR_LEN_32];				// 被审讯人姓名
	char					m_trialObjSexAttr[DPSDK_CHAR_LEN_32];				// 被审讯人性别
	char					m_trialObjIDAttr[DPSDK_CHAR_LEN_32];				// 被审讯人身份证号码
	char					m_trialObjNationAttr[DPSDK_CHAR_LEN_32];			// 民族
	char					m_trialObjBirthdayAttr[DPSDK_CHAR_LEN_32];			// 出生年月
	char					m_trialObjHomeAddrAttr[DPSDK_CHAR_LEN_32];			// 住址
	char					m_trialObjWorkUnitsAttr[DPSDK_CHAR_LEN_32];			// 工作单位
	char					m_trialObjTelephoneAttr[DPSDK_CHAR_LEN_32];			// 联系电话
	char					m_CDIDAttr[DPSDK_CHAR_LEN_32];						// 光盘编号
	char					m_recordPersonAttr[DPSDK_CHAR_LEN_32];				// 刻录人
	char					m_caseAssistantAttr[DPSDK_CHAR_LEN_32];				// 协助办案人员--卷宗信息新增，非必填项
	char					m_trialObjAgeAttr[DPSDK_CHAR_LEN_32];				// 年龄--被询问人信息-新增，非必填项

}TrialFormAttrName_t;

//刻录控制命令
typedef enum
{
	Cmd_StartBurn = 1,															// 开始刻录
	Cmd_PauseBurn,																// 暂停刻录
	Cmd_ContinueBurn,															// 继续刻录
	Cmd_StopBurn,																// 停止刻录
	Cmd_ChangeCD,																// 手动换盘
}EnumControlBurnerCmd;

//刻录主机CD状态信息
typedef struct DPSDK_API BurnerCDState
{
	uint32_t				m_burnerId;											// 刻录机ID, ID从0开始
	uint32_t				m_burnerState;										// 刻录机状态 0：可以刻录 1：刻录机类型不对，是一个非光盘设备 
																				// 2：未找到刻录机 3：有其它光盘在刻录 4：刻录机处于非空闲状态，即在备份、刻录或回放中
	uint32_t				m_romType;											// 盘片类型 0：大华文件系统 1：移动硬盘或U盘 2：光盘
	uint32_t				m_operateType;										// 操作类型 0：空闲 1：正在备份中 2：正在刻录中 3：正在进行光盘回放
	uint32_t				m_processState;										// 进度状态 0：停止或结束 1：开始 2：出错 3：满 4：正在初始化
	uint32_t				m_startTime;										// 开始时间
	uint32_t				m_elapseTime;										// 已刻录时间
	uint32_t				m_totalSpace;										// 光盘总容量
	uint32_t				m_remainSpace;										// 光盘剩余容量
	uint32_t				m_burned;											// 已刻录容量
	uint32_t				m_channelMask;										// 刻录的通道掩码
	uint32_t				m_emMode;											// 刻录模式0-BURN_MODE_SYNC,1-BURN_MODE_TURN,2-BURN_MODE_CYCLE
	uint32_t				m_emPack;											// 刻录流格式0-DHAV,1-BURN_PACK_PS...
	BurnerCDState()
	{
		m_burnerId = 0;
		m_burnerState = 0;
		m_romType= 0;
		m_operateType = 0;
		m_processState = 0;
		m_startTime = 0;
		m_elapseTime = 0;
		m_totalSpace = 0;
		m_remainSpace = 0;
		m_burned = 0;
		m_channelMask = 0;
		m_emMode = 0;
		m_emPack = 0;
	}
}BurnerCDState_t;

//刻录机信息
typedef struct DPSDK_API SBurner_Info_t
{
	uint32_t				_driverType;
	uint32_t				_busType;
	uint32_t				_totalSpace;
	uint32_t				_remainSpace;
	char					_driveName[DPSDK_DEVICE_NAME_LEN];
	char					_deviceId[DPSDK_DEVICEID_LEN];
}SBurner_Info_t;

//编码计划,刻录参数请求
typedef struct DPSDK_API EncodePlanReq
{	
	char					m_deviceId[DPSDK_CHAR_LEN_32];						// 设备ID				||查询/设置 共用
	int						m_channel;											// 通道号				||查询/设置 共用
	uint32_t				m_expectTime;										// 业务预计时长（分钟）	||查询/设置 共用
	uint32_t				m_capacity;											// 容量（M）			||查询
	std::string				m_encodeType;										// 分辨率				||设置
	uint32_t				m_bitRate;											// 视频固定码率			||设置
}EncodePlanReq_t;

//编码计划,刻录参数应答
typedef struct DPSDK_API EncodePlanResp
{	
	std::deque<std::string>	m_encodeTypes;										// 通道支持的分辨率
	std::string				m_commEncodeType;									// 推荐的分辨率
	uint32_t				m_bitRate;											// 视频固定码率
}EncodePlanResp_t;

//刻录参数
typedef struct DPSDK_API BurnParam
{
	char					m_devId[DPSDK_CHAR_LEN_32];							// 设备ID
	int						m_expectTime;										// 预计时长
	char					m_pwd[DPSDK_CHAR_LEN_64];							// 刻录叠加密码
	int						m_dataCheckOsdEn;									// 刻录数据校验叠加使能
	bool					m_multiBurnerDataCheck;								// 多光盘一致性校验使能
	int						m_multiBurnerDataCheckSpeed;						// 校验速度校验速度0 高速（头尾数据校验）,1 正常（随机数据校验）,2 低速（全盘数据校验）,默认
	bool					m_appendFile;										// 附件上传
}BurnParam_t;

typedef struct DPSDK_API UploadFileReq
{	/*附件刻录请求*/
	char	    m_deviceId[DPSDK_CHAR_LEN_32];		// 设备ID
	uint32_t	m_burnerId;					// 刻录机ID，从0开始
	char	    m_fileName[DPSDK_CHAR_LEN_256];	// 文件名（如果文件太大可分多次发送）
	uint32_t	m_action;					// 0 开始 1 继续 2 结束（将文件信息发送给服务去上传，此时并没有启动文件刻录，只是暂时保存到服务端）
	uint32_t	m_dataLen;
	char*	    m_data;
}UploadFileReq_t;

typedef struct BurnerDevInfo
{
	int				m_nBkType;//刻录设备介质类型0: 未知1: 大华文件系统2: 移动硬盘3: 光盘刻录
	int				m_nBurnerId;//刻录机Id;
	std::string		m_strBurnerName;//刻录设备名称
	int				m_nBusType;//刻录设备总线类型0：未知1：IDE2：USB3：13944：SATA5：ESATA
	int				m_nFreeSpace;//光驱剩余容量
	int				m_nOperateType;//光驱使用状态0：未知1：执行写2：执行读3：空闲
	int				m_nTotalSpace;//光驱总容量
	int				m_nTrayType;//光驱托盘状态0：未知1：光盘就绪2：托盘弹出3：无盘4：光盘未就绪

	BurnerDevInfo()
	{
		m_nBkType = 0;
		m_nBurnerId = -1;
		m_strBurnerName = "";
		m_nBusType= 0;
		m_nFreeSpace = 0;
		m_nOperateType = 0;
		m_nTotalSpace = 0;
		m_nTrayType = 0;
	}
}BurnerDevInfo_t;

//DB操作命令
typedef enum
{	
	DB_ERROR = 0,		// Error
	DB_INSERT = 1,		// 增
	DB_UPDATE,			// 改
	DB_SELECT,			// 查
	DB_DELETE = 7,		// 删
}EnumDbOperator;

//磁盘信息
typedef struct tagDiskInfo
{
	int						nDiskId;											//硬盘ID（从0开始）
	uint32_t				uVolume;											//硬盘容量
	uint32_t				uFreeSpace;											//剩余容量
	unsigned char			diskState;											//高四位的值表示硬盘类型，具体为：0 读写驱动器 1 只读驱动器 2 备份驱动器或媒体驱动器 3 冗余驱动器 4 快照驱动器；低四位的值表示硬盘的状态，0-休眠,1-活动,2-故障
	unsigned char			diskNum;											//硬盘号
	unsigned char			subareaNum;											//分区号
	unsigned char			signal;												//标识， 0本地 1 远程
}Disk_Info_t;

// 同步时间消息
class DPSDK_API SyncTimeMsg : public DPSDKCBMessage
{
public:
	SyncTimeMsg(void);
	virtual ~SyncTimeMsg(void){}

public:
	char					szDevId[DPSDK_DEV_ID_LEN];							// 设备ID
	int						nFlag;												// 标志位
	//去除组织树缓存修改
	char					szDevIp[DPSDK_IP_LEN];								// 设备IP

	uint32_t				nServerTime;										// 服务时间
};

// 案例审讯人消息
class DPSDK_API InterrogationPersonInfoMsg : public DPSDKCBMessage
{
public:
	InterrogationPersonInfoMsg(void);
	virtual ~InterrogationPersonInfoMsg(void){}

public:
	CaseInfo_t     			stuCaseInfo;
	PersonInfo_t   			stuPersonInfo;
	TrialInfo_t    			stuTrialInfo;
	int            			nDbOperator;
};

// 案例审讯消息
class DPSDK_API InterrogationCaseInfoMsg : public DPSDKCBMessage
{
public:
	InterrogationCaseInfoMsg(void);
	virtual ~InterrogationCaseInfoMsg(void){}

public:
	CaseInfo_t     			stuCaseInfo;
	PersonInfo_t   			stuPersonInfo;
	TrialInfo_t    			stuTrialInfo;

	int            			nDbOperator;
};

// 保存审讯人消息
class DPSDK_API SaveInterrogationPersonInfoMsg : public DPSDKCBMessage
{
public:
	SaveInterrogationPersonInfoMsg(void);
	virtual ~SaveInterrogationPersonInfoMsg(void){}

public:
	STrialCaseInfo_t     	stuTriCaseInfo;
	STrialPerInfo_t      	stuTriPerInfo;
	
	int                  	nDbOperator;
};

// 保存审讯消息
class DPSDK_API SaveInterrogationInfoMsg : public DPSDKCBMessage
{
public:
	SaveInterrogationInfoMsg(void);
	virtual ~SaveInterrogationInfoMsg(void);

public:
	STrialInfo_t     		stuTrialInfo;
	
	char*		     		pData;												// 经纬度数据
	int			     		nLen;
};

// 保存案件消息
class DPSDK_API SaveInterrogationCaseInfoMsg : public DPSDKCBMessage
{
public:
	SaveInterrogationCaseInfoMsg(void);
	virtual ~SaveInterrogationCaseInfoMsg(){}

public:
	SCaseInfo_t				stuCaseInfo;
};

// 下载电子笔记消息
class DPSDK_API DownLoadNoteMsg : public DPSDKCBMessage
{
public:
	DownLoadNoteMsg(void);
	virtual ~DownLoadNoteMsg(){}

public:
	char					szCaseID[DPSSDK_CASEID_LEN];						// 案例ID
	int					    nTrialSeq;											// 审讯请求
	int						nDbOperator;										// 操作	   
};

// 通用消息，可以收发与客户端通信的数据
class DPSDK_API GeneralMessageMsg:public DPSDKCBMessage
{
public:
	GeneralMessageMsg(void);
	virtual ~GeneralMessageMsg(){}

public:
	int32_t	   				iParam1;
	int32_t    				iParam2;
	char       				strMsg1[DPSDK_TIMESTR_LEN];     					// 64
	char	   				strMsg2[DPSDK_STRING_LEN];							// 字符参数1,128
   
	//reponse:
	int32_t					niParam1;
	int32_t   				niParam2;
	char    				szstrMsg1[DPSDK_TIMESTR_LEN];
	char					szstrMsg2[DPSDK_STRING_LEN];						// 字符参数1
};

// 获取审问标签信息
class DPSDK_API GetInterrogateLabelInfoMsg:public DPSDKCBMessage
{
public:
	GetInterrogateLabelInfoMsg(void);
	virtual ~GetInterrogateLabelInfoMsg(){}

public:
	uint32_t	   			nParam1;
	uint32_t    			nParam2;
	char       				szMsg1[DPSDK_TIMESTR_LEN];							// 64
	char	   				szMsg2[DPSDK_STRING_LEN];							// 字符参数1,128
};

// 获取审问用户组
class DPSDK_API GetInterrogationUserGroupsMsg:public DPSDKCBMessage
{
public:
	GetInterrogationUserGroupsMsg(void);
	virtual ~GetInterrogationUserGroupsMsg(){}

public:
	int						nRole;												// 1- 操作组， 2 - 审讯组，3 - 指挥组
};

// 获得单个案例信息
class DPSDK_API GetSingleCaseInfoMsg:public DPSDKCBMessage
{
public:
	GetSingleCaseInfoMsg(void);
	virtual ~GetSingleCaseInfoMsg(){}

public:
	uint32_t	   			nParam1;
	uint32_t    			nParam2;
	char       				szMsg1[DPSDK_TIMESTR_LEN];							// 64
	char	   				szMsg2[DPSDK_STRING_LEN];							// 字符参数1,128
};

// 最近审讯请求
class DPSDK_API InterrogationSeqMsg:public DPSDKCBMessage
{
public:
	InterrogationSeqMsg(void);
	virtual ~InterrogationSeqMsg(){}

public:
	char					szCaseId[DPSSDK_CASEID_LEN];
	int						nDbOperator;

	// response
	char					szRCaseId[DPSSDK_CASEID_LEN];
	int						nSeq;	
};

// 电子模板
class DPSDK_API NoteTemplateMsg : public DPSDKCBMessage
{
public:
	NoteTemplateMsg(void);
	virtual ~NoteTemplateMsg(void);

public:
    // request
	SNoteTemp_t				stuNoteTemp; 
	char*					pData;												// 经纬度数据
	int						nLen;

	// respone
	char					szTemplateType[DPSDK_TEMPLATE_LEN];
	char					szTtemplateName[DPSDK_TEMPLATE_LEN];
};

// 一般判决
class DPSDK_API CommonSentenceMsg : public DPSDKCBMessage
{
public:
	CommonSentenceMsg(void);
	virtual ~CommonSentenceMsg(void);

public:
	// request
	char   					szUserId[DPSSDK_CASEID_LEN];
	int    					nDbOperator;
	uint32_t 				nLen;
	char*  					pData;

	// response
	char    				szRuserId[DPSSDK_CASEID_LEN];
	uint32_t  				nRlen;
	char*   				pRdata;
}; 

// 所有通报消息
class DPSDK_API NotifyAllMsg : public DPSDKCBMessage
{
public:
	NotifyAllMsg(void);
	virtual ~NotifyAllMsg(void);

public:
	// request
    SNotifyAll_t			stuNotifyAll;

	// response
	uint32_t				count;
    SNotifyAll_Res_t*		pNotifyAllRes;
};

// 登录审讯信息
class DPSDK_API LoginInterrogationMsg : public DPSDKCBMessage
{
public:
	LoginInterrogationMsg(void);
	virtual ~LoginInterrogationMsg(void);

public:
	// request
	char						szLoginUserName[DPSDK_HOSTLOGINNAME_LEN];

	// response
	uint32_t          			count;
	SInterrogationRoomInfo_t*	pInterrogationRoomInfo;
};

// 获得电子笔记模板
class DPSDK_API GetTemplateListMsg : public DPSDKCBMessage
{
public:
	GetTemplateListMsg(void);
	virtual ~GetTemplateListMsg(void);

public:
	// request
	int						nDbOperator;

	// response
	uint32_t				count;
	SNoteTempList_t*		pNoteTempList;
};

//重点标注查询
class DPSDK_API QueryTagMsg : public DPSDKCBMessage
{
public:
	QueryTagMsg(void);
	virtual ~QueryTagMsg(void){}

public:
	//request
	std::string		m_caseId;
	int				m_seq;
	std::string		m_depCode;			//级联-->组织Coding

	//response
	std::string		m_trialTagXml;
};

//审讯打标
class DPSDK_API AddTrialTagMsg : public DPSDKCBMessage
{
public:
	AddTrialTagMsg(void);
	virtual ~AddTrialTagMsg(void){}

public:
	//request
	std::string		m_caseid;
	int				m_seq;
	uint64_t		m_timeStamp;
	std::string		m_desp;
	std::string		m_depCode;			//级联-->组织Coding

	//response
	int				m_isOk;				//1=success;  -1=failed
};

//审讯FTP信息
class DPSDK_API FtpSxMsg : public DPSDKCBMessage
{
public:
	FtpSxMsg(void);
	virtual ~FtpSxMsg(void){}

	dpsdk_operator_ftp_type_e	opType;			// 操作类型，请参考dpsdk_operator_ftp_type_e
	char			url[DPSDK_TAG_URL_LEN];		// ftp服务器存储数据的相对url
	char			path[DPSDK_TAG_PATH_LEN];	// 本地上传或者下载后的图片的地址
	char			ipIn[DPSDK_IP_LEN];			// 内网ip
	char			ipOut[DPSDK_IP_LEN];		// 外网ip
	char			user[DPSDK_USER_NAME_LEN];	// FTP用户
	char			password[DPSDK_PASSWORD_LEN];// FTP密码
	dpsdk_ftp_transport_mode_e	mode;			//	文件传输模式
};

//存放公用数据
class DPSDK_API PrisonBaseMsg : public GeneralJsonTransportMsg
{
public:
	PrisonBaseMsg( int cmd = DPSDK_CMD_UNKNOWN,int msgType = DPSDK_MSG_RESPONSE);
	virtual ~PrisonBaseMsg(){}

	//char	serverId[SERVER_ID_LEN];		//服务ID
	char	cameraId[DPSDK_CHL_ID_LEN];		//摄像头ID
};

//获取刻录机状态信息
class DPSDK_API GetDevBurnerInfoMsg: public PrisonBaseMsg
{
public:
	GetDevBurnerInfoMsg();
	virtual ~GetDevBurnerInfoMsg(){}

public:
	//response
	std::deque<SBurner_Info_t> _burnerInfo;
};

//刻录片头设置信息
class DPSDK_API SetDevBurnerHeaderMsg: public PrisonBaseMsg
{
public:
	SetDevBurnerHeaderMsg();
	virtual ~SetDevBurnerHeaderMsg(){}

public:
	DevBurnerInfoHeader_t _burnerHeader;
	TrialFormAttrName_t   _burnTrialAttrName;
};

//刻录控制信息
class DPSDK_API ControlDevBurnerMsg: public PrisonBaseMsg
{
public:
	ControlDevBurnerMsg();
	virtual ~ControlDevBurnerMsg(){}
public:
	EnumControlBurnerCmd _cmd;
	int _channelMask;
	int _burnerMask;
	int _nType;  //1是实时刻录，3是事后刻录
	//庭审相关
	int _emMode;
	int _emPack;
};

//获取光盘状态信息
class DPSDK_API GetDevBurnerCDStateMsg: public PrisonBaseMsg
{
public:
	GetDevBurnerCDStateMsg();
	virtual ~GetDevBurnerCDStateMsg(){}
public:
	uint32_t _burnerId;
	//response
	BurnerCDState_t _cdStatInfo;
};

//获取编码计划
class DPSDK_API GetEncodePlanMsg: public PrisonBaseMsg
{
public:
	GetEncodePlanMsg();
	virtual ~GetEncodePlanMsg(){}
public:
	EncodePlanReq_t _req;
	//response
	EncodePlanResp_t _resp;
};

//设置编码计划
class DPSDK_API SetEncodePlanMsg: public PrisonBaseMsg
{
public:
	SetEncodePlanMsg();
	virtual ~SetEncodePlanMsg(){}
public:
	EncodePlanReq_t _req;
};

//设置刻录格式
class DPSDK_API SetBurnRecordFormatMsg: public PrisonBaseMsg
{
public:
	SetBurnRecordFormatMsg();
	virtual ~SetBurnRecordFormatMsg(){}
public:
	char  format[DPSDK_CHAR_LEN_32];
};

//刻录状态主动上报
class DPSDK_API GetBurnStatusNotifyMsg: public PrisonBaseMsg
{
public:
	GetBurnStatusNotifyMsg();
	virtual ~GetBurnStatusNotifyMsg(){}
public:
	char		_deviceId[DPSDK_CHAR_LEN_32];		// 设备ID
	char		_burnerName[DPSDK_CHAR_LEN_256];	// 刻录机名称
	char		_status[DPSDK_CHAR_LEN_256];		// 状态 
	uint32_t	_totalSpace;						// 总容量（KB）
	uint32_t	_remainSpace;						// 剩余容量（KB）
	int         _burnId;							// 设备序号0,1...
	uint32_t    _remainTime;						// 剩余时间，单位秒
	uint32_t    _burnErrCode;						// 错误码
};

//保存刻录参数
class DPSDK_API SaveBurnParamMsg : public DPSDKCBMessage
{
public:
	SaveBurnParamMsg();
	virtual ~SaveBurnParamMsg(){}

public:
	//request
	BurnParam_t		m_burnParam;

	//response
	int				m_isOk;				//1=success;  -1=failed
};

//查询刻录参数
class DPSDK_API QueryBurnParamMsg : public DPSDKCBMessage
{
public:
	QueryBurnParamMsg();
	virtual ~QueryBurnParamMsg(){}

public:
	//request
	char		m_devId[DPSDK_CHAR_LEN_32];

	//response
	BurnParam_t		m_burnParam;
};

//语音激励信息
class DPSDK_API VoiceImpelMsg : public PrisonBaseMsg
{
public:
	VoiceImpelMsg(void);
	virtual ~VoiceImpelMsg(void){}

	int				m_nOperation;					// 操作类型，0表示关，1表示开
};

//DVD控制信息
class DPSDK_API DVDControlMsg : public PrisonBaseMsg
{
public:
	DVDControlMsg(void);
	virtual ~DVDControlMsg(void){}

	int				m_operChannelId;			// 红外设备的通道id
	int				m_nOperation;				// 操作类型，以设备说明书为准
};

//设置组合屏信息
class DPSDK_API SetCombinedScreenMsg : public PrisonBaseMsg
{
public:
	SetCombinedScreenMsg(void);
	virtual ~SetCombinedScreenMsg(void){}

	int				m_compMode;					// 组合屏模式
	int				m_chnlNo;					// 通道号
	std::vector<int> m_compDetail;				// 组合屏细节
};

//获取组合屏信息
class DPSDK_API GetCombinedScreenMsg : public PrisonBaseMsg
{
public:
	GetCombinedScreenMsg(void);
	virtual ~GetCombinedScreenMsg(void){}

	int				m_compMode;					// 组合屏模式
	int				m_chnlNo;					// 通道号
	std::vector<int> m_compDetail;				// 组合屏细节
};

//播控管理通知消息
class DPSDK_API ManageBroadcastNotifyMsg : public PrisonBaseMsg
{
public:
	ManageBroadcastNotifyMsg(void);
	virtual ~ManageBroadcastNotifyMsg(void){}

	char			m_caseCode[DPSDK_CHAR_LEN_128];	// 案件号
	int				m_caseNum;						// 案件审理次数
	char			m_judge[DPSDK_CHAR_LEN_64];		// 审判长
	int				m_status;						// 审理状态
};

class DPSDK_API CourtSnapMsg :public PrisonBaseMsg
{
public:
	CourtSnapMsg(void)
	{
		m_cmd = DPSDK_CMD_PRISON_COURTSNAP;
		trantype = GENERALJSON_TRAN_REQUEST;
		m_strJsonInfo.clear();
	}
	virtual ~CourtSnapMsg(void){}
	std::string m_strJsonInfo;
};

//设置矩阵切换信息
class DPSDK_API SetMatrixSwitchMsg : public PrisonBaseMsg
{
public:
	SetMatrixSwitchMsg(void);
	virtual ~SetMatrixSwitchMsg(void){}

	int				channelId;							//通道ID
	int				m_decodeLenth;						// 解码通道个数
	int				m_decodeChn[24];					// 解码通道
};

//还原矩阵切换信息
class DPSDK_API ResetMatrixSwitchMsg : public PrisonBaseMsg
{
public:
	ResetMatrixSwitchMsg(void);
	virtual ~ResetMatrixSwitchMsg(void){}
};

//播控管理通知消息
class DPSDK_API ControlLiveMsg : public DPSDKCBMessage
{
public:
	ControlLiveMsg(void);
	virtual ~ControlLiveMsg(void){}

	char			m_szCaseCode[DPSDK_CHAR_LEN_128];	// 案件号
	int				m_nCaseNum;							// 案件审理次数
	char			m_szJudge[DPSDK_CHAR_LEN_64];		// 审判长
	int				m_nStatus;							// 审理状态
};

//请求设备语音播报消息
class DPSDK_API VoiceBroadCastMsg : public PrisonBaseMsg
{
public:
	VoiceBroadCastMsg(void)
	{
		m_cmd = DPSDK_CMD_PRISON_VOICEBROADCAST;
		trantype = GENERALJSON_TRAN_REQUEST;
		memset(m_szDevID, 0, sizeof(m_szDevID));
		m_nStatus = 1;
	}
	virtual ~VoiceBroadCastMsg(void){}

	char				m_szDevID[DPSDK_CHAR_LEN_32];		// 设备编号
	int					m_nStatus;							// 1:开启 0:关闭
	dsl::Json::Value	sdata;								// 发出去的数据,一般是客户端填的值
};
class DPSDK_API CMSBeginCaseNotifyMsg : public DPSDKCBMessage
{
public:
	CMSBeginCaseNotifyMsg(void);
	virtual ~CMSBeginCaseNotifyMsg(void){}
	std::string  strCameraID;
};

class DPSDK_API CMSEndCaseNotifyMsg : public DPSDKCBMessage
{
public:
	CMSEndCaseNotifyMsg(void);
	virtual ~CMSEndCaseNotifyMsg(void){}
	std::string  strCameraID;
};

class DPSDK_API CMSReloadCaseNotifyMsg : public DPSDKCBMessage
{
public:
	CMSReloadCaseNotifyMsg(void);
	virtual ~CMSReloadCaseNotifyMsg(void){}

};

class DPSDK_API UploadFileBurnedMsg: public PrisonBaseMsg
{
public:
	UploadFileBurnedMsg();
	virtual ~UploadFileBurnedMsg(){SAFE_M_DELETE(_data);}
public:
	uint32_t	_burnerId;					  // 刻录机ID，从0开始
	char	    _fileName[DPSDK_CHAR_LEN_256];// 文件名（如果文件太大可分多次发送）
	uint32_t	_action;					  // 0 开始 1 继续 2 结束（将文件信息发送给服务去上传，此时并没有启动文件刻录，只是暂时保存到服务端）
	char *      _data;                        //附件数据
	uint32_t    _dataLen;					  //数据长度
};

//删除打标
class DPSDK_API DelTrialTagMsg : public DPSDKCBMessage
{
public:
	DelTrialTagMsg(void);
	virtual ~DelTrialTagMsg(void){}

public:
	//request
	std::string		m_caseid;
	int				m_seq;
	uint64_t		m_timeStamp;  

	//response
	int				m_isOk;				//1=success;  -1=failed
};

class DPSDK_API QueryBurnerDevInfoMsg : public PrisonBaseMsg
{
public:
	QueryBurnerDevInfoMsg(void);
	virtual ~QueryBurnerDevInfoMsg(void){}

	std::string		m_strDevCode;				// 设备编码

	int				m_nCount;
	BurnerDevInfo	m_BurnerDevInfo[2];
	std::map<int, BurnerDevInfo>	m_BurnerDevInfoEx;//在光盘刻录的基础上支持其他刻录类型，如USB刻录等，而m_BurnerDevInfo只支持光盘刻录，
};

class DPSDK_API GetDeviceDiskInfoMsg : public PrisonBaseMsg
{
public:
	GetDeviceDiskInfoMsg();
	virtual ~GetDeviceDiskInfoMsg(){}

public:
	//request
	char			m_szDevId[DPSDK_DEV_ID_LEN];	//设备ID

	//response
	std::deque<Disk_Info_t> m_deqDiskInfo;			//磁盘信息
};

class DPSDK_API BackupMsg: public PrisonBaseMsg
{
public:
	BackupMsg(void);
	virtual ~BackupMsg(void){}
	char				m_deviceId[DPSDK_CHAR_LEN_32];		// 设备ID
	dsl::Json::Value	jBackup;
	std::string			strResult;
	int					nErrorMask;
	std::string         strErrorMessage;
	std::string			strCmd;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

class DPSDK_API IDPSDKPrison : public IDPSDKFuncBase
{
public:
	/** 同步时间
	@param const char* szDevId								设备ID
	@param const char* szDevIP								设备IP
	@param int nFlag										标志位：0 - 客户端不主动发起校时请求，1 - 客户端主动发起校时请求
	@return													异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int SyncTime(const char* szDevId, int nFlag, const char* szDevIP = NULL) = 0;

	/** 案例审讯人信息
	@param const CaseInfo_t caseInfo						case_info
	@param const PersonInfo_t personInfo					add
	@param const TrialInfo_t trialInfo						trial object
	@param int ndbOperator									操作
	@return												    异步顺序码,用于事件回调时,无应答
	*/
	virtual int InterrogationPersonInfo(CaseInfo_t &stuCaseInfo, PersonInfo_t &stuPersonInfo, TrialInfo_t &stuTrialInfo, int nDbOperator) = 0;

	/** 案例审讯信息
	@param const CaseInfo_t caseInfo						case_info
	@param const PersonInfo_t personInfo					add
	@param const TrialInfo_t trialInfo						trial object
	@param int ndbOperator									操作
	@return												    异步顺序码,用于事件回调时,无应答
	*/
	virtual int InterrogationCaseInfo(CaseInfo_t &stuCaseInfo, PersonInfo_t &stuPersonInfo, TrialInfo_t &stuTrialInfo, int nDbOperator) = 0;

	/** 保存案例审讯人信息
	@param STrialCaseInfo_t stuTriCaseInfo;					person_info
	@param STrialPerInfo_t stuTriPerInfo;					add
	@param int ndbOperator									操作
	@return												    异步顺序码,用于事件回调时,无应答
	*/
	virtual int SaveInterrogationPersonInfo(STrialCaseInfo_t stuTriCaseInfo, STrialPerInfo_t &stuTriPerInfo, int nDbOperator) = 0;

	/** 保存案例审讯信息
	@param STrialInfo_t stuTrialInfo;				        trial_info
	@return												    异步顺序码,用于事件回调时,无应答
	*/
	virtual int SaveInterrogationInfo(STrialInfo_t &stuTrialInfo) = 0;

	/** 保存案例审讯信息
	@param SCaseInfo_t stuCaseInfo			                case_info
	@return												    异步顺序码,用于事件回调时,无应答
	*/
	virtual int SaveInterrogationCaseInfo(SCaseInfo_t &stuCaseInfo) = 0;

	/** 下载电子记录
	@param const char* szCaseID			                    案例ID
	@param int nTrialSeq			                        审讯请求
	@param int nDbOperator		                            操作
	@return												    异步顺序码,用于事件回调时,无应答
	*/
	virtual int DownLoadNote(const char* szCaseID, int nTrialSeq, int nDbOperator) = 0;

	/** 通用消息
	@param int32_t iParam1
    @param int32_t iParam2
	@param const char* strMsg1								字符参数1
	@param const char* strMsg2								
	@param int nFlag										标志位：0 - 客户端不主动发起校时请求，1 - 客户端主动发起校时请求
	@return													异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GeneralMessage(int32_t iParam1, int32_t iParam2,const char* strMsg1, const char* strMsg2) = 0;

	/** 获取审讯标签信息
	@param uint32_t nParam1
    @param uint32_t nParam2
	@param const char* szMsg1   							字符参数1
	@param const char* szMsg2							
	@param int nFlag										标志位：0 - 客户端不主动发起校时请求，1 - 客户端主动发起校时请求
	@return													异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetInterrogateLabelInfo(uint32_t nParam1, uint32_t nParam2,const char* szMsg1, const char* szMsg2) = 0;

	/** 获取审讯用户组
    @param int nUserId
	@param int nRole										1- 操作组， 2 - 审讯组，3 - 指挥组
	@return													异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetInterrogationUserGroups(int nRole) = 0;

	/** 获取单个案例信息
	@param uint32_t nParam1
    @param uint32_t nParam2
	@param const char* szMsg1   							字符参数1
	@param const char* szMsg2							
	@param int nFlag										标志位：0 - 客户端不主动发起校时请求，1 - 客户端主动发起校时请求
	@return													异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetSingleCaseInfo(uint32_t nParam1, uint32_t nParam2,const char* szMsg1, const char* szMsg2) = 0;

	/** 最近审讯请求
	@param const char* szCaseId
    @param int nDbOperator
	@return													异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int InterrogationSeq(const char* szCaseId, int nDbOperator) = 0;

	/** 电子模板
	@param SNoteTemp_t stuNoteTemp				            电子模板
	@return												    异步顺序码,用于事件回调时,无应答
	*/
	virtual int NoteTemplate(SNoteTemp_t  &stuNoteTemp) = 0;

	/** 一般判决
	@param const char* szUserId					 
	@param int nDbOperator				        				            
	@return												    异步顺序码,用于事件回调时,无应答
	*/
	virtual int CommonSentence(const char* szUserId,  int nDbOperator) = 0;

	/** 所有通报
	@param SNotifyAll_t stuNotifyAll				        电子模板
	@return												    异步顺序码,用于事件回调时,无应答
	*/
	virtual int NotifyAll(SNotifyAll_t  &stuNotifyAll) = 0;

	/** 登录审讯
	@param const char* szLoginUserName				        电子模板
	@return												    异步顺序码,用于事件回调时,无应答
	*/
	virtual int LoginInterrogation(const char* szLoginUserName) = 0;

	/** 获得电子模版
	@param int nDbOperator			            
	@return												    异步顺序码,用于事件回调时,无应答
	*/
	virtual int GetTemplateList(int nDbOperator) = 0;

	/** 卷宗管理,重点标注查询(标签查询)
	 @param std::string caseid								案例ID案件编号
	 @param int seq											审讯序号
	 @param std::string depCoding							级联组织Coding
	 @return												异步顺序码,用于事件回调时,无应答
	 */
	virtual int QueryTag(std::string caseid, int seq, std::string depCoding = "") = 0;

	/** 重点标注/打标 审讯打标
	 @param std::string caseid								案件编号
	 @param int seq											审讯序号
	 @param uint64_t timeStamp								时间戳
	 @param std::string desp								标签描述信息
	 @param std::string depCoding							级联组织Coding
	 @return												异步顺序码,用于事件回调时,无应答
	 */
	virtual int AddTrialTag(std::string caseid, int seq, uint64_t timeStamp, std::string desp, std::string depCoding = "") = 0;

	/** 上传FTP文件
	@param const char* ftpUrl								ftp服务器存储数据的相对url
	@param const char* strLocalPath							本地上传或者下载后的图片的地址	
	*/
	virtual int FTPUploadFile(const char* ftpUrl, const char* strLocalPath, const char* strIpIn = "", const char* strIpOut = "", const char* strUser = "", const char* strPassword = "", dpsdk_ftp_transport_mode_e mode = MODE_EPSV) = 0;
	
	/** 下载FTP文件
	@param const char* ftpUrl								ftp服务器存储数据的相对url
	@param const char* strLocalPath							本地上传或者下载后的图片的地址	
	*/
	virtual int FTPDownloadFile(const char* ftpUrl, const char* strLocalPath, const char* strIpIn = "", const char* strIpOut = "", const char* strUser = "", const char* strPassword = "", dpsdk_ftp_transport_mode_e mode = MODE_EPSV) = 0;

	/** 删除FTP文件
	@param const char* ftpUrl								ftp服务器存储数据的相对url	
	*/
	virtual int FTPDelFile(const char* ftpUrl, dpsdk_ftp_transport_mode_e mode = MODE_EPSV) = 0;

	/** 获取刻录机信息
	@param std::string& deviceId							设备ID
	@return													-1失败; 0成功 数据存于PDataCenter::m_burnerInfo
	*/
	virtual int GetDevBurnerInfo(std::string& deviceId) = 0;

	/** 刻录片头设置
	@param DevBurnerInfoHeader_t& infoHeader				片头信息
	@param TrialFormAttrName_t& attrName					审讯表单属性名
	@return													-1失败; 0成功
	*/
	virtual int SetDevBurnerHeader(DevBurnerInfoHeader_t& infoHeader, TrialFormAttrName_t& attrName) = 0;

	/** 刻录控制
	@param std::string& deviceId							设备ID
	@param EnumControlBurnerCmd cmd							控制命令
	@param int channelMask									通道掩码
	@param int burnerMask									刻录机掩码
	@return													-1失败; 0成功
	*/
	virtual int ControlDevBurner(std::string& deviceId, EnumControlBurnerCmd cmd, int channelMask, int burnerMask) = 0;

	/** 获取刻录实时状态信息
	@param std::string& deviceId							设备ID
	@param uint32_t burnerId								光盘刻录机ID (id从0开始计数)
	@return													-1失败; 0成功 PDataCenter::m_burnerCDState->光盘0状态信息;  PDataCenter::m_burnerCDState2->光盘1状态信息
	*/
	virtual int GetDevBurnerCDState(std::string& deviceId, uint32_t burnerId) = 0;

	
	/** 庭审刻录控制
	@param std::string& deviceId							设备ID
	@param EnumControlBurnerCmd cmd							控制命令
	@param int channelMask									通道掩码    第1个通道为1；第2个通道是：1<<1;第3个是1<<2
	@param int burnerMask									刻录机掩码  1表示光驱1；2光驱2；3双光驱
	@param int emMode										刻录模式  
	@param int emPack										刻录流格式
	@return													-1失败; 0成功
	*/
	virtual int ControlDevBurner(std::string& deviceId, EnumControlBurnerCmd cmd, int channelMask, int burnerMask, int emMode, int emPack, int nType = 1) = 0;

	
	/** 获取编码计划(刻录参数)
	@param EncodePlanReq_t& req								编码计划请求
	@return													-1失败; 0成功
	*/
	virtual int GetEncodePlan(EncodePlanReq_t& req) = 0;

	/** 设置编码计划(刻录参数)
	@param EncodePlanReq_t& req								编码计划请求
	@return													-1失败; 0成功
	*/
	virtual int SetEncodePlan(EncodePlanReq_t& req) = 0;

	/** 设置刻录格式
	@param std::string& deviceId							编码计划请求
	@param const char * format								格式format=DHAV 大华码流;format=PS流 目前仅支持两种 DHAV、PS
	@return													-1失败; 0成功
	*/
	virtual	int SetBurnRecordFormat(std::string& deviceId, const char * format) =0;

	/** 保存刻录参数
	@param BurnParam_t& param								刻录参数
	@return													-1失败; 0成功
	 */
	virtual int SaveBurnParam(BurnParam_t& param) = 0;


	/** 查询刻录参数
	@param std::string devId								设备ID
	@return													-1失败; 0成功
	 */
	virtual int QueryBurnParam(std::string devId) = 0;

	/** 语音激励
	 @param const char* szDevId								设备ID
	 @param int nOpen										操作类型，0表示关，1表示开
	 @return												异步顺序码
	 */
	virtual int VoiceImpel(const char* szDevId, int nOpen) = 0;

	/** DVD控制
	 @param const char* szDevId								设备ID
	 @param int nOperation									操作类型
	 @return												异步顺序码
	 */
	virtual int DVDControl(const char* szDevId, int operChannelId, int nOperation) = 0;

	/** 设置组合屏信息
	 @param const char* szDevId								设备ID
	 @param int compMode									组合屏模式
	 @param int chnlNo										通道号
	 @param std::vector<int> compDetail						组合屏细节
	 @return												异步顺序码
	 */
	virtual int SetCombinedScreen( const char* szDevId, int chnlNo, int compMode, std::vector<int> compDetail ) = 0;

	/** 获取组合屏信息
	 @param const char* szDevId								设备ID
	 @param int chnlNo										通道号
	 @return												异步顺序码
	 */
	virtual int GetCombinedScreen( const char* szDevId, int chnlNo) = 0;
	/** 请求庭审抓图
	@param std::string& strJson								Json串
	@return													异步顺序码
	 */
	virtual int CourtSnap( std::string& strJson) = 0;

	/** 设置矩阵信息
	 @param const char* szDevId								设备ID
	 */
	virtual int SendTaskToMatrix( const char* szDevId,const int nChn,int decodeChn[],int decodeChnLenth ) = 0;
	
	/** //获取矩阵信息
	 */
	virtual int ResetDefaultMatrix(const char* szDevId) = 0;

	/** 直播控制
	 @param const char* strCaseCode							案件编号
	 @param int   nCaseNum									案件次数
	 @param const char* strJudge							审判长
	 @param bool  bIsEnable							        1允许直播, 2禁止直播
	 @return												异步顺序码
	 */
	virtual int ControlLive(const char* strCaseCode, int nCaseNum, const char* strJudge, bool bIsEnable) = 0;

	/** 请求语音播报
	 @param const char* szDevID								设备ID
	 @param int	nStatus										1开始, 0停止
	 @param dsl::Json::Value sdata							json串，存储文件完整ftp路径名
	 @return												异步顺序码
	 */
	virtual int VoiceBroadCast(const char* szDevID, int nStatus, dsl::Json::Value sdata) = 0;

	virtual	int UploadFileBurned(UploadFileReq_t& uploadFileReq) =0;

	/** 卷宗管理,删除标注(标签删除)
	 @param std::string caseid								案例ID案件编号
	 @param int seq											审讯序号
	 @param uint64_t timeStamp								时间戳
	 @return												异步顺序码,用于事件回调时,无应答
	 */
	virtual int DelTrialTag(std::string caseid, int seq, uint64_t timeStamp) = 0;

	/** 查询光盘信息
	 @param const char* szDevId								设备ID
	 @return												异步顺序码,用于事件回调时,无应答
	 */
	virtual int QueryBurnerDevInfo(const char* szDevId) = 0;

	/** 获取设备磁盘信息
	@param const char* szDevId								设备ID
	@return													异步顺序码
	*/
	virtual int GetDeviceDiskInfo(const char* szDevId) = 0;

	virtual int OnControlBackup(dsl::Json::Value& jBackup)=0;
protected:
	virtual ~IDPSDKPrison(void){}	
};
//////////////////////////////////////////////////////////////////////////

END_NAMESPACE_DPSDK

#endif

