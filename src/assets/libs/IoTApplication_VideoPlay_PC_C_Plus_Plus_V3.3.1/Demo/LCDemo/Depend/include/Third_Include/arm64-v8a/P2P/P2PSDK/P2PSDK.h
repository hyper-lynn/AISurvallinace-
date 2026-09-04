#ifndef _P2PSDK_H_
#define _P2PSDK_H_

#include <string>
#include <map>

namespace Dahua { namespace P2PSDK {

///< 保存XML键值对
typedef std::map<std::string, std::string> KVMap;

struct Request
{
    int sequence;       ///< 请求序号，发送时填0表示由内部随机生成
    std::string op;     ///< 请求协议名，目前设备收到的只有："p2p-channel"
    std::string dev_id; ///< 请求的设备ID
    KVMap kvm;          ///< 请求的消息体
};

struct Response
{
    int sequence;       ///< 回复序号，发送时填写对应的请求序号
    int http_code;      ///< http响应码
    std::string desc;   ///< http响应码的描述
    KVMap kvm;          ///< 回复的消息体
};

struct ServerInfo
{
    std::string ip;     ///< 服务器IP
    int port;           ///< 服务器端口
    std::string key;    ///< 服务器密钥

	ServerInfo(const char *ip = "0.0.0.0", int port = 0, const char *key = "");
	const ServerInfo &operator=(const ServerInfo &src);
};

enum EventType
{
	eventTypeDestroy = 0,	///< 对象销毁事件
	eventTypeOnline,		///< 设备上线事件
	eventTypeOffline,		///< 设备断线事件
	eventTypeUnauthorized,	///< 设备认证失败（包括序列号非法，密钥错误）
	eventTypeForbidden,	    ///< 设备禁止登陆（设备ID重复，服务器拒绝）
};

///\brief 消息回调类
class INotify
{
public:
    ///\brief 析构
	virtual ~INotify() {}

	///\brief 事件回调
	///\param [in] event接收到的事件类型
	virtual void onEvent(EventType ev) {}

    ///\brief 请求回调（设备）
    ///\param [in] req接收到的请求
    virtual void onRequest(const Request &req) {}

    ///\brief 响应回调（客户端）
    ///\param [in] resp接收到的响应
    virtual void onResponse(const Response &resp) {}
};

///\brief 设备对象
class IP2PDevice
{
public:
    ///\brief 创建对象
    ///\param [in] dev_id 设备ID
    ///\param [in] 消息回调对象指针
    static IP2PDevice *create(const char *dev_id, INotify *notify);

    ///\brief 销毁对象
    virtual void destroy() = 0;

    ///\brief 开始连接服务器，登录或掉线通过事件回调
    ///\param [in] si 服务器信息
    virtual bool start(const ServerInfo &si) = 0;

    ///\brief 设备停止工作（过一会儿会掉线）
    virtual bool stop() = 0;

    ///\brief 设备当前是否在工作
    virtual bool isWoring() = 0;

    ///\brief 发送回复
    ///\param [in,out] resp发送的响应
    virtual bool sendResponse(Response &resp) = 0;
	
protected:
	virtual ~IP2PDevice() {}
};

///\brief 客户端对象
class IP2PClient
{
public:
    ///\brief 创建对象
    ///\param [in] 消息回调对象指针
    static IP2PClient *create(INotify *notify);

    ///\brief 销毁对象
	virtual void destroy() = 0;

	///\brief 查询当前服务是否在线，同步接口
	///\param [in] si 服务器信息
	///\param [in] timeout 查询超时时间，单位ms
	virtual bool isServerOnline(const ServerInfo &si, int timeout) = 0;

    ///\brief 查询当前设备是否在线，同步接口
    ///\param [in] si 服务器信息
    ///\param [in] dev_id 查询的设备ID
    ///\param [in] timeout 查询超时时间，单位ms
    virtual bool isDeviceOnline(const ServerInfo &si, char *dev_id, int timeout) = 0;

    ///\brief 发送请求
    ///\param [in] si 服务器信息
    ///\param [in,out] req 请求服务器消息/经过内部编号后的请求消息
	///\param [in] auth 发送的请求是否携带认证信息
    ///\note  内部编号产生的序列号与响应序列号一一对应
    virtual bool sendRequest(const ServerInfo &si, Request &req, bool auth = true) = 0;
	
protected:
	virtual ~IP2PClient() {}
};

}}

#endif
