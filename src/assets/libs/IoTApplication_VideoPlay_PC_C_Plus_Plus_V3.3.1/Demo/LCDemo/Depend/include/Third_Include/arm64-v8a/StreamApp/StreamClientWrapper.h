#ifndef RTSPCLIENTSDK_H
#define RTSPCLIENTSDK_H

#include "StreamSvr/Protocol/RtspUtil.h"
#include "StreamApp/Defs.h"

//最长url为1024字节
#define URL_LEN	1024

#ifdef __cplusplus
extern "C"{
#endif 

typedef enum
{
	CONN_UNKNOWN = -1,
	CONN_OVER_TCP,		//DH OVER tcp优先，不支持则采用RTP OVER TCP模式
	CONN_RTP_OVER_UDP,	//udp模式
	CONN_P2P_OVER_UDP,	//p2p over udp 模式
	CONN_RTP_OVER_TCP,	//RTP OVER TCP 模式
	CONN_DH_RTP_OVER_TCP,	//将DH帧打包成RTP标准码流
}conn_type;

typedef enum 
{
	UNKNOWN_STREAM=-1,
	REAL_VIEW_STREAM,	//实时流模式
	FILE_VIEW_STREAM,	//录像回放模式
	AUDIO_BACK_STREAM,	//反向语音模式
}stream_type;

typedef enum 
{
	STATE_PACKET_FRAME_ERROR,		//组帧失败
	STATE_RTSP_TEARDOWN_ERROR,		//内部要求关闭,如连接断开等
	STATE_RTSP_DESCRIBE_READY,		//会话已经收到Describe响应
	STATE_RTSP_AUTHORIZATION_FAIL,	//RTSP鉴权失败
	STATE_RTSP_PLAY_READY,			//收到PLAY响应
	STATE_RTSP_FILE_PLAY_OVER,		//录像文件回放正常结束
	STATE_RTSP_PAUSE_READY,			//收到PAUSE响应
	STATE_RTSP_KEY_MISMATCH,		//密钥不正确
	STATE_RTSP_LIVE_PAUSE_ENABLE,	//服务端直播支持PAUSE , 调用stream_inquirePause接口后会收到该消息或者STATE_RTSP_LIVE_PAUSE_DISABLE 消息
	STATE_RTSP_LIVE_PAUSE_DISABLE,	//服务端直播不支持PAUSE
	STATE_RTSP_TALK_BUSY_LINE,      //对讲忙线
    STATE_RTSP_TALK_CHECK_FAILED,   //对讲不满足操作条件
    STATE_RTSP_LIVE_PLAY_OVER,		//直播正常结束
	STATE_RTSP_SERVICE_UNAVAILABLE =  99,  // 基于503 错误码的连接最大数错误
	STATE_RTSP_USER_INFO_BASE_START = 100, // 用户信息起始码, 服务端上层传过来的信息码会在该起始码基础上累加
	
}state_status;

//码流回调
typedef void (*frame_proc)(const char* frame, int len, void* user);

//状态信息呈报
typedef void (*state_proc)(int error, void* user);

///\brief RTSP会话消息回调函数原型, 包括 request & response
///\param [in]	message -RTSP消息字符串指针
///\param [in]	user-回调接收对象指针
///\param [in]	reserve1-保留参数1
///\param [in]	reserve2-保留参数2
///\return	    void
typedef void (*msgcallback_proc)(const char *message, void *user, void *reserve1, void *reserve2);

///\brief 流信息回调函数原型
///\param [in]	user-回调接收对象指针
///\param [in]	message 	 -流信息字符串指针
///\param [in]	unsigned int 	 -流信息字符串长度
///\param [in]	reserve1	 -保留参数1
///\param [in]	reserve2	 -保留参数2
///\return	    void
typedef void(*stream_info_proc_func)(void *user, const char *message, unsigned int len, void *reserve1, void *reserve2);


//创建参数
struct create_param_t
{
	frame_proc			_frame_proc;
	state_proc			_state_proc;
	stream_type			_stream_type;
};

struct play_param_t
{
	bool		i_frame_only;//播放时是否进行I 帧播放
	float		start_pos;//记文件开始时间为0，相对于开始时间秒为单位的，如果为0，则从文件开始出播放
	float	 	end_pos;//同上
	float		speed;
};

//起始参数
struct start_param_t
{
	char 		url[URL_LEN];	//播放的url
	conn_type 	type; 			//拉流方式，TCP或者UDP
	int			socket;			//非0端口复用形式
	struct play_param_t	_play_param;
};

//媒体收发属性
enum send_recv_attr_t
{
	send_recv,
	recv_only,
	send_only,
	unknown_attr
};

//媒体音视频类型
enum media_type_t
{
	video,
	audio,
	application,
	unknown_type
};

//单路媒体信息
struct media_info_t
{
	media_type_t 		mt;
	send_recv_attr_t 	sr;
};

///\brief 客户端流信息上报配置, 使用前需要初始化, 避免不同平台出现随机值
struct rtsp_stream_info_config
{
	stream_info_proc_func 	stream_info_proc;	///< 数据回调接口	
	char 					*request_id;		///< 全链路唯一标示request_id
	uint32_t 				eventmask;			///< 流信息事件不同功能使能位选项, @see StreamApp::StreamEvent
	uint32_t 				lostduration;		///< 丢帧的周期性检测时间, 单位秒, 表明丢帧的开始后会进行多长时间的检测, 由应用配置, 默认60秒
	int						reserved1[8];		///< 保留字段1
	void* 					reserved2[4];		///< 保留字段2
};

///\brief RTSP协议拉流客户端连接信息
struct	rtsp_connect_info
{
	const char		*request_id;	///< 全链路唯一标示request_id
	uint32_t    	requestid_len; 	///< 全链路唯一标示request_id长度
	
	const char		*localip;		///< 本地ip
	uint32_t    	localip_len; 	///< ip字符串长度
	uint16_t		localport;	  	///< 本地端口

	const char		*remoteip;		///< 远端ip
	uint32_t    	remoteip_len; 	///< 远端ip 字符串长度
	uint16_t		remoteport;	  	///< 远端端口
};

// RTSP拉流客户端配置名称
enum rtsp_client_config_t
{
	rtsp_client_config_unknown = -1,				///< 非法配置
	rtsp_client_config_message_timeout,				///< 设置信令保活时间
	rtsp_client_config_extra_error,                 ///< 设置获取扩展错误码使能, 参数bool
	rtsp_client_config_streamInfo,					///< 设置客户端流信息配置, @see rtsp_stream_info_config, 必须在init之前设置
	rtsp_client_config_tos,							///< 设置客户端发送rtsp ip头的tos属性，参数int, 取整[0, 255]
	rtsp_client_config_dhencrypt3,					///< 设置大华帧头0xB5字段码流加密, 只允许设置一次 @see StreamSvr::DHEncrypt3Config
};


//客户端功能初始化环境
STREAMAPP_API int stream_start_up(int flag);

///\brief 创建句柄
///\param [in]	param-连接参数指针(码流回调函数，状态消息回调函数和拉流业务类型)
///\param [in]	user-码流回调和状态消息回调接收对象指针STREAMAPP_API
STREAMAPP_API void* create_handler(struct create_param_t* param, void* user);

//设置客户端User-Agent,在stream_start之前调用
STREAMAPP_API int set_user_agent(void* handler, char* agent);

//设置大华加解密参数
//参数config:传入DAHUAENCRYPTCONFIG对象指针，DAHUAENCRYPTCONFIG定义详见RtspUtil.h
//参数configlen:config的大小
STREAMAPP_API int set_encrypt(void* handler, void* config, int configlen);

///\brief 带扩展参数开始连接函数
///\param [in]	handler-句柄
///\param [in]	param-起始参数指针, 托管时将param->socket设置为fd, 且Detach该scok对象
///\return -1-fail,	0-success
STREAMAPP_API int stream_start(void* handler, struct start_param_t* param);

///\brief 带扩展参数开始连接函数
///\param [in]	handler-句柄
///\param [in]	param-起始参数指针,  使用该接口时将param->socket设置为0
///\param [in]	sock_type  0-非SSL, 1-SSL 
///\param [in]	sock-套接字指针,非托管时设置为NULL, 托管时设置为套接字对象的指针, 该指针必须为new 出来的对象，以保证指针的时域有效性, 调用该接口后，无论成功或失败都会由流媒体内部进行释放
///\param [in]	socket_param-套接字需要的一些参数指针,目前保留未使用, 可以设置为NULL
///\param [in]	reserve-保留参数
///\return -1-fail,	0-success
STREAMAPP_API int stream_start_ext(void* handler, struct start_param_t* param, int sock_type, const void *sock, void *socket_param, void *reserve);

//播放
STREAMAPP_API int stream_play(void* handler, struct play_param_t* param);

//反向对讲数据入口
//参数data：码流数据，应用需要保证进入为一个完整的大华帧
//参数len: 码流数据的长度
STREAMAPP_API void put_audio(void* handler, unsigned char* data, int len);

//暂停,实时预览不支持
STREAMAPP_API void stream_pause(void* handler);

//关闭客户端
STREAMAPP_API int stream_close(void* handler);

//释放句柄
STREAMAPP_API void destroy_handler(void* handler);

//客户端回收资源
STREAMAPP_API int stream_clean_up();

///\brief 获取会话中的媒体总数
///\param [in]	handler-句柄
///\return -1:fail, else:媒体总数
STREAMAPP_API int stream_getMediaTotal(void* handler);

///\brief 查询会话中的媒体信息
///\param [in]	handler-句柄
///\param [in]	mediaIndex-媒体索引，SDP中所有媒体块的顺序编号(0,1,2,...)
///\param [out]	info-媒体相关信息
///\return -1-fail,	0-success
STREAMAPP_API int stream_getMediaInfoByIndex(void* handler, int mediaIndex, media_info_t & info);

///\brief 设置发起Setup对应索引的媒体，默认发起所有媒体
///\param [in]	handler-句柄
///\param [in]	mediaIndex-媒体索引，SDP中所有媒体块的顺序编号(0,1,2,...)
///\return -1-fail,	0-success
STREAMAPP_API int stream_setup(void* handler, int mediaIndex);

///\brief 设置连接的方式
///\param [in]	handler-句柄
///\param [in]	connect-连接类型的字符串，流媒体将透传该字段给服务端
///\return -1-fail,	0-success
int set_connectInfo(void* handler, char* connect);

///\brief 获取SDP消息字符串
///\param [in]	handler-句柄
///\return 	NULL-fail , SDP消息字符串描述的格式-sucess
const char* stream_getSdpInfo(void* handler);

///\brief 创建带扩展参数和RTSP消息回调的句柄
///\param [in]	param-连接参数指针(码流回调函数，状态消息回调函数和拉流业务类型)
///\param [in]	user-码流回调和状态消息回调接收对象指针
///\param [in]	msg_callback-RTSP消息回调函数,回调函数内部不允许进行关闭流媒体服务操作,且为同步回调，原型见msgcallback_proc
///\param [in]	reserve1-保留参数1
///\param [in]	reserve2-保留参数2
///\return 	NULL-fail , handler对象句柄-sucess
void* create_handler_ext(struct create_param_t *param, void *user, msgcallback_proc msg_callback, void *reserve1, void *reserve2);

///\brief 查询设备直播是否支持PAUSE信令
///\param [in]	handler-句柄
///\param [return]	0:success, -1:fail
int stream_inquirePause(void* handler);

///\brief 流媒体在PLAY信令处理时会开启保活，如果上层不发送PLAY信令，需要手动开启保活定时器
///\param [in]	handler-句柄
///\param [return]	0:success, -1:fail
int start_aliveTimer(void* handler);

///\brief 设置鉴权信息
///\param [in]	handler-句柄
///\param [in]	username-用户名
///\param [in]	password-密码,无密码可以不填这个参数
///\param [in]	reserve-保留参数
///\return -1-fail,	0-success
int set_authorization(void* handler, const char *username, const char *password, void *reserve);

///\brief 设置用户配置参数
///\param [in] 	handler-句柄
///\param [in]	name-配置名称,参考@see rtsp_client_config_t
///\param [in]	value-配置参数指针
///\param [in]	len-配置参数指针所指区域的可访问长度
///\param [in]	reserve1-保留参数1
///\param [in]	reserve2-保留参数2
///\return -1-fail, 0-success
int set_config(void *handler, rtsp_client_config_t name, const void *value, int len, void *reserve1, void *reserve2);

///\brief 获取客户端连接信息
///\param [in] connectInfo-连接信息
///\return -1-fail,	0-success
int getConnectInfo(void *handler, rtsp_connect_info *connectInfo);

#ifdef __cplusplus
}
#endif 

#endif //RTSPCLIENTSDK_H

