#ifndef __INCLUDED_DAHUA_HTTPDH_MESSAGE_H__
#define __INCLUDED_DAHUA_HTTPDH_MESSAGE_H__

//负责处理HTTPDH协议流程的模块，如果在HTTPDH处理中途失败，则向消息接收者发送该消息
//收到该消息，接收者应该调用Close()进行客户端关闭，消息的附带参数attach使用参照enum httpDhMainCode和enum httpDhExtraCode组合
#define MSG_HTTPDH_FAIL					0x4000

//表示客户端已完成跟对端的初始化设置步骤
#define MSG_HTTPDH_READY				0x4001

//表示服务端通知客户端播放完成消息
#define MSG_HTTPDH_FINISH				0x4002

//表示客户端暂停后收到服务端的成功确认, 消息的附带参数attach使用参照enum httpDhMediaCode, 附带参数用于可视对讲业务
#define MSG_HTTPDH_PAUSE_READY			0x4003

//表示客户端跳转或者暂停恢复播放后收到服务端的确认, 消息的附带参数attach使用参照enum httpDhMediaCode, 附带参数用于可视对讲业务
#define MSG_HTTPDH_PLAY_READY			0x4004

//表示收到DIGEST 鉴权的盐值信息
#define MSG_HTTPDH_PASSWORD_SALT		0x4005


// 错误码提取宏, 错误码分为主错误码httpDhMainCode 和辅错误码httpDhExtraCode
// 主错误码用于定义基本的错误, 辅错误码用于定义具体的错误原因
#define HTTPDH_MAIN_ERR(httpdh_errno)     (((httpdh_errno) & 0xffff0000) >> 16)
#define HTTPDH_EXTRA_ERR(httpdh_errno)	  ((httpdh_errno)  & 0x0000ffff)	

// 错误码组装宏
#define HTTPDH_ERRNO(mainerrno, extraerrno)     (((mainerrno) << 16) | (extraerrno))


///\ 提供给外部接口的错误码,  按照HTTP协议不要定义100 以下的数字为错误码(上层可以用这一区间)
enum httpDhMainCode
{
	HTTPDH_RESPONSE_OK 							= 200,	///< 收到服务端200 响应,正常响应
	HTTPDH_ERROR_BAD_REQUEST                    = 400 ,	///< 非法请求，客户端发起的请求非法
	HTTPDH_ERROR_UNAUTHORIZED                   = 401 ,	///< 未授权, 用户名或密码错误
	HTTPDH_ERROR_FORBIDDEN	                    = 403 ,	///< 禁止访问
	HTTPDH_ERROR_NOT_FOUND	                    = 404 ,	///< 未找到相关资源
	HTTPDH_ERROR_REQUEST_TIMEOUT				= 408 , ///< 请求超时, 指拉流成功，但后续网络异常，导致拉流断开
	HTTPDH_ERROR_UNSUPPORTTRANSPORT				= 461 , ///< 服务只支持加密码流导致失败
	HTTPDH_ERROR_INTERNAL_SERVER_ERROR          = 500 ,	///< 服务端未知的错误, 或者服务器返回了客户端不识别的错误
	HTTPDH_ERROR_INTERNAL_SERVER_UNVAILABLE		= 503 , ///< 服务不可用
	HTTPDH_GATEWAY_TIMEOUT						= 504 ,	///< 网络不通, 指在连接阶段，连接不上
	HTTPDH_ERROR_INTERNAL_CLIENT_ERROR			= 1000,	///< 客户端内部错误, 一般指代码逻辑问题，导致无法进行拉流流程
};

///\ 提供给外部接口的子错误码
enum httpDhExtraCode
{
	HTTPDH_EXTRA_UNKNOW 			   	= 0, 	///< 未知的子错误, 错误原因同主错误码	
	HTTPDH_EXTRA_SERVICE_DISCONNECT   	= 1, 	///< 主错误码503, 服务端直接断开了连接，且无任何错误信息传递过来
	HTTPDH_EXTRA_CHECKCHANNEL_FAILED   	= 2, 	///< 主错误码403, 业务通道权限校验失败	
	HTTPDH_EXTRA_DEVICE_PASSWD_UNINIT  	= 3, 	///< 主错误码403,设备密码未初始化	
	HTTPDH_EXTRA_SERVICE_MAXCONNECT    	= 4, 	///< 主错误码503, 服务达到最大连接数
	HTTPDH_EXTRA_ENCRYPT_KEY_ERROR     	= 5, 	///< 主错误码1000, 客户端密钥和服务端密钥不一致
	HTTPDH_EXTRA_ERRNO_FLOWLIMIT   	   	= 6, 	///< 主错误码503, 流量达到上限
	HTTPDH_EXTRA_P2PCONNECT_MAXCONNECT 	= 7, 	///< 主错误码503, p2p连接达到上限
	HTTPDH_EXTRA_DEVICE_CHECK_FAILED 	= 8, 	///< 主错误码503, 不符合设备操作条件
	HTTPDH_EXTRA_DEVICE_BUSY_LINE 		= 9, 	///< 主错误码503, 设备忙线中
	HTTPDH_EXTRA_TRANSPORT_ENCRYPT		= 10,	///< 主错误码461, 当前只支持加密传输
};

#endif //__INCLUDED_DAHUA_HTTPDH_MESSAGE_H__

