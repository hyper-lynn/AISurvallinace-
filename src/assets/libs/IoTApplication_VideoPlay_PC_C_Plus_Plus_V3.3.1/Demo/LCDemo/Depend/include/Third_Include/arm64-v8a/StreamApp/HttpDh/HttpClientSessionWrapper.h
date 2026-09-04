#ifndef HTTPCLIENTCLIENTWRAPPER_H
#define HTTPCLIENTCLIENTWRAPPER_H

#include "Infra/IntTypes.h"

#ifdef __cplusplus
extern "C"{
#endif 

///\brief http消息回调函数原型, 包括 request & response
///\param [in]	message -HTTP消息字符串指针
///\param [in]	user-回调接收对象指针
///\param [in]	reserve1-保留参数1
///\param [in]	reserve2-保留参数2
///\return	    void
typedef void(*msgcallback_proc_func)(const char *message, void *user, void *reserve1, void *reserve2);

///\brief http客户端状态码回调函数原型  
///\param [in]	unsigned int - HTTP 消息, @see HttpDhMessage.h
///\param [in]	unsigned int - 错误码, 见HTTPDH_ERRNO
///\param [in]	user - 用户上下文指针
///\param [in]	reserve -保留参数
///\return	    void
typedef void (*state_proc_func)(unsigned int message, unsigned int error_code, void* user, void *reserve);

///\brief MediaFrame数据回调
///\param [in]	frame - 回调完整大华帧
///\param [in]	len-回调完整大华帧长度信息
///\param [in]	user-回调接收对象指针
///\param [in]	frame_info-回调帧信息参数, @see struct http_dh_frame_info, 目前只填写frame_index
///\return void
typedef void(*frame_proc_func)(const char* frame, int len, void* user, void *frame_info);

///\brief 流信息回调函数原型
///\param [in]	user-回调接收对象指针
///\param [in]	message 	 -流信息字符串指针
///\param [in]	unsigned int  -流信息字符串长度
///\param [in]	reserve1	 -保留参数1
///\param [in]	reserve2	 -保留参数2
///\return	    void
typedef void(*stream_info_proc_func)(void *user, const char *message, unsigned int len, void *reserve1, void *reserve2);


///\brief 客户端配置选项,参见http_client_set_config()
enum httpdh_client_config_t
{
	httpdh_client_config_unknown = 0,			///< 未知格式
	httpdh_client_config_serverInfo,			///< 设置连接服务端信息 @see http_dh_host_info_t，必须在init之前设置
	httpdh_client_config_authorization,			///< 设置账号信息, @see http_dh_client_authInfo，必须在init之前设置
	httpdh_client_config_proc,					///< 设置回调, @see http_dh_proc_config，必须在init之前设置
	
	httpdh_client_config_packet_type,			///< 设置打包类型, @see httpDhUrlInfo::MediaPacketType
	httpdh_client_config_keepaliveinterval,		///< 设置客户端保活时间，默认30S; 配置时opt的值以微秒为单位, int类型
	httpdh_client_config_hhyencrypt,			///< 配置大华帧头0x95字段加密配置, 只允许设置一次 @see StreamSvr::HHYEncryptConfigExt
	httpdh_client_config_append_heaher,			///< 设置客户端在发送请求时添加指定的字段，opt使用private_header_name
	httpdh_client_config_play_param,			///< 设置客户端录像回放请求参数配置, opt使用http_dh_play_param_t
	httpdh_client_config_use_private_method,	///< 设置客户端使用非HTTP协议发送拉流信令, opt使用bool类型，
	httpdh_client_config_transport_info,		///< 设置客户端传输参数, opt使用http_dh_transport_info
	httpdh_client_config_streamInfo,			///> 设置客户端流信息配置, @see http_dh_stream_info_config, 必须在init之前设置
	httpdh_client_config_connectInfo,			///< 获取客户端本地IP和端口配置, @see http_dh_connect_info_config, 
	httpdh_client_config_encrypt3,				///< 配置大华帧头0xB5字段码流加密, 只允许设置一次 @see StreamSvr::DHEncrypt3Config
	httpdh_client_config_max,
};

///\brief HTTP拉流服务端的IP和port, 使用前需要初始化, 避免不同平台出现随机值
struct http_dh_host_info_t
{
	char			*ip;        	///< 目的IP, 暂时只支持IPv4
	unsigned int	 port;	  		///< 目的端口
	char 			*httpUrl;		///< 拉流GET请求URI, 比如: /live/realmonitor.xav?channel=1&subtype=0&encrypt=2
	int				 reserved1[4];	///< 保留字段1
	void* 			 reserved2[4];	///< 保留字段2
};

///\brief 客户端认证配置, 使用前需要初始化, 避免不同平台出现随机值
struct http_dh_client_authInfo
{
	char* username;				///< 用户名
	char* password;				///< 用户密码

	bool  need_wsse;            ///< 是否使用WSSE认证
	char* device_serial_number;	///< 设备密码摘要盐值，流媒体使用该序号生成WSSE密码, 如果 wsse_password 有效, 该值设置为NULL
	char* wsse_password;		///< WSSE认证密码, 如果服务端非设备序列号生成的密码, 需要上层算出WSSE密码设置下来， 否则设置NULL
	int	  reserved1[4];			///< 保留字段1
	char* wsse_created_time;	///< WSSE认证时间戳，需要填写UTC时间，精确到秒，格式如 "2018-07-24T19:20:30Z"
	void* reserved2[3];			///< 保留字段2
};

///\brief 客户端接收媒体数据回调配置, 使用前需要初始化, 避免不同平台出现随机值
struct http_dh_proc_config
{
	int 					dstPacketType;	///< 目的转码类型，目前只支持转为大华帧, mediaPacketTypeDH, 填0
	frame_proc_func 		frame_proc;		///< 数据回调接口	
	state_proc_func			state_proc;		///< 消息回调接口
	msgcallback_proc_func	msg_proc;  		///< 目前不支持, 默认填NULL
	int						reserved1[4];	///< 保留字段1
	void* 					reserved2[4];	///< 保留字段2
};

///\brief 客户端录像回放请求参数配置, 使用前需要初始化, 避免不同平台出现随机值
struct http_dh_play_param_t
{
	bool				i_frame_only;		///< 播放时是否进行I帧播放
	float				start_pos;			///< 记文件开始时间为0，相对于开始时间秒为单位的，如果为0，则从文件开始出播放
	float	 			end_pos;			///< 同上,不填时设置为-1
	float				speed;				///< 播放速度
	int					reserved1[4];		///< 保留字段1
	void* 				reserved2[4];		///< 保留字段2
};

///\brief 自定义头部字段域名
enum private_header_name
{
	HttpdhHeaderNameConnectTypeP2P,				///> 头部字段域名 "Connect-Type: P2P"
	HttpdhHeaderNameMax,
};

///\brief 媒体帧信息, 使用前需要初始化, 避免不同平台出现随机值
struct http_dh_frame_info
{
	int 				frame_index;		///< 发送媒体帧索引, trackID值
	int 				frame_type; 		///< 发送媒体帧类型
	unsigned int 		len;				///< 媒体数据帧(大华帧)长度
	unsigned char		*data; 				///< 媒体数据帧(大华帧)指针	
	uint64_t			timestamp;			///< 时间戳信息, 单调往上递增
	int 				reserve[32];		///< 保留参数 ,默认填0		
	void 				*reserve1;			///< 保留参数,默认填0
	void				*reserve2;			///< 保留参数,默认填0
};

///\brief 大华帧中的音频信息, 使用前需要初始化, 避免不同平台出现随机值
struct audio_info
{
	unsigned int encode_type;	///< 编码类型,参考@see AudioEncodeType
	unsigned int frequency;		///< 采样率,  真实的采样率, 非枚举值
	unsigned int channel_num;	///< 声道数, 见大华码流协议0x83 字段

	unsigned int  reserve1[8];
	void     *reserve2[4];

};

///\brief 音频通道编码信息, 使用前需要初始化, 避免不同平台出现随机值
struct audio_channel_encode_info
{	
	bool        		enable;				///< 音频通道使能情况
	bool        		initd;				///< 是否初始化编码信息完成, 如果audio_info 有效, 置为true
	char				align[2];			///< 保留对齐
	int 				audio_channelNO;	///< 音频通道, 0x96 字段中的通道号, 如果不知道通道号，填-1即可
	struct audio_info	audio_info;			///< 音频编码信息

	unsigned int    	reserve1[8];
	void       			*reserve2[4];

};

///\brief 支持多音频最大通道数
enum max_audio_channel
{	
	max_audio_channel_count = 5	  		///< 最大音频个数
};

///\brief 音频通道个数及编码信息, 使用前需要初始化, 避免不同平台出现随机值
struct audio_channel_info
{	
	int 					 			channel_count;    									///< 由外部传入音频通道数,应不超过 max_audio_channel_count
	struct audio_channel_encode_info 	audio_channel_encode_info[max_audio_channel_count]; ///< 音频通道信息, 目前供语音对讲使用：下标0为设备端对讲音频解码格式
};

///\brief 音频编码信息, 使用前需要初始化, 避免不同平台出现随机值 
struct audio_encode_info
{
	bool						init_flag;		///< 是否初始化音频编码信息成功
	char						align[3];		///< 保留对齐
	struct audio_channel_info	channel_info;  	///< 音频通道编码信息

};

///\brief tcp传输参数, 使用前需要初始化, 避免不同平台出现随机值
struct http_dh_transport_info
{
	int 	socket_recv_buf_size;		///< 套接字接收缓冲, 以字节Byte为单位; 不设置填0, 使用系统默认缓存大小
	int 	socket_send_buf_size;		///< 套接字发送缓冲, 以字节Byte为单位; 不设置填0, 使用系统默认缓存大小
	int  	reserve1[8];
	void 	*reserve2[4];
};

///\brief 客户端流信息上报配置, 使用前需要初始化, 避免不同平台出现随机值
struct http_dh_stream_info_config
{
	stream_info_proc_func 	stream_info_proc;	///< 数据回调接口	
	char 					*request_id;		///< 全链路唯一标示request_id
	uint32_t 				eventmask;			///< 流信息事件不同功能使能位选项, @see enum StreamSvr::fstatStreamInfoEvent
	uint32_t 				lostduration;		///< 丢帧的周期性检测时间, 单位秒, 表明丢帧的开始后会进行多长时间的检测, 由应用配置, 默认60秒
	int						reserved1[8];		///< 保留字段1
	void* 					reserved2[4];		///< 保留字段2
};

///\brief 拉流客户端连接的信息
struct	http_dh_connect_info
{
	const char		*request_id;	///< 全链路唯一标示request_id
	uint32_t    	requestid_len; 	///< 全链路唯一标示request_id长度

	const char		*localip;		///< 本地ip
	uint32_t    	localip_len; 	///< 本地ip字符串长度
	uint16_t		localport;	  	///< 本地端口
	uint16_t		align1;			///< 对齐

	const char		*remoteip;		///< 远端ip
	uint32_t    	remoteip_len; 	///< 远端ip字符串长度
	uint16_t		remoteport;	  	///< 远端端口
	uint16_t		align2;			///< 对齐
};

/*---------------------------------------------------------------------------------------------------------
									拉流客户端接口调用的流程如下
									create_http_client_handler
												|
									http_client_set_config
	(客户端在初始化之前必须设置HttpdhclientConfigSetServerInfo, HttpdhclientConfigAuthorization, HttpdhclientConfigProc)
												|
								init_http_client  or  init_http_client_with_sock
												|
										http_client_close
	(state_proc_func回调函数中收到HttpDhMessage.h错误码中需要关闭客户端的消息,或者init失败, 或者上层主动停止拉流调用)
---------------------------------------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------------------------------
									语音对讲客户端接口调用的流程如下
									create_http_client_handler
												|
									http_client_set_config
	(客户端在初始化之前必须设置HttpdhclientConfigSetServerInfo, HttpdhclientConfigAuthorization, HttpdhclientConfigProc)
												|
									init_http_client_stream_mode
												|
									http_client_init_sdp_for_talk
												|
								init_http_client  or  init_http_client_with_sock
												|
								    http_client_get_media_encode
												|
						(客户端收到MSG_HTTPDH_READY异步消息回调后获取设备端对讲音频编码格式)
												|
									http_client_enable_media(可视对讲使用)
												|
									http_client_put_frame
												|
				(客户端收到MSG_HTTPDH_READY异步消息回调后开始推送手机到设备的正向对讲音频帧)
												|
								   http_client_disable_media(可视对讲使用)
								   				|
										http_client_close
	(state_proc_func回调函数中收到HttpDhMessage.h错误码中需要关闭客户端的消息,或者init失败, 或者上层主动停止拉流调用)
---------------------------------------------------------------------------------------------------------*/


///\brief 创建http客户端句柄
///\param [in]	user-码流回调和状态消息回调接收对象指针
///\param [in]	reserve-保留参数
///\return 	NULL-fail , handler对象句柄-sucess
void* create_http_client_handler(void *user, void *reserve);

///\brief 设置客户端配置选项
///\param [in] handler-句柄 
///\param [in] opt-配置选项,参考@see httpdh_client_config_t
///\param [in] value-配置选项参数指针
///\param [in] len-配置选项参数指针所指区域的可访问长度
///\param [in] reserve1-保留参数1
///\param [in] reserve2-保留参数2
///\return -1-fail,	0-success
int http_client_set_config(void *handler, httpdh_client_config_t opt, void *value, int len, void *reserve1, void *reserve2);

///\brief 初始化客户端(由流媒体创建链接)
///\param [in] 	handler-句柄
///\param [in]  sock_type  0-TCP, 1-SSL
///\param [in]	reserve1-保留参数1
///\param [in]	reserve2-保留参数2
///\return -1-fail,	0-success
int init_http_client(void *handler, int sock_type, void *reserve1, void *reserve2);

///\brief 初始化客户端(复用已经建立的连接)
///\param [in] handler-句柄
///\param [in] fd-已连接上的套接字fd, 由流媒体模块负责关闭
///\param [in] reserve1-保留参数1
///\param [in] reserve2-保留参数2
///\return -1-fail,	0-success
int init_http_client_with_sock(void *handler, int fd, void *reserve1, void *reserve2);

///\brief 关闭客户端，释放资源, 只允许调用一次 
///\brief 调用后, 句柄handler置为NULL, 避免因重复释放资源导致崩溃
///\param [in] handler-句柄
///\return 0-ok, -1-failed
int http_client_close(void* handler);

///\brief 暂停媒体, 主要用于回放
///\param [in] handler-句柄
///\return -1-fail,	0-success
int http_client_pause(void *handler);

///\brief 客户端再次请求播放, 主要用于回放, 跳转, 暂停后的继续播放等操作
///\param [in] handler-句柄
///\param [in] info-时间范围
///\param [in] reserve1-保留参数1
///\param [in] reserve2-保留参数2
///\return -1-fail,	0-success
int http_client_play(void *handler, const struct http_dh_play_param_t *info, void *reserve1, void *reserve2);

///\brief 获取服务端秘钥的盐值信息
///\param [in] handler-句柄
///\param [out] authsalt-指向盐值信息的地址
///\param [out] reserve-保留参数
///\return -1-fail,	0-success
int http_client_getauthsalt(void *handler, const char **authsalt, void *reserve);

///\brief 初始化客户端流模式和拉流需要获取的媒体
///\param [in] handler-句柄
///\param [in] httpUrl-GET 请求后面的url
///\param [in] mode-客户端流模式，@see		 httpDhSessionMode
///\param [in] stream_type-客户端业务类型，@see		 httpDhUrlInfo::UrlType
///\param [in] trackid_flags-拉流需要获取的媒体，指定媒体通道号对应位(共32位，暂使用低7位); 该参数仅提供给httpDhUrlInfo::UrlTypeVisualTalk使用; 视频为第0位，第一路音频为第1位，对讲为第6位
/* 
//	 高位 							 低位
//	 保留字段					   已使用字段
//	  xxxxxxxx xxxxxxxx xxxxxxxx XXXXXXXX
//								  |||||||
//正向对讲语音--------------------|||||||
//反向对讲语音---------------------||||||
//元数据 		  ----------------------|||||
//辅助帧 		  -----------------------||||
//第二路音频		  ------------------------|||
//第一路音频		  -------------------------||
//视频		  --------------------------|
*/
///\param [in] reserve -保留参数
///\return -1-fail, 0-success
int init_http_client_stream_mode(void *handler, const char *httpUrl, int mode, int stream_type, unsigned int trackid_flags, void *reserve);

///\brief 同步获取对讲编码配置参数初始化SDP, 用于客户端向服务端推送对讲数据时使用, 目前只供语音对讲和可视对讲使用
///\param [in]	handler-句柄
///\param [in] private_sdp-是否使用私有SDP, 默认填true
///\param [in] talk_enc_info -语音对讲编码配置,对讲只支持一路音频, 配置参照struct audio_encode_info
///\param [in] reserve		-保留参数
///\return -1-fail, 0-success
int http_client_init_sdp_for_talk(void* handler, bool private_sdp, struct audio_encode_info *talk_enc_info, void *reserve);

///\brief 从设备回复SDP中提取对讲编码配置参数, 上层收到MSG_HTTPDH_READY后才可调用该接口, 目前只供语音对讲和可视对讲使用
///\param [in]	handler-句柄
///\param [out] talkEncInfo -语音对讲编码配置,对讲音频暂只支持一路音频, 配置参照AudioEncodeInfo
///\param [in/out] reserve-保留参数
///\return -1-fail, 0-success
int http_client_get_media_encode(void* handler, struct audio_encode_info *talk_enc_info, void *reserve);

///\brief 开启指定通道媒体传输, 主要用于直播开始后操作, 目前只供可视对讲UrlTypeVisualTalk使用
///\param [in] handler-句柄
///\param [in] trackid_flags-拉流需要获取的媒体, 指定媒体通道号对应位(共32位，暂使用低7位); 视频为第0位, 第一路音频为第1位, 对讲为第6位
/* 
//	 高位 							 低位
//	 保留字段					   已使用字段
//	  xxxxxxxx xxxxxxxx xxxxxxxx XXXXXXXX
//								  |||||||
//正向对讲语音--------------------|||||||
//反向对讲语音---------------------||||||
//元数据 		  ----------------------|||||
//辅助帧 		  -----------------------||||
//第二路音频		  ------------------------|||
//第一路音频		  -------------------------||
//视频		  --------------------------|
///\param [in] httpUrl-GET 请求后面的url, 默认设置为NULL; 如果设置为NULL则不变更httpUrl
*/
///\param [in] reserve		-保留参数
///\return 0-ok, -1-failed
int http_client_enable_media(void* handler, unsigned int trackid_flags, char *httpUrl, void *reserve);

///\brief 关闭指定通道媒体传输, 主要用于直播开始后操作, 目前只供可视对讲UrlTypeVisualTalk使用
///\param [in] handler-句柄
///\param [in] trackid_flags-拉流需要获取的媒体，指定媒体通道号对应位(共32位，暂使用低7位); 视频为第0位, 第一路音频为第1位, 对讲为第6位
/* 
//	 高位 							 低位
//	 保留字段					   已使用字段
//	  xxxxxxxx xxxxxxxx xxxxxxxx XXXXXXXX
//								  |||||||
//正向对讲语音--------------------|||||||
//反向对讲语音---------------------||||||
//元数据 		  ----------------------|||||
//辅助帧 		  -----------------------||||
//第二路音频		  ------------------------|||
//第一路音频		  -------------------------||
//视频		  --------------------------|
*/
///\param [in] httpUrl-GET 请求后面的url, 默认设置为NULL; 如果设置为NULL则不变更httpUrl
///\param [in] reserve		-保留参数
///\return 0-ok, -1-failed
int http_client_disable_media(void* handler, unsigned int trackid_flags, char *httpUrl, void *reserve);

///\brief 推流数据入口, 上层收到MSG_HTTPDH_READY后才可调用该接口, 目前只供语音对讲和可视对讲使用
///\param [in]	handler-句柄
///\param [in] 	frame_info-媒体帧信息指针, 暂时只支持音频帧
///\param [in]	reserve-保留参数
///\return -1-fail,	0-success
int http_client_put_frame(void* handler, struct http_dh_frame_info *frame_info, void *reserve);

///\brief 获取客户端配置选项
///\param [in] handler-句柄 
///\param [in] connectInfo-获取连接信息的指针
///\return -1-fail,	0-success
int http_client_getConnectInfo(void *handler, http_dh_connect_info *connectInfo);

#ifdef __cplusplus
}
#endif 

#endif //HTTPCLIENTCLIENTWRAPPER_H
