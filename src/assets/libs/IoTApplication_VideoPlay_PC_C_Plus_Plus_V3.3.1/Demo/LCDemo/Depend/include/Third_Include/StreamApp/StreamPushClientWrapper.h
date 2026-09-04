#ifndef RTSPPUSHCLIENTWRAPPER_H
#define RTSPPUSHCLIENTWRAPPER_H

#include "StreamSvr/Protocol/RtspUtil.h"


#ifdef __cplusplus
extern "C"{
#endif 

///\brief 媒体打包方式
typedef enum
{
	PACKET_UNKNOWN = -1,
	PACKET_DH_OVER_TCP,			//将DH帧分包码流加上交织通道信息, 使用TCP协议传输
	PACKET_DH_OVER_RTP_TCP,		//将DH帧打包成RTP标准码流, 使用TCP协议传输
}media_packet_t;

///\brief 推流媒体方式配置
typedef enum 
{
	STREAM_UNKNOWN = -1,
	STREAM_VIEW_REAL,			//实时流模式
	STREAM_VIEW_FILE,			//点播流模式，暂时不支持
}stream_type;

///\brief 推流媒体帧信息
struct frame_info
{
	int 			frame_index;		///< 发送媒体帧索引, trackID值
	int 			frame_type; 		///< 发送媒体帧类型
	uint32_t 		len;				///< 媒体数据帧(大华帧)长度
	uint8_t			*data; 				///< 媒体数据帧(大华帧)指针	
	uint64_t		timestamp;			///< 时间戳信息, 单调往上递增
	int 			reserve[30];		///< 保留参数 ,默认填0		
	void 			*reserve1;			///< 保留参数,默认填0
	void			*reserve2;			///< 保留参数,默认填0
};


///\brief 推流网络连接配置
struct conn_param_t
{
	char			*url;				//推流url
	media_packet_t 	packet_type; 		//流源媒体打包类型和传输协议配置
	int				socket_fd;			//非0, 套接字复用
	stream_type		meida_type;			//流源媒体推流媒体类型配置
};

///\brief 推流客户端账号
struct account_param_t
{
	char	*username;					//用户名
	char	*password;					//密码,可为空
};

///\brief RTSP推流客户端配置名称
typedef enum
{
	rtsp_push_config_unknown = -1,					///< 非法配置
	rtsp_push_config_user_agent,					///< 设置客户端User-Agent配置
	rtsp_push_config_conn,							///< 设置需要推送连接配置,@see conn_param_t
	rtsp_push_config_proc,							///< 设置回调配置,@see proc_param_t
	rtsp_push_config_account,						///< 设置RTSP推流客户端账户配置, @see account_param_t
	rtsp_push_config_send_buf,						///< 设置RTSP推流客户端发送缓存配置, 单位字节
}rtsp_push_config_t;

///\brief  RTSP 推流客户端状态信息
typedef enum 
{
	STATE_RTSP_TEARDOWN_ERROR,			//内部要求关闭,如连接断开等
	STATE_RTSP_ANNOUNCE_READY,			//会话已经收到ANNOUNCE响应
	STATE_RTSP_AUTHORIZATION_FAIL,		//RTSP鉴权失败
	STATE_RTSP_RECORD_READY,			//收到RECORD响应
}state_status_t;


///\brief RTSP 推流状态信息呈报
///\param [in]	error -RTSP状态码, @see state_status_t
///\param [in]	user-状态信息接收对象指针
///\param [in]	reserve1-保留参数1
///\param [in]	reserve2-保留参数2
///\return	    	void
typedef void (*state_proc)(int state, void *user, void *reserve1, void *reserve2);

///\brief RTSP会话消息回调函数原型, 包括 request & response
///\param [in]	message -RTSP消息字符串指针
///\param [in]	user-回调接收对象指针
///\param [in]	reserve1-保留参数1
///\param [in]	reserve2-保留参数2
///\return	    void
typedef void (*message_proc)(const char *message, void *user, void *reserve1, void *reserve2);

//回调配置参数
struct proc_param_t
{
	state_proc			_state_proc;
	message_proc        _message_proc;		///< 暂不支持，默认填0
};

/*---------------------------------------------------------------------------------------------------------
RTSP推流客户端接口调用的流程如下
									create_stream_handler
											    |			
									    stream_set_config
											    |						                  
								           stream_push_create		    
								                          |
								              stream_init_sdp
								                          |
									      stream_push_start
                                                                                    |	                 
						                    	      stream_put_frame
		(state_proc状态回调函数中收到STATE_RTSP_RECORD_READY后开始送帧)
                                                                                    |
								   	      stream_push_close
								   		            |
								   	  destroy_stream_handler   
 (state_proc状态回调函数中收到STATE_RTSP_TEARDOWN_ERROR消息后或者stream_push_start失败, 或者上层主动停止推流调用)    
---------------------------------------------------------------------------------------------------------*/

///\brief 创建RTSP推流客户端句柄
///\param [in]	user-码流回调和状态消息回调接收对象指针
///\param [in]	reserve-保留参数
///\return 	NULL-fail , handler对象句柄-sucess
void* create_stream_handler(void* user, void *reserve);

///\brief 设置用户配置参数
///\param [in] 	handler-句柄
///\param [in]	name-配置名称,参考@see rtsp_push_config_t
///\param [in]	value-配置参数指针
///\param [in]	len-配置参数指针所指区域的可访问长度
///\param [in]	reserve1-保留参数1
///\param [in]	reserve2-保留参数2
///\return -1-fail, 0-success
int stream_set_config(void *handler, rtsp_push_config_t name, const void *value, int len, void *reserve1, void *reserve2);

///\brief 创建RTSP推流客户端
///\param [in] 	handler-句柄
///\param [in]	reserve-保留参数
///\return -1-fail,	0-success
int stream_push_create(void *handler, void *reserve);

///\brief 设置SDP信息
///\param [in]	handler-句柄
///\param [in]	sdp_len-是否由外部组装SDP,     0:由流媒体组装SDP, 大于0:外部组装SDP长度
///\			暂不支持外部组装SDP，默认填0
///\param [in]	info-传入SDP字符串指针或者媒体帧信息指针,媒体帧信息参考@see struct frame_info
///\param [in]	reserve-保留参数
///\return -1-fail,	0-success
int stream_init_sdp(void* handler, int sdp_len, const void *info, void *reserve);

///\brief 开启RTSP客户端推流服务
///\param [in]	handler-句柄
///\param [in]	reserve-保留参数
///\return -1-fail,	0-success
int stream_push_start(void *handler, void *reserve);

///\brief RTSP推流数据入口
///\param [in]	handler-句柄
///\param [in] 	frame_info-媒体帧信息指针
///\param [in]	reserve-保留参数
///\return -1-fail,	0-success
int stream_put_frame(void* handler, struct frame_info *frame_info, void *reserve);

///\brief 关闭RTSP推流客户端，由外部主动调用关闭
///\param [in] 	handler-句柄
///\return -1-fail,	0-success
int stream_push_close(void *handler);

///\brief 释放RTSP推流客户端句柄
///\param [in]	handler-句柄
///\return 
void destroy_stream_handler(void *handler);


#ifdef __cplusplus
}
#endif 

#endif //RTSPPUSHCLIENTWRAPPER_H

