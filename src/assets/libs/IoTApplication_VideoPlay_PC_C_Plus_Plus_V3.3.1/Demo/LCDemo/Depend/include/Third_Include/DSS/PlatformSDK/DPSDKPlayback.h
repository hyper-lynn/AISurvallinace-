/**
 * Copyright (c) 2012, 浙江大华
 * All rights reserved.
 *
 * 文件名称：
 * 文件标识：
 * 摘　　要：Platform SDK的接口文件,回放子模块
 *
 * 当前版本：1.0
 * 原作者　：12928
 * 完成日期：2012年8月24日
 * 修订记录：创建
 */

#ifndef INCLUDED_DPSDK_DPSDKPLAYBACK_H
#define INCLUDED_DPSDK_DPSDKPLAYBACK_H

#include "DPSDK.h"
#include <vector>
#include <string>

BEGIN_NAMESPACE_DPSDK
//////////////////////////////////////////////////////////////////////////

// 录像来源。1全部，2设备，3中心
typedef enum
{
	PB_RECSOURCE_ALL			= 1,							// 所有
	PB_RECSOURCE_DEVICE			= 2,							// 设备录像
	PB_RECSOURCE_PLATFORM		= 3,							// 平台录像
}dpsdk_recsource_type_e;

// 录像类型（时间回放参数）。1普通，2报警，81补录
typedef enum
{
	PB_RECTYPE_NORMAL			= 1,							// 普通录像
	PB_RECTYPE_ALARM			= 2,							// 报警录像
	PB_RECTYPE_SUPPLEMENT		= 81,							// 补录录像
}dpsdk_rectype_e;

// 
typedef enum
{
	QUERYRECORD_SOURCE_DSS		= 1,							// 
	QUERYRECORD_SOURCE_PSS,										// 
}dpsdk_queryrecord_source_e;

// 录像类型
typedef enum
{
	PB_RECORD_TYPE_ALL			= -1,							// 全部录像PSS用
	PB_RECORD_UNKONWN			= 0,							// 全部录像DSS用
	PB_RECORD_MANUAL			= 1,							// 手动录像
	PB_RECORD_ALARM				= 2,							// 报警录像
	PB_RECORD_MOTION_DETECT		= 3,							// 移动侦测
	PB_RECORD_VIDEO_LOST		= 4,							// 视频丢失
	PB_RECORD_VIDEO_SHELTER		= 5,							// 视频遮挡
	PB_RECORD_TIMER				= 6,							// 定时录像
	PB_RECORD_ALL_DAY			= 7,							// 全天录像
	//PB_RECORD_CARD			= 25,							// 卡号录像 协议库里面没有这个了暂时去掉
}dpsdk_record_type_e;

// 
typedef enum
{
	OP_TYPE_UNKNOW				= 0,							// 
	OP_TYPE_ADD,												// 新增
	OP_TYPE_MODIFY,												// 修改
	OP_TYPE_DELETE,												// 删除
}dpsdk_operator_type_e;

// 播放状态
typedef enum
{
	OP_TYPE_PREPLAY				= 0,							// 
	OP_TYPE_PLAY,												// 新增
	OP_TYPE_PREPAUSE,											// 修改
	OP_TYPE_PAUSE,												// 删除
}dpsdk_playbck_type_e;

// 
typedef enum
{
	PB_MODE_NORMAL				= 1,							// 普通录像
	PB_MODE_DOWNLOAD,											// 下载
}dpsdk_pb_mode_e;

typedef enum
{
	SPEED_MODE_DEFAULT				= 0,						// 默认方式
	SPEED_MODE_SPEED,											// 全帧
	SPEED_MODE_SCALE                                            // 抽帧
}dpsdk_speed_mode_e;

//码流类型
typedef enum{
	ALL_TYPE = 0,												// 主+辅
	MAIN_TYPE,													// 主码流
	ASSIST_TYPE,												// 辅码流
	THIRD_TYPE,													// 三码流
}record_streamtype_e;

//设备厂家类型
typedef enum
{
	DEV_PROVIDER_UNKNOWN		= 0,
	DEV_PROVIDER_DAHUA,											// 大华
	DEV_PROVIDER_HIK,											// 海康：回放设置码流速度时，海康设备要传full
}dev_provider_e;

typedef enum
{
	PSTREAM_TYPE_UNKNOWN		= 0,
	PSTREAM_TYPE_MAIN,											// 主码流
	PSTREAM_TYPE_MINOR,											// 辅码流
	PSTREAM_TYPE_THIRD,											// 三码流
}pstream_type_e;

typedef enum
{
	QUERY_TYPE_NORMAL			= 0,							// 普通录像查询
	QUERY_TYPE_EXTENT_INFO,										// 查询结果需有录像隐藏状态字段
}dpsdk_timeQuery_type_e;

// (DSS使用)
typedef struct DPSDK_API tagRecord_Info 									// fixme:这个结构体出自协议栈 比较累赘
{
	unsigned char	source;										// 来源类型：参见dpsdk_recsource_type_e
	unsigned int	recordType;									// 录像类型。参见dpsdk_record_type_e
	unsigned int	startTime;									// 起始时间
	unsigned int	endTime;									// 结束时间
	char			name[DPSDK_REC_FILENAME_LEN];				// 录像名字（不同厂家对文件的标识不同）
	unsigned int	length;										// 文件长度
	unsigned int	streamType;									// 主辅码流标志：参见pstream_type_e
	
	//下面是中心录像所需要的信息
	int64_t     	planId;										// 录像计划ID
	unsigned int	ssId;										// 存储服务ID
	char			diskId[DPSDK_REC_DISKID_LEN];				// 磁盘ID
	unsigned int	fileHandle;									// 文件句柄
	char			devId[DPSDK_DEV_ID_LEN];					// 支持报警录像回放，因为报警源与录像设备是分开的
	int				channelNo;									// 
	bool			bRecordHidden;								// 录像隐藏状态 true：隐藏 ；false 可见
	bool			bForgotten;									// 是否淡忘录像

	tagRecord_Info();
}Record_Info_t;

// (DSS使用)
typedef struct DPSDK_API tagDSS_NET_RECORDFILE_INFO
{
	dpsdk_recsource_type_e	source;								// 录像来源
	dpsdk_pb_mode_e			mode;								// 回放模式
	char					filename[DPSDK_REC_FILENAME_LEN];	// 录像名字（不同厂家对文件的标识不同）
	uint32_t				ssId;								// 存储服务ID(查询时返回)
	char					diskId[DPSDK_REC_DISKID_LEN];		// 磁盘ID(查询时返回)
	uint64_t				fileHandle;							// 文件句柄(查询时返回)
	int64_t					begTime;							// 开始时间
	int64_t					endTime;							// 结束时间
	uint64_t				fileOffset;							// 按文件回放偏移量，单位byte
	char                    trackID[DPSDK_TRANCODE_LEN];

	tagDSS_NET_RECORDFILE_INFO();
}DSS_NET_RECORDFILE_INFO, *LPDSS_NET_RECORDFILE_INFO;

// (DSS使用)	//for new Protocol:28181
typedef struct DPSDK_API tagDSS_NET_RECORDFILE_INFO_EX
{
	dpsdk_recsource_type_e	source;								// 录像来源
	dpsdk_pb_mode_e			mode;								// 回放模式
	char					filename[DPSDK_REC_FILENAME_LEN];	// 录像名字（不同厂家对文件的标识不同）
	uint32_t				ssId;								// 存储服务ID(查询时返回)
	char					diskId[DPSDK_REC_DISKID_LEN];		// 磁盘ID(查询时返回)
	uint64_t				fileHandle;							// 文件句柄(查询时返回)
	int64_t					begTime;							// 开始时间
	int64_t					endTime;							// 结束时间
	uint64_t				fileOffset;							// 按文件回放偏移量，单位byte

	char                    dstIp[DPSDK_IP_LEN];
	char                    trackID[DPSDK_TRANCODE_LEN];
	uint32_t                dstPort;
	int						rtpHeadType;

	tagDSS_NET_RECORDFILE_INFO_EX();
}DSS_NET_RECORDFILE_INFO_EX, *LPDSS_NET_RECORDFILE_INFO_EX;

// (PSS使用)
typedef struct DPSDK_API tagPSS_NET_TIME
{
	uint32_t		        dwYear;							    // 年
	uint32_t		        dwMonth;					  		// 月
	uint32_t		        dwDay;							    // 日
	uint32_t		        dwHour;								// 时
	uint32_t		        dwMinute;							// 分
	uint32_t		        dwSecond;							// 秒
}PSS_NET_TIME, *LPPSS_NET_TIME;

// (PSS使用)
typedef struct DPSDK_API tagPSS_NET_RECORDFILE_INFO
{
	unsigned int	        ch;									// 通道号
	char			        filename[128];						// 文件名
	unsigned int	        size;								// 文件长度
	PSS_NET_TIME	        starttime;							// 开始时间
	PSS_NET_TIME	        endtime;							// 结束时间
	unsigned int	        driveno;							// 磁盘号(区分网络录像和本地录像的类型，0－127表示本地录像，128表示网络录像)
	unsigned int	        startcluster;						// 起始簇号
	unsigned char	        nRecordFileType;					// 录象文件类型  0：普通录象；1：报警录象；2：移动检测；3：卡号录象；4：图片
	unsigned char	        bImportantRecID;					// 0:普通录像 1:重要录像
	unsigned char	        bHint;								// 文件定位索引
	unsigned char	        bRecType;							// 0-主码流录像 1-辅码1流录像 2-辅码流2 3-辅码流3录像
}PSS_NET_RECORDFILE_INFO, *LPPSS_NET_RECORDFILE_INFO;

// 
typedef struct DPSDK_API tagTag_Info
{
	dpsdk_recsource_type_e	source;								// 来源
	uint32_t				tagid;								// 标签ID
	char					cameraId[DPSDK_CHL_ID_LEN];			// 摄像头ID
	uint64_t				tagtime;							// tag的时间
	uint64_t				endtime;							// 课表录像标签使用，为0时是普通录像打标，不为0时，为课表录像标签录像的结束时间
	char					subject[DPSDK_TAG_SUBJECT_LEN];		// 主题
	char					content[DPSDK_TAG_CONTENT_LEN];		// 内容
	int32_t					ownerid;							// 创建者的ID
	uint64_t				ownertime;							// 创建时间(修改时间)
	char					url[DPSDK_TAG_URL_LEN];				// 存放图片的url
	unsigned int            roomId;								// 纪委需求：房间ID号
	char                    chnName[DPSDK_CHANL_NAME_LEN];   	// 纪委需求：通道名称
	int						readStat;							// 绍兴监管支队DH-DSS-P750功能定制：阅读状态 0-未阅读；1-已阅读。默认0
	char					ownerUserName[DPSDK_CHAR_LEN_64];	// 打标用户名称
	uint64_t				begintime;							// 打标开始时间

	tagTag_Info();
}Tag_Info_t;

typedef struct DPSDK_API tagPlaybackByFile_Info
{
	char					 cameraId[DPSDK_CHL_ID_LEN];		// 摄像头ID
	DSS_NET_RECORDFILE_INFO* pRecInfo;
	fMediaDataCallback       funCB;
	void*					 pCBParam;
	dpsdk_check_right_e		 right;
	int						 transMode;
	bool					 bBack;
	bool					 bCheckStatus;
	dpsdk_speed_mode_e		 eSpeedMode;
	bool					 bBackUp;							// 是否查询上级备份的下级录像
	int						 videoOnLowerPlatform;		        //综治项目： 回放在上级配置了存储的下级点位中心录像时， 此标志表明录像的存储位置(0默认位置，1 存储下级)
	tagPlaybackByFile_Info()
	{
		memset(cameraId, 0, sizeof(cameraId));

		right = DPSDK_CHECK_RIGHT;
		transMode = 1;
		bBack = false;
		bCheckStatus = true;
		eSpeedMode = SPEED_MODE_DEFAULT;
		bBackUp  = false;
		pRecInfo = NULL;
		funCB = NULL;
		pCBParam = NULL;
		videoOnLowerPlatform = 0;
	}
}PlaybackByFile_Info_t;

typedef struct DPSDK_API tagPlaybackByTime_Info
{
	char					 cameraId[DPSDK_CHL_ID_LEN];		// 摄像头ID
	dpsdk_recsource_type_e	 source;
	uint64_t				 beginTime;
	uint64_t				 endTime;
	dpsdk_pb_mode_e			 mode;
	fMediaDataCallback		 funCB;
	void*					 pCBParam;

	dpsdk_check_right_e		 right;
	pstream_type_e			 streamType;

	char                    trackID[DPSDK_TRANCODE_LEN];
	//const char* trackID = "";
	int						transMode;
	bool				    bBack;
	bool					isVideoPlayback;
	bool				    bCheckStatus;
	dpsdk_speed_mode_e		eSpeedMode;
	bool					bBackUp;							// 是否查询上级备份的下级录像
	dpsdk_tcpmode           tcpmode;                            //  0,默认,1 TCP主动模式,2 TCP被动模式,
	int						isNewMedia;							//0:不是；1:是； (业务：社会面视频接入需求添加
	int						videoOnLowerPlatform;				//综治项目： 回放在上级配置了存储的下级点位中心录像时， 此标志表明录像的存储位置(0默认位置，1 存储下级)
	dpsdk_rectype_e         recordType;							//录像类型(时间回放参数) 1普通，2 报警 81补录录像
	tagPlaybackByTime_Info()
	{
		memset(cameraId, 0, sizeof(cameraId));

		right = DPSDK_CHECK_RIGHT;
		streamType = PSTREAM_TYPE_MAIN;
		memset(trackID, 0, sizeof(trackID));
		transMode = 1;
		bBack = false;
		isVideoPlayback = false;
		bCheckStatus = true;
		eSpeedMode = SPEED_MODE_DEFAULT;
		bBackUp = false;
		tcpmode = DPSDK_TCPMODE_DEFAULT;
		source = PB_RECSOURCE_ALL;
		beginTime = 0;
		endTime = 0;
		mode = PB_MODE_NORMAL;
		funCB = NULL;
		pCBParam = NULL;
		isNewMedia = 1;
		videoOnLowerPlatform = 0;
		recordType = PB_RECTYPE_NORMAL;
	}
}PlaybackByTime_Info_t;

// 
union URecordInfo
{
	Record_Info_t*				pRecord;						// 具体的record数据，由CMS申请放入datacenter，由datacenter在erase时释放。
	PSS_NET_RECORDFILE_INFO*	pNetRecordFileInfo;				// 
};
//////////////////////////////////////////////////////////////////////////

// 
class DPSDK_API QueryRecordMsg : public DPSDKCBMessage
{
public:
	QueryRecordMsg(void);
	virtual ~QueryRecordMsg(void);

public:
	dpsdk_queryrecord_source_e	querySource;					// 
	char						cameraId[DPSDK_CHL_ID_LEN];		// 查询通道
	dpsdk_check_right_e			right;
	int							recSource;						// 录像来源，见dpsdk_recsource_type_e
	int							recType;						// 录像类型，见Record_Type_e
	int64_t						beginTime;						// 录像开始时间
	int64_t						endTime;						// 录像开始时间
	int							subStream;						// 主辅码流，见record_streamtype_e
	std::vector<int>			vecRecType;						// 组合查询录像类型
	
	int							recCount;						// 
	URecordInfo					uniRecord;						// 

	char                        szAlarmID[64];
	dpsdk_timeQuery_type_e		nQueryFlag;						// 0普通查询，1查询具有录像隐藏状态的录像信息
	bool						bBackUp;						// 是否查询上级存储的下级备份录像
	int							queryOnLowerPlatform;			// 指定在下级域查询乐橙云平台的点位录像  0不指定 1指定去下级域查询
};

//删除录像文件
class DPSDK_API DeleteRecordMsg : public DPSDKCBMessage
{
public:
	DeleteRecordMsg(void);
	virtual ~DeleteRecordMsg(){}

public:
	uint32_t		ssId;
	char			diskId[DPSDK_REC_DISKID_LEN];				// 磁盘ID
	uint32_t		fileHandle;
	char			filename[DPSDK_REC_FILENAME_LEN];
	int				recCount;
};

// 查询有录像的日期（单通道）---cmd=DPSDK_CMD_QUERYDATE_HASRECORD
class DPSDK_API QueryDateHasRecordMsg : public DPSDKCBMessage
{
public:
	QueryDateHasRecordMsg(void);
	virtual ~QueryDateHasRecordMsg(void){}

public:
	// request
	dpsdk_record_type_e	recType;								// 录像类型
	char				cameraId[DPSDK_CHL_ID_LEN];				// 查询通道
	int					recSource;								// 录像来源，见dpsdk_recsource_type_e
	uint64_t			beginTime;								// 开始时间
	uint64_t			endTime;								// 结束时间
	bool				bBackUp;								// 是否查询上级备份的下级录像
	dpsdk_check_right_e	right;
	
	// response
	char				days[DPSDK_RECORD_DAYS_LEN];			// 有录像的天，以逗号隔开
};

// 
class DPSDK_API StartPbByFileMsg : public DPSDKCBMessage
{
public:
	StartPbByFileMsg(void);
	virtual ~StartPbByFileMsg(void);

public:
	dpsdk_recsource_type_e		recSource;							// 
	dpsdk_queryrecord_source_e	querySource;						// 
	dpsdk_pb_mode_e				mode;								// 
	uint32_t					sessionId;							// 
	char						cameraId[DPSDK_CHL_ID_LEN];			//
	bool						bCheckStatus;
	dpsdk_check_right_e			right;
	char						filename[DPSDK_REC_FILENAME_LEN];	// 
	uint32_t					ssId;								// 
	char						diskId[DPSDK_REC_DISKID_LEN];		// 
	uint64_t					fileHandle;							// 
	int64_t						beginTime;							// 
	int64_t						endTime;							//
	uint64_t					fileOffset;								// 按文件回放偏移量，单位byte

	fMediaDataCallback			cbFun;								// 
	void*						pCBParam;							// 
	
	URecordInfo					uniRecord;							// 
	int							transMode;							// 1 tcp,0 udp;
	bool						bBack;
	bool						bAllFrame;							//倒放参数
	bool						bBackUp;							//是否上级备份的下级录像
	int							videoOnLowerPlatform;		        //综治项目： 回放在上级配置了存储的下级点位中心录像时， 此标志表明录像的存储位置(0默认位置，1 存储下级)

	//for new Protocol:28181
	char						rtpSsrc[DPSDK_RTPCODE_LEN];
	char						srcIp[DPSDK_IP_LEN];
	uint32_t					srcPort;

	dpsdk_speed_mode_e          eSpeedMode;
};

// 
class DPSDK_API StartPbByTimeMsg : public DPSDKCBMessage
{
public:
	StartPbByTimeMsg(void);
	virtual ~StartPbByTimeMsg(void){}

public:
	dpsdk_recsource_type_e	recSource;							// 
	dpsdk_pb_mode_e			mode;								// 
	uint32_t				sessionId;							// 
	char					cameraId[DPSDK_CHL_ID_LEN];			// 
	bool					bCheckStatus;
	dpsdk_check_right_e		right;
	pstream_type_e			streamType;
	
	int64_t					beginTime;							// 
	int64_t					endTime;							// 
	
	fMediaDataCallback		cbFun;								// 
	void*					pCBParam;							// 
	int						transMode;							// 1 tcp,0 udp;
	bool					bBack;
	bool					bAllFrame;							//倒放参数
	bool					bBackUp;							//是否上级备份的下级录像

	
	bool					isVideoPlayBcak;					// 区别是录像下载还是回放
	dpsdk_tcpmode			tcpmode;							//  0,默认,1 TCP主动模式,2 TCP被动模式,
	int						isNewMedia;							//0:不是；1:是； (业务：社会面视频接入需求添加）
	int						isDirectMedia;						//1: 直接从下级域MTS取流播放视频；0:原有流程（综治平台的最短路径字段，管理端添加域时配置来区分）
	int						videoOnLowerPlatform;		        //综治项目： 回放在上级配置了存储的下级点位中心录像时， 此标志表明录像的存储位置(0默认位置，1 存储下级)
	dpsdk_rectype_e			recordType;							//录像类型 1普通，2 报警 81补录录像
	//for new Protocol:28181
	char					rtpSsrc[DPSDK_RTPCODE_LEN];
	char					srcIp[DPSDK_IP_LEN];
	uint32_t				srcPort;
	dpsdk_speed_mode_e      eSpeedMode;
};

// 
class DPSDK_API StopPlaybackMsg : public DPSDKCBMessage
{
public:
	StopPlaybackMsg(void);
	virtual ~StopPlaybackMsg(void){}

public:
	uint32_t	sessionId;										// 

};

// 
class DPSDK_API PausePlaybackMsg : public DPSDKCBMessage
{
public:
	PausePlaybackMsg(void);
	virtual ~PausePlaybackMsg(void){}

public:
	uint32_t	sessionId;										// 
	int			nProvider;										// 厂商类型
};

// 
class DPSDK_API ResumePlaybackMsg : public DPSDKCBMessage
{
public:
	ResumePlaybackMsg(void);
	virtual ~ResumePlaybackMsg(void){}

public:
	uint32_t	sessionId;										// 
	float		speed;											// 
	int			nProvider;										// 厂商类型						
};

// 
class DPSDK_API SeekPlaybackMsg : public DPSDKCBMessage
{
public:
	SeekPlaybackMsg(void);
	virtual ~SeekPlaybackMsg(void){}

public:
	uint32_t	sessionId;										// 
	uint64_t	nBeginTime;										//
	uint64_t	nEndTime;										// 
};

// 
class DPSDK_API SetSpeedPlaybackMsg : public DPSDKCBMessage
{
public:
	SetSpeedPlaybackMsg(void);
	virtual ~SetSpeedPlaybackMsg(void){}

public:
	uint32_t	sessionId;										// 
	float		speed;											// 
	int			nPorvider;										// 设备厂商类型：海康设备设置码流速度时，要传full
};

// 
class DPSDK_API DataOverMsg : public DPSDKCBMessage
{ 
public:
	DataOverMsg(void);
	virtual ~DataOverMsg(void){}

public:
	dpsdk_pb_mode_e		pbMode;									// 
	uint32_t			sessionId;								// 
};

// 
class DPSDK_API QueryAlarmRecordMsg : public DPSDKCBMessage
{
public:
	QueryAlarmRecordMsg(void);
	virtual ~QueryAlarmRecordMsg(void);

public:
	//request
	char		alarmId[DPSDK_ALARMCODE_LEN];					// 

	//response
	int			recCount;										//
	URecordInfo uniRecord;										// 
};

// 
class DPSDK_API QueryTagInfoMsg : public DPSDKCBMessage
{
public:
	QueryTagInfoMsg(void);
	virtual ~QueryTagInfoMsg(void);

public:
	dpsdk_recsource_type_e	source;								// 所打标的录像的来源
	char					cameraId[DPSDK_CHL_ID_LEN];			// 摄像头ID
	uint64_t				beginTime;							// 开始时间
	uint64_t				endTime;							// 结束时间
	int32_t					owner;								// 标的拥有者
	char					subject[DPSDK_TAG_SUBJECT_LEN];		// 主题(模糊搜索)
	int						readStat;							// 标签阅读状态  0-未读；1-已读；值<0时则不作为查询条件

	int						tagCount;							// 
	Tag_Info_t*				tagInfos;							// 
};

// 
class DPSDK_API OperatorTagInfoMsg : public DPSDKCBMessage
{
public:
	OperatorTagInfoMsg(void);
	virtual ~OperatorTagInfoMsg(void);

public:
	dpsdk_operator_type_e	opType;								// 操作类型
	Tag_Info_t				tagInfo;
};

// 
class DPSDK_API OperatorTagImageMsg : public DPSDKCBMessage
{
public:
	OperatorTagImageMsg(void);
	virtual ~OperatorTagImageMsg(void);

public:
	dpsdk_operator_ftp_type_e	opType;							// 操作类型 e.g. OP_FTP_TYPE_DOWN 下载 OP_FTP_TYPE_UP 上传 OP_FTP_TYPE_DELETE 删除
	char						url[DPSDK_TAG_URL_LEN];			// ftp服务器存储数据的相对url
	char						path[DPSDK_TAG_PATH_LEN];		// 本地上传或者下载后的图片的地址
	dpsdk_ftp_transport_mode_e	mode;							// 文件传输模式
};

// 
class DPSDK_API SSExpctionMsg : public DPSDKCBMessage
{
public:
	SSExpctionMsg(void);
	virtual ~SSExpctionMsg(void){};

	char		cameraId[DPSDK_CHL_ID_LEN];						// 摄像头ID
	int			nSessionId;										// 回放会话ID
	char		szUrl[1024];									// 
};

// 回放保活
class OptionPlaybackMsg : public DPSDKCBMessage
{
public:
	OptionPlaybackMsg(void);
	virtual ~OptionPlaybackMsg(void){}

public:
	uint32_t	sessionId;										// 

	char		szRange[64];
};

// 第一段录像的时间
class DPSDK_API FirstRecordMsg : public DPSDKCBMessage
{
public:
	FirstRecordMsg(void);
	virtual ~FirstRecordMsg(void){}

public:
	char		cameraId[DPSDK_CHL_ID_LEN];						// 摄像头ID
	uint64_t	beginTime;										// 
};

// 
class DPSDK_API GetPbByTimeUrlMsg : public DPSDKCBMessage
{
public:
	GetPbByTimeUrlMsg(void);
	virtual ~GetPbByTimeUrlMsg(void){}

public:
	// request
	char					cameraId[DPSDK_CHL_ID_LEN];			// 
	dpsdk_recsource_type_e	recSource;							// 
	int64_t					beginTime;							// 
	int64_t					endTime;							// 
	dpsdk_check_right_e		right;
	uint32_t				recordType;							// 录像类型 1 一般录像,2 报警录像

	// response
	char szUrl[DPSDK_TAG_URL_LEN];
	uint32_t nSessionId;										// cms sessionid
	int nToken;
};

class DPSDK_API ClosePbByTimeUrlMsg : public DPSDKCBMessage
{
public:
	ClosePbByTimeUrlMsg(void);
	virtual ~ClosePbByTimeUrlMsg(void){};

public:
	uint32_t nSessionId;
};

class DPSDK_API StartPbByRtspUrlMsg : public DPSDKCBMessage
{
public:
	StartPbByRtspUrlMsg(void);
	virtual ~StartPbByRtspUrlMsg(void){};

public:
	dpsdk_recsource_type_e		recSource;							// 
	dpsdk_pb_mode_e				mode;								//
	uint32_t					sessionId;							// GetPlaybackByTimeUrl()返回的SessionId
	char						cameraId[DPSDK_CHL_ID_LEN];			// 
	dpsdk_check_right_e			right; 
	fMediaDataCallback			cbFun;								// 
	void*						pCBParam;							// 
	int							transMode;							// 1 tcp,0 udp;
	char						szRtspUrl[DPSDK_TAG_URL_LEN];
	uint32_t					nSessionForCMS;						// cms sessionid
	int							nToken;

	//扩展字段，为了向指定地址发送视频流
	bool						enableEx;
	std::string					dstIp;
	uint32_t					dstPort;
	std::string					trackID;
	int							rtpHeadType;
	float						speed;

	//response
	//for new Protocol:28181
	char						rtpSsrc[DPSDK_RTPCODE_LEN];
	char						srcIp[DPSDK_IP_LEN];
	uint32_t					srcPort;
};

class DPSDK_API PlayBackByTimeDescribeMsgEx: public DPSDKCBMessage
{
public:
	PlayBackByTimeDescribeMsgEx(void);
	virtual ~PlayBackByTimeDescribeMsgEx(void);
public:
	dpsdk_check_right_e			right;							// 是否检查权限，DPSDK_NOT_CHECK_RIGHT，不会检查cameraId在组织树缓存中是否存在
	int							transMode;						// 1 tcp,0 udp; 
	int							sessionId;
	char						cameraId[DPSDK_CHL_ID_LEN];
	dpsdk_recsource_type_e		recSource;
	uint64_t					beginTime;
	uint64_t					endTime; 
	std::string 				trackID;
	pstream_type_e				streamType;						 // 主辅码流类型
	bool						enableEx;
	std::string					rtspUrl;
	uint32_t					sessionForCMS;
	uint32_t					token;

	//response
	char*						sdp;
	int							sdpLength;
};

class DPSDK_API PlayBackByFileDescribeMsgEx: public DPSDKCBMessage
{
public:
	PlayBackByFileDescribeMsgEx(void);
	virtual ~PlayBackByFileDescribeMsgEx(void);
public:
	dpsdk_check_right_e			right;							// 是否检查权限，DPSDK_NOT_CHECK_RIGHT，不会检查cameraId在组织树缓存中是否存在
	int							transMode;						// 1 tcp,0 udp; 
	int							sessionId;
	char						cameraId[DPSDK_CHL_ID_LEN];
	dpsdk_recsource_type_e		recSource;
					
	bool						bCheckStatus;
	char						filename[DPSDK_REC_FILENAME_LEN];	 
	uint32_t					ssId;								 
	char						diskId[DPSDK_REC_DISKID_LEN];		 
	uint64_t					fileHandle;							 

	URecordInfo					uniRecord;					

	std::string 				trackID;
	bool						enableEx;
	std::string					rtspUrl;
	uint32_t					sessionForCMS;
	uint32_t					token;
	

	//response
	char*						sdp;
	int							sdpLength;
};

class DPSDK_API QueryRecordByFileIdMsg : public DPSDKCBMessage
{
public:
	QueryRecordByFileIdMsg(void);
	virtual ~QueryRecordByFileIdMsg(void);

public:
	char		szFileId[DPSDK_CHAR_LEN_64];	// 历史视频文件ID

	//response
	char		szCameraId[DPSDK_CHL_ID_LEN];	// 摄像头ID
	uint64_t	begTime;						// 开始时间
	uint64_t	endTime;						// 结束时间
	char		szFilePath[DPSDK_TAG_URL_LEN];	// 历史视频文件路径
	char		szFileSize[DPSDK_FTP_FILESIZE_LEN];	// 文件长度
	char		szDiskUUID[DPSDK_REC_DISKID_LEN];	// 磁盘ID
	int			token;							// 鉴权
	bool		bResult;						// 处理结果
};
//////////////////////////////////////////////////////////////////////////

class DPSDK_API IDPSDKPlayback : public IDPSDKFuncBase
{
public:
	/** 录像查询
	    @param const char* cameraId							摄像头ID
	    @param dpsdk_recsource_type_e source				录像来源
	    @param dpsdk_record_type_e recordType 				录像类型,1全部，2报警录像，3移动侦测，4手动录像，5卡号录像，6定时录像
	    @param uint64_t beginTime							查询开始时间
	    @param uint64_t endTime								查询结束时间
		@param record_streamtype_e streamType               录像码流类型
		@param bool bRecHideState							是否查询录像隐藏状态，true 查询，false 不查询，
		@param bool bBackup									是否是查询录在上级的备份录像
		@param int queryOnLowerPlatform						指定在下级域查询乐橙云平台的点位录像  0不指定 1指定去下级域查询
		@return												
	*/
	virtual int QueryRecord(const char* cameraId, dpsdk_recsource_type_e source, dpsdk_record_type_e recordType, uint64_t beginTime, uint64_t endTime, dpsdk_check_right_e right = DPSDK_CHECK_RIGHT, record_streamtype_e streamType = ALL_TYPE, const char* pAlarmID = 0, bool bRecHideState = false, const std::vector<int>& vecRecType = std::vector<int>(), bool bBackup = false, int queryOnLowerPlatform = 0) = 0;

	/** 查询有录像的日期（单个通道查询）
	    @param const char* cameraId							摄像头ID
	    @param dpsdk_recsource_type_e source				录像来源
	    @param dpsdk_record_type_e recordType 				录像类型,1全部，2报警录像，3移动侦测，4手动录像，5卡号录像，6定时录像
	    @param uint64_t beginTime							查询开始时间，目前只使用其中的年月信息，只查询一个月
	    @param uint64_t endTime								目前保留未使用。
		@param bool bBackup									是否是查询录在上级的备份录像
		@param dpsdk_check_right_e right					是否检查权限
		@return												
	*/
	virtual int QueryRecordDate(const char* cameraId, dpsdk_recsource_type_e source, dpsdk_record_type_e recordType, uint64_t beginTime, uint64_t endTime, bool bBackup = false, dpsdk_check_right_e right = DPSDK_CHECK_RIGHT) = 0;

	/** 按文件回放 forDSS
	    @param const char* cameraId							摄像头ID
	    @param dpsdk_recsource_type_e source				
	    @param fMediaDataCallback funCB						
		@param void* pCBParam	
		@param bool bCheckStatus						    是否判断通道状态
		@param bool bAllFrame								倒放参数：全帧(true)	抽帧(false)
		@param bool bBackup									是否是查询录在上级的备份录像
		@param int  videoOnLowerPlatform;		            综治项目： 回放在上级配置了存储的下级点位中心录像时， 此标志表明录像的存储位置(0默认位置，1 存储下级)
		@return												
	*/
	virtual int StartPlaybackByFile(const char* cameraId, DSS_NET_RECORDFILE_INFO* pRecInfo, fMediaDataCallback funCB, void* pCBParam, dpsdk_check_right_e right = DPSDK_CHECK_RIGHT, int transMode = 1, bool bBack = false, bool bCheckStatus = true, bool bAllFrame = true, bool bBackup = false, int  videoOnLowerPlatform = 0) = 0;

	/** 按文件回放 forDSS
	    @param PlaybackByFile_Info_t						回放参数
		@return												
	*/
	virtual int StartPlaybackByFile(PlaybackByFile_Info_t* pPlaybackByFileInfo) = 0;

	/** 按文件回放 forDSS //for new Protocol:28181
	    @param const char* cameraId							摄像头ID
	    @param dpsdk_recsource_type_e source				
	    @param fMediaDataCallback funCB						
		@param void* pCBParam								
		@return												
	*/
	virtual int StartPlaybackByFileEx(const char* cameraId, DSS_NET_RECORDFILE_INFO_EX* pRecInfo ) = 0;


	/** 按文件回放 forPSS
	    @param const char* cameraId							摄像头ID
	    @param PSS_NET_RECORDFILE_INFO* pRecInfo			
		@param fMediaDataCallback funCB						
		@param void* pCBParam								
		@return												
	*/
	virtual int StartPlaybackByFile(const char* cameraId, PSS_NET_RECORDFILE_INFO* pRecInfo, fMediaDataCallback funCB, void* pCBParam) = 0;

	/** 按时间回放
	    @param const char * cameraId						摄像头ID
	    @param dpsdk_recsource_type_e source				录像来源
	    @param uint64_t beginTime							查询开始时间
	    @param uint64_t endTime								查询结束时间
		@param dpsdk_pb_mode_e mode							
		@param fMediaDataCallback funCB						
		@param void* pCBParam		
		@param void* trackID								码流类型,'trackID=501'=PS, 'trackID=601'= 原始帧, 'trackID=701' = '大华帧', 
																		'trackID=801'=大华标准帧, 'trackID=901'=TS帧, 101(300以下)=rtp标准流(ONVIF协议标准)
		@param bool isVideoPlayback							区别回放和下载
		@param bool bAllFrame								倒放参数：全帧(true)	抽帧(false)
		@param bool bBackup									是否是查询录在上级的备份录像
		@param dpsdk_tcpmode tcpmode                        tcp连接方式，DPSDK_TCPMODE_ACTIVE 主动连接，DPSDK_TCPMODE_PASSIVE 被动连接
		@param int isNewMedia								0:不是；1:是； (业务：社会面视频接入需求添加）
		@param int  videoOnLowerPlatform;		            综治项目： 回放在上级配置了存储的下级点位中心录像时， 此标志表明录像的存储位置(0默认位置，1 存储下级)
		@return												
	*/
	virtual int StartPlaybackByTime(const char* cameraId, dpsdk_recsource_type_e source, uint64_t beginTime, uint64_t endTime, 
		dpsdk_pb_mode_e mode, fMediaDataCallback funCB, void* pCBParam, 
		dpsdk_check_right_e right = DPSDK_CHECK_RIGHT, pstream_type_e streamType = PSTREAM_TYPE_MAIN, const char* trackID = "", int transMode = 1, bool bBack = false, bool isVideoPlayback = false, bool bCheckStatus = true, bool bAllFrame = true, bool bBackup = false, dpsdk_tcpmode tcpmode = DPSDK_TCPMODE_DEFAULT, int isNewMedia = 1, int  videoOnLowerPlatform = 0, dpsdk_rectype_e recordType = PB_RECTYPE_NORMAL) = 0;
	
	/** 按文件回放 forDSS
	    @param PlaybackByFile_Info_t						回放参数
		@return												
	*/
	virtual int StartPlaybackByTime(PlaybackByTime_Info_t* pPlaybackByTimeInfo) = 0;

	/** 按时间回放 //for new Protocol:28181
	    @param const char * cameraId						摄像头ID
	    @param dpsdk_recsource_type_e source				录像来源
	    @param uint64_t beginTime							查询开始时间
	    @param uint64_t endTime								查询结束时间
		@param dpsdk_pb_mode_e mode							
		@param const char* dstIp
		@param uint16_t dstPort
		@param const char* trackID	
		@param int 	rtpHeadType	 1RTP,2NONE	
		@param dpsdk_tcpmode tcpmode                         tcp链接方式 DPSDK_TCPMODE_ACTIVE 主动连接，DPSDK_TCPMODE_PASSIVE 被动连接
		@return												
	*/
	virtual int StartPlaybackByTimeEx( const char* cameraId, dpsdk_recsource_type_e source, uint64_t beginTime, uint64_t endTime, 
		dpsdk_pb_mode_e mode, const char* dstIp, uint16_t dstPort, const char* trackID, pstream_type_e streamType = PSTREAM_TYPE_MAIN, int rtpHeadType = 1, float speed = 1.0, const char* deviceCode = "" ,dpsdk_tcpmode tcpmode = DPSDK_TCPMODE_DEFAULT) = 0;

	/** 关闭回放
	    @param uint32_t sessionId							回放session值,Start的返回值
		@return												
	*/
	virtual int StopPlayback(uint32_t sessionId) = 0;

	/** 暂停回放
	    @param uint32_t sessionId							回放session值,Start的返回值
		@param int nPorvider								设备厂商类型
		@return												
	*/
	virtual int StopPlayback(uint32_t sessionId, int seq) = 0;

	/** 暂停回放
	    @param uint32_t sessionId							回放session值,Start的返回值
		@param int nPorvider								设备厂商类型
		@return												
	*/

	virtual int PausePlayback(uint32_t sessionId, int nProvider = DEV_PROVIDER_UNKNOWN) = 0;

	/** 恢复回放
	    @param uint32_t sessionId							回放session值,Start的返回值
		@param float speed
		@param int nPorvider								设备厂商类型
		@return												
	*/
	virtual int ResumePlayback(uint32_t sessionId, float speed = 1, int nProvider = DEV_PROVIDER_UNKNOWN) = 0;

	/** 定位回放
	    @param uint32_t sessionId							回放session值
	    @param uint64_t seekBegin							定位起始值.文件模式时,是定位处的文件大小值;时间模式时,是定位处的时间值;
	    @param uint64_t seekEnd								定位结束值.文件模式时,无意义;时间模式时,是期待的结束时间.
		@return												
		@remark												seekBegin在文件模式下的计算方式可以是:(文件大小值)/100*(定位处相对文件的百分比)  
	*/
	virtual int SeekPlayabck(uint32_t sessionId, uint64_t seekBegin, uint64_t seekEnd) = 0;

	/** 设置播放速率
	    @param uint32_t sessionId							回放session值
	    @param float speed									播放速率 1/2等
		@param int nPorvider								设备类型
		@return												
		@remark
	*/
	virtual int SetPlaybackSpeed(uint32_t sessionId, float speed, int nProvider = DEV_PROVIDER_UNKNOWN) = 0;

	/** 查询报警录像
		@param const char* alarmId							
		@return												
	*/
	virtual int QueryAlarmRecord(const char* alarmId) = 0;

	/** 查询录像打标(按照默认参数填写,表示不作为查询条件)
	 	@param const char* cameraId							设备ID 为0,则不做查询条件
	 	@param uint64_t beginTime							开始时间 为0,则不做查询条件
	 	@param uint64_t endTime								结束时间 为0,则不做查询条件
	 	@param dpsdk_recsource_type_e source				设备来源 为PB_RECSOURCE_UNKNOWN,则不做查询条件
	 	@param int32_t owner								拥有者的ID 为0,则不做查询条件
	 	@param const char* subject				
		@param const int readStat							标签阅读状态  0-未读；1-已读；值<0时则不作为查询条件
		@return												
	*/
	virtual int QueryTagInfo(const char* cameraId, uint64_t beginTime, uint64_t endTime, dpsdk_recsource_type_e source, int32_t owner, const char* subject,const int readStat = 0) = 0;

	/** 操作录像打标
	 	@param Tag_Info_t taginfo							
		@param dpsdk_operator_type_e optype					
		@return												
	*/
	virtual int OperatorTagInfo(Tag_Info_t &taginfo, dpsdk_operator_type_e optype) = 0;

	/** 操作打标的图片
	 	@param dpsdk_operator_ftp_type_e optype				
		@param const char* url								
		@param const char* path
		@param dpsdk_ftp_transport_mode_e mode
		@return												
	*/
	virtual int OperatorTagImage(dpsdk_operator_ftp_type_e optype, const char* url, const char* path, dpsdk_ftp_transport_mode_e mode = MODE_EPSV) = 0;

	/** 回放Option保活
	    @param uint32_t sessionId							回放session值,Start的返回值
		@return												
	*/
	virtual int OptionPlayback(uint32_t sessionId) = 0;

	/** 查询录像开始时间
		@param const char* cameraId							设备ID 为0,则不做查询条件
		@return												
	*/
	virtual int QueryFirstRecord(const char* cameraId) = 0;

	/** 删除录像
		@param uint32_t		ssId;
		@param char			diskId[DPSDK_REC_DISKID_LEN];	磁盘ID
		@param uint32_t		fileHandle;
		@param char			filename[DPSDK_REC_FILENAME_LEN];
		@param int			recCount;
	*/
	virtual int DeleteRecPlayback( uint32_t ssId, const char* diskId, uint32_t fileHandle, const char* filename ) = 0;

	/** 获取回放视频的URL路径
	    @param const char * cameraId						摄像头ID
	    @param dpsdk_recsource_type_e source				录像来源
	    @param uint64_t beginTime							查询开始时间
	    @param uint64_t endTime								查询结束时间
		@param dpsdk_check_right_e right
		@param uint32_t  recordType							录像类型 1 一般录像,2 报警录像							
		@return												
	*/
	virtual int GetPlaybackByTimeUrl(const char* cameraId, dpsdk_recsource_type_e source, uint64_t beginTime, uint64_t endTime, dpsdk_check_right_e right = DPSDK_CHECK_RIGHT, uint32_t  recordType = 1) = 0;
	
	/** 释放回放视频的URL路径
		@param uint32_t nSessionId				
		@return									
	*/
	virtual int ClosePlaybackByTimeUrl(uint32_t nSessionId) = 0;

	/** 按URL回放
	    @param const char * cameraId						摄像头ID
		@param uint32_t nSessionId							GetPlaybackByTimeUrl()返回的SessionId
	    @param const char* szRtspUrl						录像URL
		@param int nSessionForCMS
	    @param int nToken									CMS返回的token
		@param dpsdk_pb_mode_e mode							回放模式
		@param const char* dstIp
		@param uint16_t dstPort
		@param const char* trackID	
		@param int transMode								传输模式，1：TCP 0：UDP
		@param int 	rtpHeadType	 1RTP,2NONE
		@return												
	*/
	virtual int StartPlaybackByUrl(const char* cameraId, uint32_t nSessionId, const char* szRtspUrl, int nSessionForCMS, int nToken, dpsdk_pb_mode_e mode, const char* dstIp, uint16_t dstPort, const char* trackID, int transMode = 1, int rtpHeadType = 1, float speed = 1.0) = 0;

	/** 获取按时间回放Describe应答信息（平台网关使用）
	    @param const char * cameraId						摄像头ID
	    @param dpsdk_recsource_type_e source				录像来源
	    @param uint64_t beginTime							查询开始时间
	    @param uint64_t endTime								查询结束时间
		@param const char* trackID	
		@return												
	*/
	virtual int PlayBackByTimeDescribeEx( const char* cameraId, dpsdk_recsource_type_e source, dpsdk_check_right_e right, uint64_t beginTime, uint64_t endTime, const char* trackID = "701", int transMode = 1, pstream_type_e streamType = PSTREAM_TYPE_MAIN ) = 0;

	/** 京东项目定制，根据历史视频文件ID查询录像信息
		@param szFileId										历史视频文件ID
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int QueryRecordByFileId(const char* szFileId) = 0;
protected:
	virtual ~IDPSDKPlayback(void){}
};
//////////////////////////////////////////////////////////////////////////

END_NAMESPACE_DPSDK

#endif
