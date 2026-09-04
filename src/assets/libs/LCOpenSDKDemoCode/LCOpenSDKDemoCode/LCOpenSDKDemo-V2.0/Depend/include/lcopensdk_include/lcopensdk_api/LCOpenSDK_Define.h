#ifndef _LCOPENSDK_DEFINE_H_
#define _LCOPENSDK_DEFINE_H_

#define CToS(str)	((NULL == str.cstr) ? "" : str.cstr)

/* 拉流类型 */
typedef enum
{
	STREAM_MODE_UNCERTAINTY = -1,    //拉流方式未确定(指当前没有在拉流or在拉流准备中or不涉及下面两种类型)
	STREAM_MODE_P2P,                 //使用P2P拉流
	STREAM_MODE_MTS,                 //使用MTS拉流
}LCOpenSDK_STREAM_MODE;


typedef enum
{
	STREAM_MODE_P2P_Local,           //使用P2P拉流方式-P2P_Local
	STREAM_MODE_P2P_P2P,             //使用P2P拉流方式-P2P_P2P
	STREAM_MODE_P2P_Relay,           //使用realy拉流方式
	STREAM_MODE_P2P_Unknow,           //使用P2P拉流方式，无法确定P2P流模式P2P_Unknow
}LCOpenSDK_P2P_LINKTYPE;

/* onPlayerResult回调type参数定义 */
typedef enum
{
	RESULT_PROTO_TYPE_RTSP,      //RTSP业务(包括实时预览、本地录像回放、对讲)
	RESULT_PROTO_TYPE_HLS,       //HLS业务(包括云录像播放、云录像下载)
	RESULT_PROTO_TYPE_FILE,      //FILE业务(包括本地文件播放)
	RESULT_PROTO_TYPE_NETSDK,    //NETSDK业务(包括大华P2P设备实时预览、录像回放)
	RESULT_PROTO_TYPE_SIP,       //SIP业务(包括大华Meeting)
	RESULT_PROTO_TYPE_DHHTTP,    //私有协议业务 
	RESULT_PROTO_TYPE_MULTI,     //并发拉流
	RESULT_PROTO_TYPE_COMMON,    //通用协议业务
	RESULT_PROTO_TYPE_REST = 99,      //REST业务(涉及以上RTSP、HLS、SIP业务)
}LCOpenSDK_PROTO_TYPE;

typedef enum
{
	StreamSourceSwitchToP2P = 101,   /* 拉流链路切换到p2p */
}LCOpenSDK_COMMON_MSG;


/* when type == RESULT_PROTO_TYPE_RTSP, code enum */
typedef enum
{
	STATE_PACKET_COMPONENT_ERROR = -1,      //组件内部调用流媒体接口失败
	STATE_PACKET_FRAME_ERROR = 0,        //组帧失败
	STATE_RTSP_TEARDOWN_ERROR,       //内部要求关闭,如连接断开等
	STATE_RTSP_DESCRIBE_READY,       //会话已经收到Describe响应
	STATE_RTSP_AUTHORIZATION_FAIL,   //RTSP鉴权失败
	STATE_RTSP_PLAY_READY,           //收到PLAY响应
	STATE_RTSP_FILE_PLAY_OVER,       //录像文件回放正常结束
	STATE_RTSP_PAUSE_READY,          //收到PAUSE响应
	STATE_RTSP_KEY_MISMATCH,         //密钥不正确
	STATE_RTSP_LIVE_PAUSE_ENABLE,     //服务端直播支持PAUSE , 调用stream_inquirePause接口后会收到该消息或者STATE_RTSP_LIVE_PAUSE_DISABLE 消息
	STATE_RTSP_LIVE_PAUSE_DISABLE,    //服务端直播不支持PAUSE
	STATE_RTSP_TALK_BUSY_LINE,        //对讲忙线
	STATE_RTSP_TALK_CHECK_FAILED,     //对讲不满足操作条件
	STATE_RTSP_LIVE_PLAY_OVER,        //直播正常结束(针对休眠设备增加错误码)
	STATE_RTSP_SERVICE_UNAVAILABLE =  99,  // 基于503 错误码的连接最大数错误
	STATE_RTSP_USER_INFO_BASE_START = 100, // 用户信息起始码, 服务端上层传过来的信息码会在该起始码基础上累加
	STSTE_RTSP_STREAM_LIMIT_NOTIFY = 101,        //限流通知
	STSTE_RTSP_CONCURRENT_LIMIT_NOTIFY = 102,    //并发通知

	STATE_RTSP_KEEP_ALIVE_TIMEOUT       =    408001,
	STATE_RTSP_WAIT_MESSAGE_TIMEOUT     =    408002,
	STATE_RTST_SOCK_TIMEOUT             =    504008,
	STATE_RTST_AH_DECRYPT_FAIL          =    120000,   //安恒解密失败
	STATE_RTSP_STREAM_MODIFY_ERROR      =    602019,   //码流加解密失败
}LCOpenSDK_RTSP_STATE;

typedef enum
{
	STATE_DHHTTP_COMPONENT_ERROR = -1,    //组件内部调用流媒体接口失败 
	STATE_DHHTTP_OK              = 1000,  //开启播放成功 
	STATE_DHHTTP_PLAY_FILE_OVER  = 2000,  //回放时，表示文件播放结束 
	STATE_DHHTTP_PAUSE_OK = 4000,       //子链路正常关闭
	STATE_DHHTTP_PLAY_STOP = 6000,      // 私有协议停止(下载 、 回放、 实时)
	STATE_DHHTTP_BAD_REQUEST     = 400000, //非法请求，关闭客户端 
	STATE_DHHTTP_UNAUTHORIZED    = 401000, //未授权，用户名密码错误 
	STATE_DHHTTP_FORBIDDEN       = 403000, //禁止访问，关闭客户端 
	STATE_DHHTTP_NOTFOUND        = 404000, //资源不存在，关闭客户端 
	STATE_DHHTTP_REQ_TIMEOUT     = 408000, //请求超时，指拉流成功，后续网络异常，导致拉流断开 
	STATE_DHHTTP_SERVER_ERROR    = 500000,  //服务器内部错误，关闭客户端 
	STATE_DHHTTP_SERVER_UNVAILABLE = 503000, //服务不可用 
	STATE_DHHTTP_SERVER_DISCONNECT = 503001, //远端断开了连接
	STATE_DHHTTP_FLOWLIMIT         = 503006, //mts限流
	STATE_DHHTTP_P2P_MAXCONNECT    = 503007, //P2P达到最大链接数 
	STATE_DHHTTP_CHECK_FAILED      = 503008,      //对讲错误
	STATE_DHHTTP_BUSY_LINE         = 503009,      //对讲忙线
	STATE_DHHTTP_HUNG_UP           = 503034,      //本次对讲已被接听且已挂断
	STATE_DHHTTP_GATEWAY_TIMEOUT   = 504000, //网络不通 
	STATE_DHHTTP_CLIENT_ERROR      = 1000000, //客户端内部错误，处理逻辑错误 
	STATE_DHHTTP_KEY_ERROR         = 1000005, //密钥错误

	STATE_DHHTTP_REQ_TIMEOUT_RETRY     =    408100,
	STATE_DHHTTP_SOCK_TIMEOUT        =    504015,
	STATE_DHHTTP_AH_DECRYPT_FAIL          =    130000,  //安恒解密失败
	STATE_DHHTTP_STREAM_MODIFY_ERROR      =    602017,   //码流加解密失败
	STATE_DHHTTP_LIVE_FINISH       = 16390,   //live结束消息(电池相机)
	STATE_DHHTTP_LIVE_COUNT_DOWN   = 16392,   //休眠倒计时通知消息code（电池相机）
}LCOpenSDK_DHHTTP_STATE;

typedef enum
{
	STATE_HLS_DOWNLOAD_FAILD,        //下载失败
	STATE_HLS_DOWNLOAD_BEGIN,        //开始下载
	STATE_HLS_DOWNLOAD_END,          //下载结束
	STATE_HLS_SEEK_SUCCESS,          //定位成功
	STATE_HLS_SEEK_FAILD,            //定位失败
	STATE_HLS_ABORT_DONE,
	STATE_HLS_RESUME_DONE,
	STATE_HLS_KEY_MISMATCH = 11,     //非TCM，自定义密钥或者默认密钥不正确
	STATE_HLS_DEVICE_KEY_ERROR = 14, //TCM，码流解密时的设备密码不正确
}LCOpenSDK_HLS_STATE;



#endif //_LCOPENSDK_DEFINE_H_
