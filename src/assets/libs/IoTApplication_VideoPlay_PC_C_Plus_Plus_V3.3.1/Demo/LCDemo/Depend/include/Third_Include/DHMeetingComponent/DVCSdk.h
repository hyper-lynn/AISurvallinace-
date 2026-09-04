/*************************************************************************
 ** 版权保留(C), 2001-2013, 浙江大华技术股份有限公司.
 ** 版权所有.
 **
 ** $Id$
 **
 ** 功能描述   : 大华民用会议系统sdk接口
 **
 ** 修改历史     : 2014年3月27日 zhu_long Modification
*************************************************************************/

#ifndef __DAHUA_VIDEO_CONFERENCE_SDK_H_
#define __DAHUA_VIDEO_CONFERENCE_SDK_H_

#ifdef _MSC_VER
    #ifdef DVC_DLL_BUILD
        #define  DVC_API _declspec(dllexport)
    #elif defined DVC_DLL_USE
        #define  DVC_API _declspec(dllimport)
    #else
        #define DVC_API
#endif
#else
    #define DVC_API
#endif

#ifdef  __cplusplus
extern "C" {
#endif


#define DVC_USER_LEN                  64          ///<用户id长度
#define DVC_CLIENTID_LEN              64          ///<客户端id长度
#define DVC_CLIENT_KEY_LEN            64          ///<密钥最大长度
#define DVC_SERVER_IP_LEN             64          ///<服务器ip最大长度
#define DVC_DESC_LEN                  128         ///<描述信息最大长度
#define DVC_INVALID_CONFID            -1          ///<无效会议ID
#define DVC_MAX_PARTER_NUM            8           ///<会议中参与者的最大个数
#define DVC_MAX_USER_MEMBER_NUM       6           ///<单个用户最大客户端数

#define DVC_MAX_AUDIO_ATTRIBUTE_NUM   10          ///<音频属性的最大个数
#define DVC_MAX_VIDEO_ATTRIBUTE_NUM   10          ///<视频属性的最大个数
#define DVC_MAX_RESOLUTION_NUM        10          ///<分辨率属性的最大个数
#define DVC_MAX_PTCPINFO_NUM          16          ///<查询的PTCP属性的最大个数

/*
Note:
ClientID 与UserID的组成是下述三种字符类型的任意组合， 字符类型有：
第一种：中划线(-) 或 下划线（_）
第二种: a~z的 大小字符
第三种: 0~9的数字
*/
///\brief 客户端ID，须保证全网唯一
typedef char ClientID[DVC_CLIENTID_LEN];

///\brief 用户ID，须保证全网唯一
typedef char UserID[DVC_USER_LEN];

///\brief 接口回复码定义
typedef enum
{
    DVC_Success = 0,                             ///< 处理成功
    DVC_Error_Server = -1,                       ///< 服务错误
    DVC_Error_Processing = -2,                   ///< 处理中
    DVC_Error_Failed = -3,                       ///< 失败
    DVC_Error_Timeout = -4,                      ///< 超时无响应
    DVC_Error_Parameter = -5,                    ///< 参数错误
    DVC_Error_SdkInit = -6,                      ///< SDK已启动
    DVC_Error_SdkUnInit = -7,                    ///< SDK未启动
    DVC_Error_ConfInit = -8,                     ///< 会议已启动
    DVC_Error_ConfUnInit = -9,                   ///< 会议未启动
    DVC_Error_ConfFull = -10,                    ///< 会议已满
    DVC_Error_UnkownConfId = -11,                ///< 未知会议号
    DVC_Error_ClientInConf = -12,                ///< 会议客户端加入中
    DVC_Error_ClientNotInConf = -13,             ///< 客户端不在会议中
    DVC_Error_UserInConf = -14,                  ///< 用户加入中
    DVC_Error_UserNotInConf = -15,               ///< 用户不在会议中
    DVC_Error_Unknown = -16,                     ///< 未知错误 
    DVC_Error_BUTT = -17,
}DVC_RETURN_CODE;

///brief 参与者在会议中的状态
typedef enum
{
    DVC_STATUS_Pending,                      ///<加入中
    DVC_STATUS_Connnected,                   ///<连接
    DVC_STATUS_Disconnected,                 ///<已断开
    DVC_STATUS_BUTT,
}DVC_PARTICIPANT_STATUS;

// 用户的状态
typedef enum
{
    DVC_USER_STATUS_Offline,               ///<离线状态
    DVC_USER_STATUS_Idle,                  ///<空闲状态
    DVC_USER_STATUS_Ring,                  ///<振铃中
    DVC_USER_STATUS_InConf,                ///<会议中
    DVC_USER_STATUS_BUTT,
}DVC_USER_STATUS;

///<码流传输类型
typedef enum
{
    DVC_Transport_DHAV = 0,                  ///< 大华流传输
    DVC_Transport_RTPAV,                     ///< RTP流传输
    DVC_Transport_UNKNOWM = 0xffffffff       ///< 未知传输类型
}DVC_TransportType;



///<音频格式类型
typedef enum
{
    DVC_Audio_Format_PCMU = 0,
    DVC_Audio_Format_PCMA,
    DVC_Audio_Format_AAC,
    DVC_Audio_Format_AMR,
    DVC_Audio_Format_UNKNOWN = 0xffffffff
}DVC_AudioFormatType;


///<采样率
typedef enum
{
    DVC_SampleRate_4000   = 1,    ///< 采样率4000HZ
    DVC_SampleRate_8000   = 2,    ///< 采样率8000HZ
    DVC_SampleRate_11025  = 4,    ///< 采样率11025HZ
    DVC_SampleRate_16000  = 8,    ///< 采样率16000HZ
    DVC_SampleRate_20000  = 32,   ///< 采样率20000HZ
    DVC_SampleRate_22050  = 64,   ///< 采样率22050HZ
    DVC_SampleRate_32000  = 128,  ///< 采样率32000HZ
    DVC_SampleRate_44100  = 256,  ///< 采样率44100HZ
    DVC_SampleRate_48000  = 512,  ///< 采样率48000HZ
}DVC_SampleRate;


///<视频格式类型
typedef enum
{
    DVC_Video_Format_H264 = 0,
    DVC_Video_Format_H265,
    DVC_Video_Format_UNKNOWN = 0xffffffff
}DVC_VideoFormatType;

///<分辨率信息
typedef struct
{
    int				width;					///<分辨率对应的宽
	int				height;					///<分辨率对应的高
}DVC_Resolution;


///<视频编码属性
typedef struct
{
    DVC_TransportType   transportType;                                    ///< 数据传输类型
    DVC_VideoFormatType formatType;                                       ///< 视频编码格式
    int                 maxBitRate;                                       ///< 最大码率 单位bps
    int                 minBitRate;                                       ///< 最小码率 单位bps
    int                 maxFrameRate;                                     ///< 最大帧率 单位帧/每秒
    int                 encodeResolutionNum;                              ///< 支持的编码分辨率个数
    DVC_Resolution      encodeResolution[DVC_MAX_RESOLUTION_NUM];         ///< 编码视频数据的分辨率
}DVC_VideoEncodeAttribute;

///<视频解码属性
typedef struct
{
    DVC_TransportType   transportType;               ///< 数据传输类型
    DVC_VideoFormatType encodeType;                  ///< 视频编码类型
    int                 maxBitRate;                  ///< 最大码率 单位bps
    int                 maxFrameRate;                ///< 最大帧率 单位帧/每秒
    DVC_Resolution      maxDecodeResolution;         ///< 解码支持的最大分辨率
}DVC_VideoDecodeAttribute;

///\brief PTCP协议栈内部信息
typedef struct
{
    unsigned int           channelType;    ///< P2P通道的类型，见P2PChannelType: 0 未定义; 1 audio; 2 video
    unsigned int           bandWidth;      ///< 估计的链路带宽，单位bps
    unsigned int           roundTripTime;  ///< 估计的链路RTT,单位ms
    unsigned long long     delayTime;      ///< 待发送数据的最大延时，单位ms
    unsigned int           totalSndBuf;    ///< 总共的发送缓冲区大小，单位Byte
    unsigned int           leftSndBuf;     ///< 剩余的发送缓冲区大小，单位Byte
}PTCPInfo;

typedef struct
{
    PTCPInfo        info[DVC_MAX_PTCPINFO_NUM]; ///< PTCP 通道信息
    unsigned int    infoSize;                   ///< 当前有效通道个数
}DVC_PTCPInfo;

///< 视频sdp信息
typedef struct
{
    unsigned short port;                                                    ///<视频端口
    int encodeAttributeNum;                                                 ///<视频编码属性个数
    DVC_VideoEncodeAttribute encodeAttribute[DVC_MAX_VIDEO_ATTRIBUTE_NUM];  ///<视频编码属性
    int decodeAttributeNum;                                                 ///<视频解码属性个数
    DVC_VideoDecodeAttribute decodeAttribute[DVC_MAX_VIDEO_ATTRIBUTE_NUM];  ///<视频解码属性
}DVC_VideoSdpInfo;



///<音频编解码属性
typedef struct
{
    DVC_TransportType   transportType;       ///< 码流传输类型
    DVC_AudioFormatType encodeType;          ///< 音频格式
    int                 sampleRate;          ///< 采样率, 对DVC_SampleRate 中支持的采样率做位运算的或操作，在解析时进行位运算的与操作
}DVC_AudioAttribute;

///<音频sdp信息
typedef struct
{
    unsigned short port;                                             ///<音频端口
    int encodeAttributeNum;                                          ///<音频编码属性个数
    DVC_AudioAttribute encodeAttribute[DVC_MAX_AUDIO_ATTRIBUTE_NUM]; ///<音频编码属性
    int decodeAttributeNum;                                          ///<音频解码属性个数
    DVC_AudioAttribute decodeAttribute[DVC_MAX_AUDIO_ATTRIBUTE_NUM]; ///<音频解码属性
}DVC_AudioSdpInfo;

///< sdp信息
typedef struct
{
    unsigned int     version;    ///< 历史老版本(橙聊V1.1及更早版本)version=0，后续新版本从version=1开始向上递增
    DVC_AudioSdpInfo audioInfo;  ///< 音频sdp信息
    DVC_VideoSdpInfo videoInfo;  ///< 视频sdp信息
}DVC_SdpInfo;

/// 用户退出会议的原因
typedef enum
{
    DVC_REASON_Departed,                    ///<客户端主动退出
    DVC_REASON_Booted,                      ///<客户端被主持人踢出会议
    DVC_REASON_Busy,                        ///<客户端忙（正在通话中）
    DVC_REASON_NoReply,                     ///<客户端无应答
    DVC_REASON_Offline,                     ///<客户端离线
	DVC_REASON_Failed,                      ///<服务器发起呼叫失败
    DVC_REASON_Refuse,                      ///<客户端拒绝(被叫拒绝接听)
    DVC_REASON_BUTT,
}DVC_DISCONNECTION_REASON;

// 用于上报给app 的事件类型
///\brief 事件列表
typedef enum
{
    DVC_EVENT_SystemError = 1,                ///<1.SDK 心跳超时，事件描述见DVC_EVENT_DSC_SystemError

    DVC_EVENT_InitConfResult,                 ///<2.调用接口DVCinitConf后的结果通知，事件描述见DVC_EVENT_DSC_BasicResult
    DVC_EVENT_CloseConfResult,                ///<3.调用接口DVCcloseConf 后的结果通知, 	事件描述见DVC_EVENT_DSC_BasicResult
    DVC_EVENT_QueryUserResult,                ///<4.调用接口DVCqueryUser后的结果通知,  事件描述见DVC_EVENT_DSC_QueryUserResult
    DVC_EVENT_StartConfResult,                ///<5.调用接口DVCstartConf后的结果通知，事件描述见DVC_EVENT_DSC_StartConfResult
    DVC_EVENT_RefuseConfResult,               ///<6.调用接口DVCrefuseConf后的结果通知，事件描述见DVC_EVENT_DSC_RefuseConfResult
    DVC_EVENT_AddClientResult,                ///<7.调用接口DVCaddClient后的结果通知，事件描述见DVC_EVENT_DSC_AddClientResult
    DVC_EVENT_DelClientResult,                ///<8.调用接口DVCdelClient后的结果通知，事件描述见DVC_EVENT_DSC_DelClientResult
    DVC_EVENT_AddUserResult,                  ///<9.调用接口DVCaddUser后的结果通知，事件描述见DVC_EVENT_DSC_AddUserResult
    DVC_EVENT_DelUserResult,                  ///<10.调用接口DVCdelUser后的结果通知，事件描述见DVC_EVENT_DSC_DelUserResult
    DVC_EVENT_JoinConfResult,                 ///<11.调用接口DVCjoinConf后的结果通知，事件描述见DVC_EVENT_DSC_JoinConfResult
    DVC_EVENT_SendMessageResult,              ///<12.调用接口DVCsendMessage后的结果通知，事件描述见DVC_EVENT_DSC_SendMessageResult
    DVC_EVENT_CancelConfResult,               ///<13.调用接口DVCcancelConf后的结果通知，事件描述见DVC_EVENT_DSC_BasicResult

    DVC_EVENT_NotifyJoinConfInvite = 100,     ///<100.服务器邀请client加入会议, 事件描述见DVC_EVENT_DSC_NotifyJoinConfInvite
    DVC_EVENT_NotifyCancelConf,               ///<101.服务器取消client 加入会议, 事件描述见DVC_EVENT_DSC_NotifyCancelConf
    DVC_EVENT_NotifyKickOutConf,              ///<102.服务器通知client 结束会议，事件描述见DVC_EVENT_DSC_NotifyKickOutConf
    DVC_EVENT_NotifyClientStatus,             ///<103.服务器通知client 的状态, 事件描述见DVC_EVENT_DSC_NotifyClientStatus
    DVC_EVENT_NotifyRecvMessage,              ///<104.收到其它客户端发送的消息,事件描述见 DVC_EVENT_DSC_NotifyRecvMessage
    DVC_EVENT_NotifyMissedCall,               ///<105.服务器通知有未接来电，事件描述见DVC_EVENT_DSC_NotifyMissedCall
    DVC_EVENT_NotifyClientSdpInfo,            ///<106.通知用户的sdp信息,事件描述见DVC_EVENT_DSC_NotifyClientSdpInfo

    DVC_EVENT_P2pConnectStatus = 200,         ///<200.服务器通知p2p 连接状态,  事件描述见DVC_EVENT_DSC_P2pConnectStatus

    DVC_EVENT_BUTT,

}DVC_EVENT;


///\brief 事件回调定义(事件, 事件描述)
///\param[in]   eventId        事件类型
///\param[in]   eventDsc       事件描述
///\note        请根据枚举DVC_EVENT来解析 eventId， 根据eventId解析eventDsc
typedef void(*EventCallBack)(DVC_EVENT eventId, void* eventDsc);

// 用户状态信息
typedef struct
{
    UserID                  userID;                     ///<用户ID
    DVC_USER_STATUS         status;                     ///<用户状态

}DVC_Info_User, *DVC_Info_User_Ptr;


///\brief 返回值描述信息
typedef struct
{
    DVC_RETURN_CODE     returnCode;                         ///<操作是否成功
    char                desc[DVC_DESC_LEN];                 ///<额外描述信息
}DVC_EVENT_DSC_BasicResult;


///\brief 事件DVC_EVENT_SystemError描述信息
typedef struct
{
    char            desc[DVC_DESC_LEN];                    ///<额外描述信息
}DVC_EVENT_DSC_SystemError;



///\brief 事件DVC_EVENT_QueryUserResult描述信息
typedef struct
{
    DVC_EVENT_DSC_BasicResult   basicResult;                   ///<查询用户信息操作是否成功
    int                         userNum;                       ///<返回结果的用户数量，不超过DVC_MAX_PARTER_NUM
    DVC_Info_User               userInfo[DVC_MAX_PARTER_NUM];  ///<用户信息结果
}DVC_EVENT_DSC_QueryUserResult;

///\brief 事件DVC_EVENT_StartConfResult描述信息
typedef struct
{
    DVC_EVENT_DSC_BasicResult   basicResult;             ///<操作是否成功	
    int                         confId;                  ///<会议ID，全网唯一， 如果是无效会议ID，则confID为DVC_INVALID_ID;
}DVC_EVENT_DSC_StartConfResult;

///\brief 事件DVC_EVENT_RefuseConfResult描述信息
typedef struct
{
    DVC_EVENT_DSC_BasicResult   basicResult;            ///<操作是否成功	
    int                         confId;                 ///<会议ID，全网唯一， 如果是无效会议ID，则confID为DVC_INVALID_ID;
}DVC_EVENT_DSC_RefuseConfResult;


/// \brief 事件DVC_EVENT_AddClientResult描述
typedef struct
{
    DVC_EVENT_DSC_BasicResult   basicResult;           ///<操作是否成功	
    ClientID                    clientID;              ///<增加的客户端ID
}DVC_EVENT_DSC_AddClientResult;

/// \brief 事件DVC_EVENT_DelClientResult描述
typedef struct
{
    DVC_EVENT_DSC_BasicResult   basicResult;          ///<操作是否成功	
    ClientID                    clientID;             ///<删除的客户端ID
}DVC_EVENT_DSC_DelClientResult;

/// \brief 事件DVC_EVENT_AddUserResult描述
typedef struct
{
    DVC_EVENT_DSC_BasicResult   basicResult;           ///<操作是否成功	
    UserID                      userID;                ///<增加的用户ID
}DVC_EVENT_DSC_AddUserResult;

/// \brief 事件DVC_EVENT_DelUserResult描述
typedef struct
{
    DVC_EVENT_DSC_BasicResult   basicResult;          ///<操作是否成功	
    UserID                      userID;               ///<删除的用户ID
}DVC_EVENT_DSC_DelUserResult;



/// \brief 事件DVC_EVENT_SendMessageResult描述
typedef struct
{
    DVC_EVENT_DSC_BasicResult   basicResult;         ///<操作是否成功	
    ClientID                    clientID;            ///<对端的客户端ID
    UserID                      userID;              ///<对端的用户ID
}DVC_EVENT_DSC_SendMessageResult;


///\brief 事件DVC_EVENT_JoinConfResult描述信息
typedef struct
{
    DVC_EVENT_DSC_BasicResult   basicResult;         ///<操作是否成功 
    int                         confId;              ///<会议ID，全网唯一， 如果是无效会议ID，则confID为DVC_INVALID_ID;
    ClientID                    inviterClientID;     ///<邀请加入会议的客户端ID
    UserID                      inviterUserID;       ///<邀请加入会议的用户ID 
}DVC_EVENT_DSC_JoinConfResult;


///\brief 事件DVC_EVENT_NotifyJoinConfInvite描述信息
typedef struct{
    ClientID                   chairmanClientID;     ///<会议发起者客户端ID
    UserID                     chairmanUserID;       ///<会议发起者的用户ID
    int                        confID;               ///<要加入的会议ID
    DVC_SdpInfo                chairmanSdpInfo;      ///<会议发起者的sdp 信息
}DVC_EVENT_DSC_NotifyJoinConfInvite;


typedef enum{
    DVC_CANCEL_REASON_CALLER_HANGUP, ///<主叫挂断
    DVC_CANCEL_REASON_TIMEOUT,       ///<本端超时
    DVC_CANCEL_REASON_CALLEE_REFUSE, ///<同用户下的其它终端拒绝
    DVC_CANCEL_REASON_CALLEE_ANSWER, ///<同用户下的其它终端接听
}DVC_CANCEL_CONF_REASON;

///\brief 事件DVC_EVENT_NotifyCancelConf描述信息
typedef struct{
    ClientID                   chairmanClientID;     ///<会议发起者客户端ID
    UserID                     chairmanUserID;       ///<会议发起者的用户ID
    int                        confID;               ///<要加入的会议ID
    DVC_CANCEL_CONF_REASON     reason;               ///<本段收到DVC_EVENT_NotifyCancelConf的原因
}DVC_EVENT_DSC_NotifyCancelConf;

///\brief 事件DVC_EVENT_NotifyKickOutConf描述信息
typedef struct{
    ClientID                   chairmanClientID;     ///<会议发起者客户端ID
    UserID                     chairmanUserID;       ///<会议发起者的用户ID
    int                        confID;               ///<要加入的会议ID
}DVC_EVENT_DSC_NotifyKickOutConf;


typedef struct
{
    ClientID                    clientID;           ///<客户端ID
    UserID                      userID;             ///<用户ID; 如果无组信息，值等于客户端ID；否则，值为有效用户Id
    DVC_PARTICIPANT_STATUS      status;             ///<客户端状态
    DVC_DISCONNECTION_REASON    reason;             ///<退出原因，只有status = DVC_STATUS_Disconnected 时值才有效
}ParterStatusInfo;

///\brief 事件DVC_EVENT_NotifyClientStatus描述信息
typedef struct
{
    int                       confID;                                     ///<会议ID
    int                       clientNumb;                                 ///<上报的客户端个数
    ParterStatusInfo          clientStatusInfo[DVC_MAX_PARTER_NUM];       ///<客户端状态，最大支持DVC_MAX_PARTER_NUM
}DVC_EVENT_DSC_NotifyClientStatus;

///\brief 事件DVC_EVENT_NotifyRecvMessage描述信息
typedef struct
{
    ClientID        clientID;                           ///<发送者客户端ID
    UserID          userID;                             ///<发送者用户ID
    int             confID;                             ///<会议ID
    int             len;                                ///<数据长度
    void *          data;                               ///<数据
}DVC_EVENT_DSC_NotifyRecvMessage;

///\brief 事件DVC_EVENT_NotifyMissedCall描述信息
typedef struct
{
    ClientID        chairmanClientID;                  ///<会议发起者客户端ID
    UserID          chairmanUserID;                    ///<会议发起者用户ID
}DVC_EVENT_DSC_NotifyMissedCall;

typedef struct
{
    ClientID        clientID;                          ///<客户端ID
    UserID          userID;                            ///<用户ID
    int             confID;                            ///<会议ID
    DVC_SdpInfo     sdpInfo;                           ///<用户的sdp 信息
}DVC_EVENT_DSC_NotifyClientSdpInfo;

///\brief 媒体 类型
typedef enum {
    DVC_MEDIA_Audio,                                    ///< 音频类型
    DVC_MEDIA_Video,                                    ///< 视频类型
}DVC_MediaType;

typedef enum{
    DVC_P2P_ConnectSuccess,                             ///<连接成功
    DVC_P2P_ConnectPending,                             ///<正在连接中
    DVC_P2P_ConnectFailed,                              ///<连接失败
    DVC_P2P_Offline,                                    ///<p2p离线
}DVC_P2pStatus;

///\brief 事件DVC_EVENT_P2pConnectStatus描述信息
typedef struct
{
    ClientID                            clientID;           ///<对端的客户端ID
    UserID                              userID;             ///<对端的用户ID
    int                                 confID;             ///<会议ID
	DVC_P2pStatus                       p2pStatus;          ///<p2p状态
    DVC_MediaType                       mediaType;          ///<媒体类型
    unsigned short                      port;               ///<端口号
}DVC_EVENT_DSC_P2pConnectStatus;



///\brief 用户信息
typedef struct
{
    UserID   userId;                               ///<用户Id  
    int      memberNum;                            ///<该用户下的客户端数量，不能超过 DVC_MAX_USER_MEMBER_NUM
    ClientID memberId[DVC_MAX_USER_MEMBER_NUM];    ///<成员客户端ID列表
}DVC_UserInfo;

///\brief 查询用户信息
typedef struct
{
    int                         userNum;                         ///<用户的数量，不超过DVC_MAX_PARTER_NUM
    UserID                      userId[DVC_MAX_PARTER_NUM];      ///<用户ID信息
}DVC_QueryUserInfo;

///\brief 网络会议设置
/*
注意

ClientID 与UserID 的字符类型有：
第一种： 冒号(:) 或 中划线(-) 或 下划线（_）
第二种: a~z的 大小字符
第三种: 0~9的数字
*/
typedef struct
{
    ClientID           clientID;                        ///< 客户端ID
    UserID             userID;                          ///< 用户ID，如果无则值为客户端ID
    char               clientKey[DVC_CLIENT_KEY_LEN];   ///< 客户端校验密钥

    char               sipServerIp[DVC_SERVER_IP_LEN];  ///< 会议服务器IP
    int                sipServerPort;                   ///< 会议服务器端口
    
    char               p2pServerIp[DVC_SERVER_IP_LEN];  ///< p2p 服务器IP
    int                p2pServerPort;                   ///< p2p 服务器端口
    EventCallBack      eventCallBack;                   ///< 事件回调
    void*              userData;                        ///< 用户自定数据
}DVCConfig;




/*************************会议控制API************************************/

///\brief       启动sdk
///\param[in]   config  会议配置
///\return @see DVC_RETURN_CODE
///\note 本接口立即返回，调用方会收到异步通知事件DVC_EVENT_InitConfResult
DVC_API DVC_RETURN_CODE DVCinitConf(DVCConfig *const config);

///\brief       停止sdk
///\return @see DVC_RETURN_CODE
///\note 本接口立即返回，没有异步通知事件
DVC_API DVC_RETURN_CODE DVCreleaseConf();

///\brief       开启会议
///\param[in]   sdpInfo     本端的SDP信息(媒体能力集)
///\return @see DVC_RETURN_CODE
///\note 本接口立即返回，调用方会收到异步通知事件DVC_EVENT_StartConfResult
DVC_API DVC_RETURN_CODE DVCstartConf(const DVC_SdpInfo sdpInfo);

///\brief       关闭会议/退出会议
///\param[in]   confID     关闭会议ID/退出会议ID
///\return @see DVC_RETURN_CODE
///\note 本接口立即返回，当有客户端退出会议时，收到异步通知事件DVC_EVENT_CloseConfResult
DVC_API DVC_RETURN_CODE DVCcloseConf(const int confID);

///\brief       客户端取消会议(用于创建会议后还没有收到异步响应事件时，取消会议)
///\return @see DVC_RETURN_CODE
///\note 本接口立即返回，调用方会收到异步通知事件DVC_EVENT_CancelConfResult
DVC_API DVC_RETURN_CODE DVCcancelConf();

///\brief       拒绝邀请
///\param[in]   confID     拒绝会议ID
///\return @see DVC_RETURN_CODE
///\note 本接口立即返回，调用方会收到异步通知事件DVC_EVENT_RefuseConfResult
DVC_API DVC_RETURN_CODE DVCrefuseConf(const int confID);


///\brief       接受会议
///\param[in]   confID     接收会议ID
///\param[in]   sdpInfo    本端协商后的SDP信息
///\return @see DVC_RETURN_CODE
///\note 本接口立即返回，其它会议参与方会收到异步通知事件DVC_EVENT_JoinConfResult
DVC_API DVC_RETURN_CODE DVCjoinConf(const int confID, const DVC_SdpInfo sdpInfo);

///\brief       添加会议客户端
///\param[in]   clientId    客户端ID
///\note 调用者CID为0
///\return @see DVC_RETURN_CODE
///\note 本接口立即返回，由会议发起方调用，调用方会收到异步通知事件DVC_EVENT_AddClientResult
///\note 本接口不推荐使用，已经废弃，请使用接口DVCaddUser
DVC_API DVC_RETURN_CODE DVCaddClient(const ClientID clientId);


///\brief       删除会议客户端
///\param[in]   clientId     客户端ID
///\return @see DVC_RETURN_CODE
///\note 本接口立即返回，由会议发起方调用，调用方会收到异步通知事件DVC_EVENT_DelClientResult
///\note 本接口不推荐使用，已经废弃，请使用接口DVCdelUser
DVC_API DVC_RETURN_CODE DVCdelClient(const ClientID clientId);


///\brief       添加用户
///\param[in]   userInfo    用户信息
///\note 调用者CID为0
///\return @see DVC_RETURN_CODE
///\note 本接口立即返回，由会议发起方调用，调用方会收到异步通知事件DVC_EVENT_AddUserResult
///\note 一个userId下面可能有多个clientId, 但一个clientId只属于一个userId
DVC_API DVC_RETURN_CODE DVCaddUser(const DVC_UserInfo userInfo);


///\brief       删除用户
///\param[in]   userId    用户id
///\note 调用者CID为0
///\return @see DVC_RETURN_CODE
///\note 本接口立即返回，由会议发起方调用，调用方会收到异步通知事件DVC_EVENT_DelUserResult
///\note 一个userId下面可能有多个clientId, 但一个clientId只属于一个userId
DVC_API DVC_RETURN_CODE DVCdelUser(const UserID userId);


///\brief       查询用户信息(用户的状态等信息)
///\param[in]   queryUserInfo     查询的用户信息
///\return @see DVC_RETURN_CODE
///\note 本接口立即返回，会收到异步通知事件DVC_EVENT_QueryUserResult
DVC_API DVC_RETURN_CODE DVCqueryUser(const DVC_QueryUserInfo queryUserInfo);


///\brief       查询P2P通道信息
///\param[out]   ptcpInfo     查询到的P2P信息
///\return @see DVC_RETURN_CODE
///\note 本接口立即返回,是同步接口
DVC_API DVC_RETURN_CODE DVCQueryPtcpInfo(DVC_PTCPInfo *ptcpInfo);


///\brief       向客户端发送消息，只支持向会议中的成员发送消息
///\param[in]   clientId         客户端ID
///\param[in]   userId           用户ID,如果无用户信息，值等于客户端ID
///\param[in]   data             消息数据
///\param[in]   len              数据长度
///\return  
///\				 <0 异常错误
///\				 >0 发送出去的数据长度				
///\note 
///\   1.本接口立即返回，本端会收到上报事件DVC_EVENT_SendMessageResult, 对端会收到上报事件 DVC_EVENT_NotifyRecvMessage
///\   2.本接口用来上层APP在盒子间传输私有消息，视频会议库只做透明传输
DVC_API int DVCsendMessage(const ClientID clientId, const UserID userId, const void *const data, const int len);

#ifdef  __cplusplus
}
#endif

#endif /* __DAHUA_VIDEO_CONFERENCE_SDK_H_ */
